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
    ${PROJECT_SOURCE_DIR}/src/limits/limits.cc
    ${PROJECT_SOURCE_DIR}/src/limits/memory.cc
    ${PROJECT_SOURCE_DIR}/src/limits/cpu.cc
    ${PROJECT_SOURCE_DIR}/src/limits/release.cc
    ${PROJECT_SOURCE_DIR}/src/limits/time.cc
    ${PROJECT_SOURCE_DIR}/src/limits/wait.cc
    ${PROJECT_SOURCE_DIR}/src/limits/info.cc
    ${PROJECT_SOURCE_DIR}/src/limits/pids.cc
    ${PROJECT_SOURCE_DIR}/src/utils/process.cc
    ${PROJECT_SOURCE_DIR}/src/utils/exceptions.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/all.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/config.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/procfs.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/abstruct/tmpfs.cc
    ${PROJECT_SOURCE_DIR}/src/container-fs/overlayfs/mainfs.cc
)

SET(HEADER_INCLUDE_DIR include/ssandbox)

SET(HEADER_LIST
    ${HEADER_INCLUDE_DIR}/semaphore.h
    ${HEADER_INCLUDE_DIR}/ssandbox.h 
    ${HEADER_INCLUDE_DIR}/sandbox.h 
    ${HEADER_INCLUDE_DIR}/containerfs.h 
    ${HEADER_INCLUDE_DIR}/userns.h 
    ${HEADER_INCLUDE_DIR}/cgroup.h 
    ${HEADER_INCLUDE_DIR}/limits.h 
    ${HEADER_INCLUDE_DIR}/utils/process.h 
    ${HEADER_INCLUDE_DIR}/utils/exceptions.h 
)

ADD_LIBRARY(ssandbox STATIC ${SRC_LIST})

INSTALL(TARGETS ssandbox
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

INSTALL(FILES ${HEADER_LIST} DESTINATION include/ssandbox)