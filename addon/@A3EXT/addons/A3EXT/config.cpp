/**********************************************************************************************************************\

    DESCRIPTION: A3EXT - An extension framework for ArmA 3

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  01.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Arkensor. All rights reserved!

\**********************************************************************************************************************/

class CfgPatches
{
	class A3EXT
	{
		requiredVersion = 0.1;
		fileName = "A3EXT.pbo";
		author = "Arkensor";
	};
};

class CfgFunctions
{
	class A3EXT
	{
		tag = "A3EXT";

		class Functions 
		{
			file = "\A3EXT\functions";

			class queue { preInit = 1; headerType = -1; };
			class enqueue { headerType = -1; };
			class dequeue { headerType = -1; };
			class query { headerType = -1; };

			class startexamples { postInit = 1; headerType = -1; };
		};
	};
};