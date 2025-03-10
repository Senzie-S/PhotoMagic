// Copyright 2024 Sanjana Singh
#include <iostream>
#include <bitset>
#include <random>
#include <string>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

int main(int argc, char* argv[]) {
    // Check for number of correct arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
        << " <input-image> <output-image> <LFSR-seed>" << std::endl;
        return 1;
    }

    // Input image loading
    sf::Image inputImage;
    if (!inputImage.loadFromFile(argv[1])) {
        std::cerr << "Error loading image: " << argv[1] << std::endl;
        return 1;
    }

    // Creating FibLSFR object with given seed
    std::string seed = argv[3];
    PhotoMagic::FibLFSR lfsr(seed);

    // Creating output image by copying the input image in it
    sf::Image outputImage = inputImage;

    // Transform output image using LFSR
    PhotoMagic::transform(outputImage, &lfsr);

    // Save transformed image into the output
    if (!outputImage.saveToFile(argv[2])) {
        std::cerr << "Error saving image: " << argv[2] << std::endl;
        return 1;
    }

    // Load the images into textures for display
    sf::Texture inputTexture, outputTexture;
    if (!inputTexture.loadFromImage(inputImage)) {
        std::cerr << "Error loading texture from input image" << std::endl;
        return 1;
    }
    if (!outputTexture.loadFromImage(outputImage)) {
        std::cerr << "Error loading texture from output image" << std::endl;
        return 1;
    }

    // Creating input and output sprite from the textures
    sf::Sprite inputSprite(inputTexture);
    sf::Sprite outputSprite(outputTexture);

    // Creating two SFML windows for displaying images
    sf::RenderWindow window1
    (sf::VideoMode(inputImage.getSize().x, inputImage.getSize().y), "Original Image");
    sf::RenderWindow window2
    (sf::VideoMode(outputImage.getSize().x, outputImage.getSize().y), "Transformed Image");

    // Setting frame limit
    window1.setFramerateLimit(60);
    window2.setFramerateLimit(60);

    // Loop for displaying two windows
    while (window1.isOpen() && window2.isOpen()) {
        sf::Event event;

        // Handling events for original image
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window1.close();
            }
        }

        // Handling events for tansformed image
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window2.close();
            }
        }

        // Clear and display of original image on window 1
        window1.clear();
        window1.draw(inputSprite);
        window1.display();

        // Clear and display of transformed image on window 2
        window2.clear();
        window2.draw(outputSprite);
        window2.display();
    }

    return 0;
}
