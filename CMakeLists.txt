cmake_minimum_required(VERSION 3.16)

project(Project-Heimdall VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- ENABLE AUTOMOC (Fixes the Metatype error) ---
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Dependencies
find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Multimedia Widgets)
find_package(OpenCV REQUIRED)

# Source Files
set(PROJECT_SOURCES
    src/main.cpp
)

# Executable
qt_add_executable(Project-Heimdall
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Linking Libraries
target_link_libraries(Project-Heimdall PRIVATE 
    Qt6::Quick 
    Qt6::Multimedia 
    Qt6::Widgets
    ${OpenCV_LIBS}
)

# QML Resources
qt_add_qml_module(Project-Heimdall
    URI Main
    VERSION 1.0
    QML_FILES 
        content/App.qml
)

# Installation
install(TARGETS Project-Heimdall
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
