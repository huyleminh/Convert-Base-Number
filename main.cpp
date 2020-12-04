#include "./big-interger/BigInt.h"
#include "./input-handler/InputHandler.h"
#include "machine/ConvertMachine.h"
using namespace std;


int main() {
    //*Main program
    InputHandler* handler = InputHandler::getHandler();
    string number;
    string base, fixed;
    bool check;

    while (true) {
        while (true) {
            check = handler->inputNumber(number, base, fixed);
            if (!check)
                cout << "SYNTAX ERROR!" << endl;
            else
                break;
        }

        ConvertMachine* machine = ConvertMachine::createConvertMachine();

        cout << "Convert number at standard: " << endl;
        machine->convertStandardNumber(number, stoi(base));

        cout << "Convert number at special:" << endl;
        machine->convertSpecialNumber(number, stoi(base), stoi(fixed));
        
    }

    return 0;
}