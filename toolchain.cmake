set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath-link,${CMAKE_SYSROOT}/opt/vc/lib:${CMAKE_SYSROOT}/lib/arm-linux-gnueabihf:${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf:${CMAKE_SYSROOT}/usr/local/lib")

set(ENV{PKG_CONFIG_DIR} "")
set(ENV{PKG_CONFIG_LIBDIR} "${CMAKE_SYSROOT}/usr/lib/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig:${CMAKE_SYSROOT}/usr/lib/arm-linux-gnueabihf/pkgconfig/")
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})
