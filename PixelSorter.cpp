//
// Created by Dylan Beaumont on 25/2/2025.
//

#include "PixelSorter.h"

unsigned char* PixelSorter::sort(unsigned char *data, const int x, const int y) {
    auto* newData = new unsigned char[x*y*4];
    memcpy(newData, data, x*y*4);
    char kernel[4] = {0, 1, 0, 0};
    int count = 0;
    int granularity = 1;
    int shuffleHeight = -1;
    for(int i = 0; i < y; i++) {
        if(count > shuffleHeight) {
            granularity = std::min(static_cast<int>(distRow(rng)), x);
            shuffleHeight = distCol(rng);
            count = 0;
        } else {
            count++;
        }
        sortRow(&newData[i*x*4], x, kernel, granularity);
    }
    return newData;
}

void PixelSorter::sortRow(unsigned char *row, int x, char *kernel, int granularity) {
    auto* pixelRow = new Pixel[granularity]();
    // extract pixel data for the row, and rank it
    for(int i = 0; i < x/granularity; i++) {
        for(int j = 0; j < granularity; j++) {
            // sorting pixels i*granularity to i*granularity+j
            memcpy(pixelRow[j].c, &row[(i*granularity+j)*4], 4);
            pixelRow[j].colourRank = pixelRow[j].c[0]*kernel[0]
                + pixelRow[j].c[1]*kernel[1] + pixelRow[j].c[2]*kernel[2]
                + pixelRow[j].c[3]*kernel[3];
        }
        // sort based on the ranking
        std::sort(pixelRow, pixelRow + granularity);
        // re-write back to the image
        // data oriented improvement would be to do this in a single copy rather than loop
        for(int j = 0; j < granularity; j++) {
            memcpy(&row[(i*granularity+j)*4], pixelRow[j].c, 4);
        }
    }

    int leftOver = x%granularity;
    auto* leftOverRow = new Pixel[leftOver]();
    // sort leftover elements
    for(int j = 0; j < leftOver; j++) {
        // sorting pixels i*granularity to i*granularity+j
        memcpy(leftOverRow[j].c, &row[(x-leftOver+j)*4], 4);
        leftOverRow[j].colourRank = leftOverRow[j].c[0]*kernel[0]
            + leftOverRow[j].c[1]*kernel[1] + leftOverRow[j].c[2]*kernel[2]
            + leftOverRow[j].c[3]*kernel[3];
    }
    std::sort(leftOverRow, leftOverRow + leftOver);
    // re-write back to the image
    for(int j = 0; j < leftOver; j++) {
        memcpy(&row[(x-leftOver+j)*4], leftOverRow[j].c, 4);
    }

    delete[] pixelRow;
    delete[] leftOverRow;
}
