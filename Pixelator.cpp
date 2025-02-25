//
// Created by Dylan Beaumont on 25/2/2025.
//

#include "Pixelator.h"

#include <cstring>
#include <math.h>

unsigned char *Pixelator::pixelate(unsigned char* image, int x, int y) {
    //Pixelate the image, using the intensity mask as a weight for pixel values
    auto* copy = new unsigned char[x*y*4];
    memcpy(copy, image, x*y*4);
    int weighting = (pixelSize*pixelSize);
    for(int i = 0; i < y-pixelSize; i+=pixelSize-2) {
        for(int j = 0; j < x-pixelSize; j+=pixelSize-2) {
            float averaged[4] = {0, 0, 0, 1};
            for(int k = 0; k < pixelSize; k++) {
                for(int l = 0; l < pixelSize; l++) {
                    averaged[0] += powf(image[((i+k)*x+j+l)*4] /255.f, 2.2f)/weighting;
                    averaged[1] += powf(image[((i+k)*x+j+l)*4+1]/255.f, 2.2f)/weighting;
                    averaged[2] += powf(image[((i+k)*x+j+l)*4+2]/255.f, 2.2f)/weighting;
                    averaged[3] += powf(image[((i+k)*x+j+l)*4+3]/255.f, 2.2f)/weighting;

                }
            }
            // inefficient could be doing this sums during loop, although possible cache missess.
            for(int k = 0; k < pixelSize; k++) {
                for(int l = 0; l < pixelSize; l++) {
                    copy[((i+k)*x+j+l)*4] = powf(averaged[0], 1.f/2.2f)*255.f;
                    copy[((i+k)*x+j+l)*4+1] = powf(averaged[1], 1.f/2.2f)*255.f;
                    copy[((i+k)*x+j+l)*4+2] = powf(averaged[2], 1.f/2.2f)*255.f;
                    copy[((i+k)*x+j+l)*4+3] = powf(averaged[3], 1.f/2.2f)*255.f;
                }
            }
        }
    }
    return copy;
}
