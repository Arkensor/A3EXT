/**********************************************************************************************************************\

    DESCRIPTION: A3EXT - an extension framework for ArmA 3

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  01.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/

[] spawn
{
    A3EXT_NS = createLocation [ "Hill", [ -1000, -1000, 0 ], 0, 0 ];

    A3EXT_NS setVariable [ "A3EXT_BASE_FRAMETICK", 5 ];
    A3EXT_NS setVariable [ "TICKET_ID", 0 ];
    A3EXT_NS setVariable [ "A3EXT_INPUT_QUEUE", [] ];

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
                    _buffer = "";
                };

                true
            } count _data;
        };
    };

    for "_i" from 0 to 1 step 0  do
    {
        if ( !( ( count ( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] ) ) isEqualTo 0 ) ) then
        {
			private _data = [];

			isNil
			{
				{
					_data pushBack _x;

					private _arr = ( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] );

                    if( ( count _arr ) isEqualTo 0 ) exitWith {};

					_arr deleteAt 0;

                    A3EXT_NS setVariable [ "A3EXT_INPUT_QUEUE", _arr ];

                    if ( _forEachIndex isEqualTo 1023 ) exitWith {};

				} forEach +( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] );
			};

            private _result = "A3EXT" callExtension [ "BULK", _data ];

			[ _result ] call _parseResult;
        }
        else
        {
             private _result = "A3EXT" callExtension [ "CHECK", [] ];

            [ _result ] call _parseResult;

            sleep ( ( A3EXT_NS getVariable [ "A3EXT_BASE_FRAMETICK", 5 ] ) / diag_fps );
        };
    };
};
