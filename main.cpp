//Author: Kevin Tran
//Date: XX.XX.XXXX
//Purpose:

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

uint32_t convertToBinary(string);
void MOV(string, string, string, string[], int[]);
void ADDS(string, string, string, string, string[], int[]);
void SUBS(string, string, string, string, string[], int[]);
void ANDS(string, string, string, string, string[], int[]);
void ORR(string, string, string, string, string[], int[]);
void XOR(string, string, string, string, string[], int[]);
void LSRS(string, string, string, string, string[], int[]);

int main(){
    //initialize register array
    string registerArray[8];
    //initialize flag array
    int flagArray[4];
    //set all flags to 0
    for(int i = 0; i < 4; i++){
        flagArray[i] = 0;
    }

    return 0;
}


uint32_t convertToBinary(string operand){
    stringstream ss;
    uint32_t binary;
    ss << operand;
    ss >> hex >> binary;
    return binary;
}


void MOV(string operation, string registerLocation, string hexValue, string registerArray[8], int flagArray[4]){
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

void ADDS(string operation, string result, string operand1, string operand2, string registerArray[8], int flagArray[4]){
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

    //update register array
    string resultHex = "0x" + to_string(resultValue);
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << result << " " << operand1 << " " << operand2 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
}

void SUBS(string operation, string result, string operand1, string operand2, string registerArray[8], int flagArray[4]){
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

    //takes the two's compliment of operand1
    uint32_t operand1Value = ~convertToBinary(registerArray[operand1Position]) + 1;
    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand2Position]) + operand1Value;

    //update register array
    string resultHex = "0x" + to_string(resultValue);
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << result << " " << operand1 << " " << operand2 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
}

void ANDS(string operation, string result, string operand1, string operand2, string registerArray[8], int flagArray[4]){
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

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) & convertToBinary(registerArray[operand2Position]);

    //update register array
    string resultHex = "0x" + to_string(resultValue);
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << result << " " << operand1 << " " << operand2 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
}

void ORR(string operation, string result, string operand1, string operand2, string registerArray[8], int flagArray[4]){
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

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) | convertToBinary(registerArray[operand2Position]);

    //update register array
    string resultHex = "0x" + to_string(resultValue);
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << result << " " << operand1 << " " << operand2 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags    
}

void XOR(string operation, string result, string operand1, string operand2, string registerArray[8], int flagArray[4]){
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

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) ^ convertToBinary(registerArray[operand2Position]);

    //update register array
    string resultHex = "0x" + to_string(resultValue);
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << result << " " << operand1 << " " << operand2 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
}

void LSRS(string operation, string result, string operand, string shift, string registerArray[8], int flagArray[4]){
    //get register location of result
    string r = result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(r);
    //get register location of operand1
    string op = operand.erase(0,1);
    //convert the register location to an integer
    int operandPosition = stoi(op);
    //get shift value
    string s = shift.erase(0,1);
    int shiftValue = stoi(s); 

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operandPosition]) >> shiftValue;
    registerArray[resultsPosition] = "0x" + to_string(resultValue);

    cout << operation << " " << result << " " << operand1 << " " << operand2 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
}