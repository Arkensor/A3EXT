/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  27.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/

#include "ExtensionBase.hpp"

#include <filesystem>
#include <sstream>

namespace A3
{
namespace Extension
{

CExtensionBase::CExtensionBase( std::string strName, std::string strVersion )
    : m_strName( strName )
    , m_strVersion( strVersion )
    , m_eExtensionState( A3::DataTypes::EExtensionState::e_Initialized )
    , m_strExtensionStateDescription( "" )
    , m_nMaxOutputSize( -1 )
{
#ifdef _EXTENSION_USE_CONSOLE_LOGGING
    AllocConsole();
    std::string strConsoleTitle = m_strName + " " + m_strVersion;

    //Set console title
    SetConsoleTitle( TEXT( strConsoleTitle.c_str() ) );

    //Disable key combinations
    SetConsoleCtrlHandler( NULL, true );

    //Disable closing button
    HWND oConsoleModule = ::GetConsoleWindow();
    if ( oConsoleModule )
    {
        HMENU oMenuModule = ::GetSystemMenu( oConsoleModule, FALSE );
        if ( oMenuModule )
        {
            DeleteMenu( oMenuModule, SC_CLOSE, MF_BYCOMMAND );
        }
    }

    freopen_s( &m_oStream, "CONOUT$", "w", stdout );

    auto oConsoleLogger = spdlog::stdout_color_mt( "console" );
    m_poConsoleLogger.swap( oConsoleLogger );

    //Collect all logs not matter the level for this.
    m_poConsoleLogger->set_level( loglevel::trace );

    m_poConsoleLogger->set_pattern( "[%Y-%m-%d %H:%M:%S] %v" );
#endif

#ifdef _EXTENSION_USE_FILE_DEFAULT_LOGGER
    std::string strLogLocation = std::experimental::filesystem::current_path().string() + "/@" + m_strName + "/Logs";

    std::string strLogName = fmt::format( "{0}/{1}_{2}.log", strLogLocation, m_strName, GetDateTime( "%Y-%m-%d_%I-%M-%S" ) );

    std::experimental::filesystem::create_directories( strLogLocation );

    auto oFileLogger = spdlog::basic_logger_mt( "general", strLogName );
    m_poFileLogger.swap( oFileLogger );

    //Collect all logs not matter the level for this.
    m_poFileLogger->set_level( loglevel::trace );

    m_poFileLogger->set_pattern( "[%Y-%m-%d %H:%M:%S] %v" );
#endif

#ifdef _EXTENSION_USE_START_PARAMETERS
    auto poParameterHandler = std::make_shared< A3::Extension::StartParameter::CStartParameterHandler >();
    m_poStartParameterHandler.swap( poParameterHandler );
#endif

#ifdef _EXTENSION_USE_INI_CONFIGURATION

    std::string strConfigurationPath;

    //Find the configuration.ini path in the startup parameters
#ifdef _EXTENSION_USE_START_PARAMETERS
    std::string strExtensionLower = _EXTENSION_NAME;
    std::transform( strExtensionLower.begin(), strExtensionLower.end(), strExtensionLower.begin(), ::tolower );
    if( m_poStartParameterHandler->m_oStartParamters.count( strExtensionLower ) > 0 )
    {
        strConfigurationPath = m_poStartParameterHandler->m_oStartParamters.at( strExtensionLower );
    }
#endif

    //Find the configuration file
    if( strConfigurationPath.empty() )
    {
        std::string strConfigName;

#ifdef _EXTENSION_CONFIGFILE_NAME
        strConfigName = _EXTENSION_CONFIGFILE_NAME;
#else
        strConfigName = _EXTENSION_NAME;
        strConfigName += ".ini";
#endif

        typedef std::experimental::filesystem::recursive_directory_iterator TRecursiveIterator;

        TRecursiveIterator oEndIt;

        for ( TRecursiveIterator oDirIt( std::experimental::filesystem::current_path() ); oDirIt != oEndIt; ++oDirIt )
        {
            const std::experimental::filesystem::path oFile = ( *oDirIt );

            if ( !std::experimental::filesystem::is_directory( oFile ) &&
                 !std::experimental::filesystem::is_socket( oFile )
                    )
            {
                if ( oFile.string().substr( oFile.string().size() - strConfigName.size() ) == strConfigName )
                {
                    strConfigurationPath = oFile.string();
                }
            }
        }
    }

    if( strConfigurationPath.empty() )
    {
        throw std::runtime_error( "Configuration file could not be located." );
    }

    auto oConfigReader = std::make_shared< INIReader >( strConfigurationPath );
    m_poConfiguration.swap( oConfigReader );
#endif

    //Setup mutlithreaded processing
    auto oProcessor = std::make_shared< A3::Extension::Processor::CProcessor >();
    m_poProcessor.swap( oProcessor );
}

CExtensionBase::~CExtensionBase()
{
}

std::string
CExtensionBase::GetDateTime( std::string strFormat )
{
    time_t oRawTime;
    struct tm * oTimeInfo;
    char buffer[ 256 ];

    time ( &oRawTime );
    oTimeInfo = localtime( &oRawTime );

    strftime( buffer, sizeof( buffer ), strFormat.c_str(), oTimeInfo );

    return std::string( buffer );
}

int
CExtensionBase::call( char * pstrOutput, int nOutputSize, const char *pstrFunction, const char **pArguments, int nArguments )
{
    --nOutputSize;

    if( m_nMaxOutputSize == -1 )
    {
        m_nMaxOutputSize = nOutputSize;
    }

    if( !m_poProcessor->m_bActive )
    {

#ifdef _EXTENSION_MAX_THREADS
    #define _EXTENSION_THREAD_COUNT _EXTENSION_MAX_THREADS
#else
    #define _EXTENSION_THREAD_COUNT -1
#endif

        m_poProcessor->start( std::bind( &A3::Extension::CExtensionBase::Worker, this, std::placeholders::_1 ), _EXTENSION_THREAD_COUNT );
    }

    if( nArguments )
    {
        LOG_ALL_FORMAT( loglevel::critical, "pstrFunction: {0}, nArguments: {1}", pstrFunction , nArguments );

        addRequest( pstrFunction, pArguments, nArguments );
    }

    A3::DataTypes::uint64 nCurrentSize = 2; //Opening and closing brackets.

    //Check for results
    std::string strResult = "[";

    std::vector < A3::Extension::Processor::CProcessorResult > results;

    if ( this->checkResults( results, nCurrentSize ) )
    {
        for ( auto oResult : results )
        {
            strResult += result_to_string( oResult ) + ",";
        }

        strResult.pop_back();
    }

    strResult += "]"; //Append closing bracket

    strncpy( pstrOutput, strResult.c_str(), nOutputSize );

    return 0;
}

std::vector< A3::Extension::Processor::CProcessorResult >
CExtensionBase::Worker( A3::Extension::Processor::CProcessorWorkload oWorkload )
{
    return splitIntoMultipart( Execute( oWorkload ), oWorkload );
}

void
CExtensionBase::addRequest( const char *pstrExtensionFunction, const char **pExtensionData, int nExtensionDataCount )
{
    for ( int nExtensionDataSet = 0; nExtensionDataSet < nExtensionDataCount; ++nExtensionDataSet )
    {
        std::string strArguments( pExtensionData[ nExtensionDataSet ] );
        strArguments = strArguments.substr( 1, ( strArguments.size() - 2 ) );
        A3::DataTypes::TStrVector oArguments = delimiter_split( strArguments, 29 );

        if( oArguments.size() > 1 )
        {
            std::string strID = oArguments[ 0 ];
            oArguments.erase( oArguments.begin() );

            //In case we do not need a result
            if( strID == "-1" )
            {
                strID.clear();
            }

            m_poProcessor->Add(
                    A3::Extension::Processor::CProcessorWorkload( strID, oArguments ) );
        }
        else
        {
            m_poProcessor->Add(
                    A3::Extension::Processor::CProcessorWorkload( "", oArguments ) );
        }
    }
}

bool
CExtensionBase::checkResults( std::vector< A3::Extension::Processor::CProcessorResult > & roResults, A3::DataTypes::uint64 nCurrentSize )
{
    return m_poProcessor->try_get_results( roResults, nCurrentSize, m_nMaxOutputSize );
}

std::vector< std::string >
CExtensionBase::delimiter_split( const std::string & rstrData, char cDelimiter )
{
    std::vector< std::string > oResult;
    std::stringstream string_stream( rstrData );
    std::string strNextPart;

    while ( std::getline( string_stream, strNextPart, cDelimiter ) )
    {
        oResult.push_back( strNextPart );
    }

    return oResult;
}

std::string
CExtensionBase::result_to_string( A3::Extension::Processor::CProcessorResult & roResult )
{
    return fmt::format( "[{0},{1},\"{2}\"]",
                        roResult.m_strID,
                        ( roResult.m_bIsMultiPart ? std::to_string( roResult.m_nPartIndex ) : "-1" ),
                        roResult.m_strData );
}

std::vector< A3::Extension::Processor::CProcessorResult >
CExtensionBase::splitIntoMultipart( std::string strResult, A3::Extension::Processor::CProcessorWorkload & roWorkload )
{
    std::vector< A3::Extension::Processor::CProcessorResult > results;

    //Workload hat has no id to return results -> input only call
    if( roWorkload.m_strID.empty() )
    {
        return results;
    }

    //Need to find the most optimal max size to store, to if there is lots of big results, little results get returned too..

    auto nMaxReturnConsumption = ( A3::DataTypes::uint64 )( 0.8 * m_nMaxOutputSize ); //Allow up to 80% of the return to be one request
    auto nParts = strResult.size() / nMaxReturnConsumption; //Amount of parts for the case of too much data for one
    bool bIsMultiPart = ( nParts != 0 ); //Do we have multipart?

    //Build Results as long as our data output is longer than one Result
    while ( strResult.size() > nMaxReturnConsumption )
    {
        results.push_back( A3::Extension::Processor::CProcessorResult (
                roWorkload.m_strID,
                strResult.substr( 0, ( size_t ) nMaxReturnConsumption ), true, nParts ) );

        strResult = strResult.substr( ( size_t )nMaxReturnConsumption );

        nParts--;
    }

    //Put in final Result, or the only one in case it was small enough for one anyway
    results.push_back( A3::Extension::Processor::CProcessorResult(
            roWorkload.m_strID,
            strResult,
            bIsMultiPart,
            ( bIsMultiPart ? 0 : -1 ) ) );

    return results;
}

}; // end namespace CExtension
}; // end namespace A3