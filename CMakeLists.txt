project(translate C)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(BTREE)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER} -rdynamic)

message(STATUS "Include: ${GTK3_INCLUDE_DIRS}\n LIB_DIR: ${GTK3_LIBRARY_DIRS} \n CFLAGS_OTHERS: ${GTK3_CFLAGS_OTHER} \n LIBS: ${GTK3_LIBRARIES}")


add_executable(main main.c)
target_link_libraries(main ${BT_LIBS} ${GTK3_LIBRARIES})

add_executable(test builddata.c)
target_link_libraries(test ${BT_LIBS})

