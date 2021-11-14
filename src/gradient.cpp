#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#endif

#include <string>


uint8_t* generate_greyscale_gradient_bitmap(uint64_t height, uint64_t width) {
    uint64_t size(height*width);

    uint64_t yWeight = 2*(height/256);
    uint64_t xWeight = 2*(width /256);

    uint8_t* bitmap = new uint8_t[size];
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            bitmap[i*width+j] = (i/yWeight+j/xWeight);
        }
    }

    return bitmap;
}


#ifdef TARGET_GRADIENT
int main(int argc, char const *argv[]) {
    uint64_t height = 512;
    uint64_t width  = 1024;
    int channels = 1;
    std::string filename("out.png");
    
    uint8_t *bitmap = generate_greyscale_gradient_bitmap(height, width);
    stbi_write_png(filename.c_str(), width, height, channels, bitmap, width*channels);

    return 0;
}
#endif
