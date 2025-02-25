//
// Created by Dylan Beaumont on 25/2/2025.
//

#ifndef PALETTE_H
#define PALETTE_H
#include <utility>
#include <vector>

struct Colour {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    bool operator <(Colour colour) const {
        return this->g < colour.g;
    }
};

class Palette {
    std::vector<Colour> colours;
public:
    Palette(std::vector<Colour> _colours): colours(std::move(_colours)){};
    unsigned char* filter(unsigned char* data, int x, int y);
    void findColour(unsigned char* pixel) const;
    void pickColours(unsigned char* data, int x, int y);
private:
    int NCOLOURS = 5;
};




#endif //PALETTE_H
