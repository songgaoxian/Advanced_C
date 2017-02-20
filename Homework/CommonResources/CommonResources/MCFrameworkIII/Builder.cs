// Builder.cs
//
// The builder class that creates the external systems that 
// communicate with the SUD (Mediator).
//
// (C) Datasim Education BV 2014-2016
//

using System;
using System.Collections.Generic;
using System.Linq;

// Generic delegate for a MC builder: T1 == Sde, T2 == Fdm, T3 == IRng
public delegate Tuple<T1, T2, T3> Builder<T1, T2, T3>();


public class MCBuilder<S, F, R>
    where S : ISde
    where F : IFdm
    where R : IRng
 
{ // Build the full UML model in this builder

    private double r;
    private double v;
    private double d;
    private double T;
    private double K;
    private double IC;  // S_0
    //private double beta;

    private event PathEvent<double> path;
    private event EndOfSimulation<double> finish;

    // Constructor (data important at this stage)
    public MCBuilder(Tuple<double, double, double, double, double, double, int> optionData)
    {
        // r, div, sig, T, K, IC, NSim
        // 1   2    3   4  5   6   7    (Item*)
        r = optionData.Item1;
        d = optionData.Item2; 
        v = optionData.Item3; 
        T = optionData.Item4;
        K = optionData.Item5;
        IC = optionData.Item6;
        //   beta = optionData.Item7;

    /*    int NT;
        Console.Write("How many NT? ");
        NT = Convert.ToInt32(Console.ReadLine());*/
    }

    public Tuple<S, F, R> Parts(S sde, F fdm, R rng)
    { // V1, parts initialised from the outside

        return new Tuple<S, F, R>(sde, fdm, rng);
    }

    public Tuple<ISde, FdmBase, IRng> Parts()
    { // V2, parts initialised from the inside

        // Get the SDE
        ISde sde = GetSde();
        IRng rng = GetRng();
        FdmBase fdm = GetFdm(sde);

         Payoff payoff = x => Math.Max(0.0, K - x);
        //Payoff payoff = x => Math.Max(0.0, x - K);
        Func<double> discounter = () => Math.Exp(-r * T);
        IPricer pricer = GetPricer(payoff, discounter);
        return new Tuple<ISde, FdmBase, IRng>(sde, fdm, rng);
    }

    private ISde GetSde()
    {
        Console.WriteLine("Create SDE");
        Console.Write("1. GBM, 2. CEV ");
        int c = Convert.ToInt32(Console.ReadLine());

        if (c == 1)
        { // GBM

           return new GBM(r, v, d, IC, T);
        }
        else
        {
            double beta = 0.5;
            return new CEV(r, v, d, IC, T, beta);
        }
    }

    private IRng GetRng()
    {
        Console.WriteLine("Create RNG");
        Console.WriteLine("1. Box-Muller .Net 2. Math.Net MT 19937 3. Delegate-based Box-Muller ");
        Console.Write("4. Box-Muller Sitmo 5. Polar Marsaglia .Net 6. Box-Muller Crypto: ");
        int c = Convert.ToInt32(Console.ReadLine());

        IRng rng;

        switch (c)
        {
            case 1:
                rng = new BoxMullerNet();
                break;
            case 2:
                rng = new BoxMullerNet();
                break;

            case 3:
                 Console.WriteLine("Flavour");
                 Console.Write("1. .NET Random 2. Sitmo PRNG ");
                 int c2 = Convert.ToInt32(Console.ReadLine());

                 // Delegate-based
                 if (c2 == 2)
                 {
                     rng = new BoxMullerNet();
                 }
                 else
                 {
                     Random rngNet = new Random();
                     RngDelegate rand = rngNet.NextDouble;
                     rng = new BoxMullerII(rand);
                 }

                 break;

            case 4:
                 rng = new BoxMullerNet();
                 break;
            case 5:
                 rng = new PolarMarsagliaNet();
                 break;
            case 6:
                 rng = new BoxMullerCrypto();
                 break;
            default:
                rng = new BoxMullerNet();
                break;
        }

        return rng;
    }

    private FdmBase GetFdm(ISde sde)
    {
        Console.WriteLine("Create FDM");
        Console.WriteLine("1. Euler, 2. Extrapolated Euler, 3. Milstein, 4. Predictor-Corrector (PC),");
        Console.WriteLine("5. PC adjusted, 6. PC midpoint, 7. Exact, 8. Discrete Milstein,");
        Console.WriteLine("9. Platen 1.0 strong scheme, 10. Platen 1.0 strong scheme, 11. Heun");
        Console.WriteLine("12. Derivative Free, 13. FRKI (Runge Kutta), 14. Heun2, 15. Fitted PC: ");
        int c = Convert.ToInt32(Console.ReadLine());

        FdmBase fdm;

        int NT;
        Console.Write("How many NT? ");
        NT = Convert.ToInt32(Console.ReadLine());

        double a, b;

        switch(c)
        {
            case 1:
        
                fdm = new EulerFdm(sde, NT);
                break;
            case 2:

                fdm = null;// new ExtrapolatedEulerFdm(sde, NT);
                break;
       
            case 3: 

                fdm = new MilsteinFdm(sde, NT);
                break;
            
            case 4:
                a = 0.5;
                b = 0.5;
                fdm = new PredictorCorrectorFdm(sde, NT, a, b);
                break;
            
            case 5:
                a = 0.5;
                b = 0.5;
                fdm = new ModifiedPredictorCorrectorFdm(sde, NT, a, b);
                break;
      
            case 6:
                a = 0.5;
                b = 0.5;
                fdm = new MidpointPredictorCorrectorFdm(sde, NT, a, b);
                break;
           
            case 7:
                fdm = new ExactFdm(sde, NT, IC, v, r);
                break;
        
            case 8:
                fdm = new DiscreteMilsteinFdm(sde, NT);
                break;
            
            case 9:
             
                fdm = new Platen_01_Explicit(sde, NT);
                break;

            case 10:
                fdm = new Platen_01_Explicit(sde, NT);
                break;
            
            case 11:
                fdm = new Heun(sde, NT);
                break;
            case 12:
                fdm = new DerivativeFree(sde, NT);
                break;
            case 13:
                fdm = new FRKI(sde, NT);
                break;
            case 14:
                fdm = new Heun2(sde, NT);
                break;
            case 15:
                a = 0.5;
                b = 0.5;
                fdm = new FittedMidpointPredictorCorrectorFdm(sde, NT, a, b);
                break;

            default:
                fdm = null;// new ExtrapolatedEulerFdm(sde, NT);
                break;
        }

        return fdm;
    }

    private IPricer GetPricer(Payoff payoff, Func<double> discounter)
    {
        // Choice here
           IPricer op = new EuropeanPricer(payoff, discounter);
           path += op.ProcessPath;
           finish += op.PostProcess;

       // Payoff payoff2 = x => Math.Max(0.0, x - K);
        Payoff fixedStrikePayoff = x => Math.Max(0.0, K - x);
        /*    IPricer op2 = new EuropeanPricer(payoff2, discounter);
            path += op2.ProcessPath;
            finish += op2.PostProcess;*/


        //  Payoff fixedStrikePayoff = x => Math.Max(0.0, x - K);
        Payoff ArithmeticAverage = A => Math.Max(0.0, A - K);
        IPricer op3 = new AsianPricer(ArithmeticAverage, discounter);
        path += op3.ProcessPath;
        finish += op3.PostProcess;

     /*   IPricer op4 = new LSMPricer(payoff2, discounter, 10, 10, 60.0);
        path += op4.ProcessPath;
        finish += op4.PostProcess;*/

        return op;
    }

    public PathEvent<double> GetPaths()
    {
        return path;
    }

    public EndOfSimulation<double> GetEnd()
    {
        return finish;
    }
}

