//=======================================================================
// Copyright Baptiste Wicht 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <iostream>

#include "rbm.hpp"
#include "mnist_reader.hpp"
#include "image_utils.hpp"

int main(int argc, char* argv[]){
    auto reconstruction = false;

    if(argc > 1){
        std::string command(argv[1]);

        if(command == "sample"){
            reconstruction = true;
        }
    }

    dbn::rbm<true, 50> rbm(28 * 28, 100);

    auto training_images = mnist::read_training_images();

    binarize_each(training_images);

    rbm.train(training_images, 5);

    if(reconstruction){
        for(size_t t = 0; t < 10; ++t){
            auto& image = training_images[666 * t];

            std::cout << "Source image" << std::endl;
            for(size_t i = 0; i < 28; ++i){
                for(size_t j = 0; j < 28; ++j){
                    std::cout << static_cast<size_t>(image[i * 28 + j]) << " ";
                }
                std::cout << std::endl;
            }

            rbm.reconstruct(image);

            std::cout << "Reconstructed image" << std::endl;
            rbm.display_visible_units(28);
        }
    }

    return 0;
}
