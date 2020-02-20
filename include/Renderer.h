#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <stdexcept>
#include <set>
#include <unordered_map>
#include <optional>
#include <array>
#include "ResourcesManager.h"
#include "Drawable.h"
#include "Texture.h"

#if defined(__ANDROID__)
 #include "OS_ANDROID.h"
 #include "vulkan_android/vulkan_wrapper.h"
#elif __APPLE__
 #include "TargetConditionals.h"
 #if TARGET_OS_OSX
  #include "OS_GLFW.h"
 #else
  #include "OS_iOS.h"
 #endif
#else
 #include "OS_GLFW.h"
#include "vulkan/vulkan.h"
#endif
#include "Text.h"
#include "stb_image.h"

namespace GGE
{

    struct Vertex {
        glm::vec2 pos;
        glm::vec4 color;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription = {};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }

        bool operator==(const Vertex& other) const {
            return pos == other.pos && color == other.color && texCoord == other.texCoord;
        }
    };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

    struct RenderChunk
    {
        Texture     *texture;
        uint16_t    indicesCount;
    };

    class Text;

    class Renderer
    {

        public:
            Renderer(uint16_t maxDrawables);
            ~Renderer();
            Texture* createTexture(const resourceFile *fileBuffer);
            void onRenderStart();

            void renderDrawable(const TextureRegion* textureRegion, float x, float y, float scaleX, float scaleY, float rotation, bool isFlippedX, bool isFlippedY, Vector4* color);
            void renderText(Text *text);
            void onRenderFinish();
            void swapBuffer();
            void renderResize(Point windowSize);
            void createBigBuffers(uint32_t bufferTotalSize = 128 * 1024);
            void prepare();
            Texture* createTextureImage(const resourceFile* fileBuffer);

            VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                                  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
            void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
            void calculateViewportSize(Point &viewport);
            std::vector<Texture*> activeTextures;
            void recreateSwapChain();
            void createContext();
            void destroyContext();

        private:
            void createInstance();
            void setupDebugMessenger();
            void createSurface();
            void pickPhysicalDevice();
            void createLogicalDevice();
            void createSwapChain();
            void createImageViews();

            void createRenderPass();
            void createDescriptorSetLayout();
            void createGraphicsPipeline();
            void createCommandPool();
            void createFramebuffers();
            void createUniformBuffers();
            void createDescriptorPool();
            void createDescriptorSets();
            void createCommandBuffers();
            void createSyncObjects();
            VkImageView createTextureImageView(VkImage textureImage);
            VkImageView createImageView(VkImage image, VkFormat format);

            void cleanupSwapChain();

            void copyVertexBuffer();
            void updateUniformBuffer(uint32_t currentImage);
            void flush();
            void switchTexture(Texture* newTexture);

            void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
            void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
            VkCommandBuffer beginSingleTimeCommands();

            void endSingleTimeCommands(VkCommandBuffer commandBuffer);

            void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
            void createTextureSampler();
            void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
            void copyBufferRegion(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size);

            void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

            bool checkValidationLayerSupport();
            void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
            bool isDeviceSuitable(VkPhysicalDevice device);
            QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
            bool checkDeviceExtensionSupport(VkPhysicalDevice device);
            SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
            VkShaderModule createShaderModule(const resourceFile* code);

            VkInstance         instance;
            VkDebugUtilsMessengerEXT debugMessenger;
            VkSurfaceKHR surface;

            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice device;

            VkQueue graphicsQueue;
            VkQueue presentQueue;

            VkSwapchainKHR swapChain;
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;
            std::vector<VkImageView> swapChainImageViews;

            VkSampler textureSampler;

            VkBuffer stagingBigBuffer;
            VkDeviceMemory stagingBigBufferMemory;

            VkBuffer bigBuffer;
            VkDeviceMemory bigBufferMemory;
            std::vector<VkFramebuffer> swapChainFramebuffers;
            std::vector<VkFence> imagesInFlight;

            VkRenderPass renderPass;
            VkDescriptorSetLayout descriptorSetLayout;
            VkPipelineLayout pipelineLayout;
            VkPipeline graphicsPipeline;
            VkDescriptorPool descriptorPool;
            std::unordered_map<Texture*, std::vector<VkDescriptorSet>> descriptorSets;

            std::vector<RenderChunk> renderChunks;

            std::vector<VkBuffer> uniformBuffers;
            std::vector<VkDeviceMemory> uniformBuffersMemory;

            std::vector<Vertex> vertices;
            std::vector<uint16_t> indices;

            Texture* activeTexture;

            VkCommandPool commandPool;
            std::vector<VkCommandBuffer> commandBuffers;

            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;
            size_t currentFrame = 0;
            uint32_t imageIndex;
            uint16_t totalVBOSize;
            uint16_t renderIndex;

            uint16_t renderCalls;

            VkViewport viewport;
            Point      viewportSize;
            Point      viewportPosition;


            bool framebufferResized = false;
            uint16_t indicesOld;

#if defined(DEBUG)
            const bool enableValidationLayers = true;
#else
            const bool enableValidationLayers = false;
#endif

            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };
            const std::vector<const char*> deviceExtensions = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
            };

            const size_t MAX_FRAMES_IN_FLIGHT = 2;

            static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

    };

}

#endif // RENDERER_H_INCLUDED
