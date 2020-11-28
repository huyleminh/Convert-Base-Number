#include "ConvertMachine.h"
#include <iostream>
#include <cmath>
#include "../big-interger/BigInt.h"

ConvertMachine* ConvertMachine::_instance = nullptr;

ConvertMachine* ConvertMachine::createConvertMachine() {
    if (_instance == nullptr)
        return new ConvertMachine();
    return _instance;
}

//Convert a number from base 16 or base 2 to base 10
string convertToDecimal(const string& str, const int& from) {
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
string fromDecimalToHex(const string& str) {
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
string fromHexToBinary(const string& str) {
    const vector<string> hexCode = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };

    string re = "";
    for (size_t i = 0; i < str.length(); i++) {
        int index = int(str[i]);
        if (str[i] >= 'A' && str[i] <= 'F')
            index -= 55;
        else 
            index -= 48;
        re += hexCode[index];
    }
    return re;
}

//Convert a number from base 10 base 2 or base 16
string convertFromDecimal(const string& str, const int& to) {
    if (to == 16)
        return fromDecimalToHex(str);
    string hex = fromDecimalToHex(str);
    return fromHexToBinary(hex);
}

//Interface to convert only
string ConvertMachine::convertNumber(const string& str, const int& from, const int& to) {
    if (from == to) {
        cout << "SAME BASE!" << endl;
        return str;
    }

    //From bin, hex to decimal
    if (to == 10)
        return convertToDecimal(str, from);
    //From decimal to hex, to bin
    if (from == 10)
        return convertFromDecimal(str, to);
    
    //From hex to bin
    if (from == 16) 
        return fromHexToBinary(str);
    
    //From = 2
    string decimal = convertToDecimal(str, from);
    return fromDecimalToHex(decimal);
}