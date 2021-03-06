
#include "GrayLevelImage2D.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

/**
 * Script to apply a median filter
 */

using namespace std;
int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator  Iterator;
    if ( argc < 4 )
    {
        std::cerr << "Usage: filtrage-median <input.pgm> <output.pgm> <k>" << std::endl;
        return 0;
    }
    GrayLevelImage2D img;
    // Get the input image
    ifstream input( argv[1] );
    int k = std::stoi(argv[3]);
    std::cout << "import pgm" << endl;
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    std::cout << "Start median filter" << endl;
    GrayLevelImage2D img_out(img.w(), img.h(), 5);
    int windows_width = 2 * k + 1;
    int windows_height = 2 * k + 1;
    // Calculate the edge of the image
    int edgex = static_cast<int>(floor(windows_width / 2));
    int edgey = static_cast<int>(floor(windows_height / 2));
    // Make a windows to content all the pixel of the sub window
    std::vector<GrayLevel>windows(static_cast<unsigned long>(windows_width * windows_height));
    // Parse the input image
    for ( int x = edgex; x < img.w() - edgex; ++x ) {
        for (int y = edgey; y < img.h() - edgey; ++y){
            int i = 0;
            // Parse the matrix
            for (int fx = 0; fx < windows_width; fx++){
                for (int fy = 0; fy < windows_height; fy++){
                    // Get the pixel associate to the matrix
                    windows[i] = img.at((x + fx) - edgex, (y + fy) - edgey);
                    i++;
                }
            }
            // Sort the matrix
            std::sort(windows.begin(), windows.end());
            // Get the median index
            int index = windows_width * windows_height / 2;
            // Add the new pixel
            *img_out.start(x, y) = windows[index];
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