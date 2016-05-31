#pragma once
#include "IDevice.h"
#include "IIdentification.h"
#include "../ioInterfaces/IDigitalPotentiometer.h"

namespace device
{
   //--------------------------------------------------------------
   /// \brief	Digitial potentiometer device (Family 2C)
   //--------------------------------------------------------------
   class CDigitalPotentiometer : public IDevice
   {
   public:
      //--------------------------------------------------------------
      /// \brief	Constructor
      /// \param[in]	family Device family
      /// \param[in]	id Device serial number
      /// \param[in]	api yApi context
      /// \param[in]	io I/O access object
      //--------------------------------------------------------------
      CDigitalPotentiometer(EOneWireFamily family,
                            const std::string& id,
                            boost::shared_ptr<ioInterfaces::IDigitalPotentiometer> io);

      //--------------------------------------------------------------
      /// \brief	Destructor
      //--------------------------------------------------------------
      virtual ~CDigitalPotentiometer();

   protected:
      // IDevice implementation
      boost::shared_ptr<const IIdentification> ident() const override
      {
         return m_identification;
      }
      const std::vector<boost::shared_ptr<const yApi::historization::IHistorizable> >& keywords() const override
      {
         return m_keywords;
      }
      void read() const override;
      void write(const std::string& keyword, const std::string& command) override;
      // [END] IDevice implementation

   private:
      //--------------------------------------------------------------
      /// \brief	The device identification
      //--------------------------------------------------------------
      boost::shared_ptr<const IIdentification> m_identification;

      //--------------------------------------------------------------
      /// \brief	The I/O access object
      //--------------------------------------------------------------
      boost::shared_ptr<ioInterfaces::IDigitalPotentiometer> m_io;

      //--------------------------------------------------------------
      /// \brief	The keywords
      //--------------------------------------------------------------
      boost::shared_ptr<yApi::historization::CSwitch> m_potentiometerMode;
      boost::shared_ptr<yApi::historization::CDimmable> m_dim;
      std::vector<boost::shared_ptr<const yApi::historization::IHistorizable> > m_keywords;
   };

} // namespace device
