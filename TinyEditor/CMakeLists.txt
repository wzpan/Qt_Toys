cmake_minimum_required(VERSION 2.8.9)

project(TinyEditor)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)

aux_source_directory(. DIR_SRCS)

# Set and add resource file
set(Resource ${CMAKE_SOURCE_DIR}/myResources.qrc)
qt5_add_resources(ResourceSources ${Resource})

# Tell CMake to create the executable
add_executable(TinyEditor main.cpp mainwindow.cpp finddialog.cpp ${ResourceSources})

# Use the Widgets module from Qt 5.
# The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
qt5_use_modules(TinyEditor Widgets) 
