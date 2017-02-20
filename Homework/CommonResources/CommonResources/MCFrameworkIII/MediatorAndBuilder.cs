// Pricers.cs
//
// (C) Datasim Education BV 2014
//

using System;
using System.Collections.Generic;
using System.Linq;


 // Events
public delegate void PathEvent<T> (ref T[] path);   // Send a path array
public delegate void EndOfSimulation<T>();          // No more paths

public class MCMediator
{
    // Three main components
    private ISde sde;
    private FdmBase fdm;
    private IRng rng;

    // Other MC-related data 
    private int NSim;           // Number of simulations    
    private double[] res;       // Generated path per simulation

    // Event notification
    public event PathEvent<double> path;            // Signal to the Pricers
    public event EndOfSimulation<double> finish;    // Signals that all paths are complete

    public MCMediator(Tuple<ISde, FdmBase, IRng> parts, int numberSimulations)
    {
        sde = parts.Item1;
        fdm = parts.Item2;
        rng = parts.Item3;

        NSim = numberSimulations;
        res = new double[fdm.NT];
    }

    public void start()
    { // Main event loop for path generation

        double VOld, VNew;

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
            
            // Send path data to the Pricers
            path(ref res);
        }
        finish(); // Signal to pricers to finish up
    }
}

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

    public Tuple<ISde, FdmBase, IRng> Parts()
    { // V2, parts initialised from the inside

        // Get the SDE
        ISde sde = GetSde();
        IRng rng = GetRng();
        FdmBase fdm = GetFdm(sde);
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
            return new CEV(r, v, d, IC, T, beta);
        }
    }

    private IRng GetRng()
    {
        Console.WriteLine("Create RNG");
        Console.WriteLine("1. Box-Muller .Net 2. Polar Marsaglia Sitmo 3. Delegate-based Box-Muller ");
        Console.Write("4. Box-Muller Sitmo 5. Polar Marsaglia .Net 6. Box-Muller Crypto: ");
        int c = Convert.ToInt32(Console.ReadLine());

        IRng rng;

        switch (c)
        {
            case 1:
                rng = new BoxMullerNet();
                break;
            case 2:
              //  rng = new PolarMarsagliaSitmo();
                rng = new BoxMullerNet();
                break;

            case 3:
                 Console.WriteLine("Flavour");
                 Console.Write("1. .NET Random 2. Sitmo PRNG ");
                 int c2 = Convert.ToInt32(Console.ReadLine());

                // Delegate-based
                 if (c2 == 2)
                 {
               //      SitmoWrapper.ManagedWrapper prng = new SitmoWrapper.ManagedWrapper();
                //     RngDelegate rand = prng.NextDouble;
               //      rng = new BoxMullerII(rand);
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
             //    rng = new BoxMullerSitmo();
                 rng = new BoxMullerNet();

                 break;
            case 5:
                 rng = new PolarMarsagliaNet();
                 break;
            case 6:
                 rng = new BoxMullerCrypto();
                 break;
            default:
               // rng = new BoxMullerSitmo();
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
        Console.WriteLine("9. Karhunen Loeve, 10. Platen 1.0 strong scheme, 11. Heun");
        Console.WriteLine("12. Derivative Free, 13. FRKI (Runge Kutta), 14. Heun2: ");
        int c = Convert.ToInt32(Console.ReadLine());

        FdmBase fdm;

        int NT = 500;
        Console.Write("How many NT? ");
        NT = Convert.ToInt32(Console.ReadLine());

        double a, b;

        switch(c)
        {
            case 1:
        
                fdm = new EulerFdm(sde, NT);
                break;
            case 2:

                fdm = new ExtrapolatedEulerFdm(sde, NT);
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
                fdm = new ExactFdm(sde, NT);
                break;
        
            case 8:
                fdm = new DiscreteMilsteinFdm(sde, NT);
                break;
            
            case 9:
                int N = 100; // Series truncation value
               // IRng rng = new PolarMarsagliaSitmo();

           //     fdm = new KarhunenLoeve(sde, NT, N, rng);
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
            default:
                fdm = new ExtrapolatedEulerFdm(sde, NT);
                break;
        }

        return fdm;
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
    private double beta;

    // Constructor (data important at this stage)
    public MCDefaultBuilder()
    {
        r = 0.08;
        v = 0.30;
        d = 0.0;
        IC = 60.0;
        T = 0.25;
        beta = 1.0;
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
}
// Exx. default builder



