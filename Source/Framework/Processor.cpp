/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  31.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/
#include "Processor.hpp"

#include <iostream>

namespace A3
{
namespace Extension
{
namespace Processor
{

CProcessor::CProcessor()
{
    m_bActive = false;
}

CProcessor::~CProcessor()
{
}

void
CProcessor::start( std::function< std::vector< CProcessorResult >( CProcessorWorkload ) > oFunction ,
                   A3::DataTypes::int8 nThreads )
{
    if ( m_bActive )
    {
        return;
    }

    m_bActive = true;

    auto nAvailableThreads = ( A3::DataTypes::int8 ) std::thread::hardware_concurrency();

    if ( ( nThreads == -1 ) || ( nThreads > nAvailableThreads ) )
    {
        nThreads = nAvailableThreads;
    }


    for ( int nThread = 0; nThread < nThreads; ++nThread )
    {
        std::thread oThread( [=] { run( oFunction ); } );

        oThread.detach();
    }
}

void
CProcessor::Add( CProcessorWorkload r )
{
    oWorkloadQueue.push( r ); //Todo check if we can make this copyless with references though all the processing
}

bool
CProcessor::try_get_result( CProcessorResult & oWorkload )
{
    return oResultQueue.try_pop_result( oWorkload );
}

bool
CProcessor::try_get_results( std::vector<CProcessorResult> & oWorkload,
                             A3::DataTypes::uint64 nCurrentSize,
                             A3::DataTypes::uint64 nMaxSize )
{
    return oResultQueue.try_pop_results( oWorkload, nCurrentSize, nMaxSize );
}

size_t
CProcessor::request_size()
{
    return oResultQueue.size();
}

size_t
CProcessor::result_size()
{
    return oResultQueue.size();
}

void
CProcessor::run( std::function< std::vector< CProcessorResult >( CProcessorWorkload ) > oFunction )
{
    while ( m_bActive )
    {
        CProcessorWorkload oWorkLoad = oWorkloadQueue.pop();

        std::vector< CProcessorResult > oResults = oFunction( oWorkLoad );

        for ( CProcessorResult result : oResults )
        {
            oResultQueue.push( result );
        }
    }
}

}; // end namespace Processor
}; // end namespace Extension
}; // end namespace A3