#include "InputHandler.h"
#include <regex>
#include <mutex>

InputHandler* InputHandler::_instance = nullptr;

InputHandler* InputHandler::getHandler() {
    if (_instance == nullptr) 
        return new InputHandler();
    else 
        return _instance;
}

void InputHandler::removeAllZeroHead(string& inputStr) {
    if (inputStr.length() == 0 || inputStr == "0") {
        inputStr = "0";   
        return;
    }
    
    if (inputStr[0] != '0')
        return;
    
    string::iterator begin = inputStr.begin();
    string::iterator end =inputStr.begin();
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

bool InputHandler::validateNumber(const string& inputStr) {
    //Regular expression that an input string match digit and A-F (hexadecimal format)
    std::regex reg ("^([\\dA-F]+)$");
    return std::regex_match(inputStr, reg);
}

void InputHandler::fixedBits(string& inputStr, const char& mode) {
    if (mode != InputHandler::BASE_BITS::MIN || mode != InputHandler::BASE_BITS::AVE || InputHandler::BASE_BITS::MAX)
        return;
    
    if (inputStr.length() >= mode)
        return;
    
    string fixed(mode - inputStr.length(), '0');
    inputStr = fixed + inputStr;
}
