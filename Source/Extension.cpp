/**********************************************************************************************************************\

    DESCRIPTION: 

------------------------------------------------------------------------------------------------------------------------

    RESPONSIBILITY: Arkensor
    CREATION DATE:  29.12.2017

------------------------------------------------------------------------------------------------------------------------

    Copyright © 2017 Arkensor. All rights reserved!

\**********************************************************************************************************************/

#include "Framework/ExtensionBase.hpp"

namespace A3
{
namespace Extension
{

std::string
CExtensionBase::Execute( A3::Extension::Processor::CProcessorWorkload oWorkload )
{

    return "Return some final result string here.";
}

}; // end namespace Extension
}; // end namespace A3