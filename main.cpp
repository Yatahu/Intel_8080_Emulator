#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include <iostream>
#include "func.h"
#include <string>
#include <cstdlib>
#include <sstream>
#include <csignal>
#include "random.hpp"


using Rand = effolkronium::random_static;
using namespace std;
// Class that stores Register,Memory and memory switcher
class Register {
    public:
        int lenarr = 8;
        int lenmem = 65536;
        string reg[8] = {"AH","AL","BH","BL","CH","CL","DH","DL"};
        uint8_t regprim[8] = {0,0,0,0,0,0,0,0};
        uint8_t memory[65536]{};
        bool memorytrue = false;
};
Register reg;

//Function that input random data in to the memory
void Random(){
    for (int i = 0; i < reg.lenmem ; i++){
        reg.memory[i] = Rand::get(0,255);
    }
}
//Function that checks if memory address is correct
bool checkmem(int mem){
    if (mem < 65536 && mem >=0){
        return true;
    }
    else {
        return false;
    }
}

// Function that match input id with id reg
int checkregint(const string& namereg){
    int val = 0;
    while (val< reg.lenarr){
        if (reg.reg[val] == namereg){
            return val;
        }
        val++;
    }
    return false;
}
//Function that handle ctrl-c presses
void signal_handler(int signal_num)
{
    cout << "The interrupt signal is (" << signal_num << "). \n";

    // It terminates the program
    exit(signal_num);
}
//Function that asks if we want to use memory
void membool(){
    string mem;
    cout << "Use memory instead register? Y/N:";
    cin >> mem;
    cout << endl;
    if (mem == "Y" or mem == "y"){
        reg.memorytrue = true;
    }
}
// Function that checks if input exist in register
bool checkreg(const string& namereg){
    int val = 0;
    while (val< reg.lenarr){
        if (reg.reg[val] == namereg){
            return true;
        }
        val++;
    }
    return false;
}
//Function that check if input value is in range
bool checkdecval(int hexval){
    if (hexval <= 255){
        return true;
    }
    return false;
}
//Function that prints last used memory cell
void memprint(int index){
    cout << "Memory " << hex << index << " : " << hex << unsigned(reg.memory[index]) << endl;
    cout << endl;
}
//Function that prints register
void regprint(){
    signal(SIGABRT, signal_handler);
    for (int x = 0; x < reg.lenarr;x++){
        int hexval = reg.regprim[x];
        std::stringstream ss;
        ss<< std::hex << hexval; // int decimal_value
        std::string res ( ss.str() );
        cout << reg.reg[x] << " : " << res << endl;
    }
}
//Function that Move data from register to another register/memory
void MOV(){
    signal(SIGABRT, signal_handler);
    if (reg.memorytrue){
        int indexfirstreg;
        string firstreg;
        int secondmem;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter memory adress:";
        cin >> hex  >> secondmem;
        cout << endl;
        if (checkreg(firstreg) || checkmem(secondmem)) {
            indexfirstreg = checkregint(firstreg);
            reg.regprim[indexfirstreg] = reg.memory[secondmem];
            memprint(secondmem);
            regprint();
            menu();
        } else {
            MOV();
        }
    }
    else {
        int indexfirstreg;
        int indexsecondreg;
        string firstreg;
        string secondreg;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkreg(firstreg) || checkreg(secondreg)) {
            indexfirstreg = checkregint(firstreg);
            indexsecondreg = checkregint(secondreg);
            reg.regprim[indexfirstreg] = reg.regprim[indexsecondreg];
            regprint();
            menu();
        } else {
            MOV();
        }
    }
}
//Function that Change data between register and another register/memory
void XCHG(){
    signal(SIGABRT, signal_handler);
    if (reg.memorytrue) {
        int indexfirstreg;
        string firstreg;
        int secondmem;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter memory address:";
        cin >> hex  >> secondmem;
        cout << endl;
        if (checkreg(firstreg) || checkmem(secondmem)) {
            indexfirstreg = checkregint(firstreg);
            int tempmem = reg.regprim[indexfirstreg];
            reg.regprim[indexfirstreg] = reg.memory[secondmem];
            reg.memory[secondmem] = tempmem;
            memprint(secondmem);
            regprint();
            menu();
        } else {
            XCHG();
        }
    }
    else{
        int indexfirstreg;
        int indexsecondreg;
        string firstreg;
        string secondreg;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkreg(firstreg) || checkreg(secondreg)) {
            indexfirstreg = checkregint(firstreg);
            indexsecondreg = checkregint(secondreg);
            int tempmem = reg.regprim[indexfirstreg];
            reg.regprim[indexfirstreg] = reg.regprim[indexsecondreg];
            reg.regprim[indexsecondreg] = tempmem;
            regprint();
            menu();
        } else {
            XCHG();
        }
    }
}
//Function that Negate data from register or memory
void NOT(){
    if (reg.memorytrue) {
        int firstreg;
        cout << "Enter memory address:";
        cin >> hex >> firstreg;
        cout << endl;
        if (checkmem(firstreg)) {
            reg.memory[firstreg] = ~reg.memory[firstreg];
            memprint(firstreg);
            regprint();
            menu();
        } else {
            NOT();
        }
    }
    else {
        signal(SIGABRT, signal_handler);
        int indexfirstreg;
        string firstreg;
        cout << "Enter register:";
        cin >> firstreg;
        cout << endl;
        if (checkreg(firstreg)) {
            indexfirstreg = checkregint(firstreg);
            reg.regprim[indexfirstreg] = ~reg.regprim[indexfirstreg];
            regprint();
            menu();
        } else {
            NOT();
        }
    }
}
//Function that increment data from register / memory
void INC(){
    if (reg.memorytrue) {
        signal(SIGABRT, signal_handler);
        int firstmem;
        cout << "Enter memory address:";
        cin >> hex >> firstmem;
        cout << endl;
        if (checkmem(firstmem)){
            reg.memory[firstmem]++;
            memprint(firstmem);
            regprint();
            menu();
        }
        else {
            INC();
        }
    }
    else{
        signal(SIGABRT, signal_handler);
        int indexfirstreg;
        string firstreg;
        cout << "Enter register:";
        cin >> firstreg;
        cout << endl;
        if (checkreg(firstreg)){
            indexfirstreg = checkregint(firstreg);
            reg.regprim[indexfirstreg]++;
            regprint();
            menu();
        }
        else {
            INC();
        }
    }
}
//Function that decrement data from register / memory
void DEC(){
    if (reg.memorytrue) {
        signal(SIGABRT, signal_handler);
        int firstmem;
        cout << "Enter register:";
        cin >> hex >> firstmem;
        cout << endl;
        if (checkmem(firstmem)){
            reg.memory[firstmem]--;
            memprint(firstmem);
            regprint();
            menu();
        }
        else {
            INC();
        }
    }
    else {
        signal(SIGABRT, signal_handler);
        int indexfirstreg;
        string firstreg;
        cout << "Enter register:";
        cin >> firstreg;
        cout << endl;
        if (checkreg(firstreg)){
            indexfirstreg = checkregint(firstreg);
            reg.regprim[indexfirstreg]--;
            regprint();
            menu();
        }
        else {
            INC();
        }
    }
}
//Logic Functions

