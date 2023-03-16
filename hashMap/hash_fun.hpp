#include <functional>
#include <iostream>

namespace myHash {
class HashFun {
    template <typename T>
    inline void hash_combine(size_t& seed, const T& val) {
        seed ^= std::hash<T>()(val) + 0x9e37779b9 + (seed << 6) + (seed >> 2);
    }

    template <typename T>
    inline void hash_val(size_t& seed, const T& val) {
        hash_combine(seed, val);
    }

    template <typename T, typename... Types>
    inline void hash_val(size_t& seed, const T& val, const Types&... args) {
        hash_combine(seed, val);
        hash_val(seed, args...);
    }

    template <typename... Types>
    inline size_t hash_val(const Types&... args) {
        size_t seed = 0;
        hash_val(seed, args...);
        return seed;
    }

  public:
    template <typename T>
    size_t operator()(const T& a) {
        return std::hash<T>(a);
    }
};

template <>
size_t HashFun::operator()(const std::string& a);
}  // namespace myHash
