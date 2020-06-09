#ifndef _K_LOG_LOG_H_
#define _K_LOG_LOG_H_

#ifdef WindowsBuild
#include "Log_windows.h"
#else
#include "Log_linux.h"
#endif  // LinuxBuild

#endif  // _K_LOG_LOG_H_
