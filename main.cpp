//Author: Kevin Tran
//Date: XX.XX.XXXX
//Purpose:

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

uint32_t convertToBinary(string);
void MOV(string, string, string, string[]);
void ADDS(string, string, string, string, string[]);

int main(){
    //initialize register array
    string registerArray[8];

    return 0;
}


uint32_t convertToBinary(string operand){
    stringstream ss;
    uint32_t binary;
    ss << operand;
    ss >> hex >> binary;
    return binary;
}


void MOV(string operation, string registerLocation, string hexValue, string registerArray[8]){
    //creaete array to represent flags
    string flagArray[4];
    //initialize flags to 0 because MOV operation doesnt affect any flags
    for(int i = 0; i < 4; i++){
        flagArray[i] = "0";
    }
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
    //output results
    cout << operation << " " << registerLocation << " " << hexValue << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << " " << registerArray[i] << " ";
    }
    cout << endl;
    //output flags
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;
}

void ADDS(string operation, string result, string operand1, string operand2, string registerArray[]){
    //creaete array to represent flags
    string flagArray[4];

    //get register location of result
    string r = result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(r); 
    //get register location of operand1
    string op1 = operand1.erase(0,1);
    //convert the register location to an integer
    int operand1Position = stoi(op1);
    //get register location of operand2
    string op2 = operand2.erase(0,1);
    //convert the register location to an integer
    int operand2Position = stoi(op2);

    //perform ADDS operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) + convertToBinary(registerArray[operand2Position]);


}