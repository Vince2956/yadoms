#include "stdafx.h"
#include "IOManager.h"
#include "urlManager.h"
#include <boost/regex.hpp>
#include <shared/Log.h>

CIOManager::CIOManager(std::vector<boost::shared_ptr<equipments::IEquipment> >& extensionList)
{
   m_deviceManager = extensionList;
}

void CIOManager::addEquipment(boost::shared_ptr<equipments::IEquipment> equipment)
{
   if (equipment->isMasterDevice())
      m_deviceManager.push_back(equipment);
   else
   { 
      // TODO : Create subdevice 
   }
}

void CIOManager::removeDevice(boost::shared_ptr<yApi::IYPluginApi> api, std::string deviceRemoved)
{
   for (unsigned char counter = 0; counter < m_deviceManager.size(); ++counter)
   {
      // Deletion from the list of the device
      if (m_deviceManager[counter]->getDeviceName() == deviceRemoved)
      {
         // If it's an extension, we delete the extension.
         // If it's the WES, we delete all elements
         if (m_deviceManager[counter]->getDeviceType() != "WES")
            m_deviceManager.erase(m_deviceManager.begin()+counter);
         else
            m_deviceManager.clear();
      }
   }
}

int CIOManager::getMasterEquipment()
{
   return m_deviceManager.size();
}

void CIOManager::readAllDevices(boost::shared_ptr<yApi::IYPluginApi> api, bool forceHistorization)
{
   std::vector<boost::shared_ptr<const yApi::historization::IHistorizable> > keywordsToHistorize;

   for (unsigned char counter = 0; counter < m_deviceManager.size(); ++counter)
   {
      m_deviceManager[counter]->updateFromDevice(api, forceHistorization);
   }
}

void CIOManager::onCommand(boost::shared_ptr<yApi::IYPluginApi> api,
                           boost::shared_ptr<const yApi::IDeviceCommand> command)
{
   shared::CDataContainer parameters;
   std::string keywordName = command->getKeyword();
   std::string commandSelected;

   YADOMS_LOG(information) << "Command received :" << yApi::IDeviceCommand::toString(command) ;
/*
   const auto& deviceDetails = api->getDeviceDetails(command->getDevice());
   auto deviceType = deviceDetails.get<std::string>("type");

   std::vector<boost::shared_ptr<equipments::IEquipment> >::const_iterator iteratorExtension;

   for (iteratorExtension = m_devicesList.begin(); iteratorExtension != m_devicesList.end(); ++iteratorExtension)
   {
      if (deviceType == (*iteratorExtension)->getDeviceType())
      {
         if (m_isPasswordActivated)
            parameters.set("key", m_password);

		 shared::CDataContainer results = urlManager::sendCommand(m_socketAddress, (*iteratorExtension)->buildMessageToDevice(api, parameters, command));

         // If the answer is a success, we historize the data
         if (results.containsValue("Success"))
            (*iteratorExtension)->historizePendingCommand(api, command);
         else
         {
            YADOMS_LOG(error) << "Command is not executed by the WES" ;
            
            // if an error is return, we reset the pending operation
            (*iteratorExtension)->resetPendingCommand();
         }
      }
   }*/
}

void CIOManager::readIOFromDevice(boost::shared_ptr<yApi::IYPluginApi> api, 
                                  const std::string& type,
                                  bool forceHistorization)
{
/*
   shared::CDataContainer parameters;
   shared::CDataContainer results;

   // add the password if activated
   if (m_isPasswordActivated)
      parameters.set("key", m_password);

   parameters.set("Get", type);

   results = urlManager::sendCommand( m_socketAddress, parameters);

   std::vector<boost::shared_ptr<equipments::IEquipment> >::const_iterator iteratorExtension;

   for (iteratorExtension = m_devicesList.begin(); iteratorExtension != m_devicesList.end(); ++iteratorExtension)
      (*iteratorExtension)->updateFromDevice(type, api, results, forceHistorization);
*/
}

void CIOManager::OnConfigurationUpdate(boost::shared_ptr<yApi::IYPluginApi> api,
                                           const IWESConfiguration& configuration)
{
   /*
   m_socketAddress = configuration.getIPAddressWithSocket();
   m_isPasswordActivated = configuration.isPasswordActivated();
   m_password = configuration.getPassword();
   */
}

CIOManager::~CIOManager()
{}