#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using std::cout;
using std::cin;


void make_input(){
    std::string input;
    cout << "Enter path to file: ";
    cin >> input;


    std::ofstream output(input);

    if (!output.is_open()){
        std::string error("Couldn't open file");
        throw std::runtime_error(error + input);
    }

    double size;
    cout << "File size: ";
    cin >> size;

    while(fs::file_size(input) < size){
        output << double(rand()) / double(rand()) * 10 - 100 << " ";
    } 
}