#include "ConvertMachine.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "../input-handler/InputHandler.h"

//--------------------------------------------------------------------------|
//|                                                                         |
//|                           SETUP BASE MACHINE                            |
//|                                                                         |
//--------------------------------------------------------------------------|

ConvertMachine* ConvertMachine::_instance = nullptr;

ConvertMachine* ConvertMachine::createConvertMachine() {
    if (_instance == nullptr)
        return new ConvertMachine();
    return _instance;
}

//---------------------------------------------------------------------------


//--------------------------------------------------------------------------|
//|                                                                         |
//|                              PUBLIC INTERFACES                          |
//|                                                                         |
//--------------------------------------------------------------------------|


//--------------------------------------------------------------|
//|                      CONVERT BASE NUMBER                    | 
//--------------------------------------------------------------|

/**
 * @params: str (number), base (number's base)
*/
void ConvertMachine::convertStandardNumber(const string& str, const int& base) {
    cout << "-------------------------------------------------------------------------------------------------------\n";
    cout << "|                                         CONVERT BASE NUMBER                                         |\n";
    cout << "|-----------------------------------------------------------------------------------------------------|\n";
    switch (base)
    {
    case 10:
        this->convertStandardDecimal(str);
        break;
    case 16:
        this->convertStandardHexa(str);
        break;
    case 2:
        this->convertStandardBinary(str);
        break;
    default:
        cout << "ERROR" << endl;
        break;
    }
}

//--------------------------------------------------------------|
//|                       REPRESENT NUMBER                      |
//--------------------------------------------------------------|

/**
 * @params: fixed (fixed 8 or 16 or 32)
*/
void ConvertMachine::representNumber(const string& str, const int& base, const int& fixed) {
    cout << "------------------------------------------------------------------------------------------------------------\n";
    cout << "|                                             REPRESENT NUMBER                                             |\n";
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    switch (base) {
    case 10: {
        this->representDecimal(str, fixed);
        break;
    }
    case 16: {
        this->representHexa(str, fixed);
        break;
    }
    case 2: {
        this->representBinary(str, fixed);
        break;
    }
    default:
        cout << "ERROR" << endl;
        break;
    }
}

//--------------------------------------------------------------------------

/**
 * Convert between base x and base y
 * @params: from (base of str), to (base str will be)
*/
string ConvertMachine::convertNumber(const string& str, const int& from, const int& to) {
    if (from == to) {
        cout << "SAME BASE!" << endl;
        return str;
    }
    if (to == 10)
        return this->convertToDecimal(str, from);
    if (from == 16)
        return this->fromHexToBinary(str);
    if (from == 2)
        return this->fromBinaryToHex(str);
    
    //from = 10
    string hex = this->fromDecimalToHex(str);
    if (to == 16)
        return hex;
    else 
        return this->fromHexToBinary(hex);
}

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------|
//|                                                                         |
//|                             PRIVATE METHODS                             |
//|                                                                         |
//--------------------------------------------------------------------------|

//Convert a number from base 16 or base 2 to base 10
string ConvertMachine::convertToDecimal(const string& str, const int& from) {
    long long result = 0;
    int n = str.length();

    for (int i = 0; i < n; i++) {
        int temp = str[i];
        if (temp >= 'A' && temp <= 'F')
            temp -= 55;
        else 
            temp -= 48;
        result += (temp * (long long)pow(from, n - 1 - i));
    }    
    return to_string(result);
}

//Convert a number from base 10 to base 16
string ConvertMachine::fromDecimalToHex(const string& str) {
    string re = "";
    long long number = stoull(str);
    int mod;

    do {
        mod = int(number % 16);
        if (mod > 9)
            mod += 55;
        else 
            mod += 48;
        re = char(mod) + re;
        number /= 16;
    } while (number > 0);
    return re;
}

//Convert a number from base 16 to base 2
string ConvertMachine::fromHexToBinary(const string& str) {
    const vector<string> hexCode = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };

    string re = "";
    int index;
    for (size_t i = 0; i < str.length(); i++) {
        index = int(str[i]);
        if (str[i] >= 'A' && str[i] <= 'F')
            index -= 55;
        else if (str[i] >= 'a' && str[i] <= 'f')
            index -= 87;
        else 
            index -= 48;
        re += hexCode[index];
    }
    return re;
}

