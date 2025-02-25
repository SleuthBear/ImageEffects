//
// Created by Dylan Beaumont on 25/2/2025.
//

#ifndef PIXELATOR_H
#define PIXELATOR_H



class Pixelator {
public:
    Pixelator(int size): pixelSize(size){};
    unsigned char* pixelate(unsigned char* image, int x, int y);
private:
    int pixelSize;
};



#endif //PIXELATOR_H
