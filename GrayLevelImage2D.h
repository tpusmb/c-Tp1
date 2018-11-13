//
// Created by no-code-team on 10/15/18.
//

#ifndef TP1C_M1_GRAYLEVELIMAGE2D_H
#define TP1C_M1_GRAYLEVELIMAGE2D_H

#include <iostream>
#include <vector>
#include <exception>

class GrayLevelImage2D {
public:
    typedef unsigned char GrayLevel;// le type pour les niveaux de gris.
    typedef std::vector<GrayLevel> Container;// le type pour stocker les niveaux de gris de l'image.

    /**
       Représente un itérateur sur toutes les valeurs d'une image.

       Model of DefaultConstructible, CopyConstructible, Assignable,
       RandomAccessIterator. */
    struct Iterator : public Container::iterator {
        Iterator(GrayLevelImage2D &Image, int x, int y);
    };


public:
    GrayLevelImage2D();

    /**
     * Constructor to inir a image
     * @param w Width of the image
     * @param h Height of the image
     * @param g Default value of the image
     */
    GrayLevelImage2D(int w, int h, GrayLevel g = 0);


    /**
     * Fill th image with one single value
     * @param g Value to fill
     */
    void fill(GrayLevel g);

    /**
     * Geter width
     * @return Image width
     */
    int w() const;

    /**
     * Geter height
     * @return Image height
     */
    int h() const;

    /**
     * (Read-only) Get the pixel value at a position
     * @param i position x
     * @param j position y
     * @return The pixel value at the position x, y
     */
    GrayLevel at(int i, int j) const;

    /**
     * (Read-Write) Get the pixel value at a position
     * @param i position x
     * @param j position y
     * @return The pixel value at the position x, y
     */
    GrayLevel &at(int i, int j);

    /**
     * Get the begin iterator
     * @return Yhe iterator at the begin of the image
     */
    Iterator begin();

    /**
     * Get the end list iterator
     * @return The iterator at the end of the image
     */
    Iterator end();

    /**
     * Get the iterator at a specific position
     * @param x position x
     * @param y position y
     * @return The iterator at the position x, y
     */
    Iterator start(int x, int y);

    /**
     * Import a pgm file for now we just read Binary image !
     * @param input File to read
     * @return True the import have work. False there a error
     */
    bool importPGM(std::istream &input);

    /**
     * Export the image in a pgm file
     * @param output File to write the image
     * @param ascii True the image file will be write in ascii. False in bineray mode
     * @return True the exporthave work. False there a error
     */
    bool exportPGM(std::ostream &output, bool ascii = true);


private:
    /**
     * Get the index of the pixel coordinate
     * @param x position x
     * @param y position y
     * @return The index
     */
    int index(int x, int y) const;

    // image container (is a array of char)
    Container m_data;
    // width of the image
    int m_width;
    // height of the image
    int m_height;
};


#endif //TP1C_M1_GRAYLEVELIMAGE2D_H
