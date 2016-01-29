#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include <iostream>

namespace pg {
template <typename T>
class optional {
public:
    optional() {}
    bool is_initialized() const {
        return initialized;
    }

    explicit operator bool() const {
        return initialized;
    }

    T& operator*() {
        return v;
    }

    T* operator->() {
        return &v;
    }

    T& get() {
        return v;
    }

    // singal varable
    template<typename H>
    T& operator=(H& p) {
        v = std::move(p);
        initialized = true;

        return v;
    }

    // initializer list
    template <typename H>
    T& operator=(std::initializer_list<H> &il) {
        v = il;
        initialized = true;

        return v;
    }

private:
    bool initialized = false;
    T v;
};

}

#endif // OPTIONAL_HPP

