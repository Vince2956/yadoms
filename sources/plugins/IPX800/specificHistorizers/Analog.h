#pragma once

#include <shared/plugin/yPluginApi/historization/SingleHistorizableData.hpp>
#include <shared/plugin/yPluginApi/KeywordAccessMode.h>

// Shortcut to yPluginApi namespace
namespace yApi = shared::plugin::yPluginApi;

namespace specificHistorizers
{
   //-----------------------------------------------------
   ///\brief A remote pc code historizable object
   //-----------------------------------------------------
   class CAnalog : public yApi::historization::CSingleHistorizableData<unsigned int>
   {
   public:
      //-----------------------------------------------------
      ///\brief                     Constructor
      ///\param[in] keywordName     The name of the keyword display in Yadoms
      ///\param[in] hardwareName    Name used by the IPX800
      ///\param[in] accessMode      Read or Read/Write access
      ///\param[in] measureType     type of the data historized
      ///\param[in] additionalInfo  Additionnal information
      //-----------------------------------------------------
      CAnalog(const std::string& keywordName,
              const std::string& hardwareName,
              const yApi::EKeywordAccessMode& accessMode = yApi::EKeywordAccessMode::kGet,
              const yApi::EMeasureType& measureType = yApi::EMeasureType::kAbsolute,
              yApi::historization::typeInfo::ITypeInfo& additionalInfo = yApi::historization::typeInfo::CEmptyTypeInfo::Empty);

      //-----------------------------------------------------
      ///\brief                     get the hardware name
      ///\return return the name used by the IPX800 to address this information.
      //-----------------------------------------------------
      std::string getHardwareName() const;

      //-----------------------------------------------------
      ///\brief                     Destructor
      //-----------------------------------------------------
      virtual ~CAnalog();

   private:
      std::string m_hardwareName;
   };
} // namespace specificHistorizers