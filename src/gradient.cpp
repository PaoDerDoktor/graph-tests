#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <string>
#include <algorithm>

const uint64_t SEED(17082000);

int main(int argc, char const *argv[]) {
    uint64_t height = 256;
    uint64_t width  = 256;
    uint64_t size   = width*height;
    int channels = 1;
    std::string filename("out.png");

    uint8_t* bitmap = new uint8_t[size];
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            bitmap[j+i*256] = i/2+j/2;
        }
    }

    stbi_write_png(filename.c_str(), width, height, channels, bitmap, width*channels);

    return 0;
}
