# >>> Set default Configuration directory...
if(NOT CONF_DIR)
    set(CONF_DIR "${CMAKE_INSTALL_PREFIX}/etc")
    message(STATUS "Unix: Using default Configuration Directory")
endif()

# >>> Set default Library directory...
if(NOT LIBSDIR)
    set(LIBSDIR ${CMAKE_INSTALL_PREFIX}/lib)
    message(STATUS "Unix: Using default Library Directory")
endif()

# >>> Configure Uninstaller...
configure_file(
        "${CMAKE_SOURCE_DIR}/CMake/Platform/CMakeUninstall.in.cmake"
        "${CMAKE_BINARY_DIR}/CMakeUninstall.cmake"
        @ONLY)
message(STATUS "Unix: Configuring uninstall target")

# >>> Create uninstaller target (allows for using "make uninstall")
add_custom_target(uninstall
        "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/CMakeUninstall.cmake")
message(STATUS "Unix: Created uninstall target")

# >>> Compiler specification
message(STATUS "Unix: Detected Compiler: ${CMAKE_C_COMPILER}")
if(CMAKE_C_COMPILER MATCHES "gcc" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    include(${CMAKE_SOURCE_DIR}/CMake/Compiler/GCC/Settings.cmake)
elseif(CMAKE_C_COMPILER MATCHES "icc")
    include(${CMAKE_SOURCE_DIR}/CMake/Compiler/ICC/Settings.cmake)
elseif(CMAKE_C_COMPILER MATCHES "clang" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    include(${CMAKE_SOURCE_DIR}/CMake/Compiler/Clang/Settings.cmake)
else()
    target_compile_definitions(serenity-compiling-options-interface
            INTERFACE
                -D_BUILD_DIRECTIVE="${CMAKE_BUILD_TYPE}")
endif()