#include "stdafx.h"
#include "main.h"
#include <shared/event/EventTimer.h>
#include <plugin_cpp_api/ImplementationHelper.h>
#include <shared/plugin/yPluginApi/IBindingQueryRequest.h>
#include <shared/plugin/yPluginApi/IManuallyDeviceCreationRequest.h>
#include <shared/plugin/yPluginApi/IDeviceRemoved.h>

#include "equipments/manuallyDeviceCreationException.hpp"
#include <shared/Log.h>

// Use this macro to define all necessary to make your DLL a Yadoms valid plugin.
// Note that you have to provide some extra files, like package.json, and icon.png
// This macro also defines the static PluginInformations value that can be used by plugin to get information values

IMPLEMENT_PLUGIN(CartelectronicIpBlindVelux)


CartelectronicIpBlindVelux::CartelectronicIpBlindVelux()
   : m_factory(boost::make_shared<Factory>()),
     m_pluginState(kUndefined)
{
}

CartelectronicIpBlindVelux::~CartelectronicIpBlindVelux()
{
}

// Event IDs
enum
{
   kEvtTimerRefreshCPULoad = yApi::IYPluginApi::kPluginFirstEventId, // Always start from shared::event::CEventHandler::kUserFirstId
   kRefreshStatesReceived,
   kConnectionRetryTimer,
   kAnswerTimeout
};

void CartelectronicIpBlindVelux::doWork(boost::shared_ptr<yApi::IYPluginApi> api)
{
   try
   {
      setPluginState(api, kInitialization);
	  m_ioManager = m_factory->loadConfiguration(api);

      // Create timer for refresh IOs
      m_refreshTimer = api->getEventHandler().createTimer(kRefreshStatesReceived, shared::event::CEventTimer::kPeriodic, boost::posix_time::seconds(30));

      if (m_ioManager->getEquipment() == 0 && m_ioManager->getWaitingEquipment() == 0){
         setPluginState(api, kReady);
         m_refreshTimer->stop();
      }
      else{
         m_refreshTimer->start();
		 api->getEventHandler().createTimer(kRefreshStatesReceived, shared::event::CEventTimer::kOneShot, boost::posix_time::seconds(0)); // Send an immediat refresh value event

         if (m_ioManager->getWaitingEquipment() != 0)
            setPluginState(api, kAtLeastOneConnectionFaulty);
         else
            setPluginState(api, kRunning);
      }
   }
   catch (std::exception&)
   {
      setPluginState(api, kAtLeastOneConnectionFaulty);
   }

   // the main loop
   while (true)
   {
      switch (api->getEventHandler().waitForEvents())
      {
      case yApi::IYPluginApi::kEventStopRequested:
         {
            YADOMS_LOG(information) << "Stop requested";
            setPluginState(api, kStop);
            return;
         }
      case kConnectionRetryTimer:
         break;
      case yApi::IYPluginApi::kEventDeviceCommand:
         {
            // Command received from Yadoms
            auto command(api->getEventHandler().getEventData<boost::shared_ptr<const yApi::IDeviceCommand>>());

            try
            {
               m_ioManager->onCommand(api, command);
            }
            catch (std::exception& e)
            {
               YADOMS_LOG(error) << "Fail to send command " << yApi::IDeviceCommand::toString(command) << ", error : " << e.what();
            }
            break;
         }
      case kRefreshStatesReceived:
         {
            YADOMS_LOG(information) << "Timer received";
            auto forceRefresh = false;

            try{
               forceRefresh = api->getEventHandler().getEventData<bool>();
            }
            catch (shared::exception::CBadConversion&)
            {}

            if (m_ioManager->getWaitingEquipment() != 0)
               m_ioManager->tryMissingEquipment(api);

			m_ioManager->readAllDevices(api, forceRefresh);

            analyzePluginState(api);
            break;
         }
      case yApi::IYPluginApi::kEventManuallyDeviceCreation:
         {
            // Yadoms asks for device creation
            setPluginState(api, kUpdateConfiguration);
            auto request = api->getEventHandler().getEventData<boost::shared_ptr<yApi::IManuallyDeviceCreationRequest>>();
            YADOMS_LOG(information) << "Manually device creation request received for device : " << request->getData().getDeviceName();
            try{
               if (!m_ioManager->deviceAlreadyExist(request->getData().getDeviceName())){
                  // Creation of the device only when the name doesn't already exist
                  m_factory->createDeviceManually(api, m_ioManager, request->getData());
                  request->sendSuccess();

                  // ask immediately for reading values
                  api->getEventHandler().postEvent<bool>(kRefreshStatesReceived, true);

                  if (m_ioManager->getEquipment() != 0){
                     m_refreshTimer->start();
                     setPluginState(api, kRunning);
                  }
               }
               else{
                  request->sendError("device Name already exist");
               }
            }
            catch (std::exception& e){
               YADOMS_LOG(error) << "Unknow error : " << e.what();
               request->sendError(e.what());
               setPluginState(api, kmanuallyCreationDeviceFailed);
            }
            break;
         }
      case yApi::IYPluginApi::kEventDeviceRemoved:
         {
            try{
               auto device = api->getEventHandler().getEventData<boost::shared_ptr<const yApi::IDeviceRemoved>>();

               if (m_ioManager){
                  m_ioManager->removeDevice(api, device->device());
                  YADOMS_LOG(information) << device->device() << " is removed";

                  // Check if no module present
                  if (m_ioManager->getEquipment() == 0){
                     m_refreshTimer->stop(); // No more refresh timer
                     setPluginState(api, kReady); // State ready
                  }
               }
               else
               YADOMS_LOG(error) << "Cannot remove the device " << device->device() << ". IO Manager is not initialized";
            }
            catch (std::exception& e){
               YADOMS_LOG(information) << "Unknow error : " << e.what();
            }
            break;
         }
      case yApi::IYPluginApi::kBindingQuery:
         {
            // Yadoms ask for a binding query 
            try
            {
               auto data = api->getEventHandler().getEventData<boost::shared_ptr<yApi::IBindingQueryRequest>>();

               if (data->getData().getQuery() == "wes")
               {
                  data->sendSuccess(m_ioManager->bindMasterDevice());
               }
               else
               {
                  std::string errorMessage = (boost::format("unknown query : %1%") % data->getData().getQuery()).str();
                  data->sendError(errorMessage);
                  YADOMS_LOG(error) << errorMessage;
               }
            }
            catch (std::exception& e)
            {
               YADOMS_LOG(information) << "Unknow error : " << e.what();
            }
            break;
         }
      case yApi::IYPluginApi::kEventExtraQuery:
         {
            // TODO : To be developped when received directly information from the WES
            // Check the IP address to know how send us data

            // Extra-command was received from Yadoms
            auto extraQuery = api->getEventHandler().getEventData<boost::shared_ptr<yApi::IExtraQuery>>();

            if (extraQuery)
            {
               YADOMS_LOG(information) << "Extra command received : " << extraQuery->getData()->query();

               if (extraQuery->getData()->query() == "wes")
               {
                  YADOMS_LOG(information) << "Simple command received";
               }
            }
            // Extra-query can return success or error indicator. In case of success, can also return data.
            // Return here a success without data (=empty container)
            extraQuery->sendSuccess(shared::CDataContainer());
            break;
         }
      case yApi::IYPluginApi::kSetDeviceConfiguration:
         {
            // Yadoms sent the new device configuration. Plugin must apply this configuration to device.
            auto deviceConfiguration = api->getEventHandler().getEventData<boost::shared_ptr<const yApi::ISetDeviceConfiguration>>();

            setPluginState(api, kUpdateConfiguration);
            m_ioManager->OnDeviceConfigurationUpdate(api,
                                                     deviceConfiguration->name(),
                                                     deviceConfiguration->configuration(),
                                                     kRefreshStatesReceived);

            setPluginState(api, kRunning);

            break;
         }
      default:
         {
            YADOMS_LOG(information) << "Unknown message id received";
            break;
         }
      }
   }
}

