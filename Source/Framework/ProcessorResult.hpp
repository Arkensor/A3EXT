/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  31.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/
#ifndef A3DB_PROCESSORRESULT_HPP
#define A3DB_PROCESSORRESULT_HPP

#include "../Configuration.hpp"
#include "DataTypes.hpp"

#include <string>

namespace A3
{
namespace Extension
{
namespace Processor
{

class CProcessorResult
{
public:
    CProcessorResult( const std::string & rstrID,
                      const std::string & rstrData );

    CProcessorResult(const std::string & rstrID,
                     const std::string & rstrData,
                     bool bIsMultiPart ,
                     A3::DataTypes::uint64 nPartIndex );

    virtual ~CProcessorResult();

    std::string m_strID;
    std::string m_strData;
    bool m_bIsMultiPart;
    A3::DataTypes::uint64 m_nPartIndex;
};

}; // end namespace CProcessor
}; // end namespace Extension
}; // end namespace A3

#endif //A3DB_PROCESSORRESULT_HPP