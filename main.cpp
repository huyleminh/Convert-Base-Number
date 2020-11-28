#include "./big-interger/BigInt.h"
#include "./input-handler/InputHandler.h"
#include "machine/ConvertMachine.h"
using namespace std;

int main(int args, char** argv) {
    // if (args != 3) {
    //     cout << "Unvalid input" << endl;
    //     return -1;
    // }

    // string input = argv[1];
    // bool checkInput = InputHandler::getHandler()->validateNumber(input);

    // if (checkInput == false) {
    //     cout << "Unregconized a number" << endl;
    //     return -1;
    // }

    // string base = argv[2];
    // if (base == "d") {
    //     cout << "Input decimal" << endl;
    // }    
    // else if (base == "h") {
    //     cout << "Input hexadecimal" << endl;
    // }
    // else if (base == "b") {
    //     cout << "Input binary" << endl;
    // }
    // else 
    //     cout << "Unregconized available base converter." << endl;
    /*string number = argv[1];
    string number1 = argv[2];*/

    string number;
    string from;
    string to;

    while (1) {
        getline(cin, number, '\n');
        if (number == "end")
            break;
        getline(cin, from, '\n');
        getline(cin, to, '\n');
        
        ConvertMachine* machine = ConvertMachine::createConvertMachine();
        cout << machine->convertNumber(number, stoi(from), stoi(to)) << endl;
        //cout << "a / b = " << BigInt(number) / BigInt(from);
        //break;
    }
    
    return 0;
}