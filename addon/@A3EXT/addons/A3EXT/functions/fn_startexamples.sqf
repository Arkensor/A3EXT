/**********************************************************************************************************************\

    DESCRIPTION: A3EXT - an extension framework for ArmA 3

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  01.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Arkensor. All rights reserved!

\**********************************************************************************************************************/

[] spawn
{
    sleep 5;

    arr = [];

    _time = diag_tickTime;

    for "_i" from 0 to 25 do
    {
        _test = [ "this is some sample data ...", 1 ] call A3EXT_fnc_request;
        arr pushBack _test;
    };

    diag_log format[ "FINISHED IN %1", diag_tickTime - _time ];

    diag_log arr;
};

/*
[] spawn
{
    sleep 5;

    arr = [];

    for "_i" from 0 to 1300 do
    {
        [] spawn
        {
            _test = [ "this is some sample data ...", 1 ] call A3EXT_fnc_request;
            arr pushBack _test;
        };
    };

    [] spawn
    {
        _time = diag_tickTime;
        waitUntil { count arr > 1300 };

        diag_log format[ "FINISHED IN %1", diag_tickTime - _time ];

        diag_log arr;
    };
};
*/