include(cleanCppExtensions)

# configure version.cpp.in with selected version
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.cpp"
  )
# If you want to have date and time of the build, your targets has to depend on this.
# This will force recompilation of version.o and thus forcing gcc to update __DATE__ macro.
add_custom_target(versionFileTouchForRebuild
    COMMAND ${CMAKE_COMMAND} -E touch "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")


#------------------------------------------------------------------------------
# Libraries dependencies
# find_package (Threads REQUIRED) #threading

#------------------------------------------------------------------------------
# By using macro to add common dependencies you can avoid repetition when you have
# multiple binaries.
# Use with `addCommonDependencies(ShaderGraph)`
# macro(addCommonDependencies TARGET)
#     add_dependencies(${TARGET} versionFileTouchForRebuild) # We want precise time of build in version
#     target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#     target_link_libraries (${TARGET} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
#     target_compile_definitions(${TARGET} PRIVATE -DSOME_DEFINE)
# endmacro()

#-------------------------------------------------------------------------------
# ShaderGraph executable setup

set(ICON_RESOURCE "")
if(WIN32) #windows icon resource file, provided from /packaging directory
    set(ICON_RESOURCE "${PROJECT_BINARY_DIR}/ShaderGraph.icon.rc")
elseif (APPLE) #osx icon ressource file, provided from /packaging directory
    set(ICON_RESOURCE "${PROJECT_SOURCE_DIR}/packaging/ShaderGraph.icns")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE CPPS  ./*.cpp)

add_executable(ShaderGraph MACOSX_BUNDLE
    ${ICON_RESOURCE}
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    ${CPPS})

add_dependencies(ShaderGraph versionFileTouchForRebuild) # We want precise time of build in version
target_include_directories(ShaderGraph PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (ShaderGraph PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ShaderGraph nodes)


if(APPLE)
    set_target_properties(ShaderGraph PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "ShaderGraph")
    set_target_properties(ShaderGraph PROPERTIES MACOSX_BUNDLE_BUNDLE_GUI_IDENTIFIER "com.ShaderGraph.ShaderGraph")
    set_target_properties(ShaderGraph PROPERTIES MACOSX_BUNDLE_ICON_FILE ShaderGraph.icns)
    set_target_properties(ShaderGraph PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/packaging/MacOSXBundleInfo.plist.in)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/packaging/ShaderGraph.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

install(TARGETS ShaderGraph
    BUNDLE DESTINATION "."
    RUNTIME DESTINATION bin)

# Using macro from cmake/cleanCpppExtensions.cpp included on the top
# Provides ShaderGraph-run and ShaderGraph-dbg
addRunAndDebugTargets(ShaderGraph)

# short convenience target from cmake/cleanCpppExtensions.cpp
add_custom_target(run DEPENDS ShaderGraph-run)

# Manually specified convenience target for running the binary, we use macro
# add_custom_target(ShaderGraph-run
#     WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
#     USES_TERMINAL
#     COMMAND ./ShaderGraph
#     DEPENDS Install_)

# And this would add -DBAR_ENABLE_FEATURE or equivalent to build command
# target_compile_definitions(ShaderGraph PRIVATE BAR_ENABLE_FEATURE)

# Add compile time definition based on option
# option(OPTION_NAME "description for end user" OFF)
# if(OPTION_NAME)
#     # you can do anything here, eg. setup new optional executable
#     target_compile_definitions(ShaderGraph PRIVATE DEFINE_NAME)
# endif()

# Add building new shared library
# add_library(exampleLibrary SHARED ${LIBRARY_SOURCES})
# target_link_libraries (exampleLibrary ${CMAKE_THREAD_LIBS_INIT})
# set_property(TARGET exampleLibrary PROPERTY CXX_STANDARD 14) # we want C++14

# How to include and link OpenGL and GLUT libraries
# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
# target_include_directories(ShaderGraph SYSTEM ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
# target_link_libraries(ShaderGraph ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

#------------------------------------------------------------------------------
# (val) FIXME : should be place here ?

if(APPLE AND EXISTS /usr/local/opt/qt5)
    # Homebrew installs Qt5 (up to at least 5.9.1) in
    # /usr/local/qt5, ensure it can be found by CMake since
    # it is not in the default /usr/local prefix.
    list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/qt5")
endif()

# Find the QtWidgets library
find_package(
        Qt5 COMPONENTS
        Core
        Widgets
        Gui
        OpenGL)

#------------------------------------------------------------------------------
# Unit tests

add_subdirectory(unittest)

#-------------------------------------------------------------------------------
# Copy MINGW needed libraries for building on windows

if(MINGW)
    message(STATUS "MinGW detected")
    get_filename_component(GCC_PATH ${CMAKE_C_COMPILER} PATH)
    if(${GCC_PATH} MATCHES "mingw64/bin")
        set(libgcc "libgcc_s_seh-1.dll") #64bit
        message(STATUS "  64bit dlls is building")
    else()
        set(libgcc "libgcc_s_dw2-1.dll") #32bit
        message(STATUS "  32bit dlls is building")
    endif()

    install(FILES ${GCC_PATH}/${libgcc}
        ${GCC_PATH}/libwinpthread-1.dll
        ${GCC_PATH}/libstdc++-6.dll
        DESTINATION ./bin/
    )
endif(MINGW)


#------------------------------------------------------------------------------
# Other MISC targets

# Adds misc targets: format, cppcheck, tidy, see cmake/cleanCppExtensions.cmake
addMiscTargets()
