//Author: Kevin Tran
//Date: XX.XX.XXXX
//Purpose:

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

uint32_t convertToBinary(string);
void MOV(string, string, string, string*, int*);
void ADDS(string, string, string, string, string*, int*);
void SUBS(string, string, string, string, string*, int*);
void ANDS(string, string, string, string, string*, int*);
void ORR(string, string, string, string, string*, int*);
void XOR(string, string, string, string, string*, int*);
void LSRS(string, string, string, string, string*, int*);
void LSLS(string, string, string, string, string*, int*);

int main(){
    string operation;
    string resultRegister;
    string operandRegister1;
    string operandRegister2;
    string hexValue;
    string shiftVal;

    //initialize register array
    string registerArray[8];
    //initialize flag array
    int flagArray[4];
    //set all flags to 0
    for(int i = 0; i < 4; i++){
        flagArray[i] = 0;
    }

    ifstream input("Programming-Project-3.txt");
    if(!input.is_open()){
        cout << "File Cannot Be Opened! (╯°□°）╯" << endl;
        return 1;
    }

    while(input >> operation){
        if(operation == "MOV" || operation == "mov"){
            input >> resultRegister >> hexValue;
            MOV(operation, resultRegister, hexValue, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "ADDS" || operation == "adds"){
            input >> resultRegister >> operandRegister1 >> operandRegister2;
            ADDS(operation, resultRegister, operandRegister1, operandRegister2, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "SUBS" || operation == "subs"){
            input >> resultRegister >> operandRegister1 >> operandRegister2;
            SUBS(operation, resultRegister, operandRegister1, operandRegister2, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "ANDS" || operation == "ands"){
            input >> resultRegister >> operandRegister1 >> operandRegister2;
            ANDS(operation, resultRegister, operandRegister1, operandRegister2, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "ORR" || operation == "orr"){
            input >> resultRegister >> operandRegister1 >> operandRegister2;
            ORR(operation, resultRegister, operandRegister1, operandRegister2, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "XOR" || operation == "xor"){
            input >> resultRegister >> operandRegister1 >> operandRegister2;
            XOR(operation, resultRegister, operandRegister1, operandRegister2, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "LSRS" || operation == "lsrs"){
            input >> resultRegister >> operandRegister1 >> shiftVal;
            LSRS(operation, resultRegister, operandRegister1, shiftVal, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "LSLS" || operation == "lsls"){
            input >> resultRegister >> operandRegister1 >> shiftVal;
            LSLS(operation, resultRegister, operandRegister1, shiftVal, registerArray, flagArray);
            cout << endl;
        }
        if(operation == "CMP" || operation == "cmp"){
            cout << "Extra Credit" << endl;
        }
        if(operation == "TST" || operation == "tst"){
            cout << "Extra Credit" << endl;
        }
    }
    input.close();

    return 0;
}


uint32_t convertToBinary(string operand){
    operand.erase(0, 2);
    stringstream ss;
    uint32_t binary;
    ss << hex << operand;
    ss >> binary;
    return binary;
}


void MOV(string operation, string registerLocation, string hexValue, string* registerArray, int* flagArray){
    //remove the comma from the register location
    string temp = registerLocation;
    registerLocation.pop_back();
    //remove the R part of the register location
    string rl = registerLocation.erase(0,1);
    //convert the register location to an integer
    int position = stoi(rl);
    
    //update register array
    registerArray[position] = hexValue.erase(0, 1);

    //output results
    cout << operation << " " << temp << " " << hexValue << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //output flags
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;
}

void ADDS(string operation, string result, string operand1, string operand2, string* registerArray, int* flagArray){
    string temp1 = result;
    result.pop_back();
    //get register location of result
    result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(result);

    string temp2 = operand1;
    operand1.pop_back();
    //get register location of operand1
    operand1.erase(0,1);
    //convert the register location to an integer
    int operand1Position = stoi(operand1);

    string temp3 = operand2;
    //get register location of operand2
    operand2.erase(0,1);
    //convert the register location to an integer
    int operand2Position = stoi(operand2);
    //perform ADDS operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) + convertToBinary(registerArray[operand2Position]);

    //update register array
    stringstream ss;
    ss << hex << uppercase << resultValue;
    string resultHex = "0x" + ss.str();
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << temp1 << " " << temp2 << " " << temp3 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;

    //update flag values and output flags
    flagArray[0] = (resultValue >> 31) & 1;
    if(resultValue == 0){
        flagArray[1] = 1;
    }
    else{
        flagArray[1] = 0;
    }

    if(resultValue < convertToBinary(registerArray[operand1Position])){
        flagArray[2] = 1;
    }
    else{
        flagArray[2] = 0;
    }

    if(convertToBinary(registerArray[operand1Position]) > 0 && convertToBinary(registerArray[operand2Position]) > 0 && resultValue < 0){
        flagArray[3] = 1;
    }
    else if(convertToBinary(registerArray[operand1Position]) < 0 && convertToBinary(registerArray[operand2Position]) < 0 && resultValue > 0){
        flagArray[3] = 1;
    }
    else{
        flagArray[3] = 0;
    }
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;
}

void SUBS(string operation, string result, string operand1, string operand2, string* registerArray, int* flagArray){
    string temp1 = result;
    result.pop_back();
    //get register location of result
    result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(result);

    string temp2 = operand1;
    operand1.pop_back();
    //get register location of operand1
    operand1.erase(0,1);
    //convert the register location to an integer
    int operand1Position = stoi(operand1);

    string temp3 = operand2;
    //get register location of operand2
    operand2.erase(0,1);
    //convert the register location to an integer
    int operand2Position = stoi(operand2);

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) - convertToBinary(registerArray[operand2Position]);

    //update register array
    stringstream ss;
    ss << hex << uppercase << resultValue;
    string resultHex = "0x" + ss.str();
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << temp1 << " " << temp2 << " " << temp3 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
    flagArray[0] = (resultValue >> 31) & 1;
    if(resultValue == 0){
        flagArray[1] = 1;
    }
    else{
        flagArray[1] = 0;
    }

    if(resultValue < convertToBinary(registerArray[operand1Position])){
        flagArray[2] = 1;
    }
    else{
        flagArray[2] = 0;
    }

    if(convertToBinary(registerArray[operand1Position]) > 0 && convertToBinary(registerArray[operand2Position]) > 0 && resultValue < 0){
        flagArray[3] = 1;
    }
    else if(convertToBinary(registerArray[operand1Position]) < 0 && convertToBinary(registerArray[operand2Position]) < 0 && resultValue > 0){
        flagArray[3] = 1;
    }
    else{
        flagArray[3] = 0;
    }
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;
}

void ANDS(string operation, string result, string operand1, string operand2, string* registerArray, int* flagArray){
    string temp1 = result;
    result.pop_back();
    //get register location of result
    result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(result);

    string temp2 = operand1;
    operand1.pop_back();
    //get register location of operand1
    operand1.erase(0,1);
    //convert the register location to an integer
    int operand1Position = stoi(operand1);

    string temp3 = operand2;
    //get register location of operand2
    operand2.erase(0,1);
    //convert the register location to an integer
    int operand2Position = stoi(operand2);

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) & convertToBinary(registerArray[operand2Position]);

    //update register array
    stringstream ss;
    ss << hex << uppercase << resultValue;
    string resultHex = "0x" + ss.str();
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << temp1 << " " << temp2 << " " << temp3 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
    flagArray[0] = (resultValue >> 31) & 1;
    if(resultValue == 0){
        flagArray[1] = 1;
    }
    else{
        flagArray[1] = 0;
    }
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;
}

void ORR(string operation, string result, string operand1, string operand2, string* registerArray, int* flagArray){
    string temp1 = result;
    result.pop_back();
    //get register location of result
    result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(result);

    string temp2 = operand1;
    operand1.pop_back();
    //get register location of operand1
    operand1.erase(0,1);
    //convert the register location to an integer
    int operand1Position = stoi(operand1);

    string temp3 = operand2;
    //get register location of operand2
    operand2.erase(0,1);
    //convert the register location to an integer
    int operand2Position = stoi(operand2);

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) | convertToBinary(registerArray[operand2Position]);

    //update register array
    stringstream ss;
    ss << hex << uppercase << resultValue;
    string resultHex = "0x" + ss.str();
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << temp1 << " " << temp2 << " " << temp3 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
    flagArray[0] = (resultValue >> 31) & 1;
    if(resultValue == 0){
        flagArray[1] = 1;
    }
    else{
        flagArray[1] = 0;
    }
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;   
}

void XOR(string operation, string result, string operand1, string operand2, string* registerArray, int* flagArray){
    string temp1 = result;
    result.pop_back();
    //get register location of result
    result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(result);

    string temp2 = operand1;
    operand1.pop_back();
    //get register location of operand1
    operand1.erase(0,1);
    //convert the register location to an integer
    int operand1Position = stoi(operand1);

    string temp3 = operand2;
    //get register location of operand2
    operand2.erase(0,1);
    //convert the register location to an integer
    int operand2Position = stoi(operand2);

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operand1Position]) ^ convertToBinary(registerArray[operand2Position]);

    //update register array
    stringstream ss;
    ss << hex << uppercase << resultValue;
    string resultHex = "0x" + ss.str();
    registerArray[resultsPosition] = resultHex;

    //output results
    cout << operation << " " << temp1 << " " << temp2 << " " << temp3 << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
    string binaryValue = to_string(resultValue);
    flagArray[0] = (resultValue >> 31) & 1;
    if(resultValue == 0){
        flagArray[1] = 1;
    }
    else{
        flagArray[1] = 0;
    }
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;  
}

void LSRS(string operation, string result, string operand, string shift, string* registerArray, int* flagArray){
    string temp1 = result;
    result.pop_back();
    //get register location of result
    result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(result);

    string temp2 = operand;
    operand.pop_back();
    //get register location of operand1
    operand.erase(0,1);
    //convert the register location to an integer
    int operandPosition = stoi(operand);

    //get shift value
    string s = shift.erase(0,1);
    int shiftValue = stoi(s); 

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operandPosition]) >> shiftValue;    
    stringstream ss;
    ss << hex << uppercase << resultValue;
    string resultHex = "0x" + ss.str();
    registerArray[resultsPosition] = resultHex;

    cout << operation << " " << temp1 << " " << temp2 << ", " << shift << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
    flagArray[0] = (resultValue >> 31) & 1;
    if(resultValue == 0){
        flagArray[1] = 1;
    }
    else{
        flagArray[1] = 0;
    }

    if(resultValue < convertToBinary(registerArray[operandPosition])){
        flagArray[2] = 1;
    }
    else{
        flagArray[2] = 0;
    }
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;  
}

