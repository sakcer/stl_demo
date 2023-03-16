#include "hash_fun.hpp"
#include <functional>
#include <iostream>

namespace myHash {
template <>
size_t HashFun::operator()(const std::string& a) {
    return hash_val(a);
}
}  // namespace myHash