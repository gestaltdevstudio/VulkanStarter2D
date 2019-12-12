cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 17)

project (StarterVulkan2D)

set(CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(COPY ${CPP_DIR}/conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ResourcesPath/)
file(COPY ${CPP_DIR}/libsOSX/vulkan DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ResourcesPath/)

IF(APPLE)

   FIND_LIBRARY(COCOA_LIBRARY Cocoa )
   FIND_LIBRARY(IOKIT_LIBRARY IOKit )
   FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo )
   FIND_LIBRARY(OPENAL_LIBRARY OpenAL )

ENDIF (APPLE)


if (MSVC)
  file(COPY ${CPP_DIR}/libsWin/libogg-0.dll ${CPP_DIR}/libsWin/LibVorbis.dll
        ${CPP_DIR}/libsWin/libZip.dll ${CPP_DIR}/libsWin/OpenAL32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif (MSVC)

include_directories(${CPP_DIR}/include ${CPP_DIR}/include/external/libzip ${CPP_DIR}/include/external)
file(GLOB SOURCES "${CPP_DIR}/main.cpp" "${CPP_DIR}/source/*.cpp")

if (UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -no-pie")
endif ()

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__WIN32__")
endif (MSVC)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGGE_DESKTOP")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

ADD_LIBRARY(glfw STATIC IMPORTED)
if (APPLE)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsOSX/libglfw3.a)
elseif (UNIX)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsLinux/debug/libglfw3.a)
endif ()

if (MSVC)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsWin/debug/glfw3.lib)
endif (MSVC)

ADD_LIBRARY(libzip STATIC IMPORTED)
if (APPLE)
  SET_TARGET_PROPERTIES(libzip PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsOSX/libzip.a)
elseif (UNIX)
  SET_TARGET_PROPERTIES(libzip PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsLinux/debug/libzip.a)
endif ()

if (MSVC)
  SET_TARGET_PROPERTIES(libzip PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsWin/debug/libZip.lib)
endif (MSVC)

if (APPLE)
  ADD_LIBRARY(libvorbisfile STATIC IMPORTED)
  SET_TARGET_PROPERTIES(libvorbisfile PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsOSX/libvorbisfile.a)
elseif (UNIX)
  ADD_LIBRARY(libvorbisfile STATIC IMPORTED)
  SET_TARGET_PROPERTIES(libvorbisfile PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsLinux/debug/libvorbisfile.a)
endif ()

if (MSVC)
  ADD_LIBRARY(zlib STATIC IMPORTED)
  SET_TARGET_PROPERTIES(zlib PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsWin/debug/zlib1.lib)
endif (MSVC)


ADD_LIBRARY(libvorbis STATIC IMPORTED)
if (APPLE)
  SET_TARGET_PROPERTIES(libvorbis PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsOSX/libvorbis.a)
elseif (UNIX)
  SET_TARGET_PROPERTIES(libvorbis PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsLinux/debug/libvorbis.a)
endif ()

if (MSVC)
  SET_TARGET_PROPERTIES(libvorbis PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsWin/debug/LibVorbis.lib)
endif (MSVC)

ADD_LIBRARY(libopenal STATIC IMPORTED)
if (UNIX)
  SET_TARGET_PROPERTIES(libopenal PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsLinux/debug/libopenal.a)
endif (UNIX)

if (MSVC)
  SET_TARGET_PROPERTIES(libopenal PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsWin/debug/OpenAL32.lib)
endif (MSVC)


ADD_LIBRARY(libogg STATIC IMPORTED)
if (APPLE)
  SET_TARGET_PROPERTIES(libogg PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsOSX/libogg.a)
elseif (UNIX)
  SET_TARGET_PROPERTIES(libogg PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsLinux/debug/libogg.a)
endif ()

if (MSVC)
SET_TARGET_PROPERTIES(libogg PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsWin/debug/libogg-0.lib)
endif (MSVC)


if (MSVC)
ADD_LIBRARY(libvulkan STATIC IMPORTED)
SET_TARGET_PROPERTIES(libvulkan PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsWin/debug/vulkan-1.lib)
endif(MSVC)

if (APPLE)
ADD_LIBRARY(libvulkan SHARED IMPORTED)
SET_TARGET_PROPERTIES(libvulkan PROPERTIES IMPORTED_LOCATION ${CPP_DIR}/libsOSX/libvulkan.1.dylib)

file(GLOB_RECURSE RSC_FILES "${CMAKE_BINARY_DIR}/ResourcesPath/*")
add_executable(StarterVulkan2D MACOSX_BUNDLE ${SOURCES} ${RSC_FILES})
else()
add_executable(StarterVulkan2D ${SOURCES})
endif()


if (APPLE)
  target_link_libraries (StarterVulkan2D glfw libvulkan ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${OPENAL_LIBRARY} z bz2 libzip libvorbisfile libvorbis libogg)


  foreach(RSC_FILE ${RSC_FILES})

    file(RELATIVE_PATH RES_PATH "${CMAKE_BINARY_DIR}/ResourcesPath" ${RSC_FILE})

    get_filename_component(RESOURCE_SUBDIR ${RES_PATH} DIRECTORY)
    set(RESOURCE_DIRECTORY "Resources/${RESOURCE_SUBDIR}")

    set_property(SOURCE ${RSC_FILE} PROPERTY MACOSX_PACKAGE_LOCATION ${RESOURCE_DIRECTORY})

  endforeach(RSC_FILE)


  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
            XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS    "@executable_path/../Frameworks"
        )
 
  add_custom_command(
      TARGET
      ${CMAKE_PROJECT_NAME}
      POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory
      ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)/${CMAKE_PROJECT_NAME}.app/Contents/Frameworks
  )
 
  add_custom_command(
      TARGET
      ${CMAKE_PROJECT_NAME}
      POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_CURRENT_SOURCE_DIR}/libsOSX/libMoltenVK.dylib
      ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)/${CMAKE_PROJECT_NAME}.app/Contents/Frameworks
      POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_CURRENT_SOURCE_DIR}/libsOSX/libvulkan.1.dylib
      ${CMAKE_CURRENT_BINARY_DIR}/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)/${CMAKE_PROJECT_NAME}.app/Contents/Frameworks
  )

elseif (UNIX)
  target_link_libraries (StarterVulkan2D glfw vulkan X11 Xxf86vm Xinerama Xcursor Xrandr dl libzip libvorbisfile libvorbis libopenal libogg z)
endif ()

if (MSVC)
  target_link_libraries (StarterVulkan2D libvulkan libzip libvorbis libopenal libogg zlib glfw )  
endif (MSVC)

#[[
Xcode 11, Command CodeSign failed with a nonzero exit code


Add --deep to the "Other Code Signing Flags" in the "Build Settings".
In the "Signing & Capabilities" of your target click on "+ Capability" in the top left corner and choose "Hardened Runtime".
Then turn on "Disable Library Validation" in the list.
I don't really know if there's any drawbacks by using this capability, however my application compiles and works fine both on macOS and iOS.
Source: https://stackoverflow.com/questions/58195914/xcode-11-command-codesign-failed-with-a-nonzero-exit-code
]]#
