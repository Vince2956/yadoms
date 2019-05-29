#include "stdafx.h"
#include "IlluminationWm2.h"
#include "../StandardCapacities.h"

namespace shared
{
   namespace plugin
   {
      namespace yPluginApi
      {
         namespace historization
         {
            CIlluminationWm2::CIlluminationWm2(const std::string& keywordName,
                                               const EKeywordAccessMode& accessMode,
                                               const EMeasureType& measureType,
                                               typeInfo::CDoubleTypeInfo& additionalInfo)
               : CSingleHistorizableData<double>(keywordName,
                                                 CStandardCapacities::IlluminationWm2(),
                                                 accessMode,
                                                 0.0,
                                                 measureType,
                                                 additionalInfo)
            {
            }
         }
      }
   }
} // namespace shared::plugin::yPluginApi::historization