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

g_nRuns = 3000;
g_oResults = [];

diag_log "started ...";

[] spawn
{
    for "_i" from 1 to g_nRuns do
    {
        [] spawn
        {
            private _result = [ "this is some sample data ...", 1 ] call A3EXT_fnc_request;
            g_oResults pushBack _result;
        };
    };
};

[] spawn
{
    _time = diag_tickTime;

    waitUntil { ( count g_oResults ) >= g_nRuns };

    diag_log format[ "A3EXT - Examples: Processed %1 request(s) in %2 seconds(s) - %3 seconds per request.", ( count g_oResults ), ( diag_tickTime - _time ), ( diag_tickTime - _time ) / g_nRuns ];

    diag_log format[ "A3EXT - Examples: Results: %1", g_oResults ];
};