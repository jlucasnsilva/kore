#ifndef _K_LOG_LOG_H_
#define _K_LOG_LOG_H_

#ifdef WindowsBuild
#include "log_windows.h"
#else
#include "log_linux.h"
#endif  // LinuxBuild

#endif  // _K_LOG_LOG_H_
