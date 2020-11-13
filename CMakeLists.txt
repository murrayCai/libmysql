cmake_minimum_required(VERSION 3.16)
project(libmysql C)
set(CMAKE_INSTALL_PREFIX /usr)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_DEBUG_POSTFIX "_d")

find_path(h_readline readline/readline.h)
find_library(l_readline readline)

find_path(h_mysql mysql/mysql.h)
find_library(l_mysqlclient mysqlclient /usr/local/lib/mysql)

include_directories(${h_readline} ${h_mysql} "../libbase/include" "./include")
find_library(l_mc mc "../libbase")

add_subdirectory(src)
add_subdirectory(test)
