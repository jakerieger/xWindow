cmake_minimum_required(VERSION 3.30)
project(xWindow)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
set(INC ${CMAKE_CURRENT_SOURCE_DIR}/Include/xWindow)
set(SHARED ${CMAKE_CURRENT_SOURCE_DIR}/Shared)
set(VEND ${CMAKE_CURRENT_SOURCE_DIR}/Vendor)

include(CMake/DetectWindowingSystem.cmake)

include_directories(
        ${INC}
        ${SHARED}
        ${SRC}
        ${VEND}
)

add_library(xWindow STATIC
        # SHARED
        ${SHARED}/Types.hpp
        ${SHARED}/Panic.hpp
        ${SHARED}/Expect.hpp
        ${SHARED}/IO.hpp
        ${SHARED}/EventSystem.hpp

        # INCLUDES
        ${INC}/Events.hpp
        ${INC}/NativeWindow.hpp
        ${INC}/Window.hpp

        # SOURCES
        ${SRC}/Window.cpp
)


# Handle platform-specific sources
if (WINDOWING_SYSTEM STREQUAL "Win32")
    target_compile_definitions(xWindow PUBLIC -D_WS_WINDOWS)

    target_sources(xWindow PRIVATE
            ${INC}/Platform/Win32Window.hpp
            ${SRC}/Platform/Win32Window.cpp
    )
elseif (WINDOWING_SYSTEM STREQUAL "X11")
    add_definitions(-D_WS_X11)
    target_compile_definitions(xWindow PUBLIC -D_WS_X11)

    target_sources(xWindow PRIVATE
            ${INC}/Platform/X11Window.hpp
            ${SRC}/Platform/X11Window.cpp
    )

    target_link_libraries(xWindow PRIVATE X11)
elseif (WINDOWING_SYSTEM STREQUAL "Wayland")
    add_definitions(-D_WS_WAYLAND)
    target_compile_definitions(xWindow PUBLIC -D_WS_WAYLAND)

    target_sources(xWindow PRIVATE
            ${INC}/Platform/xdg-shell-client-protocol.h
            ${INC}/Platform/WaylandWindow.hpp
            ${SRC}/Platform/xdg-shell-client-protocol.c
            ${SRC}/Platform/WaylandWindow.cpp
    )

    target_link_libraries(xWindow PRIVATE
            wayland-client
            wayland-egl
    )
elseif (WINDOWING_SYSTEM STREQUAL "Apple")
    target_compile_definitions(xWindow PUBLIC -D_WS_APPLE)

    #    target_sources(xWindow PRIVATE
    #            ${INCDIR}/xWindow/AppleWindow.h
    #            ${SRCDIR}/AppleWindow.cpp
    #    )
endif ()

# Build demo
message("-- Building xWindow Demo.")
add_subdirectory(Demo)