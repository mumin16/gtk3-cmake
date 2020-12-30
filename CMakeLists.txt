cmake_minimum_required(VERSION 3.0.0)

project(gtkexample CXX)
set(CMAKE_CXX_STANDARD 17)
add_executable(gtkexample main.cpp)

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GTK "gtk+-3.0")
  if (GTK_FOUND)    
    target_link_libraries(gtkexample ${GTK_LIBRARIES})
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
  endif()
endif()
