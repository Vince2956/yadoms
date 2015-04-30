#pragma once
#include "IUpdateSource.h"

namespace update {
   namespace source {

      class CYadoms : public IUpdateSource
      {
      public:
         //---------------------------------------------
         ///\brief   Constructor
         //---------------------------------------------
         CYadoms();

         //---------------------------------------------
         ///\brief   Destructor
         //---------------------------------------------
         virtual ~CYadoms();

         // IUpdateSource implementation 
         virtual const std::string getUpdateLocation() const;
         virtual const tools::CVersion getInstalledVersion() const;
         virtual const EUpdateType getUpdateType() const;
         // [END] - IUpdateSource implementation 

      };

   } // namespace source
} // namespace update