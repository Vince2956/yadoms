#pragma once

#include "../IFactory.h"

namespace communication { namespace rules { namespace rfxLanXpl {

   class CRuleFactory : public IFactory
   {
   public:
      CRuleFactory();
      virtual ~CRuleFactory();
      
      // IFactory implementation
      virtual bool isHandled(shared::xpl::CXplMessage & message);
      virtual boost::shared_ptr<IRule> identifyRule(shared::xpl::CXplMessage & msg, CRuleInstanceManager & instanceManager);

      virtual bool isHandled(database::entities::CDevice & device);
      virtual boost::shared_ptr<IRule> identifyRule(database::entities::CDevice & device, CRuleInstanceManager & instanceManager);

      virtual shared::xpl::CXplActor identifyXplActor(database::entities::CDevice & device);
      // [END] IFactory implementation
   private:

      //------------------------------------------
      ///\brief  Check if the hardware name is handled by factory
      ///\param [in] hardwareName : the hardware name (i.e. : rfxlan-0x12345)
      ///\return true if the hardware name starts with "rfxlan-"
      //------------------------------------------
      bool isHandled(const std::string & hardwareName);

      //------------------------------------------
      ///\brief  Get the rule for a protocol
      ///\param [in] protocolName : the protocol name (i.e. : ac.basic)
      ///\return the rule for the given protocol (may be null if protocol not handled
      //------------------------------------------
      boost::shared_ptr<IRule> identifyRule(const std::string & protocolName, CRuleInstanceManager & instanceManager);

   };
   
} //namespace rfxLanXpl
} //namespace rules
} //namespace communication