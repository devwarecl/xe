
#include "Vector.hpp"
#include <cassert>

namespace XE::Math {
    template<typename T, int N>
    Vector<T, N>::Vector() {

    }

    template<typename T, int N>
    Vector<T, N>::Vector(T value) {
        for (T &element : Data) {
            element = value;
        }
    }

    template<typename T, int N>
    Vector<T, N>::Vector(const T *values) {
        assert(values);

        for (int i=0; i<N; i++) {
            Data[i] = values[i];
        }
    }

    template<> struct Vector<std::int32_t, 2>;
    template<> struct Vector<std::int32_t, 3>;
    template<> struct Vector<std::int32_t, 4>;

    template<> struct Vector<float, 2>;
    template<> struct Vector<float, 3>;
    template<> struct Vector<float, 4>;

    template<> struct Vector<double, 2>;
    template<> struct Vector<double, 3>;
    template<> struct Vector<double, 4>;
}
