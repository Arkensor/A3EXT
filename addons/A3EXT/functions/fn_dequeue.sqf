/**********************************************************************************************************************\

    DESCRIPTION: A3EXT - an extension framework for ArmA 3

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  01.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/

params
[
	[ "_ticketID", -1, [0] ]
];

if ( _ticketID isEqualTo -1 ) exitWith
{
    diag_log "A call to a non existing ticket was performed. Check of possible errors and data loss!";
};

private _stringTicket = str _ticketID;

waitUntil { !isNil { A3EXT_NS getVariable _stringTicket } };

private _result = A3EXT_NS getVariable _stringTicket;

A3EXT_NS setVariable [ _stringTicket, nil ];

_result;