// Interfaces.cs
//
// Standardised interfaces for the Monte Carlo option
// pricing based on Domain Architecture model (in this case a
// Resource Allocation and Tracking (RAT)).
//
// Modifications
//
// 2013-11-DD advance .. now two random numbers needed because of Extrapolated Euler
// 2013-11-DD Tuples in Builder
// 2013-11-20 DD Heun, KL, Platen schemes
// 201-11-30 DD a) factory method for Builder, b) arithmetic Asian option.
//
// (C) Datasim Education BV 2014
//

using System;
using System.Collections.Generic;
using System.Linq;

public interface ISde<T>
{ // Standard one-factor SDE dX = a(X,t)dt + b(X,t)dW, X(0)given

    T Drift(T x, T t);          // a
    T Diffusion(T x, T t);      // b

    T DriftCorrected(T x, T t, T B);
    T DiffusionDerivative(T x, T t);

    T InitialCondition
    {
        get;
        set;
    }

    T Expiry
    {
        get;
        set;
    }

}

public class GBM<T> : ISde<T>
{ // Simple SDE

        private T mu;   // r
        private T vol;  // Constant volatility
        private T d;    // Constant dividend yield
        private T ic;   // Initial condition
        private T exp;  // Expiry

        public GBM(T driftCoefficient, T diffusionCoefficient, T dividendYield, T initialCondition, T expiry)
        {
            mu = driftCoefficient;
            vol = diffusionCoefficient;
            d = dividendYield;
            ic = initialCondition;
            exp = expiry;
        }

        public T Drift(T x, T t) { return ((dynamic)mu - (dynamic)d)*(dynamic)x;}
        public T Diffusion(T x, T t) { return (dynamic)vol*(dynamic)x;}

        public T DriftCorrected(T x, T t, T B) 
        {
            //return drift(X, t) - B * diffusion(X, t) * diffusionDerivative(X, t);
            return Drift(x, t) - (dynamic)B * Diffusion(x, t) * DiffusionDerivative(x, t); 
        }

        public T DiffusionDerivative(T x, T t)
        {
            return vol;
        }

        public T InitialCondition
        {
            get
            {
                return ic;
            }
            set
            {
                ic = value;
            }
        }

        public T Expiry
        {
            get
            {
                return exp;
            }
            set
            {
                exp = value;
            }
        }

}

public class CEV<T> : ISde<T>
{ // CEV model

    private T mu;   // r
    private T vol;  // Constant volatility
    private T d;    // Constant dividend yield
    private T ic;   // Initial condition
    private T exp;  // Expiry
    private T b;    // Beta

    public CEV(T driftCoefficient, T diffusionCoefficient, T dividendYield, T initialCondition, 
               T expiry, T beta)
    {
        mu = driftCoefficient;
        b = beta;
        ic = initialCondition;
        vol = diffusionCoefficient * (dynamic) Math.Pow((dynamic)ic, 1.0 - (dynamic) b);
        d = dividendYield;
        exp = expiry;
    }

    public T Drift(T x, T t) { return ((dynamic)mu - (dynamic)d) * (dynamic)x; }
    public T Diffusion(T x, T t) { return (dynamic)vol * (dynamic)Math.Pow((dynamic)x, (dynamic)b); }

    public T DriftCorrected(T x, T t, T B)
    {
        //return drift(X, t) - B * diffusion(X, t) * diffusionDerivative(X, t);
        return Drift(x, t) - (dynamic)B * Diffusion(x, t) * DiffusionDerivative(x, t);
    }

    public T DiffusionDerivative(T x, T t)
    {
        if ((dynamic)b > 1.0)
        {
            return (dynamic) vol * b * Math.Pow((dynamic) x, (dynamic) b - 1.0);
        }
        else
        {
              return (dynamic) vol * b / Math.Pow((dynamic) x, (dynamic) 1.0 - b);
        }


    }

    public T InitialCondition
    {
        get
        {
            return ic;
        }
        set
        {
            ic = value;
        }
    }

