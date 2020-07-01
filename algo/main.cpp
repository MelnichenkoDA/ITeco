#include <iostream>

using std::cout;
using std::cin;

#include "algo.hpp"
#include "input_maker.hpp"


int main(){
    std::string input, filename;

    while(true){
        try{
            cout << "Would you want to make new input file? y/n: ";
            cin >> input;
            if (input == "y" || input == "yes"){
                    make_input();
            } else if (input == "n" || input == "no"){
            } else {
                cout << input;
                cout << "Couldn.t understand input.\n";
                continue;
            }

            cout << "Enter name of file for sorting: ";
            cin >> filename;

            size_t limit = 0;
            cout << "Enter memory limit (in bytes):";
            cin >> limit;
            
            bool order = true;
            cout << "Sort ascending? (y/n): ";
            cin >> input;
            if (input == "y" || input == "yes"){
                sort<std::less<double>>(limit, filename.c_str(), "out");
            } else {
                sort<std::greater<double>>(limit, filename.c_str(), "out");
            }
        } catch(const std::exception & ex){
            cout << ex.what() << "\n";
        }
        cout << "Do you want to quit? (q): ";
        cin >> input;
        if (input == "q" || input == "quit"){
            break;
        }
    }  
    
    return 0;
}