#pragma once

#if defined(_WIN32) || defined(_WIN64)
#if defined(EXPORT_DLL)
#define CAEPARSER_API __declspec(dllexport)
#else
#define CAEPARSER_API __declspec(dllimport)
#endif
#elif defined(__linux__)
#define CAEPARSER_API __attribute__((visibility("default")))
#endif

#include <string>
#include <typeindex>

namespace CAEParser {
CAEPARSER_API std::string demangle_type_index(
    const std::type_index& type_index);
}
