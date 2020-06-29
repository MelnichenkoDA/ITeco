#include "algo.hpp"

void show(std::map<double, int>& buff){
    for (auto it: buff){
        cout << it.first << ": " << it.second << "\n";
    }
}

std::string func(const int lim, const char * inputFilename, const char * outputFilename){
    ifstream input(inputFilename);
    if (!input.is_open()){
        return std::string("Couldn't open file ") + inputFilename;
    }

    ofstream output(outputFilename);
    if (!output.is_open()){
        return std::string("Couldn't open file ") + outputFilename;
    }

    std::map<double, int> buff;
    std::map<double, int>::iterator it;
    double min = std::numeric_limits<double>::max();
    cout << min << "\n";
    double value;
    for (bool changed = true; changed; ){
        while((buff.size() < lim) && (input >> value)){            
            if (value < min){
                buff[value] += 1;
            }
        }
        
        if (!buff.size()){      //we've sorted all numbers
            changed = false;
        }

        while(input >> value){
            if (value >= min){
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

    return "";
}
    
    
    /*for (bool changed = true; changed;){
        while (buff.size() < lim && )
    }*/
