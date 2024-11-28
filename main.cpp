//Author: Kevin Tran
//Date: XX.XX.XXXX
//Purpose:

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

uint32_t convertToBinary(string);


int main(){
    return 0;
}


uint32_t convertToBinary(string operand){
    stringstream ss;
    uint32_t binary;
    ss << operand;
    ss >> hex >> binary;
    return binary;
}