#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define CAEPARSER_API __declspec(dllexport)
#elif defined(__linux__)
#define CAEPARSER_API __attribute__((visibility("default")))
#endif