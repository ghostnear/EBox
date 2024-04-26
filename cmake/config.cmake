 # Defaults for variables go here.

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

add_compile_definitions(BUILD_TYPE_${CMAKE_BUILD_TYPE})
add_compile_definitions(BUILD_PLATFORM_${CMAKE_BUILD_PLATFORM})

# VitaSDK targets
if(CMAKE_BUILD_PLATFORM MATCHES "VITA")
    # VitaSDK is required
    if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        if(DEFINED ENV{VITASDK})
            set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
        else()
            message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
        endif()
    endif()

    include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

    ## Configuration options for this app
    # Display name (under bubble in LiveArea)
    set(VITA_APP_NAME "EBox")

    # Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X =
    # unique string of developer and Y = a unique number for this app
    set(VITA_TITLEID  "GHNR00000")

    # Optional version string to show in LiveArea's more info screen
    set(VITA_VERSION  "00.10")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif()