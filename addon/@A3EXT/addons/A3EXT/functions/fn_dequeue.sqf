/**********************************************************************************************************************\

    DESCRIPTION: A3EXT - Waiting for the data to be returned

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
    [ "_ticketID", -1, [ 0 ] ]
];

if ( _ticketID isEqualTo -1 ) exitWith
{
    diag_log "A3EXT: A call to a non existing ticket was performed. Check of possible errors and data loss!";
};

private _stringTicket = str _ticketID;

waitUntil { !isNil { A3EXT_NS getVariable _stringTicket } };

private _result = A3EXT_NS getVariable _stringTicket;

A3EXT_NS setVariable [ _stringTicket, nil ];

_result;