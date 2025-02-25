//
// Created by Dylan Beaumont on 25/2/2025.
//

#include "Palette.h"

unsigned char *Palette::filter(unsigned char *data, int x, int y) {
    auto filtered = new unsigned char[x*y*4];
    if(colours.size() == 0) {
        pickColours(data, x, y);
    }
    memcpy(filtered, data, x*y*4);
    for(int i = 0; i < x*y; i++) {
        findColour(&filtered[(i)*4]);
    }
    return filtered;
}

void Palette::findColour(unsigned char *pixel) const {
    int distance = 999;
    Colour colour = {0, 0, 0, 1};
    for(int i = 0; i < colours.size(); i++) {
        int localDistance = std::sqrt(
        std::pow((pixel[0]-colours[i].r), 2) +
        std::pow((pixel[1]-colours[i].g), 2) +
        std::pow((pixel[2]-colours[i].b), 2)
        );
        if(localDistance < distance) {
            distance = localDistance;
            colour = colours[i];
        }
    }
    pixel[0] = (pixel[0] + colour.r*4)/5;
    pixel[1] = (pixel[1] + colour.g*4)/5;
    pixel[2] = (pixel[2] + colour.b*4)/5;
}

void Palette::pickColours(unsigned char* data, int x, int y) {
    // pick 5 colours from the range
    std::vector<Colour> range;
    for(int i = 0; i < x*y; i++) {
        range.push_back({data[i*4], data[i*4+1], data[i*4+2], data[i*4+3]});
    }
    std::sort(range.begin(), range.end());
    for(int i = 0; i < NCOLOURS; i++) {
        colours.emplace_back(range[(1+i)*range.size()/NCOLOURS]);
    }
}