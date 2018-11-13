//
// Created by no-code-team on 10/26/18.
//
#include "Histogramme.h"

#include "math.h"

Histogramme::Histogramme() = default;

/**
 * Generate an histogram of an input image
 * @param img Image to generat is histogram
 */
Histogramme::Histogramme(GrayLevelImage2D &img) {
    histogramme.resize(255);
    histogramme_cumule.resize(255);
    std::fill(histogramme.begin(), histogramme.end(), 0);

    // Make the histogram
    for ( GrayLevelImage2D::Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
        histogramme[(int)*it]++;

    // Cumulative histogram
    histogramme_cumule[0] = histogramme[0];
    for(int index_histo = 1; index_histo < histogramme.size(); index_histo++)
        histogramme_cumule[index_histo] = histogramme_cumule[index_histo - 1] + histogramme[index_histo];

    // Normalisation between 0 and 1
    for(int index_histo = 0; index_histo < histogramme.size(); index_histo++)
        histogramme_cumule[index_histo] /= (img.h() * img.w());

}

/**
 * Get the equalise value of the input pixel value
 * @param pixel_value Pixel value to equalise
 * @return The equalise value of the input pixel
 */
int Histogramme::egalisation(int pixel_value) {
    return static_cast<int>(round(histogramme_cumule[pixel_value] * 255));
}
