// Copyright 2019 Medvate <ilia.bezverzhenko@mail.ru>

#include "header.h"

int main() {
    Population pop;
    pop.generation_first_population();

    std::cout << "|  №  |     X     |     Y     |    FIT    |    Max    |Average fit|" << std::endl;
    std::cout << "+=====+===========+===========+===========+===========+===========+" << std::endl;

    for (size_t i = 0; i < 100; ++i) {

        size_t IndexOfBest = pop.get_index_of_best();
        double GlobalFit = pop.get_global_fit();

        for (size_t j = 0; j < pop.get_size(); j++) {
            std::cout << "|";

            if (j == 0) {
                std::cout << std::right << std::setw(4) << i << " |";
            } else {
                std::cout << "     |";
            }

            std::cout << std::right << std::setw(10) << pop.get_x(j) << " |";
            std::cout << std::right << std::setw(10) << pop.get_y(j) << " |";
            std::cout << std::right << std::setw(10) << pop.get_fit(j) << " |";

            if (j == 0) {
                std::cout << std::right << std::setw(10) << pop.get_fit(j) << " |";
                std::cout << std::right << std::setw(10) << GlobalFit / pop.get_size() << " |" << std::endl;
            } else {
                std::cout << "           |" << "           |" << std::endl;;
            }
        }

        pop.evolution();
    }

    return 0;
}
