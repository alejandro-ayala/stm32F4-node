#pragma once
#include "IEdgeDetectorAlgorithm.h"
#include "SobelEdgeDetectorAlgorithm.h"
#include <vector>
#include <array>
#include <memory>
#include "EdgeDetector.h"

namespace business_logic
{
namespace DataHandling
{
class EdgeDetector
{
private:
    std::shared_ptr<IEdgeDetectorAlgorithm> m_detectionEdgeAlgo;

public:
    EdgeDetector(const std::shared_ptr<IEdgeDetectorAlgorithm> &detectionEdgeAlgo = std::make_shared<SobelEdgeDetectorAlgorithm>());
    ~EdgeDetector() = default;
    void processImage(const uint8_t* const bufferAddr,double* * edges);
};
}
}
