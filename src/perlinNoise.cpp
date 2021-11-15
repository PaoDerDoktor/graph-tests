#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#endif

#include <random>
#include <cmath>
#include <array>

std::pair<double, double> generate_2d_unit_vector()  {
    std::uniform_real_distribution doubleGen(-1, 1);
    std::default_random_engine engine;

    double x = doubleGen(engine);
    double y = doubleGen(engine);

    double magnitude = std::sqrt(x*x + y*y);

    x /= magnitude;
    y /= magnitude;

    return std::make_pair(x, y);
}

std::pair<double, double> compute_2D_vector(std::pair<double, double> pointA, std::pair<double, double> pointB) {
    return std::make_pair(pointB.first-pointA.first, pointB.second-pointB.second);
}

double compute_2D_dot_product(std::pair<double, double> v1, std::pair<double, double> v2) {
    return v1.first*v2.first + v1.second*v1.second;
}

std::array<std::pair<double, double>, 4> get_2D_corners(std::pair<double, double> pixel, uint64_t cellSize) {
    double x = std::floor(pixel.first/cellSize);
    double y = std::floor(pixel.second/cellSize);

    return {
        std::make_pair(x,   y),
        std::make_pair(x+1, y),
        std::make_pair(x,   y+1),
        std::make_pair(x+1, y+1)
    };
}

double interpolate(double dot00, double dot10, double dot01, double dot11, std::pair<double, double> point) {
    double fracX = point.first  - std::floor((point.first) /4);
    double fracY = point.second - std::floor((point.second)/4);

    double ab = dot00 + fracX*(dot10 - dot00);
    double cd = dot01 + fracX*(dot11 - dot01);

    return ab + fracY*(cd-ab);
}

uint8_t* generate_greyscale_perlin_noise_bitmap(uint64_t height, uint64_t width, uint64_t cellSize) {
    uint64_t imageSize(height*width);

    uint64_t cellGridHeight(height/cellSize+1);
    uint64_t cellGridWidth(  width/cellSize+1);
    uint64_t cellGridSize(cellGridHeight*cellGridWidth);

    // Computing gradient vectors

    std::pair<double, double> *cellGrid = new std::pair<double, double>[cellGridSize];
    for (size_t i = 0; i <= height; i++) {
        for (size_t j = 0; j <= width; j++) {
            cellGrid[i*width+j] = generate_2d_unit_vector();
        }
    }

    // Dot products & interpolate

    uint8_t *bitmap = new uint8_t[imageSize];

    for(size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            std::array<std::pair<double, double>, 4> corners = get_2D_corners(std::make_pair(i, j), cellSize);
            double *dots = new double[4];
            
            for (size_t i = 0; i < 4; i++) { // mul cellSize ?
                std::pair<double, double> corner = corners[i];
                dots[i] = compute_2D_dot_product(
                    compute_2D_vector(std::make_pair(i, j), corner),
                    cellGrid[(int)(corner.first*width*cellSize)+(int)(corner.second*cellSize)]
                );
            }
            // Interpolate
            bitmap[i*width+j] = 255*interpolate(dots[0], dots[1], dots[2], dots[3], std::make_pair(i, j));
        }
    }

    return bitmap;
}

#ifdef TARGET_PERLINNOISE
int main(int argc, char const *argv[]) {
    uint64_t height = 512;
    uint64_t width  = 1024;
    int channels = 1;
    
    // Truly pseudorandom one
    std::string filename("randomPattern - timed random.png");
    uint8_t *bitmap = generate_greyscale_perlin_noise_bitmap(height, width, 4);
    stbi_write_png(filename.c_str(), width, height, channels, bitmap, width*channels);

    return 0;
}
#endif