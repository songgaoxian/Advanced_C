// Fdm.cs
//
// Finite difference methods for SDEs.
//
// 2016-1-23 DD removed some schemes
// 2016-7-13 DD update drift-adjusted PC
//
// (C) Datasim Education BV 2014-2016
//

using System;


public interface IFdm
{ // Interface for one-step FDM methods for SDEs

    // Choose which SDE model to use
    ISde StochasticEquation
    {
        get;
        set;
    }

    // Advance solution from level t[n] to level t[n+1]
    double  advance(double  xn, double  tn, double  dt, double  WienerIncrement, double  WienerIncrement2);
}

public abstract class FdmBase : IFdm
{
    protected ISde sde;

    public int NT;           // Number of subdivisions
    public double [] x;       // The mesh array
    public double  k;         // Mesh size

    protected double dtSqrt;

    public FdmBase(ISde stochasticEquation, int numSubdivisions)
    {
        sde = stochasticEquation;
        NT = numSubdivisions;
        k = sde.Expiry / (double)NT;
        dtSqrt = Math.Sqrt(k);
        x = new double[NT + 1];

        // Create the mesh array
        x[0] = 0.0;
        for (int n = 1; n < x.Length; n++)
        {
            x[n] = x[n - 1] + k;
        }

    }

    public ISde StochasticEquation
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

    public abstract double  advance(double  xn, double  tn, double  dt, double  WienerIncrement, double  WienerIncrement2);
}

public class EulerFdm : FdmBase
{
    public EulerFdm(ISde stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override double  advance(double  xn, double  tn, double  dt, double  normalVar, double  normalVar2)
    {
         return xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * dtSqrt * normalVar;
    }
}

public class ExactFdm : FdmBase
{
    private double S0;
    private double sig;
    private double mu;

    public ExactFdm(ISde stochasticEquation, int numSubdivisions,
            double S0, double vol, double drift) : base(stochasticEquation, numSubdivisions) 
     {
        this.S0 = S0;
        sig = vol;
        mu = drift;
            
    }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        // Compute exact value at tn + dt.
        double alpha = 0.5 * sig * sig;
        return S0 * Math.Exp((mu - alpha) * (tn + dt) + sig * Math.Sqrt(tn + dt) * normalVar);
    }
}



public class MilsteinFdm : FdmBase
{
    public MilsteinFdm(ISde stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override double  advance(double  xn, double  tn, double  dt, double  normalVar, double  normalVar2)
    {
         return xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * Math.Sqrt(dt) * normalVar
                  + 0.5 * dt * sde.Diffusion(xn, tn) * sde.DiffusionDerivative(xn, tn) * (normalVar * (dynamic)normalVar - 1.0);
    }
}

public class DiscreteMilsteinFdm : FdmBase
{
    public DiscreteMilsteinFdm(ISde stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override double  advance(double  xn, double  tn, double  dt, double  normalVar, double  normalVar2)
    {
        double dt1 = dt; double sqrt = Math.Sqrt(dt1);
        double a = sde.Drift(xn, tn);
        double b = sde.Diffusion(xn, tn);
        double Yn = xn + a * dt1 + b * sqrt;
        //return xn + 0.5*(sde.Drift(Yn,tn) + a)*dt1 + b*sqrt*normalVar;
        return xn + a * dt1 + b * sqrt * normalVar
            //  + 0.5 * dt1 * diffdouble erm * sde.DiffusionDerivative(xn, tn) * (normalVar * (dynamic)normalVar - 1.0);
                    + 0.5 * sqrt * (sde.Diffusion(Yn, tn) - b) * (normalVar * (dynamic)normalVar - 1.0);
    }
}


public class PredictorCorrectorFdm : FdmBase
{
    private double A, B, VMid;

    public PredictorCorrectorFdm(ISde stochasticEquation, int numSubdivisions, double  a, double  b)
        : base(stochasticEquation, numSubdivisions)
    {
        A = a;
        B = b;
    }

