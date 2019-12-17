// Copyright 2019 Medvate <ilia.bezverzhenko@mail.ru>

#include "header.h"

double rand_double(const double min, const double max) {
    std::random_device rd;
    std::mt19937 mersenne(rd());

    unsigned long MER_MAX = mersenne.max();

    double result = (double)mersenne() / MER_MAX;
    return min + result * (max - min);
}

/// Функции особи.
Population::Individual::Individual(const double x, const double y) {
    this->_X = x;
    this->_Y = y;

    this->_FIT = sin(x) * sin(y) / (1 + x * x + y * y);
}

void Population::Individual::refresh_fit() {
    this->_FIT = sin(_X) * sin(_Y) / (1 + _X * _X + _Y * _Y);
}

/// Функции популяции.
void Population::generation_first_population() {
    for (size_t i = 0; i < 4; ++i) {
        this->_POP.emplace_back(rand_double(0, 2), rand_double(-2, 2));
    }
}

void Population::evolution() {
    this->selection();
    this->generation_new_population();
    this->mutation();
}

size_t Population::get_index_of_best() {
    size_t res = 0;

    for (size_t i = 0; i < this->_POP.size(); ++i) {

        if (this->_POP[i]._FIT > this->_POP[res]._FIT) {
            res = i;
        }
    }

    return res;
}

size_t Population::get_index_of_worst() {
    size_t res = 0;

    for (size_t i = 0; i < this->_POP.size(); ++i) {

        if (this->_POP[i]._FIT < this->_POP[res]._FIT) {
            res = i;
        }
    }

    return res;
}

size_t Population::get_size() {
    return this->_POP.size();
}

double Population::get_x(size_t index) {
    return this->_POP[index]._X;
}

double Population::get_y(size_t index) {
    return this->_POP[index]._Y;
}

double Population::get_fit(size_t index) {
    return this->_POP[index]._FIT;
}

double Population::get_global_fit() {
    double sum = 0;

    for(auto& i : this->_POP) {
        i.refresh_fit();
        sum += i._FIT;
    }

    return sum;
}

void Population::generation_new_population() {
    this->sort();

    this->_POP.emplace_back(this->_POP[0]._X, this->_POP[1]._Y);
    this->_POP.emplace_back(this->_POP[1]._X, this->_POP[0]._Y);
    this->_POP.emplace_back(this->_POP[0]._X, this->_POP[2]._Y);
    this->_POP.emplace_back(this->_POP[2]._X, this->_POP[0]._Y);

    this->_POP.erase(this->_POP.begin(), this->_POP.begin() + 3);
}

void Population::sort() {
    for (size_t i = 0; i < this->_POP.size(); ++i) {

        for (size_t j = 0; j < this->_POP.size() - i - 1; ++j) {

            if (this->_POP[j + 1]._FIT > this->_POP[j]._FIT) {
                std::swap(this->_POP[j], this->_POP[j + 1]);
            }
        }
    }
}

void Population::mutation() {
    for (size_t i = 0; i < this->_POP.size(); ++i) {

        if (rand_double(0, 1) <= 0.25) {

            if(rand_double(0, 1) <= 0.50) {
                this->_POP[i]._X += 0.1;
            } else {
                this->_POP[i]._X -= 0.1;
            }

            if(rand_double(0, 1) <= 0.50) {
                this->_POP[i]._Y += 0.1;
            } else {
                this->_POP[i]._Y -= 0.1;
            }

            this->_POP[i].refresh_fit();
        }
    }
}

void Population::selection() {
    double gFit = this->get_global_fit();

    for(size_t i = 0; i < this->_POP.size(); ++i) {
        if (rand_double(0, 1) < (this->_POP[i]._FIT / gFit)) {
            this->_POP.erase(this->_POP.begin() + i);
            return;
        }
    }

    this->_POP.erase(this->_POP.begin() + this->get_index_of_worst());
}