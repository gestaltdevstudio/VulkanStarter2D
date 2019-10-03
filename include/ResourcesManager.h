#ifndef RESOURCES_MANAGER_H_INCLUDED
#define RESOURCES_MANAGER_H_INCLUDED

#include "Definitions.h"
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <zip.h>

namespace GGE
{

    struct resourceFile
    {
        const char* fileName;
        char *content;
        uint64_t size;
        resourceFile()
        {
        }
        ~resourceFile()
        {
            if (content)
            {
                free(content);
                content = NULL;
            }
        }
    };

    class ResourcesManager
	{
        public:

            static ResourcesManager *getInstance()
            {
               if (!ResourcesManager::instance) ResourcesManager::instance = new ResourcesManager();
               return ResourcesManager::instance;
            }
            void destroy();

            ~ResourcesManager();

            bool loadZip(const char* zipFileName, const char* key);
            resourceFile* loadFile(const char* cfileName);
            resourceFile* loadCompressedFile(const char* cFileName);
            char *sgets( char * str, int num, char **input );

        private:

            ResourcesManager();
            static ResourcesManager *instance;

            zip   *zipFile;

    };

}

#endif // RESOURCES_MANAGER_H_INCLUDED
