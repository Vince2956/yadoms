#pragma once

#include "IRfxcomMessage.h"
#include "RFXtrxHelpers.h"
#include <shared/plugin/yPluginApi/IYPluginApi.h>
#include "../IUnsecuredProtocolFilter.h"

namespace yApi = shared::plugin::yPluginApi;

namespace rfxcomMessages
{
   //--------------------------------------------------------------
   /// \brief	The current/energy protocol support (reception only)
   //--------------------------------------------------------------
   class CCurrentEnergy : public IRfxcomMessage
   {
   public:
      CCurrentEnergy(boost::shared_ptr<yApi::IYPluginApi> api,
                     const RBUF& rbuf,
                     size_t rbufSize,
                     boost::shared_ptr<IUnsecuredProtocolFilter> messageFilter);

      virtual ~CCurrentEnergy();

      static boost::shared_ptr<IUnsecuredProtocolFilter> createFilter();

      // IRfxcomMessage implementation
      boost::shared_ptr<std::queue<shared::communication::CByteBuffer> > encode(boost::shared_ptr<ISequenceNumber> seqNumberProvider) const override;
      void historizeData(boost::shared_ptr<yApi::IYPluginApi> api) const override;
      void filter() const override;
      void declareDevice(boost::shared_ptr<yApi::IYPluginApi> api) const override;
      const std::string& getDeviceName() const override;
      const std::vector<boost::shared_ptr<const yApi::historization::IHistorizable>>& keywords() override;
      // [END] IRfxcomMessage implementation

   protected:
      void buildDeviceName();
      void buildDeviceModel();

   private:
      //--------------------------------------------------------------
      /// \brief	The device sub-type
      //--------------------------------------------------------------
      unsigned char m_subType;

      //--------------------------------------------------------------
      /// \brief	The device id
      //--------------------------------------------------------------
      unsigned short m_id;

      //--------------------------------------------------------------
      /// \brief	The filter for unsecured protocols
      //--------------------------------------------------------------
      boost::shared_ptr<IUnsecuredProtocolFilter> m_messageFilter;

      //--------------------------------------------------------------
      /// \brief	The device name
      //--------------------------------------------------------------
      std::string m_deviceName;

      //--------------------------------------------------------------
      /// \brief	The device model
      //--------------------------------------------------------------
      std::string m_deviceModel;

      //--------------------------------------------------------------
      /// \brief	The current (A), for the 3 channels
      //--------------------------------------------------------------
      boost::shared_ptr<yApi::historization::CCurrent> m_current1;
      boost::shared_ptr<yApi::historization::CCurrent> m_current2;
      boost::shared_ptr<yApi::historization::CCurrent> m_current3;

      //--------------------------------------------------------------
      /// \brief	The instant power (W)
      //--------------------------------------------------------------
      boost::shared_ptr<yApi::historization::CPower> m_instantPower;

      //--------------------------------------------------------------
      /// \brief	The total power (Wh)
      //--------------------------------------------------------------
      boost::shared_ptr<yApi::historization::CEnergy> m_totalPower;

      //--------------------------------------------------------------
      /// \brief	The battery level (percent)
      //--------------------------------------------------------------
      boost::shared_ptr<yApi::historization::CBatteryLevel> m_batteryLevel;

      //--------------------------------------------------------------
      /// \brief	The signalPower (percent)
      //--------------------------------------------------------------
      boost::shared_ptr<yApi::historization::CSignalPower> m_signalPower;

      //--------------------------------------------------------------
      /// \brief	The keywords list to historize in one step for better performances
      //--------------------------------------------------------------
      std::vector<boost::shared_ptr<const yApi::historization::IHistorizable> > m_keywords;
   };
} // namespace rfxcomMessages


