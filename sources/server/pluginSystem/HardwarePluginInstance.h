//
// HardwarePluginInstance.h
//
// yadoms-plugin instance handler
//
#pragma once

#include <boost/thread.hpp>
#include "tools/ThreadBase.h"
#include "plugins/hardware/IHardwarePlugin.h"

//--------------------------------------------------------------
/// \brief	this class is used to manage a plugin instance. 
//--------------------------------------------------------------
class CHardwarePluginInstance : public CThreadBase
{
public:
    //--------------------------------------------------------------
    /// \brief	Constructor
    /// \param [in]	plugin: the plugin instance to handle
    //--------------------------------------------------------------
    CHardwarePluginInstance(IHardwarePlugin * plugin);

protected:
    //--------------------------------------------------------------
    /// \brief			The main plugin work
    //--------------------------------------------------------------
    virtual void doWork();

private:
    //--------------------------------------------------------------
    /// \brief			The plugin instance
    //--------------------------------------------------------------
    IHardwarePlugin * m_pPlugin;
};
