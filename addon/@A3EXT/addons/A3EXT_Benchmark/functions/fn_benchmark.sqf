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

waitUntil{ !isNil "A3EXT_NS" };

diag_log "A3EXT - Benchmark started ...";

g_nCallingThreads = 1000; //Simulating n requests from different sources like remoteexec on your server which all run in parallel
g_nCallsEach = 10; //How many calls does each of the threads do for the simulation

g_oResults = [];
g_nExtensionCalls = 0;

[] spawn
{
    _time = diag_tickTime;

    waitUntil { ( count g_oResults ) >= ( g_nCallingThreads * g_nCallsEach ) };

    diag_log format[ "%1 request(s) (%2 threads with %3 requests each) in %4 seconds(s) - %5 seconds per request -> The extension was called %6 times.",
                     ( count g_oResults ),
                     g_nCallingThreads,
                     g_nCallsEach,
                     ( diag_tickTime - _time ),
                     ( diag_tickTime - _time ) / ( g_nCallingThreads * g_nCallsEach ),
                     g_nExtensionCalls ];

    //diag_log format[ "A3EXT - Examples: Results: %1", g_oResults ];
};

for "_i" from 1 to g_nCallingThreads do
{
    [] spawn
    {
        for "_i" from 1 to g_nCallsEach do
        {
            private _result = [ "this is some sample data ...", 1 ] call A3EXT_fnc_request;
            g_oResults pushBack _result;
        };
    };
};