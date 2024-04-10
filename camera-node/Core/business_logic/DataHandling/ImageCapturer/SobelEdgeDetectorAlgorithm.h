#pragma once
#include "IEdgeDetectorAlgorithm.h"
#include <iostream>
#include <iostream>
#include <cmath>
#include <vector>

class SobelEdgeDetectorAlgorithm : public IEdgeDetectorAlgorithm
{
private:
    std::vector<std::vector<int>> sobel_x = {{-1, 0, 1},
                                             {-2, 0, 2},
                                             {-1, 0, 1}};

    std::vector<std::vector<int>> sobel_y = {{-1, -2, -1},
                                             {0, 0, 0},
                                             {1, 2, 1}};


    int applyKernel(const std::vector<std::vector<int>> &kernel, const uint8_t* region)
    {
        int sum = 0;
        for (size_t i = 0; i < kernel.size(); ++i)
        {
            for (size_t j = 0; j < kernel[i].size(); ++j)
            {
                sum += kernel[i][j] * region[i * imgWidth + j];
            }
        }
        return sum;
    }

    void sobelGradient(const uint8_t* const bufferAddr, double** edges)
    {
        for (size_t i = 1; i < imgHeight - 1; ++i)
        {
            for (size_t j = 1; j < imgWidth - 1; ++j)
            {
                // Calcular gradientes en dirección x e y
                int gx = applyKernel(sobel_x, bufferAddr + ((i - 1) * imgWidth + j - 1));
                int gy = applyKernel(sobel_y, bufferAddr + ((i - 1) * imgWidth + j - 1));


                // Calcular la magnitud del gradiente
                const auto idx = (i * imgWidth) + j;
                edges[i][j] = sqrt(pow(gx, 2) + pow(gy, 2));
            }
        }
    }

//
//    int applyKernel(const std::vector<std::vector<int>> &kernel, const uint8_t* region)
//    {
//        int sum = 0;
//        for (size_t i = 0; i < kernel.size(); ++i)
//        {
//            for (size_t j = 0; j < kernel[i].size(); ++j)
//            {
//                sum += kernel[i][j] * region[i * imgWidth + j];
//            }
//        }
//        return sum;
//    }
//
//    // Función para calcular la magnitud del gradiente en una imagen dada
//    void sobelGradient(const uint8_t* const bufferAddr, double** edges)
//    {
//        for (size_t i = 1; i < imgHeight - 1; ++i)
//        {
//            for (size_t j = 1; j < imgWidth - 1; ++j)
//            {
//                // Calcular gradientes en dirección x e y
//                int gx = applyKernel(sobel_x, bufferAddr + ((i - 1) * imgWidth + j - 1));
//                int gy = applyKernel(sobel_y, bufferAddr + ((i - 1) * imgWidth + j - 1));
//
//                // Calcular la magnitud del gradiente
//                const auto idx = (i*imgHeight) + j;
//                edges[i][j] = sqrt(pow(gx, 2) + pow(gy, 2));
//            }
//        }
//    }

public:
    void process(const uint8_t* const bufferAddr,double* * edges) override
    {
//        const auto height = image.size();
//        const auto width = image.at(0).size();
//        const auto sizeImg = height * width;
//        std::cout << "SobelEdgeDetectorAlgorithm executed for image of size:" << std::to_string(sizeImg) << std::to_string(height) << "x" << std::to_string(width) << std::endl;

        sobelGradient(bufferAddr, edges);
    }
};
