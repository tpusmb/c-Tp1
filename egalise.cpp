
#include "GrayLevelImage2D.h"
#include "Histogramme.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

/**
 * Script to equalize all the pixal of an image
 */

using namespace std;
int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator  Iterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: egalise <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }
    GrayLevelImage2D img;
    // Get input image name
    ifstream input( argv[1] );
    std::cout << "import pgm" << endl;
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    std::cout << "Start histogram equalize" << endl;
    GrayLevelImage2D img_out(img.w(), img.h(), 5);
    Histogramme histogramme(img);
    // Parse the input image
    for ( int x = 0; x < img.w(); ++x )
        for (int y = 0; y < img.h(); ++y)
            // Get the new pixel value
            *img_out.start(x, y) = static_cast<GrayLevel>(histogramme.egalisation(((int)img.at(x, y))));
    std::cout << std::endl;
    ofstream output( argv[2] ); // récupère le 2ème argument.
    ok = img_out.exportPGM( output, false );
    if ( !ok )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    std::cout << "End of the filter" << std::endl;
    return 0;
}