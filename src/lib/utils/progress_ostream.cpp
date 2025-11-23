#include "progress_ostream.h"

namespace CAEParser {

OstreamWrapper& OstreamWrapper::operator<<(ProgressBar& v) {
  _ost << "\r" << v;
  _progress_mod = true;
  _ost.flush();
  return *this;
}

OstreamWrapper cout_wrapper;
}  // namespace CAEParser