void CartelectronicIpBlindVelux::analyzePluginState(boost::shared_ptr<yApi::IYPluginApi> api)
{
   auto newState = kRunning; // default state

   for (const auto& devicesStatus : m_ioManager->getDeviceStates())
   {
      if (devicesStatus == specificHistorizers::EdeviceStatus::kTimeOut ||
         devicesStatus == specificHistorizers::EdeviceStatus::kError)
      {
         newState = kAtLeastOneConnectionFaulty;
      }
   }

   if (m_ioManager->getWaitingEquipment() != 0) {
	   newState = kAtLeastOneConnectionFaulty;
   }

   setPluginState(api, newState);
}

void CartelectronicIpBlindVelux::setPluginState(boost::shared_ptr<yApi::IYPluginApi> api, EPluginState newState)
{
   if (m_pluginState != newState)
   {
      switch (newState)
      {
      case kInitialization:
         api->setPluginState(yApi::historization::EPluginState::kCustom, "initialization");
         break;
      case kReady:
         api->setPluginState(yApi::historization::EPluginState::kCustom, "ready");
         break;
      case kAtLeastOneConnectionFaulty:
         api->setPluginState(yApi::historization::EPluginState::kCustom, "kAtLeastOneConnectionFaulty");
         break;
      case kmanuallyCreationDeviceFailed:
         api->setPluginState(yApi::historization::EPluginState::kCustom, "manuallyCreationError");
         break;
      case kRunning:
         api->setPluginState(yApi::historization::EPluginState::kRunning);
         break;
      case kStop:
         api->setPluginState(yApi::historization::EPluginState::kStopped);
         break;
      default:
         YADOMS_LOG(error) << "this plugin status does not exist : " << newState;
         break;
      }

      m_pluginState = newState;
   }
}

