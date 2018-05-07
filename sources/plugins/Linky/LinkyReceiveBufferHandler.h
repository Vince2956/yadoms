#pragma once
#include <shared/event/EventHandler.hpp>
#include <shared/communication/IReceiveBufferHandler.h>
#include <shared/communication/Buffer.hpp>
#include <shared/communication/IBufferLogger.h>
#include "ProtocolManager.h"

//--------------------------------------------------------------
/// \brief	Receive buffer handler for linky
///
/// This class manages the linky receive buffer.
/// A message is considered complete from its content (see protocol specification)
//--------------------------------------------------------------
class CLinkyReceiveBufferHandler : public shared::communication::IReceiveBufferHandler
{
public:
   //--------------------------------------------------------------
   /// \brief	                           Constructor
   /// \param[in] receiveDataEventHandler The event handler to notify for received data event
   /// \param[in] receiveDataEventId      The event id to notify for received data event
   /// \param[in] logger                  logger in developer mode
   /// \param[in] isDeveloperMode         developer mode is active
   //--------------------------------------------------------------
   CLinkyReceiveBufferHandler(const EProtocolType type, 
                              shared::event::CEventHandler& receiveDataEventHandler,
                              int receiveDataEventId,
                              boost::shared_ptr<shared::communication::IBufferLogger> logger,
                              const bool isDeveloperMode);

   //--------------------------------------------------------------
   /// \brief	                           Destructor
   //--------------------------------------------------------------
   virtual ~CLinkyReceiveBufferHandler();

   // ILinkyReceiveBufferHandler implementation
   void push(const shared::communication::CByteBuffer& buffer) override;
   void flush() override;
   // [END] ILinkyReceiveBufferHandler implementation

   void activate();
   void desactivate();
   void changeProtocol(const EProtocolType type);

protected:
   //--------------------------------------------------------------
   /// \brief	                     Check if we got a complete message
   /// \return                      The complet message
   //--------------------------------------------------------------
   boost::shared_ptr<std::map<std::string, std::vector<std::string> > > getCompleteMessage();

   //--------------------------------------------------------------
   /// \brief	                     Retreive all labels/values in a frame
   /// \param[in] frame             the frame to decode
   /// \return                      A map containing labels/values
   //--------------------------------------------------------------
   boost::shared_ptr<std::map<std::string, std::vector<std::string> > > getMessages(boost::shared_ptr<const std::vector<unsigned char>> frame);

   //--------------------------------------------------------------
   /// \brief	                     Check if the CRC is ok
   /// \param[in] message           a message to be check
   /// \return                      true if the checksum is ok
   //--------------------------------------------------------------
   bool isCheckSumOk(const std::string& message);

   //--------------------------------------------------------------
   /// \brief	                     Send a message to the target event handler
   /// \param[in] messages          Received messages as map(key, value)
   //--------------------------------------------------------------
   void notifyEventHandler(boost::shared_ptr<std::map<std::string, std::vector<std::string> > > messages) const;

private:
   //--------------------------------------------------------------
   /// \brief	Buffer content
   //--------------------------------------------------------------
   std::vector<unsigned char> m_content;

   //--------------------------------------------------------------
   /// \brief	The event handler to notify for received data event   
   //--------------------------------------------------------------
   shared::event::CEventHandler& m_receiveDataEventHandler;

   //--------------------------------------------------------------
   /// \brief	The event id to notify for received data event  
   //--------------------------------------------------------------
   int m_receiveDataEventId;

   //--------------------------------------------------------------
   /// \brief  The communication port
   //--------------------------------------------------------------
   boost::shared_ptr<shared::communication::IBufferLogger> m_logger;

   EProtocolType m_type;

   bool m_isDeveloperMode;
   bool m_pushActivated;
};

