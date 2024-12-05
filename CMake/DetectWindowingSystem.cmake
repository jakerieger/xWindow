if (WIN32)
    set(WINDOWING_SYSTEM "Win32")
    message(STATUS "Found windowing system: Win32")
elseif (UNIX AND NOT APPLE)
    add_definitions(-DPLATFORM_LINUX)
    # Check for X11
    find_package(X11 QUIET)
    # Check for Wayland
    find_package(PkgConfig)
    pkg_check_modules(WAYLAND_CLIENT QUIET wayland-client)

    # Determine the active windowing system and set preprocessor defines
    if (DEFINED ENV{WAYLAND_DISPLAY})
        set(WINDOWING_SYSTEM "Wayland")
        message(STATUS "Found windowing system: Wayland/EGL")

        pkg_check_modules(WAYLAND_EGL REQUIRED wayland-egl)
        pkg_check_modules(WAYLAND_PROTO REQUIRED wayland-protocols)
        pkg_check_modules(EGL REQUIRED egl)
    elseif (DEFINED ENV{DISPLAY})
        set(WINDOWING_SYSTEM "X11")
        message(STATUS "Found windowing system: X11 (Xlib)")
    else ()
        message(STATUS "No active windowing system detected")
    endif ()
elseif (APPLE)
    set(WINDOWING_SYSTEM "Apple")
    message(STATUS "Found windowing system: macOS")
else ()
    message(STATUS "No active or supported windowing system was detected.")
endif ()