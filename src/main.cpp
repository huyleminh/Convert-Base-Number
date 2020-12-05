#include "./input-handler/InputHandler.h"
#include "./machine/ConvertMachine.h"
#include <iostream>
#include <Windows.h>
using namespace std;


int main() {
    //*Main program
    InputHandler* handler = InputHandler::getHandler();
    string number;
    string base, fixed;
    bool check, start;

    while (true) {
        //Start program
        system("cls");
        Sleep(500);
        start = handler->start();
        if (!start) {
            system("cls");
            cout << "THANK YOU!!!" << endl;
            Sleep(1000);
            exit(0);
        }   

        while (true) {
            check = handler->inputNumber(number, base, fixed);
            if (!check)
                cout << "SYNTAX ERROR!" << endl;
            else
                break;
        }

        ConvertMachine* machine = ConvertMachine::createConvertMachine();
        cout << endl << endl;
        machine->convertStandardNumber(number, stoi(base));
        cout << endl << endl;
        machine->representNumber(number, stoi(base), stoi(fixed));

        system("pause");
    }

    return 0;
}