
cmake_minimum_required(VERSION 3.10)
project(cDemo
        VERSION 0.0.0.1
        DESCRIPTION "A demo c project"
        LANGUAGES C
)

#设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

#TEST模式启动情况下，包含test源文件
if(TEST_MOD)
file(GLOB TEST_SRC_FILES
    ./test/*.c
)
endif()

#组件源文件包含
file(GLOB_RECURSE SRC_FILES
    ./component/**/*.c
)

#组件头文件包含
include_directories(${PROJECT_SOURCE_DIR}/component)
include_directories(${PROJECT_SOURCE_DIR}/component/zlog)
include_directories(${PROJECT_SOURCE_DIR}/component/zlog/inc)
include_directories(${PROJECT_SOURCE_DIR}/component/pthread)
include_directories(${PROJECT_SOURCE_DIR}/component/pthread/inc)
include_directories(${PROJECT_SOURCE_DIR}/c_public)
include_directories(${PROJECT_SOURCE_DIR}/os)
include_directories(${PROJECT_SOURCE_DIR}/os/linux)
include_directories(${PROJECT_SOURCE_DIR}/os/linux/inc)
#链接库位置
if(TOOL_CHAIN STREQUAL "aarch64_linux")
link_directories(${PROJECT_SOURCE_DIR}/component/zlog/lib/aarch64_linux)
elseif(TOOL_CHAIN STREQUAL "x86_64_linux")
link_directories(${PROJECT_SOURCE_DIR}/component/zlog/lib/x86_64_linux)
else()
message(FATAL_ERROR "<=== Please choose the tool chain! ===>")
endif()


add_executable(${PROJECT_NAME} ${SRC_FILES} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_NAME} 
                        pthread         
                        zlog                   
)
