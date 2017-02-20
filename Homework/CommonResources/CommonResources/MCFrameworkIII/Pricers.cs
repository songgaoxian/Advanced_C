// Pricers.cs
//
// 1) One-factor option pricer classes
// 2) Factory Method to create option classes
//
// (C) Datasim Education BV 2014-2016
//

using System;
using System.Collections.Generic;
using System.Linq;



public interface IPricer
{
    void ProcessPath(ref double[] arr); // The path from the evolver
    void PostProcess();                 // Finish off computations
    double DiscountFactor();            // (simple) discounting function
    double Price();                     // Computed option price

}

// The payoff function
public delegate double Payoff(double underlying);

public abstract class Pricer : IPricer
{
    public abstract void ProcessPath(ref double[] arr);     // Create a single path
    public abstract void PostProcess();                     // Notify end of simulation
    public abstract double DiscountFactor();                // Discounting, should be a delegate
    public abstract double Price();                         // Option price

    public Payoff m_payoff;
    protected Func<double> m_discounter;

    public Pricer(Payoff payoff, Func<double> discounter)
    {
        m_payoff = payoff;
        m_discounter = discounter;
    }
}

// Pricing Engines
public class EuropeanPricer : Pricer
{
    private double price;
    private double sum;
    private int NSim;

    public EuropeanPricer(Payoff payoff, Func<double> discounter) : base(payoff, discounter) { price = sum = 0.0; NSim = 0; }

    public override void ProcessPath(ref double[] arr) 
    { // A path for each simulation/draw

       	// Sum of option values at terminal time T
        sum += m_payoff(arr[arr.Length - 1]); NSim++;
    }

    public override double DiscountFactor()
    { // Discounting

        return m_discounter();
    }
    
    public override void PostProcess()
    {
        Console.Write("Compute Plain price: "); price = DiscountFactor() * sum / NSim; Console.WriteLine("Price, #Sims: {0}, {1}", price, NSim);
    }

    public override double Price()
    {
        return price;
    }

}

public class AsianPricer : Pricer
{ // e.g. arithmetic Asian average of the asset price taken on a set of observations (fixings) of the asset price

    private double price;
    private double sum;
    private double avg = 0.0;    // Arithmetic average at the fixing points
    private int NSim;

    private static double Average(double[] array)
    { // Arithmetic average

        double avg = array[0];

        foreach (double item in array)
        {
            avg += item;
        }
        return (double)avg / (double) array.Length;
    }

    private static double GeometricAverage(double[] array)
    {
        double avg = array[0];

        foreach (double item in array)
        {
            avg *= item;
        }
        return (double)(1.0 / Math.Pow(avg, (double)array.Length));
    }

    private static double Max(double[] array)
    {
        double max = array[0];

        foreach (double item in array)
        {
            max = (double) Math.Max((double)item, max);
        }
        return (double)max;
    }

    public AsianPricer(Payoff payoff, Func<double> discounter) : base(payoff, discounter) { price = sum = 0.0; NSim = 0; }

    public override void ProcessPath(ref double[] arr)
    { // A path for each simulation/draw

        // Compute the arithmetic average using LINQ
        avg = Average(arr);
        //avg = GeometricAverage(arr);
     //   avg = Max(arr);

        //   sum += m_payoff(arr[arr.Length - 1]); NSim++;
        sum += m_payoff(avg); NSim++;
    //    Console.WriteLine("sum {0}", sum);
    }

    public override double DiscountFactor()
    { // Discounting

        return m_discounter();
    }

    public override void PostProcess()
    {
        Console.Write("Compute Asian price: "); price = DiscountFactor() * sum / NSim; Console.WriteLine("Price, #NSims: {0}, {1}", price, NSim);
    }

    public override double Price()
    {
        return price;
    }

}

public class BarrierPricer : Pricer
{
    private double price;
    private double sum, sum2;
    private int NSim;
    
    public BarrierPricer(Payoff payoff, Func<double> discounter) : base(payoff, discounter) { price = sum = sum2 = 0.0; NSim = 0; }

    public override void ProcessPath(ref double[] arr) 
    {

        double L = 170.0;
        double rebate = 0.0;

        bool crossed = false;
        for (int n = 0; n < arr.Length; n++)
        {
            //if (arr[n] <= L || arr[n] >= U)
            if (arr[n] >= L)
            { // Down and out

                crossed = true;
                break;
            }
        }

        if (crossed == false)
        {
          //  sum += Math.Max(0.0, arr[arr.Length - 1] - K);
            sum += m_payoff(arr[arr.Length - 1]);
         //   Console.WriteLine(m_payoff((double)75.0));
        }
        else
        {
            sum += rebate;
        }

        NSim++;
    }

    public override void PostProcess()
    {
               
        // V1 Hard-coded discounting; V2 this will be an algorithm (delegate)
        Console.WriteLine("Compute Barrier price"); price = DiscountFactor() * sum / NSim; Console.WriteLine("Price: {0}, {1}", price, NSim);
    }
    
    public override double DiscountFactor()
    { // Discounting

        return m_discounter();
    }
    

    public override double Price()
    {
        return price;
    }
}


public class BrownianBridgePricer : Pricer
{
    private double price;
    private double sum, sum2;
    private int NSim;
    private Random rand;
    private double dt;
    private GBM sde;
    private int counter = 0;


    public BrownianBridgePricer(Payoff payoff, Func<double> discounter, GBM stochasticDE, double step) : base(payoff, discounter) 
    { 
        price = sum = sum2 = 0.0; NSim = 0;
        rand = new Random();
        dt = step;
        sde = stochasticDE;
    }

    public override void ProcessPath(ref double[] arr)
    {

        double L = 170.0;
        double rebate = 0.0;
        double P, tmp, u;

        bool crossed = false;
        for (int n = 1; n < arr.Length; n++)
        {
            // Calculate exit probability
            tmp = sde.Diffusion((double)arr[n - 1], (double)(n-1) * dt);
           //P = 1.0;
          //  if ((arr[n] < L) && (arr[n-1] < L)) 
            P =  Math.Exp(-2.0*(L - arr[n-1])*(L - arr[n])/(tmp*tmp*dt));

            u = rand.NextDouble();
            if (P >= u)
            {
                counter++;
         //       Console.Write("{0},* {1}, {2},{3},{4} ", P, u, tmp, arr[n-1],arr[n]);
            //    string str = Console.ReadLine();
            }
            if (arr[n] >= L || P >= u)
          //  if (arr[n] >= L)
            { // Down and out

                crossed = true;
                break;
            }
        }

        if (crossed == false)
        {
            //  sum += Math.Max(0.0, arr[arr.Length - 1] - K);
            sum += m_payoff(arr[arr.Length - 1]);
            //   Console.WriteLine(m_payoff((double)75.0));
        }
        else
        {
            sum += rebate;
        }

        NSim++;
    }

    public override void PostProcess()
    {

        // V1 Hard-coded discounting; V2 this will be an algorithm (delegate)
        Console.WriteLine("Compute Brownian bridge price"); price = DiscountFactor() * sum / NSim; Console.WriteLine("Price: {0}, {1}", price, NSim);
        Console.WriteLine(counter);
    }

    public override double DiscountFactor()
    { // Discounting

        return m_discounter();
    }


    public override double Price()
    {
        return price;
    }
}

// Factory method 