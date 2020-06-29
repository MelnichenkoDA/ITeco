#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void make_input(size_t size, const char *filename){
    std::ofstream output(filename);
    while(fs::file_size(filename) < size){
        output << double(rand()) / double(rand()) * 10 - 100 << " ";
    } 
}

int main(){
    make_input(100, "in");
}