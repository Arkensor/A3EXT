/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  31.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/
#include "ProcessorWorkload.hpp"

namespace A3
{
namespace Extension
{
namespace Processor
{

CProcessorWorkload::CProcessorWorkload( const std::string & rstrID,
                                        const A3::DataTypes::TStrVector & oArguments )
    : m_strID( rstrID )
    , m_oArguments( oArguments )
{
}

CProcessorWorkload::~CProcessorWorkload()
{
}

}; // end namespace CProcessor
}; // end namespace Extension
}; // end namespace A3