void AND(){
    signal(SIGABRT, signal_handler);
    if (reg.memorytrue) {
        int indexsecondreg;
        int firstmem;
        string secondreg;
        cout << "Enter first memory:";
        cin >> firstmem;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkmem(firstmem) || checkreg(secondreg)) {
            indexsecondreg = checkregint(secondreg);
            reg.memory[firstmem] = reg.memory[firstmem] & reg.regprim[indexsecondreg];
            memprint(firstmem);
            regprint();
            menu();
        } else {
            AND();
        }
    }
    else {
        int indexfirstreg;
        int indexsecondreg;
        string firstreg;
        string secondreg;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkreg(firstreg) || checkreg(secondreg)) {
            indexfirstreg = checkregint(firstreg);
            indexsecondreg = checkregint(secondreg);
            reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] & reg.regprim[indexsecondreg];
            regprint();
            menu();
        } else {
            AND();
        }
    }
}

void OR(){
    signal(SIGABRT, signal_handler);
    if (reg.memorytrue) {
        int indexsecondreg;
        int firstmem;
        string secondreg;
        cout << "Enter first memory address:";
        cin >> hex >> firstmem;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkmem(firstmem) || checkreg(secondreg)) {
            indexsecondreg = checkregint(secondreg);
            reg.memory[firstmem] = reg.memory[firstmem] | reg.regprim[indexsecondreg];
            memprint(firstmem);
            regprint();
            menu();
        } else {
            OR();
        }
    }
    else{
        int indexfirstreg;
        int indexsecondreg;
        string firstreg;
        string secondreg;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkreg(firstreg) || checkreg(secondreg)) {
            indexfirstreg = checkregint(firstreg);
            indexsecondreg = checkregint(secondreg);
            reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] | reg.regprim[indexsecondreg];
            regprint();
            menu();
        } else {
            OR();
        }
    }
}

