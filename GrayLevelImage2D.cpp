//
// Created by no-code-team on 10/15/18.
//

#include "GrayLevelImage2D.h"

#include <string> // chaînes de caractères
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
#include <assert.h>

GrayLevelImage2D::GrayLevelImage2D() {}

GrayLevelImage2D::GrayLevelImage2D(int w, int h, GrayLevelImage2D::GrayLevel g) {

    m_data.resize(static_cast<unsigned long>(w * h));
    std::fill(m_data.begin(), m_data.end(), g);
    m_width = w;
    m_height = h;

}

int GrayLevelImage2D::index(int x, int y) const {
    assert(x < m_width && y < m_height);
    return w() * y + x;
}

void GrayLevelImage2D::fill(GrayLevelImage2D::GrayLevel g) {
    std::fill(m_data.begin(), m_data.end(), g);
}

int GrayLevelImage2D::w() const {
    return m_width;
}

int GrayLevelImage2D::h() const {
    return m_height;
}

GrayLevelImage2D::GrayLevel GrayLevelImage2D::at(int i, int j) const {
    return m_data[index(i, j)];
}

GrayLevelImage2D::GrayLevel &GrayLevelImage2D::at(int i, int j) {
    return m_data[index(i, j)];
}

GrayLevelImage2D::Iterator GrayLevelImage2D::begin() {
    return Iterator(*this, 0, 0);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::end() {
    return Iterator(*this, w() - 1, h() - 1);
}

GrayLevelImage2D::Iterator GrayLevelImage2D::start(int x, int y) {
    return Iterator(*this, x, y);
}

GrayLevelImage2D::Iterator::Iterator(GrayLevelImage2D &Image, int x, int y) : Container::iterator(
        Image.m_data.begin() + Image.index(x, y)) {}

bool GrayLevelImage2D::importPGM(std::istream &input) {

    // teste si tout va bien
    if (!input.good()){
        std::cerr << "Le fichier donner n'est pas valide !";
        return false;
    }

    std::string line;
    // 1 - On passe le premiere ligne
    std::getline(input, line);
    bool ascii = line.compare("P2") == 1;

    // On se mais sur la ligne commenter
    std::getline(input, line);
    // 2- on lie le deuxieme
    // 3 - on parcour les ligne tant que c'est des commentaire
    while (line[0] == '#')
        std::getline(input, line);
    // 4 - On recupaire le hauteur est la largeur
    std::istringstream istr(line);
    istr >> m_width >> m_height;
    m_data.resize(static_cast<unsigned long>(m_width * m_height));
    // on passe a la ligne suivant
    std::getline(input, line);
    std::istringstream istr2(line);
    int pix_val = 0;
    istr2 >> pix_val;
    std::cout << pix_val << std::endl;
    // std::getline(input, line);
    Iterator m_data_iterator = begin();
    if (ascii) {
        std::cout << "Ascii mode" << std::endl;
        input >> std::skipws;
    }else {
        input >> std::noskipws;
    }
    // Parcoure du fichier
    while (!input.eof()){
        GrayLevel g;
        // on recupaire le gray level
        input >> g;
        // on l'ajout a notre obj m-data via l'iterateur
        *m_data_iterator++ = g;
    }
    return true;
}

bool GrayLevelImage2D::exportPGM(std::ostream &output, bool ascii) {

    // teste si tout va bien
    if (!output.good()){
        std::cerr << "Le fichier donner n'est pas valide !";
        return false;
    }
    if(ascii)
        output << "P2\n";
    else
        output << "P5\n";

    output << m_width << ' ' << m_height << '\n' << "255\n";
    for (Iterator it = begin(), itE = end(); it != itE; ++it ) {
        // std::cout << (int) *it << std::endl;
        if (ascii)
            output << (int) *it << ' ';
        else
            output << *it;
    }
    return true;
}
