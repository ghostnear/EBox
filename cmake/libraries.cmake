# VitaSDK targets
if(CMAKE_BUILD_PLATFORM MATCHES "VITA")
    target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
            # SDL libraries.
            SDL2
            SDL2_ttf
            SDL2_image

            # Stubs required by SDL.
            SceDisplay_stub
            SceCtrl_stub
            SceAudio_stub
            SceAudioIn_stub
            SceSysmodule_stub
            SceGxm_stub
            SceCommonDialog_stub
            SceAppMgr_stub
            SceTouch_stub
            SceHid_stub
            SceMotion_stub
            jpeg png webp
            pthread
            freetype
            z m
    )
# Others
else()
    # OpenGL preferred standard.
    set(OpenGL_GL_PREFERENCE "GLVND")

    find_package(SDL2 CONFIG REQUIRED)
    find_package(Curses REQUIRED)

    target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
            $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
            $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
            ncurses
    )
endif()