// Sde.cs
// 
// One-factor Stochastic Differential Equatons (SDEs)
//
// (C) Datasim Education BV 2014
//

using System;
using System.Collections.Generic;

public interface ISde
{ // Standard one-factor SDE dX = a(X,t)dt + b(X,t)dW, X(0)given
  //                         dX = mu(X,t)dt + sig(X,t)dW


    double Drift(double x, double t);          // a (mu)
    double Diffusion(double x, double t);      // b (sig)

    // Some extra functions associated with the SDE
    double DriftCorrected(double x, double t, double B);
    double DiffusionDerivative(double x, double t);

    double InitialCondition
    {
        get;
        set;
    }

    double Expiry
    {
        get;
        set;
    }
}

public class GBM : ISde
{ // Simple SDE

    private double mu;   // Drift
    private double vol;  // Constant volatility
    private double d;    // Constant dividend yield
    private double ic;   // Initial condition
    private double exp;  // Expiry

    public GBM(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition, double expiry)
    {
        mu = driftCoefficient;
        vol = diffusionCoefficient;
        d = dividendYield;
        ic = initialCondition;
        exp = expiry;
    }

    public double Drift(double x, double t) { return (mu - d) * x; }
    public double Diffusion(double x, double t) { return vol * x; }

    public double DriftCorrected(double x, double t, double B)
    {
       return Drift(x, t) - B * Diffusion(x, t) * DiffusionDerivative(x, t);
    }

    public double DiffusionDerivative(double x, double t)
    {
        return vol;
    }

    // Property to set/get initial condition
    public double InitialCondition
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

    // Property to set/get time T
    public double Expiry
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

public class CEV : ISde
{ // CEV model

    private double mu;   // r
    private double vol;  // Constant volatility
    private double d;    // Constant dividend yield
    private double ic;   // Initial condition
    private double exp;  // Expiry
    private double b;    // Beta

    public CEV(double driftCoefficient, double diffusionCoefficient, double dividendYield, double initialCondition,
               double expiry, double beta)
    {
        mu = driftCoefficient;
        b = beta;
        ic = initialCondition;
        vol = diffusionCoefficient * Math.Pow(ic, 1.0 - b);
        d = dividendYield;
        exp = expiry;
    }

    public double Drift(double x, double t) { return (mu - d) * x; }
    public double Diffusion(double x, double t) { return vol * Math.Pow(x, b); }

    public double DriftCorrected(double x, double t, double B)
    {
        //return drift(X, t) - B * diffusion(X, t) * diffusionDerivative(X, t);
        return Drift(x, t) - B * Diffusion(x, t) * DiffusionDerivative(x, t);
    }

    public double DiffusionDerivative(double x, double t)
    {
        if (b > 1.0)
        {
            return vol * b * Math.Pow(x, b - 1.0);
        }
        else
        {
            return vol * b / Math.Pow(x, 1.0 - b);
        }


    }

    public double InitialCondition
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

    public double Expiry
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