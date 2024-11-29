//Author: Kevin Tran
//Date: XX.XX.XXXX
//Purpose:

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

uint32_t convertToBinary(string);
void MOV(string, string, string);

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


void MOV(string operation, string registerLocation, string hexValue){
    //create array to represent registers
    string registerArray[8];
    //remove the R part of the register location
    string rl = registerLocation.erase(0,1);
    //convert the register location to an integer
    int position = stoi(rl);
    //inserting the hex value into the register array at the correct position, and making every other position 0x0
    for(int i = 0; i < 8; i++){
        if(i == position){
            registerArray[i] = hexValue;
        }
        else{
            registerArray[i] = "0x0";
        }
    }
}
