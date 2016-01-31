#ifndef MAKE_UNIQUE_HPP
#define MAKE_UNIQUE_HPP

#include <memory>

namespace pg {
template <typename T, typename ...Args>
std::unique_ptr<T> make_unique(Args&& ...args) {
   return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
std::unique_ptr<T> make_unique(size_t size) {
    return std::unique_ptr<T>(new T[size]{});
}
}

#endif // MAKE_UNIQUE_HPP