    public T Expiry
    {
        get
        {
            return exp;
        }
        set
        {
            exp = value;
        }
    }

}

public interface IFdm<T>
{ // Interface for one-step FDM methods for SDEs

    // Choose which SDE model to use
    ISde<T> StochasticEquation
    {
        get;
        set;
    }

    // Advance solution from level t[n] to level t[n+1]
    T advance(T xn, T tn, T dt, T WienerIncrement, T WienerIncrement2);
}

public abstract class FdmBase<T> : IFdm<T>
{
    protected ISde<T> sde;

    public int NT;         // Number of subdivisions
    public T[] x;          // The mesh array
    public dynamic k;      // Mesh size

    public FdmBase(ISde<T> stochasticEquation, int numSubdivisions)
    {
        sde = stochasticEquation;
        NT = numSubdivisions;
        k = (dynamic)sde.Expiry / (dynamic)NT;
 //       Console.WriteLine("{0},{1},{2} k", k, sde.Expiry, NT);
        x = new T[NT+1];

        // Create the mesh array
        x[0] = (dynamic)0.0;
        for (int n = 1; n < x.Length; n++)
        {
            x[n] = x[n - 1] + k;
        }
        for (int j = 0; j < x.Length; j++)
        {
          //  Console.Write("{0}, ", x[j]);            
        }
  //      string s = Console.ReadLine();
       
    }

    public ISde<T> StochasticEquation
    {
        get
        {
            return sde;
        }
        set
        {
            sde = value;
        }
    }

    public abstract T advance(T xn, T tn, T dt, T WienerIncrement, T WienerIncrement2);
}

public class EulerFdm<T> : FdmBase<T>
{
    public EulerFdm(ISde<T> stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt;
        return xn + sde.Drift(xn,tn)*dt1 + sde.Diffusion(xn,tn) * Math.Sqrt(dt1)*normalVar;
    }
}

public class KarhunenLoeve : FdmBase<double>
{
    private int N; // Truncated series value
    private IRng<double> rng;
    private double tmp;

    public KarhunenLoeve(ISde<double> stochasticEquation, int numSubdivisions, int nTruncated, IRng<double> randomGen)
        : base(stochasticEquation, numSubdivisions) 
    { 
        N = nTruncated;
        rng = randomGen;

        tmp = Math.Sqrt(2.0 * sde.Expiry);
    }

    private double OrthogonalFunction(double t, int n)
    { // Eigenvector in KL expansion

        double f = (2.0*n + 1.0)*3.14159 / 2.0;
        
        return (tmp/f) * Math.Sin((f*t)/sde.Expiry);
    }
    
    private double KLExpansion (double s, double t)
    { // W(s) - W(t) for s > t
        
        double result = 0.0;
        for (int n = 0; n <= N; n++)
        {
            result += (OrthogonalFunction(s, n) - OrthogonalFunction(t, n)) * rng.GenerateRn();
        }

        return result;
    } 


    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        //return xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * Math.Sqrt(dt) * normalVar;
        return xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * KLExpansion(tn + dt, tn);
    }
}


public class MilsteinFdm<T> : FdmBase<T>
{
    public MilsteinFdm(ISde<T> stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt;
        dynamic diffTerm = sde.Diffusion(xn, tn);
        return xn + sde.Drift(xn, tn) * dt1 + diffTerm * Math.Sqrt(dt1) * normalVar
                  + 0.5 * dt1 * diffTerm * sde.DiffusionDerivative(xn, tn) * (normalVar * (dynamic)normalVar  - 1.0);
    }
}

