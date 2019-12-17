// Copyright 2019 Medvate <ilia.bezverzhenko@mail.ru>

#ifndef __RK3__LAB4__HEADER_H
#define __RK3__LAB4__HEADER_H

#include <iostream>
#include <random>
#include <vector>
#include <iomanip>

// Функция выдает рандомный double в данном промежутке.
double rand_double(const double min, const double max);

/* Класс Популяции, которая
 * состоит из особей. */
class Population {
private:
    // Класс особи.
    class Individual {
    public:
        Individual(const double x, const double y);

        // Обновляет значение функции.
        void refresh_fit();

    public:
        /* Координаты X и Y, и значение
         * функции Fit(x, y). */
        double _X = 0,
               _Y = 0,
               _FIT = 0;
    };

public:
    // Создает первую популяцию.
    void generation_first_population();

    // Функция эволюции.
    void evolution();

    // Выдает индекс на наилучшую особь.
    size_t get_index_of_best();

    // Выдает индекс на наихудшую особь.
    size_t get_index_of_worst();

    // Выдает размер популяции.
    size_t get_size();

    // Выдает значение X данной особи.
    double get_x(size_t index);

    // Выдает значение Y данной особи.
    double get_y(size_t index);

    // Выдает значение FIT данной особи.
    double get_fit(size_t index);

    /* Выдаем сумму параметров
     * FIT всех особей в популяции. */
    double get_global_fit();

private:
    // Создает последующую популяцию.
    void generation_new_population();

    // Функция сортировки особей в порядке возрастания.
    void sort();

    // Функция мутации популяции.
    void mutation();

    // Функция селекции популяции.
    void selection();

private:
    std::vector<Individual> _POP;
};

#endif //__RK3__LAB4__HEADER_H
