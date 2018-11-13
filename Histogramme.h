//
// Created by no-code-team on 10/26/18.
//

#ifndef TP1C_M1_HISTOGRAMME_H
#define TP1C_M1_HISTOGRAMME_H

#include "GrayLevelImage2D.h"

#include <iostream>
#include <vector>
#include <exception>

class Histogramme {
public:
    Histogramme();

    /**
     * Generate an histogram of an input image
     * @param img Image to generat is histogram
     */
    explicit Histogramme(GrayLevelImage2D &img);

    /**
     * Get the equalise value of the input pixel value
     * @param pixel_value Pixel value to equalise
     * @return The equalise value of the input pixel
     */
    int egalisation(int pix_value);

private:

    // Histogram of the image
    std::vector<int> histogramme;
    // Cumulative histogram normalisation between 0 and 1
    std::vector<double> histogramme_cumule;
};

#endif //TP1C_M1_HISTOGRAMME_H
