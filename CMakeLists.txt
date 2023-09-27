cmake_minimum_required(VERSION 3.20)
project(Majestic VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(proto)

find_package(fmt REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

pkg_check_modules(Argon2 REQUIRED IMPORTED_TARGET libargon2)

set(PROJECT_SOURCES
	include/about_dialog.hpp
	include/constants.hpp
	include/client.hpp
	include/login_widget.hpp
	include/main_window.hpp
	src/about_dialog.cpp
	src/client.cpp
	src/main.cpp
	src/main_window.cpp
	src/login_widget.cpp
	ui/about_dialog.ui
	ui/login_widget.ui
	ui/main_window.ui
)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Majestic
        MANUAL_FINALIZATION
	Resources.qrc
        ${PROJECT_SOURCES}
    )
endif()

#[[
# This is merely to suppress CMake warnings.
set_property(SOURCE proto/majestic.pb.h PROPERTY SKIP_AUTOGEN ON)
set_property(SOURCE proto/majestic.pb.cc PROPERTY SKIP_AUTOGEN ON)
set_property(SOURCE proto/majestic.grpc.pb.h PROPERTY SKIP_AUTOGEN ON)
set_property(SOURCE proto/majestic.grpc.pb.cc PROPERTY SKIP_AUTOGEN ON)
]]

target_include_directories(Majestic PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Majestic PRIVATE fmt::fmt)
target_link_libraries(Majestic PRIVATE MyGrpc)
target_link_libraries(Majestic PRIVATE PkgConfig::Argon2)
target_link_libraries(Majestic PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(Majestic PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Majestic PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Majestic
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Majestic)
endif()
