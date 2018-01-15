/**********************************************************************************************************************\

    DESCRIPTION: Global configuration for the extension framework

------------------------------------------------------------------------------------------------------------------------

    CREATION DATE:  29.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2018
    Paul L. (https://github.com/Arkensor)
    Ollie W. (https://github.com/BoGuu)
    All rights reserved!

\**********************************************************************************************************************/
#ifndef A3DB_CONFIGURATION_HPP
#define A3DB_CONFIGURATION_HPP

/*
 * Extension configuration
 */
#define _EXTENSION_NAME    "A3EXT"
#define _EXTENSION_VERSION "1.0"

/*
 * Define the maximum amount of threads that will be created
 * If not defined, there will be a thread for each cpu core
 */
#define _EXTENSION_MAX_THREADS 4

/*
 * Do you want to print something to the console?
 */
#define _EXTENSION_USE_CONSOLE_LOGGING

/*
 * Do you want to write log files?
 */
#define _EXTENSION_USE_FILE_LOGGING

/*
 * @Required: _EXTENSION_USE_FILE_LOGGING
 *
 * Using this provides you with a default log file that you can write to.
 * The default folder for the log files is @<Extensionname>/Logs/
 * The default name for the logfile is <Extensioname>.log
 */
#define _EXTENSION_USE_FILE_DEFAULT_LOGGER

/*
 * Do you want to have access to the start parameters from the arma executable?
 */
#define _EXTENSION_USE_START_PARAMETERS

/*
 * Do you want to make use of the ini configuration system?
 */
#define _EXTENSION_USE_INI_CONFIGURATION

/*
 * @Required: _EXTENSION_USE_INI_CONFIGURATION
 *
 * You may specify the name of the config file
 * that will be searched in the entire arma directory
 * and all subfolders.
 *
 * The default value for this is <Extensionname>.ini
 *
 * NOTE: This option will be overwritten when the user adds a -<Extensionname>=some/path/to/config.ini in the start parameters.
 */
#define _EXTENSION_CONFIGFILE_NAME "A3EXT.ini"

#endif //A3DB_CONFIGURATION_HPP
