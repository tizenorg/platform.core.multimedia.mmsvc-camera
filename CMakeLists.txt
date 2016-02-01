CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# project
SET(maintainer "Jeongmo Yang<jm80.yang>, Hyuntae Kim<ht1211.kim@samsung.com>, Sejong Park<sejong123.park@samsung.com>")
SET(description "A Camera module for muse server")
SET(service "mmsvc")
SET(submodule "camera")
SET(fw_name "${service}-${submodule}")

PROJECT(${fw_name})

SET(pc_dependents "dlog mm-common mused libtbm")

SET(PC_NAME ${fw_name})
SET(PACKAGE_DESCRIPTION "muse camera module")
SET(PC_REQUIRED ${pc_dependents})
SET(PC_LDFLAGS -lmuse-camera)

SET(PC_NAME2 legacy-camera)
SET(PACKAGE_DESCRIPTION2 "legacy camera library")
SET(PC_REQUIRED2 "mm-camcorder capi-media-tool")
SET(PC_LDFLAGS2 -llegacy-camera)

CONFIGURE_FILE(
    ${fw_name}.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc
    @ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)

CONFIGURE_FILE(
    legacy-camera.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/legacy-camera.pc
    @ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/legacy-camera.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)

ADD_SUBDIRECTORY(legacy)
ADD_SUBDIRECTORY(muse)

IF(UNIX)

ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
ADD_CUSTOM_COMMAND(
        DEPENDS clean
        COMMENT "distribution clean"
        COMMAND find
        ARGS    .
        -not -name config.cmake -and \(
        -name tester.c -or
        -name Testing -or
        -name CMakeFiles -or
        -name cmake.depends -or
        -name cmake.check_depends -or
        -name CMakeCache.txt -or
        -name cmake.check_cache -or
        -name *.cmake -or
        -name Makefile -or
        -name core -or
        -name core.* -or
        -name gmon.out -or
        -name install_manifest.txt -or
        -name *.pc -or
        -name *~ \)
        | grep -v TC | xargs rm -rf
        TARGET  distclean
        VERBATIM
)

ENDIF(UNIX)
