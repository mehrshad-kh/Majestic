#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdint>

constexpr uint32_t kSaltLen = 16;
constexpr uint32_t kHashLen = 32;
constexpr uint32_t kTimeCost = 2; // 2-pass computation
constexpr uint32_t kMemoryCost = (1 << 16); // 64 MiB memory usage
constexpr uint32_t kParallelism = 2; // Number of threads and lanes


#endif // CONSTANTS_HPP
