#pragma once

#include "entities/Page.h"

class IPageRequester
{
public:
   //--------------------------------------------------------------
   /// \brief           Add new page 
   /// \param [in]      name   The page name
   /// \param [in]      pageOrder  The page order
   /// \return          pageId generated by the database
   /// \throw           CEmptyResultException if fails
   //--------------------------------------------------------------
   virtual int addPage(const std::string& name, const int pageOrder) = 0;

   //--------------------------------------------------------------
   /// \brief                 Get page informations
   /// \param [in] pageId     Page Id
   /// \throw                 CInvalidParameterException if pageId is unknown
   //--------------------------------------------------------------
   virtual boost::shared_ptr<CPage> getPage(int pageId) = 0;

   //--------------------------------------------------------------
   /// \brief           List all pages
   /// \return          List of registered pages
   //--------------------------------------------------------------
   virtual std::vector<boost::shared_ptr<CPage> > getPages() = 0;

   //--------------------------------------------------------------
   /// \brief           Update page informations
   /// \param [in]      pageId   Page  Id
   /// \param [in]      name   New name
   /// \param [in]      pageOrder  The page order
   /// \throw           CEmptyResultException if fails
   //--------------------------------------------------------------
   virtual void updatePage(int pageId, const std::string& name, const int pageOrder) = 0;

   //--------------------------------------------------------------
   /// \brief           Remove page 
   /// \param [in] pageId   Page  Id
   /// \throw           CEmptyResultException if fails
   //--------------------------------------------------------------
   virtual void removePage(int pageId) = 0;

   //--------------------------------------------------------------
   /// \brief           Remove all pages
   /// \throw           CEmptyResultException if fails
   //--------------------------------------------------------------
   virtual void removeAllPages() = 0;

   //--------------------------------------------------------------
   /// \brief       Destructor
   //--------------------------------------------------------------
   virtual ~IPageRequester()
   {
   }
};
