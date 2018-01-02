/**********************************************************************************************************************\

    DESCRIPTION: A3EXT - Extension framework - The main file you most likely add your changes

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  02.01.2018

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018 Arkensor. All rights reserved!

\**********************************************************************************************************************/

#include "Framework/ExtensionBase.hpp"

namespace A3
{
namespace Extension
{

/*
 * CExtensionBase::Setup is called once before the first workload is processed
 *
 * @Return: void
 */
void
CExtensionBase::Setup()
{
    /*
     * The logging is provided by the spdlog library
     *
     * Infos and the library can be found here: https://github.com/gabime/spdlog/wiki/1.-QuickStart
     *
     * Note: If enabled in the Configuration.hpp everything is already initialized for you
     *       so you do not need to download or compile anything to use it.
     */
    auto console = spdlog::stdout_color_mt( "some_console_name" );
    console->info( "Welcome to spdlog!" ) ;
    console->info( "An info message example {0}.." , 1 );

    /*
     * The path where the arma3server was executed on the system is available via the variable m_strExecutablePath
     */
    std::experimental::filesystem::create_directories( m_strExecutablePath + "/mydirectory" );
    auto my_file_logger = spdlog::basic_logger_mt( "basic_file_logger_name", m_strExecutablePath + "/mydirectory/mylog.txt" );

    /*
     * You can use the LOG_ALL and LOG_ALL_FORMAT macros to write something to all loggers that were created
     * by you and or the framework. If no loggers are available you are still able to use the macros.
     * It just won't do anything.
     *
     * Note: By default this example will log it twice, since there is a logger active from the framework too
     */
    LOG_ALL( loglevel::debug , "This is a debug message send to all available loggers" );
    LOG_ALL_FORMAT( loglevel::critical, "This is a critial information with {0}: {1}", "formatting", 12345 )

    /*
     * You may also use the logging provided via the Configuration.hpp options
     * _EXTENSION_USE_CONSOLE_LOGGING will provide you with m_poConsoleLogger
     * _EXTENSION_USE_FILE_DEFAULT_LOGGER will provide you with m_poFileLogger
     *
     * The start parameters from the ArmA server can also be accessed
     * when having _EXTENSION_USE_START_PARAMETERS defined. They are stored
     * inside the m_poStartParameterHandler.
     *
     * Mods and servermods, are also parsed to have those ready to use for you.
     *
     * Blow there is an example of printing all parameters and mods to the console
     */
    for( auto & startParameter : m_poStartParameterHandler->m_oStartParamters )
    {
        m_poConsoleLogger->debug( "Parameter: {0} - Value: {1}", startParameter.first, startParameter.second );
    }

    for( auto & strMod : m_poStartParameterHandler->m_oMods )
    {
        m_poConsoleLogger->debug( "Mod: {0}", strMod );
    }

    for( auto & strServerMod : m_poStartParameterHandler->m_oServerMods )
    {
        m_poConsoleLogger->debug( "Servermod: {0}", strServerMod );
    }
}

/*
 * CExtensionBase::Execute is called for each workload that is processed
 *
 * @Return: Returns a string as result to the processed workload
 */
std::string
CExtensionBase::Execute( A3::Extension::Processor::CProcessorWorkload oWorkload )
{
    /*
     * The function that was called is stored inside oWorkload.m_strFunction
     * When the extension was called using the old "<name>" callExtension "<string>" syntax
     * the function is __RVEXTENSION__
     */
    m_poFileLogger->info( "The function called was: {0}", oWorkload.m_strFunction );

    /*
     * All Arguments that are given the the framework from the SQF side, are parsed as a vector of strings.
     * You may access them like this:
     */
    for( auto & oArugment : oWorkload.m_oArguments )
    {
        //do something with oArugment ...
    }

    //Some dummy work that takes 5 seconds to execute
    std::this_thread::sleep_for( std::chrono::seconds( 5 ) );

    /*
     * You may do anything inside this function. You can also declare functions outside of this function
     * within this file, or make your own classes and include them etc. The only thing that you need to take care of
     * is that if there needs to a return value, you give some thing back.
     *
     * If the oWorkload.m_strID is not -1 (string), there is a result expected. If you get the id -1 for exampe,
     * then you do not need to give something back. The result would be dropped in that case anyway.
     */
    return "A3EXT rocks!";
}

}; // end namespace Extension
}; // end namespace A3