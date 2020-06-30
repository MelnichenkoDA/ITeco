#include "Sorter.hpp"


using std::ifstream;
using std::ofstream;
using std::map;



void Sorter::sort(size_t lim, const char *inputFilename,
                                 const char *outputFilename, std::function<bool (double, double)> comp)
{
    ifstream input(inputFilename);
    if (!input.is_open()){
        throw std::string("Couldn't open file ") + inputFilename;
    }

    ofstream output(outputFilename);
    if (!output.is_open()){
        throw std::string("Couldn't open file ") + outputFilename;
    }

    std::map<double, int, decltype(comp)> buff;
    std::map<double, int, decltype(comp)>::iterator it;
    double min = std::numeric_limits<double>::max();
    double value;
    for (bool changed = true; changed; ){
        while((buff.size() < lim) && (input >> value)){
            if (comp(value, min)){
                buff[value] += 1;
            }
        }

        if (!buff.size()){
            changed = false;
        }

        while(input >> value){
            if (comp(value, min) || value == min){
                continue;
            }

            it = buff.lower_bound(value);
            if (it != buff.end()){
                if (it->first == value){
                    buff[value] += 1;
                }
                if (it->first > value && it != buff.begin()){
                    buff.erase(buff.begin());
                    buff[value] += 1;
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
        min = buff.begin()->first;
        buff.clear();
        input.clear();
        input.seekg(0, std::ios::beg);
    }

    input.close();
    output.close();
}


