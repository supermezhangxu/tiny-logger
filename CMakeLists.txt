# 最低需要版本 3.8
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
# 项目名称HELLO ,程序语言为C++
PROJECT (tiny-logger LANGUAGES CXX) 

set(CMAKE_C_FLAGS "-g -Wall")

#设置执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR}/src/include)

aux_source_directory(./src logger_src)

# 递归获取目录下所有的C文件
file(GLOB_RECURSE cpp_files ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/test/*.cpp)

# 将 SRC 指代的 cpp文件 编译为 test
ADD_EXECUTABLE(test ${cpp_files})
