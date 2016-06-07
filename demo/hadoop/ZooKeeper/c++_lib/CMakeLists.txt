# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (zkclass)

# 编译选项
add_definitions(-std=c++11)

# 为构建树添加包含路径
include_directories(../zookeeper/src/c/include/)
include_directories(../zookeeper/src/c/include/zookeeper)
include_directories(../zookeeper/src/c/include/zookeeper/zookeeper)

# 链接目录
link_directories(../zookeeper/src/c/lib)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(test ${DIR_SRCS})
#target_link_libraries(test libzookeeper_st.a)
target_link_libraries(test libzookeeper_mt.a)
target_link_libraries(test pthread)