public class DiscreteMilsteinFdm<T> : FdmBase<T>
{
    public DiscreteMilsteinFdm(ISde<T> stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt; dynamic sqrt = Math.Sqrt(dt1);
        dynamic a = sde.Drift(xn, tn);
        dynamic b = sde.Diffusion(xn, tn);
        dynamic Yn = xn + a*dt1 + b*sqrt;
        //return xn + 0.5*(sde.Drift(Yn,tn) + a)*dt1 + b*sqrt*normalVar;
        return xn + a*dt1 + b*sqrt*normalVar
                //  + 0.5 * dt1 * diffTerm * sde.DiffusionDerivative(xn, tn) * (normalVar * (dynamic)normalVar - 1.0);
                    + 0.5*sqrt*(sde.Diffusion(Yn, tn) - b)*(normalVar * (dynamic)normalVar - 1.0);
    }
}
public class ExtrapolatedEulerFdm<T> : FdmBase<T>
{
    public ExtrapolatedEulerFdm(ISde<T> stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt;
        dynamic dt2 = 0.5 * (dynamic)dt;
        dynamic xA = xn + sde.Drift(xn, tn) * dt2 + sde.Diffusion(xn, tn) * Math.Sqrt(dt2) * normalVar;
        dynamic xB = xA + sde.Drift(xA, tn + dt2) * dt2 + sde.Diffusion(xA, tn + dt2) * Math.Sqrt(dt2) * normalVar2;

        dynamic normalVar3 = ((dynamic)normalVar + (dynamic)normalVar2) / Math.Sqrt(2.0);
        dynamic xC = xn + sde.Drift(xn, tn) * dt1 + sde.Diffusion(xn, tn) * Math.Sqrt(dt1) * normalVar3;

        return 2.0 * xB - xC;
    }
}

public class PredictorCorrectorFdm<T> : FdmBase<T>
{
    private dynamic A, B, VMid;

    public PredictorCorrectorFdm(ISde<T> stochasticEquation, int numSubdivisions, T a, T b)
        : base(stochasticEquation, numSubdivisions)
    {
        A = a;
        B = b;
    }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt;

        // Euler for predictor
        VMid = xn + sde.Drift(xn, tn) * dt1 + sde.Diffusion(xn, tn) * Math.Sqrt(dt1) * normalVar;

        // Modified Trapezoidal rule
        dynamic driftTerm = (A * sde.Drift(VMid, tn + dt1) + ((1.0 - A) * sde.Drift(xn, tn))) * dt1;
        dynamic diffusionTerm = (B * sde.Diffusion(VMid, tn + dt1) + ((1.0 - B) * sde.Diffusion(xn, tn))) * Math.Sqrt(dt1) * normalVar;
        return xn + driftTerm + diffusionTerm;
    }
}

public class ModifiedPredictorCorrectorFdm<T> : FdmBase<T>
{ // PC using adjusted drift

    private dynamic A, B, VMid;

    public ModifiedPredictorCorrectorFdm(ISde<T> stochasticEquation, int numSubdivisions, T a, T b)
        : base(stochasticEquation, numSubdivisions)
    {
        A = a;
        B = b;
        Console.WriteLine("Modified PC");

    }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt;

        // Euler for predictor
        VMid = xn + sde.Drift(xn, tn) * dt1 + sde.Diffusion(xn, tn) * Math.Sqrt(dt1) * normalVar;


        // Modified Trapezoidal rule
        dynamic driftTerm = (A * sde.DriftCorrected(VMid, tn + dt1, B) + ((1.0 - A) * sde.DriftCorrected(xn, tn, B))) * dt1;

        dynamic diffusionTerm = (B * sde.Diffusion(VMid, tn + dt1) + ((1.0 - B) * sde.Diffusion(xn, tn))) * Math.Sqrt(dt1) * normalVar;

        return xn + driftTerm + diffusionTerm;
    }
}

public class MidpointPredictorCorrectorFdm<T> : FdmBase<T>
{ // PC using adjusted drift

    private dynamic A, B, VMid;

    public MidpointPredictorCorrectorFdm(ISde<T> stochasticEquation, int numSubdivisions, T a, T b)
        : base(stochasticEquation, numSubdivisions)
    {
        A = a;
        B = b;
    }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt;

        // Euler for predictor
        VMid = xn + sde.Drift(xn, tn) * dt1 + sde.Diffusion(xn, tn) * Math.Sqrt(dt1) * normalVar;

