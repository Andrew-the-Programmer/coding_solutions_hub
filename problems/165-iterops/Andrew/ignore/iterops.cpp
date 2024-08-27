#pragma once

#include <iterator>

namespace concepts {
template <class Iter>
concept InputIterator = requires(Iter it) {
    it != it;
    *it;
    ++it;
};
}  // namespace concepts
