//
// Created by Dylan Beaumont on 25/2/2025.
//

#ifndef PIXELSORTER_H
#define PIXELSORTER_H
#include <random>

struct Pixel {
    int colourRank {0};
    char c[4] {0, 0, 0, 0};
    bool operator < (const Pixel pixel) const {
        return colourRank < pixel.colourRank;
    }
};

class PixelSorter {
public:
    PixelSorter(int rowLow, int rowHigh, int colLow, int colHigh):
        dev(),
        rng(dev()),
        distRow(rowLow, rowHigh),
        distCol(colLow, colHigh)
    {};

    unsigned char* sort(unsigned char* data, int x, int y);
    void sortRow(unsigned char* row, int x, char *kernel, int granularity);
private:
    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<int> distRow;
    std::uniform_int_distribution<int> distCol;
};



#endif //PIXELSORTER_H
