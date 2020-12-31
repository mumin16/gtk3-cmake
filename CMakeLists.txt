cmake_minimum_required(VERSION 3.17)

project(gtkdemo CXX)

set(CMAKE_CXX_STANDARD 17)

if (APPLE)
  link_directories(/usr/local/lib)
  # NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
  # the property added to Info.plist
  set(MACOSX_BUNDLE_ICON_FILE gtkdemoicon.icns)
  # And this part tells CMake where to find and install the file itself
  set(myApp_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Resources/gtkdemoicon.icns)
  set_source_files_properties(${myApp_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
  add_executable(gtkdemo MACOSX_BUNDLE ${myApp_ICON} main.cpp)
else()
  # the WIN32 is needed for Windows in order for it to look for WinMain
  # instead of the main function. This is ignored on other systems,
  # so it works on all platforms
  add_executable(gtkdemo WIN32 main.cpp)
endif()

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GTK "gtk4")
  if (GTK_FOUND)
    target_link_libraries(gtkdemo ${GTK_LIBRARIES})
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
  endif()
endif()
