#include <iostream>
#include <random>
#include <stb_image.h>
#include <stb_image_write.h>

#include "Effect.h"
#include "Palette.h"
#include "Pixelator.h"
#include "PixelSorter.h"

unsigned char* maskBlend(unsigned char* base, unsigned char* toBlend, unsigned char* mask, int x, int y);

int main() {
    // load in the data
    int x,y,n;
    unsigned char *data = stbi_load("../image.jpg", &x, &y, &n, 4);

    // Pixelated
    Pixelator pixelator(7);
    unsigned char* pixelated = pixelator.pixelate(data, x, y);
    std::cout << stbi_write_jpg("../images/pixelated.jpg",x,y,4,pixelated,100);

    // Restricted Palette
    std::vector<Colour> colours; // when an empty colour vector is passed, colours are auto-generated
    Palette palette(colours);
    unsigned char* repainted = palette.filter(data, x, y);
    std::cout << stbi_write_jpg("../images/palette.jpg",x,y,4,repainted,100);

    // Pixelated + Restricted Palette
    unsigned char* pixelPalette = palette.filter(pixelated, x, y);
    std::cout << stbi_write_jpg("../images/pixelPalette.jpg",x,y,4,pixelPalette,100);

    // Box Blur + Sharpen Edges
    float blurKernel[25] = {0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,0.04,};
    Effect blur{blurKernel, 5, 5, 1};
    unsigned char* blurred = blur.apply(data, x, y);
    float maskKernel[9] = {-2,-1,0, -1,0,1, 0,1,2};
    Effect edges{maskKernel, 3, 3, 1};
    unsigned char* mask = edges.apply(data, x, y);
    unsigned char* blended = maskBlend(blurred, data, mask, x, y);
    std::cout << stbi_write_jpg("../images/edges.jpg",x,y,4,mask,100);
    std::cout << stbi_write_jpg("../images/blurSharp.jpg",x,y,4,blended,100);

    // Sort the Pixels
    PixelSorter pixelSorter(20, 100, 3, 5);
    unsigned char* sorted = pixelSorter.sort(data, x, y);
    std::cout << stbi_write_jpg("../images/sorted.jpg",x,y,4,sorted,100);

}

unsigned char* maskBlend(unsigned char* base, unsigned char* toBlend, unsigned char* mask, int x, int y) {
    for(int i = 0; i < y; i++) {
        for(int j = 0; j < x; j++) {
            float intensity = std::clamp(((float)mask[(i*x+j)*4] + (float)mask[(i*x+j)*4+1] + (float)mask[(i*x+j)*4+2]) / 255.f, 0.0f, 1.0f); // weighting
            base[(i*x+j)*4] = base[(i*x+j)*4]*(1.0f-intensity) + toBlend[(i*x+j)*4]*(intensity);
            base[(i*x+j)*4+1] = base[(i*x+j)*4+1]*(1.0f-intensity) + toBlend[(i*x+j)*4+1]*(intensity);
            base[(i*x+j)*4+2] = base[(i*x+j)*4+2]*(1.0f-intensity) + toBlend[(i*x+j)*4+2]*(intensity);
        }
    }
    return base;
}
