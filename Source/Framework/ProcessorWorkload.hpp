/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  31.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/
#ifndef A3DB_WORKLOAD_HPP
#define A3DB_WORKLOAD_HPP

#include "DataTypes.hpp"

#include <string>
#include <vector>

namespace A3
{
namespace Extension
{
namespace Processor
{

class CProcessorWorkload
{
public:
    CProcessorWorkload( const std::string & rstrID,
                        const A3::DataTypes::TStrVector & oArguments );

    virtual ~CProcessorWorkload();

    std::string m_strID;
    A3::DataTypes::TStrVector m_oArguments;
};

}; // end namespace CProcessor
}; // end namespace Extension
}; // end namespace A3

#endif //A3DB_WORKLOAD_HPP
