/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  27.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/
#ifndef A3DB_EXTENSIONBASE_HPP
#define A3DB_EXTENSIONBASE_HPP

#include "../Configuration.hpp"

#include "DataTypes.hpp"
#include "Processor.hpp"

//Required thridparty includes
#include "../ThridParty/spdlog/spdlog.h"

#define LOG_ALL( level, message) \
spdlog::apply_all([&](std::shared_ptr<spdlog::logger> oLogger){oLogger->log( level, message ); oLogger->flush();});

#define LOG_ALL_FORMAT( level, message, ...) \
spdlog::apply_all([&](std::shared_ptr<spdlog::logger> oLogger){oLogger->log( level, message, __VA_ARGS__); oLogger->flush();});

namespace loglevel = spdlog::level;

//Optional includes
#ifdef _EXTENSION_USE_START_PARAMETERS
    #include "../Framework/StartParameterHandler.hpp"
#endif

#ifdef _EXTENSION_USE_INI_CONFIGURATION
    #include "inih/INIReader.hpp"
#endif

//System includes
#include <string>
#include <memory>

namespace A3
{
namespace Extension
{

class CExtensionBase
{
public:
    CExtensionBase( std::string strName, std::string strVersion );
    virtual ~CExtensionBase();

    int
    call( char * pstrOutput, int nOutputSize, const char *pstrFunction, const char **pArguments, int nArguments );

public:
    std::string m_strName;
    std::string m_strVersion;
    A3::DataTypes::int64 m_nMaxOutputSize;
    A3::DataTypes::EExtensionState m_eExtensionState;
    std::string m_strExtensionStateDescription;

protected:
    std::shared_ptr< A3::Extension::Processor::CProcessor > m_poProcessor;

#ifdef _EXTENSION_USE_CONSOLE_LOGGING
    FILE *m_oStream;
    std::shared_ptr< spdlog::logger > m_poConsoleLogger;
#endif

#ifdef _EXTENSION_USE_FILE_DEFAULT_LOGGER
    std::shared_ptr< spdlog::logger > m_poFileLogger;
#endif

#ifdef _EXTENSION_USE_START_PARAMETERS
    std::shared_ptr< A3::Extension::StartParameter::CStartParameterHandler > m_poStartParameterHandler;
#endif

#ifdef _EXTENSION_USE_INI_CONFIGURATION
    std::shared_ptr< INIReader > m_poConfiguration;
#endif

protected:
    std::string
    GetDateTime( std::string strFormat );

    std::vector< A3::Extension::Processor::CProcessorResult >
    Worker( A3::Extension::Processor::CProcessorWorkload oWorkload );

    std::string
    Execute( A3::Extension::Processor::CProcessorWorkload oWorkload );

    void
    addRequest( const char *pstrExtensionFunction, const char **pExtensionData, int nExtensionDataCount );

    bool
    checkResults( std::vector< A3::Extension::Processor::CProcessorResult > & roResults, A3::DataTypes::uint64 nCurrentSize );

    std::vector< std::string >
    delimiter_split( const std::string & rstrData, char cDelimiter );

    std::string
    result_to_string( A3::Extension::Processor::CProcessorResult & roResult );

    std::vector< A3::Extension::Processor::CProcessorResult >
    splitIntoMultipart( std::string strResult, A3::Extension::Processor::CProcessorWorkload & roWorkload );
};

}; // end namespace Extension
}; // end namespace A3

#endif //A3DB_EXTENSIONBASE_HPP