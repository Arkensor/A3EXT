/**********************************************************************************************************************\

    DESCRIPTION: Adds an element to the queue. Returns a ticket number is returned that will be used
                 to fetch the results. If no results are expected the ticket number will return -1

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  01.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018
    Paul L. (https://github.com/Arkensor)
    Ollie W. (https://github.com/BoGuu)
    All rights reserved!

\**********************************************************************************************************************/

params
[
    [ "_data", "", [ "", 0 ] ],
    [ "_return", 1, [ 0 ] ]
];

private "_ticketID";

if( _return isEqualTo 1 ) then
{
    isNil
    {
        _ticketID = ( A3EXT_NS getVariable [ "TICKET_ID", 0 ] );
        A3EXT_NS setVariable [ "TICKET_ID", ( _ticketID + 1 ) ];

        private _arr = ( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] );
        _arr pushBack format ["%1%2%3", _ticketID, toString [ 29 ], _data];
        A3EXT_NS setVariable [ "A3EXT_INPUT_QUEUE", _arr ];
    };

    _ticketID;
}
else
{
    isNil
    {
        private _arr = ( A3EXT_NS getVariable [ "A3EXT_INPUT_QUEUE", [] ] );
        _arr pushBack format ["%1%2%3", -1, toString [ 29 ], _data];
        A3EXT_NS setVariable [ "A3EXT_INPUT_QUEUE", _arr ];
    };

    -1;
};