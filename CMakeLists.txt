# cmake_minimum_required(VERSION 3.0.0)
# project(yd_demo VERSION 0.1.0)

# include(CTest)
# enable_testing()

# add_executable(yd_demo main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

cmake_minimum_required(VERSION 3.0.0)
project(yubao_yd_Demo)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
# 头文件目录
include_directories(include)
# 库文件目录
link_directories(linux64)
# 源文件列表存储进SRC变量
aux_source_directory(src SRC)
# 生成可执行文件
add_executable(yd_demo ${SRC})
# 链接动态库
target_link_libraries(yd_demo yd)
# 将资源文件目录config_files中的文件拷贝至bulid/config_files目录下
# add_custom_command(TARGET main_linux POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/config_files ${CMAKE_BINARY_DIR}/config_files)