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

            }
            inline VkImageView getTextureImageView() { return textureImageView; }

            VkDevice device;
            VkImage textureImage;
            VkImageView textureImageView;
            VkDeviceMemory textureImageMemory;


        private:


    };

}

#endif // TEXTURE_H_INCLUDED
