#include "../include/ResourcesManager.h"

#if defined(__ANDROID__)
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "../include/OS_ANDROID.h"
#endif

namespace GGE
{

    ResourcesManager* ResourcesManager::instance = 0;

    ResourcesManager::ResourcesManager()
    {
        zipFile = nullptr;
    }

    ResourcesManager::~ResourcesManager()
    {
        if (zipFile)
            zip_close(zipFile);
    }

    char* ResourcesManager::sgets( char * str, int num, char **input )
    {
        char *next = *input;
        int  numread = 0;

        while ( numread + 1 < num && *next ) {
            int isnewline = ( *next == '\n' );
            *str++ = *next++;
            numread++;
            if ( isnewline )
                break;
        }

        if ( numread == 0 )
            return NULL;  // "eof"

        *str = '\0';
        *input = next;
        return str;
    }

    void ResourcesManager::destroy()
    {
        if (zipFile)
            zip_close(zipFile);
        zipFile = NULL;
	    delete instance;
        instance = NULL;
    }

    bool ResourcesManager::loadZip(const char* zipFileName, const char* key)
    {
        int err = 0;
        zipFile = ::zip_open(zipFileName, 0, &err);
        if (err)
        {
            printf("Impossible to open zipFile %s\n", zipFileName);
            return false;
        }

        err = zip_set_default_password(zipFile, key);
        if (err < 0)
        {
            printf("Wrong password to open zipFile %s\n", zipFileName);
            return false;
        }
        return true;
    }

    resourceFile* ResourcesManager::loadFile(const char* cfileName)
    {


#if defined(__ANDROID__)
        AAssetManager* mgr = OS::getInstance()->getAndroidApp()->activity->assetManager;
        AAsset *asset = AAssetManager_open(mgr,("conf/" + to_string(cfileName)).c_str(), AASSET_MODE_BUFFER);
        if (asset) {
            uint64_t fileLength = AAsset_getLength(asset);


            resourceFile *rf = new resourceFile();
            rf->fileName = cfileName;
            rf->size = fileLength;

            rf->content = new char[fileLength + 1];

            AAsset_read(asset, rf->content, fileLength);

            rf->content[fileLength] = '\0';

            AAsset_close(asset);

            return rf;
        } else
        {
            return NULL;
        }
#endif

        long size;
        std::ifstream File(("conf/" + to_string(cfileName)).c_str(), std::ifstream::binary);
        if(File.is_open())
        {

            File.seekg(0, std::ifstream::end);
            size=File.tellg();
            File.seekg(0);

            resourceFile* rf = new resourceFile();
            rf->fileName = cfileName;
            rf->size = size ;

            rf->content = (char*) calloc(size + 1, sizeof(char));

            File.read (rf->content, size);

            File.close();

            return rf;

        } else
        {
            printf("Impossible to open %s\n", cfileName);
            return NULL;
        }

    }

    resourceFile* ResourcesManager::loadCompressedFile(const char* cFileName)
    {

#if 1 //defined(DEBUG)
        return loadFile(cFileName);
#endif
        zip_file *f = zip_fopen(zipFile, cFileName, 0);
        if (!f)
        {
            printf("Impossible to open %s\n", cFileName);
            return NULL;
        }
        const char *name = cFileName;
        struct zip_stat st;
        zip_stat_init(&st);
        zip_stat(zipFile, name, 0, &st);

        resourceFile* rf = new resourceFile();
        rf->fileName = cFileName;
        rf->size = st.size;

        rf->content = (char*) calloc(st.size + 1, sizeof(char));

        zip_fread(f, rf->content, st.size);
        zip_fclose(f);


        return rf;
    }

}