// Default builder

public class MCDefaultBuilder<S, F, R>
    where S : ISde
    where F : IFdm
    where R : IRng
 
{ // Build the full UML model in this builder

    private double r;
    private double v;
    private double d;
    private double IC;
    private double T;
    private double K;
    private double beta;

    private event PathEvent<double> path;
    private event EndOfSimulation<double> finish;


    // Constructor (data important at this stage)
    public MCDefaultBuilder(Tuple<double, double, double, double, double, double, int> optionData)
    {
        r = optionData.Item1;
        v = optionData.Item2;
        d = optionData.Item3;
        T = optionData.Item4;
        K = optionData.Item5;
        IC = optionData.Item6;
        beta = optionData.Item7;
    }

    public Tuple<S, F, R> Parts(S sde, F fdm, R rng)
    { // V1, parts initialised from the outside

        return new Tuple<S, F, R>(sde, fdm, rng);
    }

    public Tuple<ISde, FdmBase, IRng> Parts()
    { // V2, parts initialised from the inside

        // Get the SDE
        ISde sde = GetSde();
        IRng rng = GetRng();
        FdmBase fdm = GetFdm(sde);

   /*  //   double K = 65;
        Payoff payoff = x => Math.Max(0.0, K - x);
        //  Payoff payoff = x => Math.Max(0.0, x - K);
        //  Console.WriteLine(payoff(75.0));

        Func<double> discounter = () => Math.Exp(-r * T);
        IPricer pricer = GetPricer(payoff, discounter);
        */
        return new Tuple<ISde, FdmBase, IRng>(sde, fdm, rng);
    }

    private ISde GetSde()
    {
        return new GBM(r, v, d, IC, T);
  
    }

    private IRng GetRng()
    {
        return new BoxMullerNet();
    }

    private FdmBase GetFdm(ISde sde)
    {
        int NT = 500;
        Console.Write("How many NT? ");
        NT = Convert.ToInt32(Console.ReadLine());

        return new EulerFdm(sde, NT);
   
    }

   
    private IPricer GetPricer(Payoff payoff, Func<double> discounter)
    {
        // Choice here
     //   IPricer op = new EuropeanPricer(payoff, discounter);
      //  path += op.ProcessPath;
     //   finish += op.PostProcess;

        //Payoff payoff2 = x => Math.Max(0.0, x - K);
        Payoff payoff2 = x => Math.Max(0.0, K-x);
        IPricer op2 = new EuropeanPricer(payoff2, discounter);
        path += op2.ProcessPath;
        finish += op2.PostProcess;

        return op2;
    }

    public PathEvent<double> GetPaths()
    {
        return path;
    }

    public EndOfSimulation<double> GetEnd()
    {
        return finish;
    }
}
// Exx. default builder

public static class BuilderFactory
{

    // Choose which builder you want
    public static Tuple<ISde, FdmBase, IRng> ChooseBuilder(int n, 
                        Tuple<double, double, double, double, double, double, int> optionData)
    {// Factory method to choose your builder

        MCPricerApplication.print(optionData);

        MCBuilder<ISde, FdmBase, IRng> builder;
        MCBuilder<ISde, FdmBase, IRng> builder2;

        int c = 1;
        Console.Write("1. MCBuilder, 2. Default Builder ");
        c = Convert.ToInt32(Console.ReadLine());

        if (1 == n)
        {
            Console.Write("Chosen 1. MCBuilder ");
            builder = new MCBuilder<ISde, FdmBase, IRng>(optionData);
            return builder.Parts();
        }
        else
        {
            Console.Write("Chosen 2. MCDefaultBuilder ");
            builder2 = new MCBuilder<ISde, FdmBase, IRng>(optionData);
            return builder2.Parts();
        }

    }
}


