#include "ConvertMachine.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

#include "../big-interger/BigInt.h"
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
//|                        STANDARD NUMBER                      |
//--------------------------------------------------------------|

/**
 * @params: str (number), base (number's base)
*/
void ConvertMachine::convertStandardNumber(const string& str, const int& base) {
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
//|                        SPECIAL NUMBER                       |
//--------------------------------------------------------------|

/**
 * @params: fixed (fixed 8 or 16 or 32)
*/
void ConvertMachine::convertSpecialNumber(const string& str, const int& base, const int& fixed) {
    switch (base) {
    case 10: {
        this->convertSpecialDecimal(str, fixed);
        break;
    }
    case 16: {
        this->convertSpecialHexa(str, fixed);
        break;
    }
    case 2: {
        this->convertSpecialBinary(str, fixed);
        break;
    }
    default:
        cout << "ERROR" << endl;
        break;
    }
}

//--------------------------------------------------------------------------

/*
    *Convert between base x and base y
    *@params: from (base of str), to (base str will be)
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
    
    //frorm = 10
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
    BigInt result;
    int n = str.length();
    for (int i = 0; i < n; i++) {
        int temp = str[i];
        if (temp >= 'A' && temp <= 'F')
            temp -= 55;
        else 
            temp -= 48;
        result = result + to_string(temp * (int)pow(from, n - 1 - i));
    }    
    return result.toString();
}

//Convert a number from base 10 to base 16
string ConvertMachine::fromDecimalToHex(const string& str) {
    BigInt clone(str);
    BigInt zero("0");
    string mod = "";
    string re = "";

    do {
        mod = clone % "16";
        if (stoi(mod) > 9)
            mod = (char)(stoi(mod) + 55);
        re = mod + re;
        clone = clone / "16";
    } while (clone > zero);
    return re;
}

//Convert a number from base 16 to base 2
string ConvertMachine::fromHexToBinary(const string& str) {
    const vector<string> hexCode = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };

    string re = "";
    for (size_t i = 0; i < str.length(); i++) {
        int index = int(str[i]);
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
    string re = "";
    string clone = str;
    if (str.length() > 16)
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


void ConvertMachine::convertStandardDecimal(const string& str) {
    string decimal;
    decimal = (str[0] != '-') ? str : str.substr(1, str.length() - 1);

    string hexa = fromDecimalToHex(decimal);
    string binary = fromHexToBinary(hexa);

    if (str[0] == '-') {
        hexa = '-' + hexa;
        binary = '-' + binary;
    }

    cout << "Your input is " << str << " is at base 10." << endl;
    cout << "---------------------------------------------------------------\n";
    cout << "| Value at base 16 | " << setw(40) << left << hexa << " |" << endl;
    cout << "---------------------------------------------------------------\n";
    cout << "| Value at base 2  | " << setw(40) << left << binary << " |" << endl;
    cout << "---------------------------------------------------------------\n";
}

void ConvertMachine::convertStandardHexa(const string& str) {
    string hexa;
    hexa = (str[0] != '-') ? str : str.substr(1, str.length() - 1);

    string decimal = convertToDecimal(hexa, 16);
    string binary = fromHexToBinary(hexa);

    if (str[0] == '-') {
        decimal = '-' + decimal;
        binary = '-' + binary;
    }

    cout << "Your input is " << str << " is at base 16." << endl;
    cout << "---------------------------------------------------------------\n";
    cout << "| Value at base 10 | " << setw(40) << left << decimal << " |" << endl;
    cout << "---------------------------------------------------------------\n";
    cout << "| Value at base 2  | " << setw(40) << left << binary << " |" << endl;
    cout << "---------------------------------------------------------------\n";
}

void ConvertMachine::convertStandardBinary(const string& str) {
    string binary;
    binary = (str[0] != '-') ? str : str.substr(1, str.length() - 1);

    string decimal = convertToDecimal(binary, 2);
    string hexa = fromDecimalToHex(decimal);

    if (str[0] == '-') {
        decimal = '-' + decimal;
        hexa = '-' + hexa;
    }

    cout << "Your input is " << str << " is at base 2." << endl;
    cout << "---------------------------------------------------------------\n";
    cout << "| Value at base 10 | " << setw(40) << left << decimal << " |" << endl;
    cout << "---------------------------------------------------------------\n";
    cout << "| Value at base 16 | " << setw(40) << left << hexa << " |" << endl;
    cout << "---------------------------------------------------------------\n";
}



void ConvertMachine::convertSpecialDecimal(const string& str, const int& fixed) {
    string binary, hexa, one, two, sign;

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
        //Fixed 8 - 16 - 32 bits
        InputHandler::fixedBits(binary, fixed);

        one = this->convertOneComplement(binary);
        two = this->convertTwoComplement(binary);

        sign = '1' + binary.substr(1, binary.length() - 1);

        //Convert from two's complement
        string tmp = convertToDecimal(two, 2);
        hexa = fromDecimalToHex(tmp);         
    }
    
    cout << "--------------------------------------------------------------------\n";
    cout << "| Hexa                  | " << setw(40) << left << hexa << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Binary (abs of input) | " << setw(40) << left << binary << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| One's complement      | " << setw(40) << left << one << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Two's complement      | " << setw(40) << left << two << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Sign magnitude        | " << setw(40) << left << sign << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
}

void ConvertMachine::convertSpecialHexa(const string& str, const int& fixed) {
    string binary, decimal;

    decimal = this->convertToDecimal(str, 16);
    binary = this->fromHexToBinary(str);
    InputHandler::fixedBits(binary, fixed);
    
    cout << "--------------------------------------------------------------------\n";
    cout << "| Decimal               | " << setw(40) << left << decimal << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Binary                | " << setw(40) << left << binary << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| One's complement      | " << setw(40) << left << binary << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Two's complement      | " << setw(40) << left << binary << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Sign magnitude        | " << setw(40) << left << binary << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
}

void ConvertMachine::convertSpecialBinary(const string& str, const int& fixed) {
    string one, two, hexa, decimal;

    hexa = this->fromBinaryToHex(str);
    decimal = this->convertToDecimal(str, 2);

    string clone = str;
    InputHandler::fixedBits(clone, fixed);
    if (str != "0") {
        one = this->convertOneComplement(clone);
        two = this->convertTwoComplement(clone);
    }
    else {
        one = clone;
        two = clone;
    }

    cout << "--------------------------------------------------------------------\n";
    cout << "| Decimal               | " << setw(40) << left << decimal << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Hexa                  | " << setw(40) << left << hexa << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| One's complement      | " << setw(40) << left << one << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
    cout << "| Two's complement      | " << setw(40) << left << two << " |" << endl;
    cout << "--------------------------------------------------------------------\n";
}

//---------------------------------------------------------------------------