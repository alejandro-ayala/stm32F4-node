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

    // Función para aplicar el kernel de convolución a una región de la imagen
    int applyKernel(const std::vector<std::vector<int>> &kernel, const std::vector<std::vector<uint8_t>> &region)
    {
        int sum = 0;
        for (size_t i = 0; i < kernel.size(); ++i)
        {
            for (size_t j = 0; j < kernel[i].size(); ++j)
            {
                sum += kernel[i][j] * region[i][j];
            }
        }
        return sum;
    }

    // Función para calcular la magnitud del gradiente en una imagen dada
    void sobelGradient(const std::array<std::array<uint8_t, imgWidth>, imgHeight> &image, std::array<std::array<double, imgWidth>, imgHeight> &edges)
    {
        for (size_t i = 1; i < image.size() - 1; ++i)
        {
            for (size_t j = 1; j < image[i].size() - 1; ++j)
            {
                // Calcular gradientes en dirección x e y
                int gx = applyKernel(sobel_x, {{image[i - 1][j - 1], image[i - 1][j], image[i - 1][j + 1]},
                                               {image[i][j - 1], image[i][j], image[i][j + 1]},
                                               {image[i + 1][j - 1], image[i + 1][j], image[i + 1][j + 1]}});
                int gy = applyKernel(sobel_y, {{image[i - 1][j - 1], image[i - 1][j], image[i - 1][j + 1]},
                                               {image[i][j - 1], image[i][j], image[i][j + 1]},
                                               {image[i + 1][j - 1], image[i + 1][j], image[i + 1][j + 1]}});

                // Calcular la magnitud del gradiente
                edges[i][j] = sqrt(pow(gx, 2) + pow(gy, 2));
            }
        }
    }

public:
    void process(const std::array<std::array<uint8_t, imgWidth>, imgHeight> &image, std::array<std::array<double, imgWidth>, imgHeight> &edges) override
    {
        const auto height = image.size();
        const auto width = image.at(0).size();
        const auto sizeImg = height * width;
        std::cout << "SobelEdgeDetectorAlgorithm executed for image of size:" << std::to_string(sizeImg) << std::to_string(height) << "x" << std::to_string(width) << std::endl;

        sobelGradient(image, edges);
    }
};
