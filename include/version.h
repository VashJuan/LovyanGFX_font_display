/**
 * @file version.h
 * @brief Version information - auto-generated during build
 */

#pragma once

// Version will be injected by build system from git tags
#ifndef PROJECT_VERSION
#define PROJECT_VERSION "unknown"
#endif

#ifndef BUILD_TIMESTAMP
#define BUILD_TIMESTAMP __DATE__ " " __TIME__
#endif

// Helper macros for version display
#define VERSION_STRING "LovyanGFX Font Display v" PROJECT_VERSION
#define STARTUP_MESSAGE_VERSION "=== M5 Dial Font Display v" PROJECT_VERSION " ==="