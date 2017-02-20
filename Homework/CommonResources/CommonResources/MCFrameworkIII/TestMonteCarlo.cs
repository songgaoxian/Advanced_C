// TestMonteCarlo.cs
//
// (C) Datasim Education BV 2014-2016
//

using System;
using System.Collections.Generic;
using System.Diagnostics; // For StopWatch

// Main program etc.
public class MCPricerApplication
    {
  
        // Simple data factory
        // r, div, sig, T, K, IC, NSim
        // 1   2    3   4  5   6   7    (Item*)
        public static Tuple<double, double, double, double, double, double, int> GetOptionData()
        {

        // Test A, zero dividend
       /*    double r = 0.08;
           double div = 0.0;
           double sig = 0.3;
           double T = 0.25;
           double K = 65.0;
           double S_0 = 60.0;*/

        // Test B, non-zero dividend
        /*   double r = 0.0;
           double div = 0.0022;
           double sig = 0.8;
           double T = 10.0;
           double K = 1.0;
           double S_0 = 1.0;*/

        // Test C, for Asian option
        double r = 0.05;
        double div = 0.0;
        double sig = 0.2;
        double T = 1.0;
        double K = 100;
        double S_0 = 100.0;

        int NSim = 1000000;
            Console.Write("How many NSim? ");
            NSim = Convert.ToInt32(Console.ReadLine());
        // v2 named vars
            var result = new Tuple<double, double, double, double, double, double, int>
                                (r, div, sig, T, K, S_0, NSim);

            // r, div, sig, T, K, IC, NSim
            // 1   2    3   4  5   6   7    (Item*)
            Console.WriteLine("r {0}: ", r);
            Console.WriteLine("q/d {0}: ", div);
            Console.WriteLine("sig {0}: ", sig);
            Console.WriteLine("T {0}: ", T);
            Console.WriteLine("K {0}: ", K);
            Console.WriteLine("S_0/IC {0}: ", S_0);
            Console.WriteLine("NSim {0}: ", NSim);

            return result;
        }

    public static void print(Tuple<double, double, double, double, double, double, int> optionData)
    {

        // r, div, sig, T, K, IC, NSim
        // 1   2    3   4  5   6   7    (Item*)
        Console.WriteLine("r {0}: ", optionData.Item1);
        Console.WriteLine("q/d {0}: ", optionData.Item2);
        Console.WriteLine("sig {0}: ", optionData.Item3);
        Console.WriteLine("T {0}: ", optionData.Item4);
        Console.WriteLine("K {0}: ", optionData.Item5);
        Console.WriteLine("S_0/IC {0}: ", optionData.Item6);
        Console.WriteLine("NSim {0}: ", optionData.Item7);
    }

    public static void Main()
    {

        // Get data from Source
        Tuple<double, double, double, double, double, double, int> data = GetOptionData();

        Console.WriteLine("Choose builder");
        // Choose which builder to use
     //   int choice = 2;
      //  Tuple<ISde, FdmBase, IRng> parts = BuilderFactory.ChooseBuilder(choice, data);
        MCBuilder<ISde, FdmBase, IRng> builder = new MCBuilder<ISde, FdmBase, IRng>(data);
        var parts = builder.Parts();
        var path = builder.GetPaths();
        var finish = builder.GetEnd();
        MCMediator mcp = new MCMediator(parts, path, finish, data.Item7);
        mcp.start();

        // Nestes tuples
    /*    var t = Tuple.Create(1, 1);
        var t2 = Tuple.Create(t,t);
        Console.WriteLine(t2.Item1.Item1);*/
    }
}