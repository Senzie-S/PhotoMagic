// Copyright 2024 Sanjana Singh
// PhotoMagic.hpp
#ifndef PHOTOMAGIC_HPP
#define PHOTOMAGIC_HPP
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

namespace PhotoMagic {
    void transform(sf::Image& image, FibLFSR* lfsr);
}

#endif
