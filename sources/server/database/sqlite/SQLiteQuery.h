#pragma once

#include "../common/Query.h"


namespace database
{
   namespace sqlite
   {
      //
      /// \brief  Class used to create queries
      //
      class CSQLiteQuery : public common::CQuery
      {
      public:
         //
         /// \brief           Constructor
         //
         CSQLiteQuery();

         //
         /// \brief           Destructor
         //
         virtual ~CSQLiteQuery();

         // Overriding common::CQuery
         std::string functionDateToIsoString(const std::string& sqlPart) override;
         std::string functionSubstring(const std::string& sqlPart, int offset, int count) override;
         // [END] - Overriding common::CQuery 
      };
   } //namespace sqlite
} //namespace database 


