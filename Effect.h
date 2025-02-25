//
// Created by Dylan Beaumont on 24/2/2025.
//

#ifndef IMAGEKERNEL_H
#define IMAGEKERNEL_H
#include <cstring>
#include <iostream>


class Effect {
public:
    Effect(float *_kernel, int _x, int _y, int _stride): kernel(new float[_x*_y]), x(_x), y(_y), stride(_stride) {
        if(x%2 == 0 || y%2 == 0) {
            std::cout << "x and y must be odd" << std::endl;
            delete[] kernel;
            return;
        }
        memcpy(kernel, _kernel, x*y*sizeof(float));
    }

    ~Effect() {
        delete[] kernel;
    }

    unsigned char* apply(unsigned char* data, const int w, const int h);

private:
    float *kernel;
    int x, y; // width and height of the kernel
    int stride;
};



#endif //IMAGEKERNEL_H
