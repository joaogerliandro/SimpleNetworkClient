cmake_minimum_required(VERSION 3.16)

project(SimpleNetworkClient VERSION 0.1 LANGUAGES CXX)

message(STATUS "Project: ${PROJECT_NAME} (version ${CMAKE_PROJECT_VERSION})")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMake Generator: ${CMAKE_GENERATOR}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${PROJECT_SOURCE_DIR}/forms")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

file(GLOB_RECURSE SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "source/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/*.h")
file(GLOB_RECURSE WRAPPERS RELATIVE ${PROJECT_SOURCE_DIR} "include/*.hpp")
file(GLOB_RECURSE FORMS RELATIVE ${PROJECT_SOURCE_DIR} "forms/*.ui")
file(GLOB_RECURSE RESOURCES RELATIVE ${PROJECT_SOURCE_DIR} "resources/*.qrc")

set(PROJECT_SOURCES
        ${SOURCES}
        ${HEADERS}
        ${WRAPPERS}
        ${FORMS}
        ${RESOURCES}
)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SimpleNetworkClientGUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Qt linked libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
)

# Boost linked libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${Boost_LIBRARIES}
)

if(WIN32)
    target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ws2_32
    )
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SimpleNetworkClient)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
