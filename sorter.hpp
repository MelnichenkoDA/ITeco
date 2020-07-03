#ifndef ALGO_HPP
#define ALGO_HPP

#include <fstream>
#include <unordered_map>
#include <map>
#include <limits>
#include <functional>
#include <QDebug>

using std::ifstream;
using std::ofstream;
using std::map;


template<class Comparator>
void sort(size_t lim, const char *inputFilename,
          const char *outputFilename, std::function<void (int)> updateCallback)
{

    ifstream input(inputFilename, std::ios::binary);
    if (!input.is_open()){
        throw std::runtime_error("Couldn't open input file");
    }

    ofstream output(outputFilename, std::ios::binary);
    if (!output.is_open()){
        throw std::runtime_error("Couldn't open output file");
    }

    Comparator comp;
    std::map<double, unsigned int, Comparator> buff;
    auto it = buff.begin();

    double border = std::numeric_limits<double>::max();
    if (comp(border, 0)){
        border *= -1;
    }

    unsigned tempSize = 50;
    char* tempBuff = new char[tempSize];

    double value;
    double temp = 0, count = 0;
    while (true) {
        while((buff.size() < lim)){

            input >> value;                      
            if (input.fail()) {                
                input.clear();                
                input.get(tempBuff, tempSize, ' ');                
            }

            if (input.eof()) {
                break;
            }

            ++count;
            if (comp(value, border)){
                buff[value] += 1;
            }
        }
        
        if (!buff.size()){
            break;
        }

        while(true){
            input >> value;
            if (input.fail()) {                
                input.clear();
                input.get(tempBuff, tempSize, ' ');
            }

            if (input.eof()) {
                break;
            }

            ++count;
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
            for (unsigned i = 0; i < t->second; ++i){
                ++temp;
                output << t->first << " ";
            }
        }

        updateCallback(int((temp /  count) * 100));
        temp = count = 0;

        border = buff.begin()->first;
        buff.clear();

        input.clear();
        input.seekg(0, std::ios::beg);
    }

    delete[] tempBuff;
}

#endif // ALGO_HPP
