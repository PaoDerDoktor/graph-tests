#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#endif

#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

uint8_t* generate_greyscale_random_pattern_bitmap(uint64_t height, uint64_t width, unsigned int seed) {
    uint64_t size(width*height);
    std::srand(seed);

    uint8_t* bitmap = new uint8_t[size];

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            bitmap[i*width+j] = std::rand()%256;
        }
    }

    return bitmap;
}

#ifdef TARGET_RANDOMPATTERN
int main(int argc, char const *argv[]) {
    uint64_t height = 512;
    uint64_t width  = 1024;
    int channels = 1;
    
    // Truly pseudorandom one
    std::string filename("randomPattern - timed random.png");
    uint8_t *bitmap = generate_greyscale_random_pattern_bitmap(height, width, std::time(nullptr));
    stbi_write_png(filename.c_str(), width, height, channels, bitmap, width*channels);

    delete bitmap;

    // Seeded psuedorandom one
    filename = "randomPattern - seeded random.png";
    bitmap = generate_greyscale_random_pattern_bitmap(height, width, 17082000);
    stbi_write_png(filename.c_str(), width, height, channels, bitmap, width*channels);

    return 0;
}
#endif