void LSLS(string operation, string result, string operand, string shift, string* registerArray, int* flagArray){
    string temp1 = result;
    result.pop_back();
    //get register location of result
    result.erase(0,1);
    //convert the register location to an integer
    int resultsPosition = stoi(result);

    string temp2 = operand;
    operand.pop_back();
    //get register location of operand1
    operand.erase(0,1);
    //convert the register location to an integer
    int operandPosition = stoi(operand);

    //get shift value
    string s = shift.erase(0,1);
    int shiftValue = stoi(s); 
 

    //perform operation
    uint32_t resultValue = convertToBinary(registerArray[operandPosition]) << shiftValue;
    stringstream ss;
    ss << hex << uppercase << resultValue;
    string resultHex = "0x" + ss.str();
    registerArray[resultsPosition] = resultHex;

    cout << operation << " " << temp1 << " " << temp2 << ", " << shift << endl;
    for(int i = 0; i < 8; i++){
        cout << "R" << i << ": " << registerArray[i] << " ";
    }
    cout << endl;
    //update flag values and output flags
    flagArray[0] = (resultValue >> 31) & 1;
    if(resultValue == 0){
        flagArray[1] = 1;
    }
    else{
        flagArray[1] = 0;
    }

    if(resultValue < convertToBinary(registerArray[operandPosition])){
        flagArray[2] = 1;
    }
    else{
        flagArray[2] = 0;
    }
    cout << "N: " << flagArray[0] << " Z: " << flagArray[1] << " C: " << flagArray[2] << " V: " << flagArray[3] << endl;  
}