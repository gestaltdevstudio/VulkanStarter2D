cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)

project (VulkanStarter2D)

file(GLOB VULKAN_STARTER_2D_SRC "${CMAKE_CURRENT_SOURCE_DIR}/../android_main.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../source/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../source/android/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -DVK_USE_PLATFORM_ANDROID_KHR -DVK_NO_PROTOTYPES")

set(libs_DIR ${CMAKE_SOURCE_DIR}/libs)

add_library(libzip SHARED IMPORTED)
set_target_properties(libzip PROPERTIES IMPORTED_LOCATION
${libs_DIR}/${ANDROID_ABI}/libzip.so)

add_library(libbullet SHARED IMPORTED)
set_target_properties(libbullet PROPERTIES IMPORTED_LOCATION
${libs_DIR}/${ANDROID_ABI}/libbullet.so)

add_library(libopenal SHARED IMPORTED)
set_target_properties(libopenal PROPERTIES IMPORTED_LOCATION
${libs_DIR}/${ANDROID_ABI}/libopenal.so)

add_library(libogg SHARED IMPORTED)
set_target_properties(libogg PROPERTIES IMPORTED_LOCATION
${libs_DIR}/${ANDROID_ABI}/libogg.so)

add_library(libvorbis SHARED IMPORTED)
set_target_properties(libvorbis PROPERTIES IMPORTED_LOCATION
${libs_DIR}/${ANDROID_ABI}/libvorbis.so)

add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

add_library(VulkanStarter2D SHARED ${VULKAN_STARTER_2D_SRC})

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")


target_include_directories(VulkanStarter2D PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../conf
    ${ANDROID_NDK}/sources/android/native_app_glue)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/external/libzip
        Google
        ${GPG_SDK_PATH}/include
        )

target_link_libraries(VulkanStarter2D
    android
    native_app_glue
    log
    libzip
    libopenal
    libogg
    libvorbis
    z
)


