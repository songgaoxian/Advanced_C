// Mediator.cs
//
// The centarl mediating SUD that communicates with its external
// systems that have been created by the Builder.
//
// (C) Datasim Education BV 2014-2016
//

using System;
using System.Collections.Generic;
using System.Linq;


 // Events
public delegate void PathEvent<T> (ref T[] path);   // Send a path array
public delegate void EndOfSimulation<T>();          // No more paths

// Events to MIS system
public delegate void NotifyMIS(int n);

public class MCMediator
{
    // Three main components
    private ISde sde;
    private FdmBase fdm;
    private IRng rng;
   
    // Other MC-related data 
    int NSim;
    private double[] res;       // Generated path per simulation

    // Event notification
    private event PathEvent<double> path;            // Signal to the Pricers
    private event EndOfSimulation<double> finish;    // Signals that all paths are complete

    // MIS notification
    private event NotifyMIS mis;
       
    public MCMediator(Tuple<ISde, FdmBase, IRng> parts, PathEvent<double> optionPaths,
                        EndOfSimulation<double> finishOptions,  int numberSimulations)
    {
        sde = parts.Item1;
        fdm = parts.Item2;
        rng = parts.Item3;

        // Define slots for path information
        path = optionPaths;
        // Signal end of simulation
        finish = finishOptions;

        NSim = numberSimulations;
        res = new double[fdm.NT+1];

        mis = i => { if ((i / 10000) * 10000 == i) Console.WriteLine("Iteration # {0}", i); };
    }

    public void start()
    { // Main event loop for path generation

        double VOld, VNew;
     
        for (int i = 1; i <= NSim; ++i)
        { // Calculate a path at each iteration

         //   if ((i / 5000) * 5000 == i)
            { // Give status after a given numbers of iterations

                mis(i);
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