        // Modified Trapezoidal rule
        dynamic driftTerm = sde.DriftCorrected(A*VMid + (1.0-A)*xn, tn + 0.5*dt1, B) * dt1;
        dynamic diffusionTerm = sde.Diffusion(B*VMid + (1.0-B)*xn, tn + 0.5*dt1) * Math.Sqrt(dt1) * normalVar;

        return xn + driftTerm + diffusionTerm;
    }
}

public class Platen_01_Explicit : FdmBase<double>
{ // 


    public Platen_01_Explicit(ISde<double> stochasticEquation, int numSubdivisions)
        : base(stochasticEquation, numSubdivisions)
    {
        Console.WriteLine("Platen 1.0");
    }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        double b = sde.Diffusion(xn, tn);
        double drift_Strat = sde.Drift(xn, tn) - 0.5 * b * sde.DiffusionDerivative(xn, tn);
        double suppValue = xn + drift_Strat * dt + b * Math.Sqrt(dt);

        return xn + drift_Strat*dt + b*Math.Sqrt(dt)*normalVar + 0.5*Math.Sqrt(dt)*(sde.Diffusion(suppValue,tn) - b)*normalVar*normalVar;
    }
}
public class Heun : FdmBase<double>
{ // Npt consistent with Ito calculus

    public Heun(ISde<double> stochasticEquation, int numSubdivisions)
        : base(stochasticEquation, numSubdivisions)
    {

    }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        double a = sde.Drift(xn, tn);
        double b = sde.Diffusion(xn, tn);
        double suppValue = xn + a*dt + b*Math.Sqrt(dt)*normalVar;

        return xn + 0.5*(sde.Drift(suppValue, tn) + a)*dt + 0.5*(sde.Diffusion(suppValue, tn) + b)*Math.Sqrt(dt)*normalVar;
    }
}

public class ExactFdm<T> : FdmBase<T>
{
    public ExactFdm(ISde<T> stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override T advance(T xn, T tn, T dt, T normalVar, T normalVar2)
    {
        dynamic dt1 = dt;
        dynamic r = ((dynamic) sde.Drift(xn,tn)/ (dynamic)xn);
        dynamic sig = ((dynamic) sde.Diffusion(xn,tn)/ (dynamic)xn);

        return xn * Math.Exp(((r - 0.5*sig*sig)*dt1) + sig * Math.Sqrt(dt1)*(dynamic)normalVar);
    }
}


public interface IRng<T>
{
    T GenerateRn();
}

public abstract class Rng<T> : IRng<T>
{
    public abstract T GenerateRn();
}

/*
public class PolarMarsaglia<T> : Rng<T>
{
    private Random rand;

    public PolarMarsaglia() {  rand = new Random();} // Seed is from system clock
    
    public override T GenerateRn()
    {

        dynamic u, v, S;

        do
        {
            u = 2.0 * rand.NextDouble() - 1.0;
            v = 2.0 * rand.NextDouble() - 1.0;
            S = u * u + v * v;
        }
        while (S >= 1.0);

        dynamic fac = Math.Sqrt(-2.0 * Math.Log(S) / S);
        return (T)(u * fac);
    }
}
*/


public class PolarMarsaglia<T> : Rng<T>
{
    private SitmoWrapper.ManagedWrapper rand;

    public PolarMarsaglia() { rand = new SitmoWrapper.ManagedWrapper(); } // Seed is from system clock

