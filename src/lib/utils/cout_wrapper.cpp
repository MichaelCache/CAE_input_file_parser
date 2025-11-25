#include "cout_wrapper.h"

namespace CAEParser {

OstreamWrapper& OstreamWrapper::operator<<(ProgressBar& v) {
  _ost << v;
  _progress_mod = true;
  return *this;
}

OstreamWrapper cout_wrapper;
}  // namespace CAEParser
