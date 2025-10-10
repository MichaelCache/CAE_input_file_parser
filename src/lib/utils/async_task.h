#pragma once

#include "platform.h"

namespace CAEParser {

template <typename F>
concept VoidFunction = std::is_invocable_r_v<void, F>;

template <typename Func>
class AsyncTask;

}  // namespace CAEParser
