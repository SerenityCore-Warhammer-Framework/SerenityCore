# >>> Prüft auf was für einer Platform Serenity Installiert bzw Compilert werden soll...
if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PLATFORM 64)
    message(STATUS "Detected 64-bit Platform")
else()
    set(PLATFORM 32)
    message(STATUS "Detected 32-bit Platform")
endif()

if(WIN32)
    include("${CMAKE_SOURCE_DIR}/CMake/Platform/Windows/Settings.cmake")
elseif(UNIX)
    include("${CMAKE_SOURCE_DIR}/CMake/Platform/Unix/Settings.cmake")
endif()