    public override T GenerateRn()
    {

        dynamic u, v, S;

        do
        {
            u = 2.0 * rand.NextDouble() - 1.0;
            v = 2.0 * rand.NextDouble() - 1.0;

         //   Console.Write(", {0}", rand.NextDouble());
            S = u * u + v * v;
        }
        while (S >= 1.0);

        dynamic fac = Math.Sqrt(-2.0 * Math.Log(S) / S);
        return (T)(u * fac);
    }
}

/*

public class BoxMuller<T> : Rng<T>
{
    private SitmoWrapper.ManagedWrapper rand;

    public BoxMuller() { rand = new SitmoWrapper.ManagedWrapper(); } // Seed is from system clock

    public override T GenerateRn()
    {
        // U1 and U2 should be independent uniform random numbers
        dynamic U1 = rand.NextDouble();   // In interval [0,1)
        dynamic U2 = rand.NextDouble();  // In interval [0,1)

        // Box-Muller method
        dynamic G1 = Math.Sqrt(-2.0 * Math.Log(U1)) * Math.Cos(2.0 * 3.1415159 * U2);

        return (T)G1;
    }
}

*/
public class BoxMuller<T> : Rng<T>
{
    private Random rand;

    public BoxMuller() { rand = new Random(); } // Seed is from system clock

    public override T GenerateRn()
    {
        // U1 and U2 should be independent uniform random numbers
        dynamic U1 = rand.NextDouble();   // In interval [0,1)
        dynamic U2 = rand.NextDouble();  // In interval [0,1)

        // Box-Muller method
        dynamic G1 = Math.Sqrt(-2.0 * Math.Log(U1)) * Math.Cos(2.0 * 3.1415159 * U2);

        return (T)G1;
    }
}


// The Status system that actually computes option pricing

public interface IPricer<T>
{
    void ProcessPath(ref T[] arr);
    void PostProcess();
    T DiscountFactor();      
    T Price();

}

public delegate T Payoff<T>(T underlying);
//public delegate T Func<T> ();

public abstract class Pricer<T> : IPricer<T>
{
    public abstract void ProcessPath(ref T[] arr);  // Create a single path
    public abstract void PostProcess();             // Notify end of simulation
    public abstract T DiscountFactor();             // Discounting
    public abstract T Price();                      // Option price


//    public delegate T Payoff<T>(T underlying);
    public Payoff<T> m_payoff;
    protected Func<T> m_discounter;

    public Pricer(Payoff<T> payoff, Func<T> discounter)
    {
        m_payoff = payoff;
        m_discounter = discounter;
    }
}

// Pricing Engines
public class EuropeanPricer<T> : Pricer<T>
{
    private dynamic price;
    private dynamic sum;
    private int NSim;

    public EuropeanPricer(Payoff<T> payoff, Func<T> discounter) : base(payoff, discounter) { price = sum = 0.0; NSim = 0; }

    public override void ProcessPath(ref T[] arr) 
    { // A path for each simulation/draw

       	// Sum of option values at terminal time T
     //   dynamic K = 65;
    //    sum += Math.Max(0.0, K - arr[arr.Length-1]); NSim++;
          sum += m_payoff(arr[arr.Length - 1]); NSim++;
     //     Console.WriteLine(arr[arr.Length - 1]); string d = Console.ReadLine();
        //  Console.WriteLine(m_payoff((dynamic)75.0));
    }

    public override T DiscountFactor()
    { // Discounting

      //  return Math.Exp(-r * expiry);
        return m_discounter();
    }
    
    public override void PostProcess()
    {
        Console.WriteLine("Compute Plain price"); price = DiscountFactor() * sum / NSim; Console.WriteLine("Price: {0}, {1}", price, NSim);
    }

    public override T Price()
    {
        return price;
    }

}

public class AsianPricer<T> : Pricer<T>
{ // e.g. arithmetic Asian average of the asset price taken on a set of observations (fixings) of the asset price

    private dynamic price;
    private dynamic sum;
    private dynamic avg = 0.0;    // Arithmetic average at the fixing points
    private int NSim;

    private static T Average<T>(T[] array)
    {
        dynamic avg = array[0];

        foreach (T item in array)
        {
            avg += item;
        }
        return (T)avg / (dynamic) array.Length;
    }

    private static T GeometricAverage<T>(T[] array)
    {
        dynamic avg = array[0];

        foreach (T item in array)
        {
            avg *= item;
        }
        return (T)(1.0 / Math.Pow(avg, (dynamic)array.Length));
    }

