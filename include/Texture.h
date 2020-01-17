#ifndef TEXTURE_SDL_H_INCLUDED
#define TEXTURE_SDL_H_INCLUDED

//#include <SDL.h>
//#include "vulkan/vulkan.h"
#if defined(__ANDROID__)
 #include "vulkan_android/vulkan_wrapper.h"
#else
 #include "vulkan/vulkan.h"
#endif

namespace GGE
{
//    typedef SDL_Rect RenderRect;

    class Texture
    {

        public:
            inline Texture() { }
            inline virtual ~Texture() {

                if (device)
                {
                    vkDeviceWaitIdle(device);
                    if (textureImageView)vkDestroyImageView(device, textureImageView, nullptr);
                    if (textureImage)vkDestroyImage(device, textureImage, nullptr);
                    if (textureImageMemory)vkFreeMemory(device, textureImageMemory, nullptr);
                }

            } // { if (sdlTexture) SDL_DestroyTexture(sdlTexture); sdlTexture = NULL; }
            inline VkImageView getTextureImageView() { return textureImageView; }
//            inline void setSDLTexture(SDL_Texture *_sdlTexture) { sdlTexture = _sdlTexture; }
//            inline SDL_Texture* getSDLTexture() { return sdlTexture; }

            VkDevice device;
            VkImage textureImage;
            VkImageView textureImageView;
            VkDeviceMemory textureImageMemory;


        private:
//            SDL_Texture     *sdlTexture;


    };

}

#endif // TEXTURE_H_INCLUDED
