#ifndef SO_ANDROID_H
#define SO_ANDROID_H


#include <memory>
#include <cstdlib>
#include <cstring>
#include <jni.h>
#include <errno.h>
#include <cassert>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <stdio.h>
#include <stdlib.h>

#include "Definitions.h"
#include "GraphicsManager.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "VulkanStarter2D", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "VulkanStarter2D", __VA_ARGS__))

enum MobileHand {
    LEFT_HAND = 0,
    RIGHT_HAND = 1
};


namespace GGE {

    class Controller;

    struct resourceFile;

    class OS {
    public:
        static OS *getInstance() {
            if (!OS::instance) OS::instance = new OS();
            return OS::instance;
        }

        void destroy();
        void checkInputEvent();
        void procEvent();
        void swapBuffer();
        void resizeWindow();
        void resizeWindow(int _adsYOffset);
        bool getRunning();
        bool isOnFocus();
        const Point getMouseCoord();
        float getTime();
        inline void setMouseCoord(const Point &p) { mouseCoord = p; }
        int alert(const char *lpCaption, const char *lpText);

        inline void setRunning(bool _yn) { running = _yn; }

        void toggleFullScreen();

//        inline bool isFullScreen() { return fullScreen; };
        inline bool isAlive() {return alive;}
        inline void setIsAlive(bool _alive) {alive = _alive;}

        void setAndroidApp(struct android_app *_app);
        inline struct android_app *getAndroidApp() { return app; }
        inline void setInputCoord(int index, const Point &p) {
            if (index > -1 && index < 2)
                inputCoord[index] = p;
        }

        inline void setTouchCoord(const Point &p) { touchCoord = p;}

        inline Point getInputCoord(int index) { return inputCoord[index]; }

        Point getWindowSize();

        Point calculateMousePoint(const Point &point);

        int32_t width;
        int32_t height;

        struct android_app *app;

        inline bool isFocused() { return !lostFocus; };

        bool lostFocus;
        bool killApp;
        int handID[2];
        void resetTouchInput();
    	std::vector<const char*> getRequiredExtensions(bool enableValidationLayers);
        bool createSurface(const VkInstance *instance, VkSurfaceKHR *surface);
        void destroyRendererContext();
        void createRendererContext();

    private:
        static OS *instance;

        OS();
        Point inputCoord[2];
        Point touchCoord;
        Point mouseCoord;
        Point windowedPosition, windowedSize;
        bool running;
        bool alive;

        static void error_callback(int error, const char *description);

        int restoreWidth, restoreHeight;

        timeval     tv0, tv;
    };

}

#endif //SO_ANDROID_H
