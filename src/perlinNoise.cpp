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
#include <iostream>
#include <vector>
#include <algorithm>

#include "utils/Vect2D.hpp"

std::vector<Vect2D> generate_2D_unit_vectors(uint64_t amount) {
    // Preparing random
    std::uniform_real_distribution<double> randomRange(0.0, 1.0);
    std::default_random_engine randomEngine;
    
    // Computing randoms
    std::vector<Vect2D> unitVectors;
    for (uint64_t i=0; i < amount; i++) {
        // Getting 2 random [0.0, 1.0] doubles
        double x(randomRange(randomEngine));
        double y(randomRange(randomEngine));
        // Building a Vect2D from those doubles
        Vect2D randomVect(x, y);
        
        // Making the Vect2D unit (magnitude of `1`) and adding it to the std::vector
        randomVect.make_unit();
        unitVectors.push_back(randomVect);
    }

    return unitVectors;
}

std::array<Vect2D, 4> get_2D_corners(Vect2D point, uint64_t cellSize) {
    // Getting top-left corner coordinates
    Vect2D topLeftPoint(std::floor(point.get_x()/cellSize), std::floor(point.get_y()/cellSize));

    // Computing corners
    std::array<Vect2D, 4> corners;
    corners[0] = Vect2D(topLeftPoint);
    corners[1] = Vect2D(topLeftPoint.get_x()+1, topLeftPoint.get_y());
    corners[2] = Vect2D(topLeftPoint.get_x()  , topLeftPoint.get_y()+1);
    corners[3] = Vect2D(topLeftPoint.get_x()+1, topLeftPoint.get_y()+1);

    return corners;
}

std::array<Vect2D, 4> get_2D_corners_to_point_vectors(const std::array<Vect2D, 4> &corners, const Vect2D &point) {
    // Getting the coordinates of the point in the subgrid
    Vect2D subgridPoint(point.get_x(), point.get_y());

    // Getting vectors going from each cell corner to the studied point
    std::array<Vect2D, 4> cornersToPointVectors;
    cornersToPointVectors[0] = Vect2D(corners[0], subgridPoint);
    cornersToPointVectors[1] = Vect2D(corners[1], subgridPoint);
    cornersToPointVectors[2] = Vect2D(corners[2], subgridPoint);
    cornersToPointVectors[3] = Vect2D(corners[3], subgridPoint);

    return cornersToPointVectors;
}

double fade(double t) {
    return 3*t*t - 2*t*t*t;
}

std::vector<uint8_t> generate_greyscale_perlin_noise_bitmap(uint64_t height, uint64_t width, uint64_t cellSize) {
    // Preparing result bitmap
    std::vector<uint8_t> bitmap;
    
    // Generating gradient vectors
    std::vector<Vect2D> gradientVectors = generate_2D_unit_vectors((height/cellSize+1)*(width/cellSize+1));

    // Computing dot products
    for (uint64_t j=0; j < height; j++) {
        for (uint64_t i=0; i < width; i++) {
            // Getting current point
            Vect2D point(i, j);
            
            // Getting corners
            std::array<Vect2D, 4> corners = get_2D_corners(point, cellSize);

            // Getting vectors to point
            std::array<Vect2D, 4> vectorsToPoint = get_2D_corners_to_point_vectors(corners, point);

            // Getting dot products
            double s = gradientVectors[corners[0].get_y()*(width/cellSize+1)+corners[0].get_x()].dot(vectorsToPoint[0]);
            double t = gradientVectors[corners[1].get_y()*(width/cellSize+1)+corners[1].get_x()].dot(vectorsToPoint[1]);
            double u = gradientVectors[corners[2].get_y()*(width/cellSize+1)+corners[2].get_x()].dot(vectorsToPoint[2]);
            double v = gradientVectors[corners[3].get_y()*(width/cellSize+1)+corners[3].get_x()].dot(vectorsToPoint[3]);

            // Getting dimensional weights
            double Sx = fade(i/cellSize - corners[0].get_x());
            double Sy = fade(j/cellSize - corners[0].get_y());

            // Getting interpolations
            double a = s + Sx*(t-s);
            double b = u + Sx*(v-u);

            double z = a + Sy*(b-a);

            bitmap.push_back(z);
        }
    }

    return bitmap;
}

#ifdef TARGET_PERLINNOISE
int main(int argc, char const *argv[]) {
    uint64_t height = 2048;
    uint64_t width  = 2048;
    int channels = 1;
    
    // Truly pseudorandom one
    std::string filename("perlinNoise.png");
    std::vector<uint8_t> bitmap = generate_greyscale_perlin_noise_bitmap(height, width, 4);
    stbi_write_png(filename.c_str(), width, height, channels, &bitmap[0], width*channels);


    return 0;
}
#endif