string ConvertMachine::fromBinaryToHex(const string& str) {
    if (str == "0")
        return str;
    const vector<string> hexCode = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
    const vector<string> binCode = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
    string re = "", clone = str;

    if (str.length() > 32)
        InputHandler::fixedBits(clone, 64);
    else if (str.length() > 16)
        InputHandler::fixedBits(clone, 32);
    else if (str.length() > 8)
        InputHandler::fixedBits(clone, 16);
    else 
        InputHandler::fixedBits(clone, 8);
    
    for (size_t i = 0; i < clone.length(); i += 4) {
        string code = clone.substr(i, 4);
        vector<string>::const_iterator it = find(hexCode.begin(), hexCode.end(), code);
        if (it != hexCode.end()) {
            size_t index = it - hexCode.begin();
            re += binCode[index];
        }
    }
    return re;
}


/**
 * @return: one's complement of a binary string
 * @params: str (binary string)
*/
string ConvertMachine::convertOneComplement(const string& str) {
    string re;
    re = str;
    for (size_t i = 0; i < re.length(); ++i) 
        re[i] = !((int)re[i] - 48) + 48;
    return re;
}

/**
 * @return: two's complement of a binary string
 * @params: str (binary string)
*/
string ConvertMachine::convertTwoComplement(const string& str) {
    string re;
    re = str;
    //Find last charactor match bit 1
    size_t pos = re.find_last_of('1');
    
    if (pos == std::string::npos)
        pos = re.length();
    //Not all bit before pos
    for (size_t i = 0; i < pos; ++i)
        re[i] = !((int)re[i] -48) + 48;
    return re;    
}


//--------------------------------------------------------------|
//|                      CONVERT BASE NUMBER                    |
//--------------------------------------------------------------|

void ConvertMachine::convertStandardDecimal(const string& str) {
    string decimal, hexa = "0", binary = "0";
    if (str == "0")
        goto DISPLAY;
    decimal = (str[0] != '-') ? str : str.substr(1, str.length() - 1);

    hexa = fromDecimalToHex(decimal);
    binary = fromHexToBinary(hexa);

    if (str[0] == '-') {
        hexa = '-' + hexa;
        binary = '-' + binary;
    }
DISPLAY:
    cout << "| Value at base 16 | " << setw(80) << left << hexa << " |" << endl;
    cout << "|-----------------------------------------------------------------------------------------------------|\n";
    cout << "| Value at base 2  | " << setw(80) << left << padding(binary) << " |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------\n";
}

void ConvertMachine::convertStandardHexa(const string& str) {
    string hexa, decimal = "0", binary = "0";
    if (str == "0")
        goto DISPLAY;
    hexa = (str[0] != '-') ? str : str.substr(1, str.length() - 1);

    decimal = convertToDecimal(hexa, 16);
    binary = fromHexToBinary(hexa);

    if (str[0] == '-') {
        decimal = '-' + decimal;
        binary = '-' + binary;
    }
DISPLAY:

    cout << "| Value at base 10 | " << setw(80) << left << decimal << " |" << endl;
    cout << "|-----------------------------------------------------------------------------------------------------|\n";
    cout << "| Value at base 2  | " << setw(80) << left << padding(binary) << " |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------\n";
}

void ConvertMachine::convertStandardBinary(const string& str) {
    string binary;
    binary = (str[0] != '-') ? str : str.substr(1, str.length() - 1);

    string decimal = convertToDecimal(binary, 2);
    string hexa = fromBinaryToHex(binary);

    if (str[0] == '-') {
        decimal = '-' + decimal;
        hexa = '-' + hexa;
    }

    cout << "| Value at base 10 | " << setw(80) << left << decimal << " |" << endl;
    cout << "|-----------------------------------------------------------------------------------------------------|\n";
    cout << "| Value at base 16 | " << setw(80) << left << hexa << " |" << endl;
    cout << "-------------------------------------------------------------------------------------------------------\n";
}

