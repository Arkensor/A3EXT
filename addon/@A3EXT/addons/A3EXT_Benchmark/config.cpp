/**********************************************************************************************************************\

    DESCRIPTION: A3EXT - An extension framework for ArmA 3

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  01.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018
    Paul L. (https://github.com/Arkensor)
    Ollie W. (https://github.com/BoGuu)
    All rights reserved!

\**********************************************************************************************************************/

class CfgPatches
{
    class A3EXT_Benchmark
    {
		requiredVersion = 1.67;
		requiredAddons[] = { "A3EXT" };
        fileName = "A3EXT_Benchmark.pbo";
        author = "Arkensor";
    };
};

class CfgFunctions
{
    class A3EXT_Benchmark
    {
        tag = "A3EXT_Benchmark";

        class Functions 
        {
            file = "\A3EXT_Benchmark\functions";
			class benchmark { postInit = 1; headerType = -1; };
        };
    };
};