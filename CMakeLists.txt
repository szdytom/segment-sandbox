CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(SegmentSandbox)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/include/
)

SET(CMAKE_CXX_STANDARD 17)

SET(SRC_LIST
    ${PROJECT_SOURCE_DIR}/src/userns.cc
    ${PROJECT_SOURCE_DIR}/src/semaphore.cc
    ${PROJECT_SOURCE_DIR}/src/sandbox.cc
    ${PROJECT_SOURCE_DIR}/src/cgroup/subsys.cc
    ${PROJECT_SOURCE_DIR}/src/cgroup/unit.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/limits.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/memory.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/cpu.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/release.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/time.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/wait.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/info.cc
    ${PROJECT_SOURCE_DIR}/src/limits/resources/pids.cc
    ${PROJECT_SOURCE_DIR}/src/utils/process.cc
    ${PROJECT_SOURCE_DIR}/src/utils/exceptions.cc
    ${PROJECT_SOURCE_DIR}/src/utils/listfile.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/all.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/config.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/procfs.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/tmpfs.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/overlayfs/mainfs.cc
)

SET(HEADER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/ssandbox)

ADD_LIBRARY(ssandbox STATIC ${SRC_LIST})

INSTALL(TARGETS ssandbox
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

INSTALL(CODE "EXECUTE_PROCESS(COMMAND cp -r ${HEADER_INCLUDE_DIR} ${CMAKE_INSTALL_PREFIX}/include)")
