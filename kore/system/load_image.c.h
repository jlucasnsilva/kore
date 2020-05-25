#include "loader.h"

#ifdef WindowsBuild
// Implementations are in a header file because
// the Makefile adds *.c
#include "load_image_windows.h"
#endif

#ifdef LinuxBuild
// Implementations are in a header file because
// the Makefile adds *.c
#include "load_image_linux.h"
#endif