    public override double  advance(double  xn, double  tn, double  dt, double  normalVar, double  normalVar2)
    {
     
        // Euler for predictor
        VMid = xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * dtSqrt * normalVar;

        // Modified double rapezoidal rule
        double driftdoubleTerm = (A * sde.Drift(VMid, tn + dt) + ((1.0 - A) * sde.Drift(xn, tn))) * dt;
        double diffusiondoubleTerm = (B * sde.Diffusion(VMid, tn + dt) + ((1.0 - B) * sde.Diffusion(xn, tn))) * dtSqrt* normalVar;
        return xn + driftdoubleTerm + diffusiondoubleTerm;
    }
}

public class ModifiedPredictorCorrectorFdm : FdmBase
{ // PC using adjusted drift, Trapezoidal rule

    private double A, B, VMid;

    public ModifiedPredictorCorrectorFdm(ISde stochasticEquation, int numSubdivisions, double  a, double  b)
        : base(stochasticEquation, numSubdivisions)
    {
        A = a;
        B = b;
        Console.WriteLine("Modified PC");

    }

    public override double  advance(double  xn, double  tn, double  dt, double  normalVar, double  normalVar2)
    {
       
        // Euler for predictor
        VMid = xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * dtSqrt * normalVar;


        // Modified Trapezoidal rule
        double  driftTerm = (A * sde.DriftCorrected(VMid, tn + dt, B) + ((1.0 - A) * sde.DriftCorrected(xn, tn, B))) * dt;

        double  diffusionTerm = (B * sde.Diffusion(VMid, tn + dt) + ((1.0 - B) * sde.Diffusion(xn, tn))) * dtSqrt * normalVar;

        return xn + driftTerm + diffusionTerm;

        // Exx. midpoint adjusted
    }
}

public class MidpointPredictorCorrectorFdm : FdmBase
{ // PC using adjusted drift, midpoint rule

    private double A, B, VMid;

    public MidpointPredictorCorrectorFdm(ISde stochasticEquation, int numSubdivisions, double a, double b)
        : base(stochasticEquation, numSubdivisions)
    {
        A = a;
        B = b;
        Console.WriteLine("Midpoint Adjusted PC");

    }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {

        // Euler for predictor
        VMid = xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * dtSqrt * normalVar;


        // Modified Trapezoidal rule
        //   double driftTerm = (A * sde.DriftCorrected(VMid, tn + dt, B) + ((1.0 - A) * sde.DriftCorrected(xn, tn, B))) * dt;
        double driftTerm = (sde.DriftCorrected(A*VMid + (1.0 - A)*xn, tn + dt/2, B)) * dt;

      //  double diffusionTerm = (B * sde.Diffusion(VMid, tn + dt) + ((1.0 - B) * sde.Diffusion(xn, tn))) * Math.Sqrt(dt) * normalVar;
        double diffusionTerm = (sde.Diffusion(B*VMid + (1.0 - B)*xn, tn + dt/2)) * dtSqrt * normalVar;
        return xn + driftTerm + diffusionTerm;

        // Exx. midpoint adjusted
    }
}

public class FittedMidpointPredictorCorrectorFdm : FdmBase
{ // PC using adjusted drift, midpoint rule

    // Fitted version, drift must be of the form dS = aSdt + bSdW

    private double A, B, VMid;

    public FittedMidpointPredictorCorrectorFdm(ISde stochasticEquation, int numSubdivisions, double a, double b)
        : base(stochasticEquation, numSubdivisions)
    {
        A = a;
        B = b;
        Console.WriteLine("Fitted midpoint Adjusted PC");

    }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {

        // Euler for predictor
        //VMid = xn + sde.Drift(xn, tn) * dt + sde.Diffusion(xn, tn) * dtSqrt * normalVar;
        double aFit = (Math.Exp(0.08 * dt) - 1.0) / dt;
        VMid = xn + aFit*xn*dt + sde.Diffusion(xn, tn) * dtSqrt * normalVar;

        // Modified Trapezoidal rule
        //   double driftTerm = (A * sde.DriftCorrected(VMid, tn + dt, B) + ((1.0 - A) * sde.DriftCorrected(xn, tn, B))) * dt;
        double driftTerm = (sde.DriftCorrected(A * VMid + (1.0 - A) * xn, tn + dt / 2, B)) * dt;

        //  double diffusionTerm = (B * sde.Diffusion(VMid, tn + dt) + ((1.0 - B) * sde.Diffusion(xn, tn))) * Math.Sqrt(dt) * normalVar;
        double diffusionTerm = (sde.Diffusion(B * VMid + (1.0 - B) * xn, tn + dt / 2)) * dtSqrt * normalVar;
        return xn + driftTerm + diffusionTerm;

        // Exx. midpoint adjusted
    }
}



public class Platen_01_Explicit : FdmBase
{ // 


