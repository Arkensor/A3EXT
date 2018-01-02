/**********************************************************************************************************************\

    DESCRIPTION: Workloads, parsed from the ArmA input

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  31.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Arkensor. All rights reserved!

\**********************************************************************************************************************/
#include "ProcessorWorkload.hpp"

namespace A3
{
namespace Extension
{
namespace Processor
{

CProcessorWorkload::CProcessorWorkload( const std::string & rstrID,
                                        const std::string & rstrFunction,
                                        const A3::DataTypes::TStrVector & roArguments )
    : m_strID( rstrID )
    , m_strFunction( rstrFunction )
    , m_oArguments( roArguments )
{
}

CProcessorWorkload::~CProcessorWorkload()
{
}

}; // end namespace CProcessor
}; // end namespace Extension
}; // end namespace A3