void XOR(){
    signal(SIGABRT, signal_handler);
    if (reg.memorytrue) {
        int indexsecondreg;
        int firstmem;
        string secondreg;
        cout << "Enter first memory address:";
        cin >> hex >> firstmem;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkmem(firstmem) || checkreg(secondreg)) {
            indexsecondreg = checkregint(secondreg);
            reg.memory[firstmem] = reg.memory[firstmem] ^ reg.regprim[indexsecondreg];
            memprint(firstmem);
            regprint();
            menu();
        } else {
            XOR();
        }
    }
    else{
        int indexfirstreg;
        int indexsecondreg;
        string firstreg;
        string secondreg;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkreg(firstreg) || checkreg(secondreg)) {
            indexfirstreg = checkregint(firstreg);
            indexsecondreg = checkregint(secondreg);
            reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] ^ reg.regprim[indexsecondreg];
            regprint();
            menu();
        } else {
            XOR();
        }
    }
}
//Function that add data from register to register / memory
void ADD(){
    signal(SIGABRT, signal_handler);
    if (reg.memorytrue) {
        int indexsecondreg;
        int firstmem;
        string secondreg;
        cout << "Enter first memory address:";
        cin >> hex >>firstmem;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkmem(firstmem) || checkreg(secondreg)) {
            indexsecondreg = checkregint(secondreg);
            if (reg.memory[firstmem] + reg.regprim[indexsecondreg] > 255) {
                reg.memory[firstmem] = (~(reg.memory[firstmem]) + reg.regprim[indexsecondreg]);
            }
            else {
                reg.memory[firstmem] = reg.memory[firstmem] + reg.regprim[indexsecondreg];
            }
            memprint(firstmem);
            regprint();
            menu();
        } else {
            ADD();
        }
    }
    else{
        int indexfirstreg;
        int indexsecondreg;
        string firstreg;
        string secondreg;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkreg(firstreg) || checkreg(secondreg)) {
            indexfirstreg = checkregint(firstreg);
            indexsecondreg = checkregint(secondreg);
            if (reg.regprim[indexfirstreg] + reg.regprim[indexsecondreg] > 255) {
                reg.regprim[indexfirstreg] = (~(reg.regprim[indexfirstreg]) + reg.regprim[indexsecondreg]);
            }
            else {
                reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] + reg.regprim[indexsecondreg];
            }
            regprint();
            menu();
        } else {
            ADD();
        }
    }
}
//Function that substract data from register to register / memory
void SUB(){
    signal(SIGABRT, signal_handler);
    if (reg.memorytrue) {
        int indexsecondreg;
        int firstmem;
        string secondreg;
        cout << "Enter first memory address:";
        cin >> hex >> firstmem;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkmem(firstmem) || checkreg(secondreg)) {
            indexsecondreg = checkregint(secondreg);
            if (reg.memory[firstmem] + reg.regprim[indexsecondreg] < 0) {
                reg.memory[firstmem] = ~(reg.memory[firstmem]) + reg.regprim[indexsecondreg];
            }
            else {
                reg.memory[firstmem] = reg.memory[firstmem] - reg.regprim[indexsecondreg];
            }
            memprint(firstmem);
            regprint();
            menu();
        } else {
            SUB();
        }
    }
    else{
        int indexfirstreg;
        int indexsecondreg;
        string firstreg;
        string secondreg;
        cout << "Enter first register:";
        cin >> firstreg;
        cout << endl;
        cout << "Enter Second register:";
        cin >> secondreg;
        cout << endl;
        if (checkreg(firstreg) || checkreg(secondreg)) {
            indexfirstreg = checkregint(firstreg);
            indexsecondreg = checkregint(secondreg);
            if (reg.regprim[indexfirstreg] + reg.regprim[indexsecondreg] < 0) {
                reg.regprim[indexfirstreg] = ~(reg.regprim[indexfirstreg]) + reg.regprim[indexsecondreg];
            }
            reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] - reg.regprim[indexsecondreg];
            regprint();
            menu();
        } else {
            SUB();
        }
    }
}
// Menu Function
void menu(){
    signal(SIGABRT, signal_handler);
    int instruct;
    cout << endl;
    cout << "1. MOV" << endl;
    cout << "2. XCHG" << endl;
    cout << "3. NOT" << endl;
    cout << "4. INC" << endl;
    cout << "5. DEC" << endl;
    cout << "6. AND" << endl;
    cout << "7. OR" << endl;
    cout << "8. XOR" << endl;
    cout << "9. ADD" << endl;
    cout << "10.SUB" << endl;
    cout << "11.EXIT" << endl;
    cout << "Choose instruction :";
    cin  >> instruct;

    switch (instruct) {
        case 1:
            MOV();
        case 2:
            XCHG();
        case 3:
            NOT();
        case 4:
            INC();
        case 5:
            DEC();
        case 6:
            AND();
        case 7:
            OR();
        case 8:
            XOR();
        case 9:
            ADD();
        case 10:
            SUB();
        case 11:
            exit(0);
        default:
            menu();
    }
}

// Function that fill register with given data
void defregfill(){
    signal(SIGABRT, signal_handler);
    int defreg[8] ={0x01,0x04,0x69,0x35,0x58,0xA1,0x2C,0x97};
    for (int val = 0; val < reg.lenarr; val++)
        reg.regprim[val] = defreg[val];
    regprint();
    menu();
}
// Function that fill register with entered data
void regfill(){
    signal(SIGABRT, signal_handler);
    string defreg;
    cout << "Do you want to fill reg with default values? Y/N:";
    cin >> defreg;
    if (defreg == "Y" || defreg == "y"){
        defregfill();
    }
    int val = 0;
    while (val < reg.lenarr){
        int hexval;
        cout << "Wprowadz " + reg.reg[val] + " rejestr:";
        cin >> hex >> hexval;
        if (checkdecval(hexval)){
            reg.regprim[val] = hexval;
            val++;
        }
    }
    regprint();
}




int main() {
    signal(SIGABRT, signal_handler);
    Random();
    membool();
    regfill();
    menu();
    return 0;
}



#pragma clang diagnostic pop