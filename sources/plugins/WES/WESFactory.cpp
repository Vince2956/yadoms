#include "stdafx.h"
#include "WESFactory.h"
#include "equipments/WESEquipment.h"
#include "equipments/manuallyDeviceCreationException.hpp"
#include <shared/Log.h>

CWESFactory::CWESFactory()
{
}

boost::shared_ptr<CIOManager> CWESFactory::loadConfiguration(boost::shared_ptr<yApi::IYPluginApi> api,
                                                             const boost::shared_ptr<IWESConfiguration> configuration) const
{
   std::vector<boost::shared_ptr<equipments::IEquipment>> deviceList;

   boost::shared_ptr<equipments::IEquipment> equipment;

   // Create all devices and equipments
   for (const auto& device : api->getAllDevices())
   {
      std::string type = "";

      // plugin state have no type
      try
      {
         type = api->getDeviceDetails(device).getWithDefault<std::string>("type", "");

         if (type == "WES")
         {
            equipment = boost::make_shared<equipments::CWESEquipment>(api,
                                                                      device,
                                                                      api->getDeviceConfiguration(device));
            deviceList.push_back(equipment);
         }

         // Do Noting, all is done into CWESEquipments
         if (type == "TIC")
         {
         }
      }
      catch (std::exception& e)
      {
         YADOMS_LOG(error) << e.what();
         throw;
      }

      YADOMS_LOG(information) << "Name : " << device;
      YADOMS_LOG(information) << "Model : " << type;
   }

   return boost::make_shared<CIOManager>(deviceList);
}

std::string CWESFactory::createDeviceManually(boost::shared_ptr<yApi::IYPluginApi> api,
                                              const boost::shared_ptr<CIOManager> ioManager,
                                              const yApi::IManuallyDeviceCreationData& data,
                                              const boost::shared_ptr<IWESConfiguration> configuration) const
{
   boost::shared_ptr<equipments::IEquipment> equipment;

   try
   {
      if (data.getDeviceType() == "WES")
      {
         equipment = boost::make_shared<equipments::CWESEquipment>(api,
                                                                   data.getDeviceName(),
                                                                   data.getConfiguration(),
                                                                   configuration);
         ioManager->addEquipment(equipment);
      }
      else
      {
         YADOMS_LOG(error) << "no section defined for " << data.getDeviceType();
      }
   }
   catch (std::exception& e)
   {
      YADOMS_LOG(error) << "Error : " << e.what();
      throw CManuallyDeviceCreationException(e.what());
   }

   return equipment->getDeviceName();
}

CWESFactory::~CWESFactory()
{
}

