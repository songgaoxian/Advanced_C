// Rng.cs
//
// Random number generators. They are meaant to show design
// features mainly.
//
// (C) Datasim Education BV 2014-2016
//

using System;
using System.Security.Cryptography;
using MathNet.Numerics.Distributions;
using MathNet.Numerics.Random;

public interface IRng
{
    double GenerateRn();
}

public abstract class Rng : IRng
{
    public abstract double GenerateRn();
}


public class PolarMarsagliaNet : Rng
{
    private Random rand;

    public PolarMarsagliaNet() {  rand = new Random(((int)DateTime.Now.Ticks & 0x0000FFFF)); } 
    
    public override double GenerateRn()
    {

        double u, v, S;

        do
        {
            u = 2.0 * rand.NextDouble() - 1.0;
            v = 2.0 * rand.NextDouble() - 1.0;
            S = u * u + v * v;
        }
        while (S > 1.0 || S <= 0.0);

        double fac = Math.Sqrt(-2.0 * Math.Log(S) / S);
        return u * fac;
    }
}

public class MyMersenneTwister : Rng
{ // Math.Net 19937

      
    /*
// sample a single value from a standard distribution
double a = Normal.Sample(0.0, 1.0);

// sample using a custom random number generator
double b = Normal.Sample(new MersenneTwister(), 0.0, 1.0);

// sample a large number of values in one go
double[] c = new double[100000];
Normal.Samples(c, 0.0, 1.0);*/

    public MyMersenneTwister() { }

    public override double GenerateRn()
    {
        double b = Normal.Sample(new MersenneTwister(), 0.0, 1.0);
        return b;
    }
}


public class BoxMullerNet : Rng
{
    private Random rand;

    public BoxMullerNet() { rand = new Random(((int)DateTime.Now.Ticks & 0x0000FFFF)); } // Seed is from system clock
    double U1, U2;
  
    public override double GenerateRn()
    {
        // U1 and U2 should be independent uniform random numbers
        do
        {
            U1 = rand.NextDouble();   // In interval [0,1)
            U2 = rand.NextDouble();  // In interval [0,1)
        }
        while (U1 <= 0.0);

        // Box-Muller method
        return Math.Sqrt(-2.0 * Math.Log(U1)) * Math.Cos(2.0 * 3.1415159 * U2);
    }
}



public class BoxMullerCrypto : Rng
{
    private System.Security.Cryptography.RandomNumberGenerator rand;
    private byte[] random;
    private double min_ = 0;
    private double max_ = 0xFFFFFFFF;
    private UInt32 rng_;
    private double U1, U2;
 
    public BoxMullerCrypto() { rand = System.Security.Cryptography.RandomNumberGenerator.Create(); random = new byte[4]; } 

    double NextDouble()
    {
  
         rand.GetBytes(random);
         rng_ = BitConverter.ToUInt32(random, 0);
        
         return (rng_ - min_ ) / (max_ - min_ + 1);
    }

    public override double GenerateRn()
    {
        // U1 and U2 should be independent uniform random numbers
        U1 = NextDouble();   // In interval [0,1)
        U2 = NextDouble();  // In interval [0,1)

        // Box-Muller method
        return Math.Sqrt(-2.0 * Math.Log(U1)) * Math.Cos(2.0 * 3.1415159 * U2);
    }
}


public delegate double RngDelegate();

public class BoxMullerII : Rng
{ // RNG with embedded delegate

    private RngDelegate rand;
    private double U1, U2;

    public BoxMullerII(RngDelegate randomGenerator){ rand = randomGenerator; } 

    public override double GenerateRn()
    {
        // U1 and U2 should be independent uniform random numbers
        U1 = rand();   // In interval [0,1)
        U2 = rand();   // In interval [0,1)
   
        // Box-Muller method
        return Math.Sqrt(-2.0 * Math.Log(U1)) * Math.Cos(2.0 * 3.1415159 * U2);
    }
}