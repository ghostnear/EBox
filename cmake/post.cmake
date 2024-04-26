# Post build stuff per platform.
if(CMAKE_BUILD_PLATFORM MATCHES "VITA")
    ## Create Vita files
    vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})

    # The FILE directive lets you add additional files to the VPK, the syntax is
    # FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
    vita_create_vpk(
        ${PROJECT_NAME}.vpk
        ${VITA_TITLEID}
        ${PROJECT_NAME}.self
        VERSION ${VITA_VERSION}
        NAME ${VITA_APP_NAME}
        FILE metadata/vita sce_sys
    )
endif()