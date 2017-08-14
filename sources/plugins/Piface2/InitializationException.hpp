#pragma once
#include <shared/exception/Exception.hpp>

//--------------------------------------------------------------
/// \brief	Exception handling for protocol errors
//--------------------------------------------------------------
class CInitializationException : public shared::exception::CException
{
public:
   //--------------------------------------------------------------
   /// \brief	                        Constructor
   //--------------------------------------------------------------
   explicit CInitializationException()
      :CException("Initialization error - SPI is present - Board is not detected")
   {
   }

   //--------------------------------------------------------------
   /// \brief      Destructor
   //--------------------------------------------------------------
   virtual ~CInitializationException() throw()
   {
   }
};
