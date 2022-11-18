//
// Created by Wojciech Szyjka on 27/10/2022.
//

#ifndef INTEL_EMULATOR_FUNC_H
#define INTEL_EMULATOR_FUNC_H
void menu();
int checkregint();
bool checkreg();
bool checkdecval();
void regprint();
void signal_handler();
void MOV();
void XCHG();
void DEC();
void INC();
void NOT();
void AND();
void ADD();
void SUB();
class Register;
#endif //INTEL_EMULATOR_FUNC_H
