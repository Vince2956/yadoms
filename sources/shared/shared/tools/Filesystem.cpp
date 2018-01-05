#include "stdafx.h"
#include "Filesystem.h"


namespace shared
{
   namespace tools
   {
      boost::filesystem::path CFilesystem::makeRelative(const boost::filesystem::path& from,
                                                        const boost::filesystem::path& to)
      {
         // Start at the root path and while they are the same then do nothing then when they first
         // diverge take the entire from path, swap it with '..' segments, and then append the remainder of the to path.
         auto fromIter = from.begin();
         auto toIter = to.begin();

         // Loop through both while they are the same to find nearest common directory
         while (fromIter != from.end() && toIter != to.end() && (*toIter) == (*fromIter))
         {
            ++toIter;
            ++fromIter;
         }

         // Replace from path segments with '..' (from => nearest common directory)
         boost::filesystem::path finalPath;
         while (fromIter != from.end())
         {
            finalPath /= "..";
            ++fromIter;
         }

         // Append the remainder of the to path (nearest common directory => to)
         while (toIter != to.end())
         {
            finalPath /= *toIter;
            ++toIter;
         }

         return finalPath;
      }
   } // namespace tools 
} // namespace shared
