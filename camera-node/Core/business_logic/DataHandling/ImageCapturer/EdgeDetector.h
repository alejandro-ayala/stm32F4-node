#pragma once
#include "IEdgeDetectorAlgorithm.h"
#include "SobelEdgeDetectorAlgorithm.h"
#include <vector>
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
    std::vector<std::vector<uint8_t>> m_rawImage;
    std::vector<std::vector<double>> processImage(std::vector<std::vector<uint8_t>> rawImage);

public:
    EdgeDetector(const std::shared_ptr<IEdgeDetectorAlgorithm> &detectionEdgeAlgo = std::make_shared<SobelEdgeDetectorAlgorithm>());
    ~EdgeDetector() = default;
};
}
}
