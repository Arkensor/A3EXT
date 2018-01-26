/**********************************************************************************************************************\

    DESCRIPTION: Queue that runs on the server handling input and output into/from the extension

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  01.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018
    Paul L. (https://github.com/Arkensor)
    Ollie W. (https://github.com/BoGuu)
    All rights reserved!

\**********************************************************************************************************************/

[] spawn
{
    if( !isNil "A3EXT_NS" ) exitWith
    {
        diag_log "ERROR: A3EXT could not be loaded, as a different extension used the same namespace.";
    };

    A3EXT_NS = createLocation [ "Hill", [ -1000, -1000, 0 ], 0, 0 ];

    A3EXT_NS setVariable [ "A3EXT_BASE_FRAMETICK", 5 ];
    A3EXT_NS setVariable [ "TICKET_ID", 0 ];
    A3EXT_NS setVariable [ "A3EXT_INPUT_QUEUE", [] ];
    A3EXT_NS setVariable [ "RESULTS_EXPECTED", 0 ];

    private _buffer = "";

    private _parseResult =
    {
        params
        [
            ["_data", [], [[]]]
        ];

        if ( _data isEqualTo [] ) exitWith {};

        _data = parseSimpleArray ( _data select 0 );

        if ( !( _data isEqualTo [] ) ) then
        {
            {
                _buffer = _buffer + ( _x select 2 );

                private _currentIndex = _x select 1;

                if ( _currentIndex isEqualTo 0 || { _currentIndex isEqualTo -1 } ) then
                {
                    A3EXT_NS setVariable [ str (_x select 0), _buffer ];

                    private _results_exptected = A3EXT_NS getVariable [ "RESULTS_EXPECTED", 0 ];

                    if( _results_exptected < 0 ) then
                    {
                        _results_exptected = 0;
                    };

                    A3EXT_NS setVariable [ "RESULTS_EXPECTED", _results_exptected ];

                    _buffer = "";
                };

                true
            } count _data;
        };
    };

    for "_i" from 0 to 1 step 0  do
    {
        if !( count( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] ) isEqualTo 0 ) then
        {
            private _data = [];

            isNil
            {
                {
                    _data pushBack _x;

                    private _arr = ( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] );

                    if( count( _arr ) isEqualTo 0 ) exitWith {};

                    _arr deleteAt 0;

                    A3EXT_NS setVariable [ "A3EXT_INPUT_QUEUE", _arr ];

                    A3EXT_NS setVariable [ "RESULTS_EXPECTED", ( A3EXT_NS getVariable [ "RESULTS_EXPECTED", 0 ] ) + 1 ];

                    if ( _forEachIndex isEqualTo 1023 ) exitWith {};

                } forEach +( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] );
            };

            private _result = "A3EXT" callExtension [ "BULK", _data ];

            //THIS SHOULD ONLY BE USED FOR DEBUGGING!!!
            g_nExtensionCalls = g_nExtensionCalls + 1;

            [ _result ] call _parseResult;
        }
        else
        {
            if !( A3EXT_NS getVariable [ "RESULTS_EXPECTED", 0 ] isEqualTo 0 ) then
            {
                private _result = "A3EXT" callExtension [ "CHECK", [] ];

                //THIS SHOULD ONLY BE USED FOR DEBUGGING!!!
                g_nExtensionCalls = g_nExtensionCalls + 1;

                [ _result ] call _parseResult;
            };

            sleep ( ( A3EXT_NS getVariable [ "A3EXT_BASE_FRAMETICK", 5 ] ) / diag_fps );
        };
    };
};