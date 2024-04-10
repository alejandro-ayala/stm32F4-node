#pragma once
#include <cstdint>
#include <vector>
#include <array>
constexpr uint32_t imgWidth = 32;
constexpr uint32_t imgHeight = 24;
class IEdgeDetectorAlgorithm
{
public:
    virtual void process(const uint8_t* const bufferAddr,double* * edges) = 0;
};
