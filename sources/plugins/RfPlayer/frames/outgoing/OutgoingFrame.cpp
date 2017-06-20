#include "stdafx.h"
#include "OutgoingFrame.h"
#include "AsciiCommand.h"

namespace frames {
namespace outgoing {
   
      COutgoingFrame::COutgoingFrame(const std::string & protocol)
         :m_protocol(protocol)
      {
      }

      COutgoingFrame::~COutgoingFrame()
      {
      }
      
      const std::string COutgoingFrame::generateAsciiCommand(boost::shared_ptr<shared::plugin::yPluginApi::IYPluginApi> api, boost::shared_ptr<const shared::plugin::yPluginApi::IDeviceCommand> command)
      {
         shared::CDataContainer details = api->getDeviceDetails(command->getDevice());
         shared::CDataContainer config = api->getDeviceConfiguration(command->getDevice());

         const std::string cmd = command->getBody();

         std::string dim = "";
         std::string burst = "";
         std::string qualifier = "";

         if (details.containsValue("id"))
         {
            std::string id = details.get<std::string>("id");
            return CAsciiCommand::generateCommandById(m_protocol, cmd, id);
         }
         else
         {
            std::string addr = (boost::format("%1%%2%") % config.get<std::string>("groupCode") % config.get<int>("unitCode")).str();
            return CAsciiCommand::generateCommandByAddress(m_protocol, cmd, addr);
         }
      }
      
} //namespace incoming
} //namespace frames