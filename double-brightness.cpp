
#include "GrayLevelImage2D.h"
#include <iostream>
#include <fstream>

/**
 * Script to double the brihtness of a image
 */

using namespace std;
int main( int argc, char** argv )
{
    typedef GrayLevelImage2D::GrayLevel GrayLevel;
    typedef GrayLevelImage2D::Iterator  Iterator;
    if ( argc < 3 )
    {
        std::cerr << "Usage: double-brightness <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }
    GrayLevelImage2D img;
    // Get input image name
    ifstream input( argv[1] );
    // Import the image
    bool ok = img.importPGM( input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    // Now double all the pixel
    for ( Iterator it = img.begin(), itE = img.end(); it != itE; ++it )
    {
        *it = ( 2 * (int)(*it) ) % 256;
    }
    // Write the new image
    ofstream output( argv[2] );
    ok = img.exportPGM( output, false );
    if ( !ok )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}