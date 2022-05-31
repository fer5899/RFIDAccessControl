#include "SerialInput.h"

std::vector<std::string> separar_datos(std::string str) 
{ 
    const char delim = ' ';
    std::vector<std::string> str_separado;
    
    std::stringstream ss(str); 
 
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        str_separado.push_back(s);
    } 
    return str_separado;
}