    private static T Max<T>(T[] array)
    {
        dynamic max = array[0];

        foreach (T item in array)
        {
            max = (dynamic) Math.Max((dynamic)item, max);
        }
        return (T)max;
    }

    public AsianPricer(Payoff<T> payoff, Func<T> discounter) : base(payoff, discounter) { price = sum = 0.0; NSim = 0; }

    public override void ProcessPath(ref T[] arr)
    { // A path for each simulation/draw

        // Compute the arithmetic average using LINQ
        //avg = Average(arr);
        //avg = GeometricAverage(arr);
        avg = Max(arr);

        //   sum += m_payoff(arr[arr.Length - 1]); NSim++;
        sum += m_payoff(avg); NSim++;
  
    }

    public override T DiscountFactor()
    { // Discounting

        return m_discounter();
    }

    public override void PostProcess()
    {
        Console.WriteLine("Compute Asian price"); price = DiscountFactor() * sum / NSim; Console.WriteLine("Price: {0}, {1}", price, NSim);
    }

    public override T Price()
    {
        return price;
    }

}

public class BarrierPricer<T> : Pricer<T>
{
    private dynamic price;
    private dynamic sum, sum2;
    private int NSim;
    
    public BarrierPricer(Payoff<T> payoff, Func<T> discounter) : base(payoff, discounter) { price = sum = sum2 = 0.0; NSim = 0; }

    public override void ProcessPath(ref T[] arr) 
    {

        dynamic L = 170.0;
        dynamic rebate = 0.0;

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
         //   Console.WriteLine(m_payoff((dynamic)75.0));
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
    
    public override T DiscountFactor()
    { // Discounting

        return m_discounter();
    }
    

    public override T Price()
    {
        return price;
    }
}


public class BrownianBridgePricer<T> : Pricer<T>
{
    private dynamic price;
    private dynamic sum, sum2;
    private int NSim;
    private Random rand;
    private dynamic dt;
    private GBM<T> sde;
    private int counter = 0;


    public BrownianBridgePricer(Payoff<T> payoff, Func<T> discounter, GBM<T> stochasticDE, T step) : base(payoff, discounter) 
    { 
        price = sum = sum2 = 0.0; NSim = 0;
        rand = new Random();
        dt = step;
        sde = stochasticDE;
    }