//---------------------------------------------------------------


//--------------------------------------------------------------|
//|                       REPRESENT NUMBER                      |
//--------------------------------------------------------------|

void ConvertMachine::representDecimal(const string& str, const int& fixed) {
    string binary = "0", hexa = "0", one = "0", two = "0", sign = "0";
    if (str == "0")
        goto DISPLAY;
    if (str[0] != '-') {
        hexa = fromDecimalToHex(str);
        binary = fromHexToBinary(hexa);
        InputHandler::fixedBits(binary, fixed);

        one = binary;
        two = binary;
        sign = binary;
    }
    else {
        string clone = str.substr(1, str.length() - 1);

        binary = this->convertNumber(clone, 10, 2);
        InputHandler::fixedBits(binary, fixed);

        one = this->convertOneComplement(binary);
        two = this->convertTwoComplement(binary);
        sign = '1' + binary.substr(1, binary.length() - 1);

        //Convert from two's complement
        hexa = fromDecimalToHex(convertToDecimal(two, 2));         
    }
DISPLAY:  

    cout << "| Hexa                  | " << setw(80) << left << hexa << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Binary (abs of input) | " << setw(80) << left << padding(binary) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| One's complement      | " << setw(80) << left << padding(one) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Two's complement      | " << setw(80) << left << padding(two) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Sign magnitude        | " << setw(80) << left << padding(sign) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
}

void ConvertMachine::representHexa(const string& str, const int& fixed) {
    string binary = "0", clone;

    if (str == "0")
        goto DISPLAY;
    if (str[0] == '-') {
        clone = str.substr(1, str.length() - 1);
        string decimal;
        decimal = '-' + this->convertToDecimal(clone, 16);
        return this->representDecimal(decimal, fixed);
    }

    clone = str;
    binary = this->fromHexToBinary(clone);
    InputHandler::fixedBits(binary, fixed);

DISPLAY:
    cout << "| Binary                | " << setw(80) << left << padding(binary) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| One's complement      | " << setw(80) << left << padding(binary) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Two's complement      | " << setw(80) << left << padding(binary) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Sign magnitude        | " << setw(80) << left << padding(binary) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
}

void ConvertMachine::representBinary(const string& str, const int& fixed) {
    string hexa = "0", clone = "0";

    if (str == "0")
        goto DISPLAY;
    if (str[0] == '-') {
        clone = str.substr(1, str.length() - 1);
        string decimal = '-' + this->convertToDecimal(clone, 2);
        this->representDecimal(decimal, fixed);
        return;
    } 

    clone = str;
    InputHandler::fixedBits(clone, fixed);

    hexa = this->fromBinaryToHex(clone);
DISPLAY:
    cout << "| Hexa                  | " << setw(80) << left << hexa << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Binary (abs of input) | " << setw(80) << left << padding(clone) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| One's complement      | " << setw(80) << left << padding(clone) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Two's complement      | " << setw(80) << left << padding(clone) << " |" << endl;
    cout << "|----------------------------------------------------------------------------------------------------------|\n";
    cout << "| Sign magnitude        | " << setw(80) << left << padding(clone) << " |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------\n";
}

//---------------------------------------------------------------


/**
 * @return: string displayed with padding (seperated 4 bits)
 * example: 11001001 => 1100 1001
*/
string ConvertMachine::padding(const string& str) {
    if (str == "0")
        return str;
    string clone = (str[0] != '-') ? str : str.substr(1, str.length() - 1);
    if (clone.length() > 32)
        InputHandler::fixedBits(clone, 64);
    else if (clone.length() > 16)
        InputHandler::fixedBits(clone, 32);
    else if (clone.length() > 8)
        InputHandler::fixedBits(clone, 16);
    else 
        InputHandler::fixedBits(clone, 8);
    for (size_t i = 4; i < clone.length(); i += 5)
        clone.insert(i, " ");
    return (str[0] != '-') ? clone : '-' + clone;
}

//---------------------------------------------------------------------------