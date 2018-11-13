
#include "GrayLevelImage2D.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

/**
 * Script to clear an image with a kernel, convolution matrix
 */

#define KERNEL_SIZE 3

using namespace std;
int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator  Iterator;
    if ( argc < 4 )
    {
        std::cerr << "Usage: image_clear <input.pgm> <output.pgm> <alpha>\n"
                     "Matrix generation:\n"
                     "0          | -alpha / 4 | 0\n"
                     "-alpha / 4 | 1 + alpha  | -alpha / 4\n"
                     "0          | -alpha / 4 | 0" << std::endl;
        return 0;
    }
    GrayLevelImage2D img;
    // Get the input image
    ifstream input( argv[1] );
    int alpha = std::stoi(argv[3]);
    std::cout << "import pgm" << endl;
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    std::cout << "Start clearing image" << endl;
    GrayLevelImage2D img_out(img.w(), img.h(), 5);
    // Calculate the edge of the image
    int edgex = static_cast<int>(floor(KERNEL_SIZE / 2));
    int edgey = static_cast<int>(floor(KERNEL_SIZE / 2));
    // Set the kernel
    int kernel[] = {0, -alpha / 4, 0,
                    -alpha / 4, 1 + alpha, -alpha / 4,
                    0, -alpha / 4, 0};
    // Parse the input image
    for ( int x = edgex; x < img.w() - edgex; ++x ) {
        for (int y = edgey; y < img.h() - edgey; ++y){
            int accumulator = 0;
            // Parse the matrix
            for (int fx = 0; fx < KERNEL_SIZE; fx++)
                for (int fy = 0; fy < KERNEL_SIZE; fy++) {

                    int kernel_value = kernel[KERNEL_SIZE * fy + fx];
                    int pixel_val = img.at((x + fx) - edgex, (y + fy) - edgey);
                    // multiply the pixel associate to the matrix with the kernel
                    accumulator += pixel_val * kernel_value;
                }
            // Add the new pixel
            *img_out.start(x, y) = static_cast<GrayLevel>(accumulator);
        }
    }
    std::cout << std::endl;
    ofstream output( argv[2] ); // récupère le 2ème argument.
    ok = img_out.exportPGM( output, true );
    if ( !ok )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    std::cout << "End of the filter" << std::endl;
    return 0;
}