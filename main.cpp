#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include <iostream>
#include "func.h"
#include <string>
#include <cstdlib>
#include <sstream>
#include <csignal>

using namespace std;

class Register {
    public:
        int lenarr = 8;
        string reg[8] = {"AH","AL","BH","BL","CH","CL","DH","DL"};
        uint8_t regprim[8] = {0,0,0,0,0,0,0,0};
        uint8_t memory[65536];
};
Register reg;

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

void signal_handler(int signal_num)
{
    cout << "The interrupt signal is (" << signal_num << "). \n";

    // It terminates the program
    exit(signal_num);
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

bool checkdecval(int hexval){
    if (hexval <= 255){
        return true;
    }
    return false;
}

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

void MOV(){
    signal(SIGABRT, signal_handler);
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
    if (checkreg(firstreg) || checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        indexsecondreg = checkregint(secondreg);
        reg.regprim[indexfirstreg] = reg.regprim[indexsecondreg];
        regprint();
        menu();
    }
    else {
        MOV();
    }
}

void XCHG(){
    signal(SIGABRT, signal_handler);
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
    if (checkreg(firstreg) || checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        indexsecondreg = checkregint(secondreg);
        int tempmem = reg.regprim[indexfirstreg];
        reg.regprim[indexfirstreg] = reg.regprim[indexsecondreg];
        reg.regprim[indexsecondreg] = tempmem;
        regprint();
        menu();
    }
    else {
        XCHG();
    }
}

void NOT(){
    signal(SIGABRT, signal_handler);
    int indexfirstreg;
    string firstreg;
    cout << "Enter register:";
    cin >> firstreg;
    cout << endl;
    if (checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        reg.regprim[indexfirstreg] = ~reg.regprim[indexfirstreg];
        regprint();
        menu();
    }
    else {
        NOT();
    }
}

void INC(){
    signal(SIGABRT, signal_handler);
    int indexfirstreg;
    string firstreg;
    cout << "Enter register:";
    cin >> firstreg;
    cout << endl;
    if (checkreg(firstreg)){ // || checkreg(firstreg)
        indexfirstreg = checkregint(firstreg);
        reg.regprim[indexfirstreg]++;
        regprint();
        menu();
    }
    else {
        INC();
    }
}

void DEC(){
    signal(SIGABRT, signal_handler);
    int indexfirstreg;
    string firstreg;
    cout << "Enter register:";
    cin >> firstreg;
    cout << endl;
    if (checkreg(firstreg)){ // || checkreg(firstreg)
        indexfirstreg = checkregint(firstreg);
        reg.regprim[indexfirstreg]--;
        regprint();
        menu();
    }
    else {
        INC();
    }
}

void AND(){
    signal(SIGABRT, signal_handler);
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
    if (checkreg(firstreg) || checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        indexsecondreg = checkregint(secondreg);
        reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] & reg.regprim[indexsecondreg];
        regprint();
        menu();
    }
    else {
        AND();
    }
}

void OR(){
    signal(SIGABRT, signal_handler);
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
    if (checkreg(firstreg) || checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        indexsecondreg = checkregint(secondreg);
        reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] | reg.regprim[indexsecondreg];
        regprint();
        menu();
    }
    else {
        OR();
    }
}

void XOR(){
    signal(SIGABRT, signal_handler);
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
    if (checkreg(firstreg) || checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        indexsecondreg = checkregint(secondreg);
        reg.regprim[indexfirstreg] = reg.regprim[indexfirstreg] ^ reg.regprim[indexsecondreg];
        regprint();
        menu();
    }
    else {
        XOR();
    }
}

void ADD(){
    signal(SIGABRT, signal_handler);
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
    if (checkreg(firstreg) || checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        indexsecondreg = checkregint(secondreg);
        if ( reg.regprim[indexfirstreg] + reg.regprim[indexsecondreg] > 255){
            reg.regprim[indexfirstreg] = (reg.regprim[indexfirstreg] + reg.regprim[indexsecondreg]) - 255;
        }
        reg.regprim[indexfirstreg] =  reg.regprim[indexfirstreg] + reg.regprim[indexsecondreg];
        regprint();
        menu();
    }
    else {
        ADD();
    }
}

void SUB(){
    signal(SIGABRT, signal_handler);
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
    if (checkreg(firstreg) || checkreg(firstreg)){
        indexfirstreg = checkregint(firstreg);
        indexsecondreg = checkregint(secondreg);
        if ( reg.regprim[indexfirstreg] + reg.regprim[indexsecondreg] < 0 ){
            reg.regprim[indexfirstreg] = ~(reg.regprim[indexfirstreg]) + reg.regprim[indexsecondreg];
        }
        reg.regprim[indexfirstreg] =  reg.regprim[indexfirstreg] - reg.regprim[indexsecondreg];
        regprint();
        menu();
    }
    else {
        SUB();
    }
}

void menu(){
    signal(SIGABRT, signal_handler);
    int instruct;
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


void defregfill(){
    signal(SIGABRT, signal_handler);
    int defreg[8] ={0x01,0x04,0x69,0x35,0x58,0xA1,0x2C,0x97};
    for (int val = 0; val < reg.lenarr; val++)
        reg.regprim[val] = defreg[val];
    regprint();
    menu();
}

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
    regfill();
    menu();
    return 0;
}



#pragma clang diagnostic pop