    public Platen_01_Explicit(ISde stochasticEquation, int numSubdivisions)
        : base(stochasticEquation, numSubdivisions)
    {
        Console.WriteLine("Platen 1.0");
    }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        double b = sde.Diffusion(xn, tn);
        double drift_Strat = sde.Drift(xn, tn) - 0.5 * b * sde.DiffusionDerivative(xn, tn);
        double suppValue = xn + drift_Strat * dt + b * Math.Sqrt(dt);

        return xn + drift_Strat * dt + b * Math.Sqrt(dt) * normalVar + 0.5 * Math.Sqrt(dt) * (sde.Diffusion(suppValue, tn) - b) * normalVar * normalVar;
    }
}
public class Heun : FdmBase
{ // Npt consistent with Ito calculus

    public Heun(ISde stochasticEquation, int numSubdivisions)
        : base(stochasticEquation, numSubdivisions)
    {

    }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        double a = sde.Drift(xn, tn);
        double b = sde.Diffusion(xn, tn);
        double suppValue = xn + a * dt + b * Math.Sqrt(dt) * normalVar;

        return xn + 0.5 * (sde.Drift(suppValue, tn) + a) * dt + 0.5 * (sde.Diffusion(suppValue, tn) + b) * Math.Sqrt(dt) * normalVar;
    }
}


public class DerivativeFree : FdmBase
{
    double F1,G1,G2, addedVal, Wincr;
    double sqrk;

    // Code ported from C++
    public DerivativeFree(ISde stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        double dt1 = dt;
        sqrk = Math.Sqrt(dt1);
        Wincr = sqrk * normalVar;

	    F1 = sde.Drift(xn, tn);
		G1 = sde.Diffusion(xn, tn);

		G2 = sde.Diffusion(xn + G1 * sqrk, tn);
		addedVal = 0.5 *(G2 - G1) * (Wincr * Wincr - dt1)/sqrk;

		return xn + (F1 * dt1 + G1 * Wincr + addedVal);

    }
}

public class FRKI : FdmBase
{ // 1st order Runge Kutta with Ito coefficient

    double F1, G1, G2, addedVal, Wincr;
    double sqrk;

    // Code ported from C++
    public FRKI(ISde stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    public override double advance(double xn, double tn, double dt, double normalVar, double normalVar2)
    {
        double dt1 = dt;
        sqrk = Math.Sqrt(dt1);
        Wincr = sqrk * normalVar;

        // Ported from C++
        F1 = sde.Drift(xn, tn);
        G1 = sde.Diffusion(xn, tn);

        G2 = sde.Diffusion(xn+ 0.5 * G1 * (Wincr - sqrk), tn);

        return xn + (F1 * k + G2 * Wincr + (G2 - G1) * sqrk);
    }
}

public class Heun2 : FdmBase
{ // 

    double F1, F2, G1, G2, addedVal, Wincr, tmp;
    double sqrk;

    private double  F(double  x, double  t)
    {
        return sde.Drift(x, t) - 0.5 * (dynamic)sde.DiffusionDerivative(x, t) * sde.Diffusion(x, t);
    }

    // Code ported from C++
    public Heun2(ISde stochasticEquation, int numSubdivisions) : base(stochasticEquation, numSubdivisions) { }

    
    public override double  advance(double  xn, double  tn, double  dt, double  normalVar, double  normalVar2)
    {
        double dt1 = dt;
        sqrk = Math.Sqrt(dt1);
        Wincr = sqrk * normalVar;

        // Ported from C++
        F1 = F(xn, tn);
        G1 = sde.Diffusion(xn, tn);

        tmp = xn + F1*dt1 + G1*Wincr;
        F2 = F(tmp,tn);
        G2 = sde.Diffusion(tmp, tn);

        return xn + 0.5*(F1 + F2)*dt1 + 0.5*(G1 + G2)*Wincr;
    }
}

