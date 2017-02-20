Project MC:
Intro:
MC is composed of the following modules:
OptionData, RNG, SDE, FDM, Pricer, Builder, DefaultBuilder & Builder Factory, Mediator and StopWatch

Acknowledgement: 
This project is developed by referring to MC application in C# as given in common resources.

Description:
OptionData is responsible for input data. It contains the parameters for an option to be priced, including drift, volatility, expiry time, 
Payoff and Discount functions, etc;

RNG is responsible for generating random variables. It contains three derived classes which can generate standard normal random variables
in different ways, i.e. using the <random> library (LibRandom), using PolarMarsaglia and BoxMuller.

SDE is responsible for defining the stochastic equation. It contains three derived classes. GBM implements the standard Geometric Brownion
Motion. CustomizedGBM implements a variation of stand GBM by letting the drift and volatility be able to vary w.r.t time-to-maturity,
instead of being constant, which is just used to illustrate the flexibility that any scheme of SDE can be implemented. CEV implements the CEV
Model.

FDM is responsible for providing the scheme to calculate each step of the price path based on the defined SDE. Three versions of FDM are 
provided in derived classes, i.e. EulerFdm, MilsteinFdm and ModifiedPredictorCorrectorFdm.

Pricer is responsible for computing the payoff with given price path of underlying asset and getting the simulated price. Three different
types of pricers are provided in derived classes, i.e EuropeanPricer, AssianPricer and BarrierPricer.

Builder, implemented in MCBuilder class, is responsible for giving the end-user the freedom to choose customized types of RNG, SDE and FDM,
and then create these parts in a tuple, which is returned.
DefaultBuilder always returns a standardized setting of RNG, SDE and FDM in tuple.
Builder Factory lets user choose which Builder to use to get the parts for MC.

Mediator is responsible for carrying out the MC process.It uses all other components to create a price path of underlying asset and triggers
the pricers attached to path signal to process each path and uses the finish signal to show that simulation task is complete.

StopWatch is embedded in Mediator to monitor the running time for each thread running mediator.start().

Main is responsible for testing the application. I use three sets of options and each option is associated with three pricers (European, Assian
and Barrier). Three mediators are created with each option and they are executed with thread_group.

Note: differences between this project and the sample MC project in C#

1, Input data is aggregated in struct OptionData;
2, Each mediator is associated with an id and the running time of each mediator is displayed with its id;
3, The number of simulation is set to long long, which can be very large to increate its accuracy.





