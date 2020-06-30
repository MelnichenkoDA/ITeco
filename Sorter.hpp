#ifndef ALGO_HPP
#define ALGO_HPP

#include <fstream>
#include <map>
#include <limits>
#include <functional>
#include <QDebug>


using std::ifstream;
using std::ofstream;
using std::map;


template<class Comparator>
void sort(size_t lim, const char *inputFilename,
                                 const char *outputFilename)
{
    ifstream input(inputFilename);
    if (!input.is_open()){
        throw std::runtime_error("Couldn't open input file");
    }

    ofstream output(outputFilename);
    if (!output.is_open()){
        throw std::runtime_error("Couldn't open output file");
    }

    Comparator comp;
    std::map<double, int, Comparator> buff;
    auto it = buff.begin();

    double border = std::numeric_limits<double>::max();
    if (comp(border, 0)){
        border *= -1;
    }

    double value;

    for (bool changed = true; changed; ) {
        while((buff.size() < lim) && (input >> value)){
            if (comp(value, border)){
                buff[value] += 1;
            }
        }

        if (!buff.size()){
            changed = false;
        }

        while(input >> value){
            if (!comp(value, border) || value == border){
                continue;
            }

            it = buff.lower_bound(value);
            if (it != buff.end()){
                if (it->first == value){
                    buff[value] += 1;
                } else {
                    if (!comp(value, buff.begin()->first)){
                        buff.erase(buff.begin());
                        buff[value] += 1;
                    }
                }
            } else {
                buff.erase(buff.begin());
                buff[value] += 1;
            }
        }

        for (auto t = buff.rbegin(); t != buff.rend(); t++){
            for (int i = 0; i < t->second; ++i){
                output << t->first << " ";
            }
        }

        border = buff.begin()->first;
        buff.clear();

        input.clear();
        input.seekg(0, std::ios::beg);
    }

    input.close();
    output.close();
}

#endif // ALGO_HPP
