#ifndef ALGO_HPP
#define ALGO_HPP

#include <fstream>
#include <map>
#include <limits>
#include <functional>

class Sorter{
    Sorter();
    Sorter(const Sorter& other) = delete;
    Sorter& operator=(const Sorter& other) = delete;
public:
    static void sort(size_t lim, const char * inputFilename,
                     const char * outputFilename, std::function<bool (double, double)>);
};

#endif // ALGO_HPP
