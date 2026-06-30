#pragma once

#ifdef _WIN32
    #ifdef LOGEN_CORE_EXPORTS
        #define LOGEN_API __declspec(dllexport)
    #else
        #define LOGEN_API __declspec(dllimport)
    #endif
#else
    #define LOGEN_API __attribute__((visibility("default")))
#endif