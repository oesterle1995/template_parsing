#include <string>
#include <iostream>

int main()
{ 
    char c = '4';
    std::string special_char = "{}#;";
    size_t pos;
    pos = special_char.find(c);
    if(pos == std::string::npos)
        std::cout << "not found" << std::endl;
    else
        std::cout << pos << std::endl;

}