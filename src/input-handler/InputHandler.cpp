#include "InputHandler.h"
#include <regex>
#include <mutex>
#include <iostream>
using namespace std;

//--------------------------------------------------------------------------|
//|                                                                         |
//|                           SETUP BASE HANDLER                            |
//|                                                                         |
//--------------------------------------------------------------------------|

InputHandler* InputHandler::_instance = nullptr;

InputHandler* InputHandler::getHandler() {
    if (_instance == nullptr) 
        return new InputHandler();
    else 
        return _instance;
}

//---------------------------------------------------------------------------

//--------------------------------------------------------------------------|
//|                                                                         |
//|                             PUBLIC METHODS                              |
//|                                                                         |
//--------------------------------------------------------------------------|

bool InputHandler::start() {
    cout << "1. Start (press 1)\n";
    cout << "2. Exit (press any key to exit except 1)\n";
    cout << ">Input your choice: ";
    string op = "";
    getline(cin, op, '\n');
    if (op == "1")
        return true;
    else 
        return false;
}

bool InputHandler::inputNumber(string& str, string& base, string& fixed) {
    cout << "----------------------------------------------\n";
    cout << "Input your number: ";
    getline(cin, str, '\n');
    cout << "Input your base number: ";
    getline(cin, base, '\n');

    const std::regex bReg("^\\d+$");
    if (regex_match(base, bReg) == false)
        base = "0";

    if (!this->validateNumber(str, stoi(base)))
        return false;
    
    this->removeAllZeroHead(str);

    do {
        cout << "Input number of bits to fix 8 or 16 or 32 or 64: ";
        getline(cin, fixed, '\n');
    } while (fixed != "8" && fixed != "16" && fixed != "32" && fixed != "64");
    cout << "----------------------------------------------\n";
    return true;
}

void InputHandler::removeAllZeroHead(string& inputStr) {
    if (inputStr == "0")
        return;
        
    string::iterator begin = inputStr.begin();
    string::iterator end =inputStr.begin();
    if (inputStr[0] == '-') {
        ++begin;
        ++end;
    }
    while (end != inputStr.end()) {
        if (*end != '0')
            break;
        end++;
    }
    
    if (end == inputStr.end()) 
        inputStr = "0";
    else 
        inputStr.erase(begin, end);
}

bool InputHandler::validateNumber(const string& inputStr, const int& base) {
    switch (base) {
    case 2: {
        const std::regex binary ("^(-?)([0-1]+)$");    
        return regex_match(inputStr, binary);
    }
    case 16: {
        const std::regex hexa ("^(-?)([\\dA-Fa-f]+)$");
        return regex_match(inputStr, hexa);
    }
    case 10: {
        const std::regex decimal ("^(-?)(\\d+)$");
        return regex_match(inputStr, decimal);
    }
    default:
        return false;
    }
}

void InputHandler::fixedBits(string& inputStr, const int& mode) {
    if (mode != InputHandler::BASE_BITS::MIN && mode != InputHandler::BASE_BITS::AVE && mode != InputHandler::BASE_BITS::MAX && mode != InputHandler::BASE_BITS::S_MAX)
        return;
    
    if (inputStr.length() > mode) {
        inputStr.erase(0, inputStr.length() - mode);
        return;
    }
    
    string fixed(mode - inputStr.length(), '0');
    inputStr = fixed + inputStr;
}
