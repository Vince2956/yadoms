#pragma once
#include <shared/plugin/yPluginApi/IYPluginApi.h>
#include "IWeatherSubtype.h"

namespace yApi = shared::plugin::yPluginApi;

namespace rfxcomMessages
{
   //--------------------------------------------------------------
   /// \brief	The Weather1 keyword
   //--------------------------------------------------------------
   class CWeather1 : public IWeatherSubtype
   {
   public:
      //--------------------------------------------------------------
      /// \brief	                        Constructor
      //--------------------------------------------------------------
      CWeather1();
      virtual ~CWeather1() = default;

      // IWeatherSubtype implementation
      std::string getModel() const override;
      const std::vector<boost::shared_ptr<const yApi::historization::IHistorizable>>& keywords() const override;
      void setFromProtocolState(unsigned short windDirection,
                                unsigned short windSpeed,
                                unsigned short windGust,
                                short temperature,
                                short chill,
                                unsigned char humidity,
                                unsigned short rainRate,
                                unsigned int rainTotal,
                                unsigned char uv,
                                unsigned short solar,
                                unsigned short pressure,
                                EWeatherForecast forecast) override;
      // [END] IWeatherSubtype implementation

   private:
      //--------------------------------------------------------------
      /// \brief	                        The keywords
      //--------------------------------------------------------------
      boost::shared_ptr<yApi::historization::CSpeed> m_averageWind;
      boost::shared_ptr<yApi::historization::CSpeed> m_gustWind;
      boost::shared_ptr<yApi::historization::CTemperature> m_temperature;
      boost::shared_ptr<yApi::historization::CRain> m_rainTotal;

      //--------------------------------------------------------------
      /// \brief	The keywords list to historize in one step for better performances
      //--------------------------------------------------------------
      std::vector<boost::shared_ptr<const yApi::historization::IHistorizable>> m_keywords;
   };
} // namespace rfxcomMessages