    public override void ProcessPath(ref T[] arr)
    {

        dynamic L = 170.0;
        dynamic rebate = 0.0;
        double P, tmp, u;

        bool crossed = false;
        for (int n = 1; n < arr.Length; n++)
        {
            // Calculate exit probability
            tmp = sde.Diffusion((dynamic)arr[n - 1], (dynamic)(n-1) * dt);
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
            //   Console.WriteLine(m_payoff((dynamic)75.0));
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

    public override T DiscountFactor()
    { // Discounting

        return m_discounter();
    }


    public override T Price()
    {
        return price;
    }
}

// Events
public delegate void PathEvent<T> (ref T[] path);
public delegate void EndOfSimulation<T>();

public class MCMediator<T> where T : new()
{
    private ISde<T> sde;
    private FdmBase<T> fdm;
    private IRng<T> rng;

    private int NSim;
    private T[] res;

    // Event notification
    public event PathEvent<T> path;
    public event EndOfSimulation<T> finish;

    public MCMediator(Tuple<ISde<T>, FdmBase<T>, IRng<T>> parts, int numberSimulations)
    {
        sde = parts.Item1;
        fdm = parts.Item2;
        rng = parts.Item3;

        NSim = numberSimulations;
        res = new T[fdm.NT];
    }

    public void start()
    {
        T VOld, VNew;

        for (long i = 1; i <= NSim; ++i)
        { // Calculate a path at each iteration

            if ((i / 5000) * 5000 == i)
            { // Give status after a given numbers of iterations

                Console.WriteLine(i);
            }

            VOld = sde.InitialCondition; res[0] = VOld;

            for (int n = 1; n < res.Length; n++)
            { // Compute the solution at level n+1
    
                VNew = fdm.advance(VOld, fdm.x[n-1], fdm.k, rng.GenerateRn(), rng.GenerateRn());
                res[n] = VNew; VOld = VNew;
            }
            
            path(ref res);
        }
        finish();
    }
}

public delegate Tuple<T1, T2, T3> Builder<T1, T2, T3>();


public class MCBuilder<S, F, R>
    where S : ISde<double>
    where F : IFdm<double>
    where R : IRng<double>
{ // Build the full UML model in this builder

    private double r;
    private double v;
    private double d;
    private double IC;
    private double T;
    private double beta;

    // Constructor (data important at this stage)
    public MCBuilder(Tuple<double, double, double, double, double, double> data)
    {
        r = data.Item1;
        v = data.Item2;
        d = data.Item3;
        IC = data.Item4;
        T = data.Item5;
        beta = data.Item6;
    }

    public Tuple<S, F, R> Parts(S sde, F fdm, R rng)
    { // V1, parts initialised from the outside

        return new Tuple<S, F, R>(sde, fdm, rng);
    }

    public Tuple<ISde<double>, FdmBase<double>, IRng<double>> Parts()
    { // V2, parts initialised from the inside

        // Get the SDE
        ISde<double> sde = GetSde();
        IRng<double> rng = GetRng();
        FdmBase<double> fdm = GetFdm(sde);
        return new Tuple<ISde<double>, FdmBase<double>, IRng<double>>(sde, fdm, rng);
    }

    private ISde<double> GetSde()
    {
        Console.WriteLine("Create SDE");
        Console.Write("1. GBM, 2. CEV ");
        int c = Convert.ToInt32(Console.ReadLine());

        if (c == 1)
        { // GBM

           return new GBM<double>(r, v, d, IC, T);
        }
        else
        {
            return new CEV<double>(r, v, d, IC, T, beta);
        }
    }

    private IRng<double> GetRng()
    {
        Console.WriteLine("Create RNG");
        Console.Write("1. Box-Muller 2. Polar Marsaglia ");
        int c = Convert.ToInt32(Console.ReadLine());

        if (c == 1)
        { // 
            return new BoxMuller<double>();
        }
        else
        {
            return new PolarMarsaglia<double>();
        }
    }

    private FdmBase<double> GetFdm(ISde<double> sde)
    {
        Console.WriteLine("Create FDM");
        Console.WriteLine("1. Euler, 2. Extrapolated Euler, 3. Milstein, 4. Predictor-Corrector (PC),");
        Console.WriteLine("5. PC adjusted, 6. PC midpoint, 7. Exact, 8. Discrete Milstein,");
        Console.WriteLine("9. Karhunen Loeve, 10. Platen 1.0 strong scheme, 11. Heun");
        int c = Convert.ToInt32(Console.ReadLine());

        FdmBase<double> fdm;

        int NT = 500;
        Console.Write("How many NT? ");
        NT = Convert.ToInt32(Console.ReadLine());

        double a, b;

        switch(c)
        {
            case 1:
        
                fdm = new EulerFdm<double>(sde, NT);
                break;
            case 2:

                fdm = new ExtrapolatedEulerFdm<double>(sde, NT);
                break;
       
            case 3: 

                fdm = new MilsteinFdm<double>(sde, NT);
                break;
            
            case 4:
                a = 0.5;
                b = 0.5;
                fdm = new PredictorCorrectorFdm<double>(sde, NT, a, b);
                break;
            
            case 5:
                a = 0.5;
                b = 0.5;
                fdm = new ModifiedPredictorCorrectorFdm<double>(sde, NT, a, b);
                break;
      
            case 6:
                a = 0.5;
                b = 0.5;
                fdm = new MidpointPredictorCorrectorFdm<double>(sde, NT, a, b);
                break;
           
            case 7:
                fdm = new ExactFdm<double>(sde, NT);
                break;
        
            case 8:
                fdm = new DiscreteMilsteinFdm<double>(sde, NT);
                break;
            
            case 9:
                int N = 100; // Series truncation value
                IRng<double> rng = new PolarMarsaglia<double>();

                fdm = new KarhunenLoeve(sde, NT, N, rng);
                break;

            case 10:
                fdm = new Platen_01_Explicit(sde, NT);
                break;
            
            case 11:
                fdm = new Heun(sde, NT);
                break;
            default:
                fdm = new ExtrapolatedEulerFdm<double>(sde, NT);
                break;
        }

        return fdm;
    }
}


    // Main program etc.
    public class MCPricerApplication
    {
        // Choose which builder you want
        public static Builder<ISde<double>, FdmBase<double>, IRng<double>> ChooseBuilder(int n)
        {
           double r = 0.08;
           double v = 0.3;
           double div = 0.0;
           double IC = 60.0;
           double T = 0.25;
           double K = 65.0;
           double beta = 1.0;

       /*     double r = 0.05;
            double v = 0.2;
            double div = 0.025;
            double IC = 100.0;
            double T = 1.0;
            double K = 100.0;
            double beta = 1.0;// 2.0 / 3.0;*/

       /*     double r = 0.1;
            double v = 0.2;
            double div = 0.0;
            double IC = 100.0;
            double T = 1.0;
            double K = 100.0;
            double beta = 1.0;*/
            Tuple<double, double, double, double, double, double> data = new Tuple<double, double, double, double, double, double>(r, v, div, IC, T, beta);

            MCBuilder<ISde<double>, FdmBase<double>, IRng<double>> builder = new MCBuilder<ISde<double>, FdmBase<double>, IRng<double>>(data);

            return builder.Parts;
        }


        public static void Main()
        {
            // Choose which builder to use
            int choice = 1;
            Builder<ISde<double>, FdmBase<double>, IRng<double>> factory = ChooseBuilder(choice);

            // Create the parts of the object network
            Tuple<ISde<double>, FdmBase<double>, IRng<double>> parts2 = factory();

            int NSim = 1000000;
            Console.Write("How many NSim? ");
            NSim = Convert.ToInt32(Console.ReadLine());

            MCMediator<double> mcp = new MCMediator<double>(parts2, NSim);

        /*    double v = 0.2;
            double r = 0.05;
            double div = 0.0;
            double IC = 100.0;
            double T = 1.0;
            double K = 100.0;
            double beta = 1.0;// 2.0 / 3.0;*/

            double r = 0.08;
            double v = 0.3;
            double div = 0.0;
            double IC = 60.0;
            double T = 0.25;
            double K = 65.0;
            double beta = 1.0;

      /*      double r = 0.08;
            double v = 0.3;
            double div = 0.0;
            double IC = 60.0;
            double T = 0.25;
            double K = 65.0;
            double beta = 1.0;*/

            // Events
            Payoff<double> payoff = x => Math.Max(0.0, K - x);
          //  Payoff<double> payoff = x => Math.Max(0.0, x - K);
        //    Console.WriteLine(payoff(75.0));

       
            Func<double> discounter = () => Math.Exp(-r * T);

            IPricer<double> op = new EuropeanPricer<double>(payoff, discounter);
            IPricer<double> op2 = new BarrierPricer<double>(payoff, discounter);
 
            GBM<double> sde = new GBM<double>(r, v, div, IC, T);
            int NT = 400;
            IPricer<double> op3 = new BrownianBridgePricer<double>(payoff, discounter, sde, NT);
            IPricer<double> op4 = new AsianPricer<double>(payoff, discounter);

            // Define slots for path information
            mcp.path += op.ProcessPath;
          //  mcp.path += op2.ProcessPath;
         //   mcp.path += op3.ProcessPath;
         //   mcp.path += op4.ProcessPath;

            // Signal end of simulation
            mcp.finish += op.PostProcess;
       //     mcp.finish += op2.PostProcess;
        //    mcp.finish += op3.PostProcess;
        //    mcp.finish += op4.PostProcess;

            mcp.start();
            
   
        }
    }