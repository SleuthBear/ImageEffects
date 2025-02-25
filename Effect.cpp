//
// Created by Dylan Beaumont on 24/2/2025.
//

#include "Effect.h"

unsigned char* Effect::apply(unsigned char *data, const int w, const int h) {
    // create a new image buffer we can load the transformed data into
    auto *newData = new unsigned char[w*h*4];

    for(int i = y/2; i < h-y/2; i+=stride) {
        for(int j = x/2; j < w-x/2; j+=stride) {
            int r, g, b, a;
            r = (kernel[x*y/2] * (float)data[(i*w+j)*4]);// R
            g = (kernel[x*y/2] * (float)data[(i*w+j)*4+1]);// G
            b = (kernel[x*y/2] * (float)data[(i*w+j)*4+2]);// B
            a = (kernel[x*y/2] * (float)data[(i*w+j)*4+3]);// A
            for(int k = 0; k < y; k++) {
                for(int l = 0; l < x; l++) {
                    r += (kernel[k*x + l] * (float)data[((i-y/2+k)*w+j-x/2+l)*4]);
                    g += (kernel[k*x + l] * (float)data[((i-y/2+k)*w+j-x/2+l)*4+1]);
                    b += (kernel[k*x + l] * (float)data[((i-y/2+k)*w+j-x/2+l)*4+2]);
                    a += (kernel[k*x + l] * (float)data[((i-y/2+k)*w+j-x/2+l)*4+3]);
                }
            }
            newData[(i*w+j)*4] += std::clamp(r, 0, 255);
            newData[(i*w+j)*4+1] += std::clamp(g, 0, 255);
            newData[(i*w+j)*4+2] += std::clamp(b, 0, 255);
            newData[(i*w+j)*4+3] += std::clamp(a, 0, 255);
        }
    }
    return newData;
}
