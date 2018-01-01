/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  31.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/
#ifndef A3DB_PROCESSOR_HPP
#define A3DB_PROCESSOR_HPP

#include "ProcessorQueue.hpp"
#include "ProcessorWorkload.hpp"
#include "ProcessorResult.hpp"

namespace A3
{
namespace Extension
{
namespace Processor
{

class CProcessor
{
public:
    CProcessor();
    virtual ~CProcessor();

    void
    start( std::function< std::vector< CProcessorResult >( CProcessorWorkload ) > oFunction ,
           A3::DataTypes::int8 nThreads );

    void
    Add( CProcessorWorkload oWorkload );

    bool
    try_get_result( CProcessorResult & oWorkload );

    bool
    try_get_results( std::vector<CProcessorResult> & oWorkload,
                     A3::DataTypes::uint64 nCurrentSize,
                     A3::DataTypes::uint64 nMaxSize );

    size_t
    request_size();

    size_t
    result_size();

    bool m_bActive;

protected:
    CProcessorQueue< CProcessorResult > oResultQueue;
    CProcessorQueue< CProcessorWorkload > oWorkloadQueue;

protected:
    void run( std::function< std::vector< CProcessorResult >( CProcessorWorkload ) > oFunction );
};

}; // end namespace Processor
}; // end namespace Extension
}; // end namespace A3

#endif //A3DB_PROCESSOR_HPP
