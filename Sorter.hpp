#ifndef ALGO_HPP
#define ALGO_HPP

#include <fstream>
#include <map>
#include <limits>
#include <functional>

class Sorter{
public:
    template<typename Comparator>
    static void sort(size_t lim, const char * inputFilename,
                     const char * outputFilename, Comparator);
};

#endif // ALGO_HPP
