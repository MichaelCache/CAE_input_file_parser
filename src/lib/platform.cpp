#include "platform.h"

#ifdef __GNUC__
#include <cxxabi.h>
#endif
namespace CAEParser {

std::string demangle_type_index(const std::type_index& type_index) {
#ifdef __GNUC__
  int status = 0;
  char* demangled =
      abi::__cxa_demangle(type_index.name(), nullptr, nullptr, &status);
  if (status == 0) {
    std::string result(demangled);
    std::free(demangled);
    return result;
  } else {
    return "cxa_demangle_error";
  }
#endif
  return type_index.name();
}
}  // namespace CAEParser