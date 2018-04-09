#include "stdafx.h"
#include "TeleInfoFactory.h"
#include <shared/communication/AsyncSerialPort.h>
#include <shared/communication/AsciiBufferLogger.h>
#include "TeleInfoReceiveBufferHandler.h"
#include "Decoder.h"
#include <shared/Log.h>
#include <boost/regex.hpp>

CTeleInfoFactory::~CTeleInfoFactory()
{
}

boost::shared_ptr<shared::communication::IAsyncPort> CTeleInfoFactory::constructPort(const ITeleInfoConfiguration& configuration,
                                                                                           shared::event::CEventHandler& eventHandler,
                                                                                           boost::shared_ptr<shared::communication::IReceiveBufferHandler> receiveBufferHandler,
                                                                                           int evtPortConnectionId)
{
   YADOMS_LOG(information) << "Connecting TeleInfo on serial port " << configuration.getSerialPort() << "..." ;

   boost::shared_ptr<shared::communication::IAsyncPort> port = boost::make_shared<shared::communication::CFT2xxSerialPort>(boost::asio::serial_port_base::baud_rate(1200),
                                                                                                                           boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::even),
                                                                                                                           boost::asio::serial_port_base::character_size(7),
                                                                                                                           boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one),
                                                                                                                           boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

   auto FTDIPortList = boost::static_pointer_cast<shared::communication::CFT2xxSerialPort>(port)->getPortComNumber();
   bool isFTDISerialPort = false;
   boost::regex reg("\\d+");
   boost::smatch match;

   //Set parameters
   if (boost::regex_search(configuration.getSerialPort(), match, reg))
   {
      std::vector<int>::const_iterator iterator;
      int counter = 0;

      // change all hardware names
      for (iterator = FTDIPortList.begin(); iterator != FTDIPortList.end(); ++iterator)
      {
         if (match[0] == boost::lexical_cast<std::string>((*iterator) - 1))
         {
            YADOMS_LOG(information) << "The serial port is a FTDI port. The FTDI driver will be used instead of the generic serial driver.";

            // Set the port number
            boost::static_pointer_cast<shared::communication::CFT2xxSerialPort>(port)->setPortNumber(counter);
            isFTDISerialPort = true;
            break;
         }
         ++counter;
      }
   }

   if (!isFTDISerialPort)
   {
      port = boost::make_shared<shared::communication::CAsyncSerialPort>(configuration.getSerialPort(),
                                                                         boost::asio::serial_port_base::baud_rate(1200),
                                                                         boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::even),
                                                                         boost::asio::serial_port_base::character_size(7),
                                                                         boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one),
                                                                         boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

   }

   port->subscribeForConnectionEvents(eventHandler,
                                      evtPortConnectionId);

   port->setReceiveBufferHandler(receiveBufferHandler);

   return port;
}

boost::shared_ptr<CTeleInfoReceiveBufferHandler> CTeleInfoFactory::GetBufferHandler(shared::event::CEventHandler& eventHandler,
                                                                                    int evtPortDataReceived,
                                                                                    const bool isDeveloperMode)
{
   boost::shared_ptr<shared::communication::IBufferLogger> logger;

   logger = boost::make_shared<shared::communication::CAsciiBufferLogger>("trace");

   return boost::make_shared<CTeleInfoReceiveBufferHandler>(eventHandler,
                                                            evtPortDataReceived,
                                                            logger,
                                                            isDeveloperMode);
}

boost::shared_ptr<IDecoder> CTeleInfoFactory::constructDecoder(boost::shared_ptr<yApi::IYPluginApi> api)
{
   return boost::make_shared<CDecoder>(api);
}