#include <iostream>
#include <limits>

int main(int argc , char** argv){
    
    int max = std::numeric_limits<int>::max();
    int min = std::numeric_limits<int>::min();

    std::cout << "max : " << max << std::endl;
    std::cout << "min : " << min;
}