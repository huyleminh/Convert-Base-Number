#include "BigInt.h"
#include <cstring>
#include <stdlib.h>

template<class T>
void _swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

void reverse(string& str) 
{ 
    int n = str.length(); 
    for (int i = 0; i < n / 2; i++) 
        _swap(str[i], str[n - i - 1]); 
} 

void removeAllZero(string& str) {
    size_t pos = str.find_first_not_of("0");
    str.erase(0, pos);
    if (str == "")
        str = "0";
}

BigInt::BigInt() {
    this->_myVal = "";
    this->_sign = 1;
}

BigInt::BigInt(const BigInt& bigInt) {
    this->_myVal = bigInt._myVal;
    this->_sign = bigInt._sign;
}

BigInt::BigInt(const string& str) {
    this->_sign = (str[0] == '-') ? -1 : 1;
    this->_myVal = (_sign == -1) ? str.substr(1, str.length() - 1) : str;
    removeAllZero(this->_myVal);
}

BigInt& BigInt::operator =(const BigInt& bigInt) {
    this->_myVal = bigInt._myVal;
    this->_sign = bigInt._sign;
    return *this;
}

BigInt& BigInt::operator =(const string& str) {
    this->_sign = (str[0] == '-') ? -1 : 1;
    this->_myVal = (_sign == -1) ? str.substr(1, str.length() - 1) : str;
    removeAllZero(this->_myVal);
    return *this;
}

string BigInt::operator +(const BigInt& bigInt) {
    if (bigInt == "0") 
        return this->toString();
    else if (*this == "0")
        return BigInt(bigInt).toString(); 

    BigInt cloneThis = *this;
    BigInt cloneIn = bigInt;
    BigInt re;

    if (cloneThis._sign != cloneIn._sign) {
        if (cloneThis._myVal == cloneIn._myVal)
            return "0";
        return cloneThis - cloneIn.negative();
    }
    
    re._sign = cloneThis._sign;

    //Reverse 
    reverse(cloneThis._myVal);
    reverse(cloneIn._myVal);

    int carry = 0, i = 0, j = 0;

    while (i < cloneThis._myVal.length() && j < cloneIn._myVal.length()) {
        int sum = (int)cloneThis._myVal[i++] + (int)cloneIn._myVal[j++] - 96 + carry;
        carry = sum / 10;
        re._myVal += to_string(sum % 10);
    }

    while (i < cloneThis._myVal.length()) {
        int sum = (int)cloneThis._myVal[i++] - 48 + carry;
        carry = sum / 10;
        re._myVal += to_string(sum % 10);
    }
    while (j < cloneIn._myVal.length()) {
        int sum = (int)cloneIn._myVal[j++] - 48 + carry;
        carry = sum / 10;
        re._myVal += to_string(sum % 10);
    }

    re._myVal += to_string(carry);

    reverse(re._myVal);
    removeAllZero(re._myVal);

    return re.toString();
}

string BigInt::operator +(const string& bigInt) {
    BigInt tmp(bigInt);
    tmp = tmp + *this;
    return tmp.toString();
}

string BigInt::operator -(const BigInt& bigInt) {
    BigInt cloneThis(*this);
    BigInt cloneIn(bigInt);

    if (cloneThis == cloneIn)
        return "0";

    if (cloneThis._sign != cloneIn._sign) 
        return cloneThis + cloneIn.negative();
    
    if (cloneThis._sign == -1) 
        return (cloneThis > cloneIn) ? (cloneIn.positive() - cloneThis.positive()) : (cloneIn.positive() + cloneThis);
    
    BigInt re;
    if (cloneThis < cloneIn) {
        re._sign = -1;
        _swap(cloneThis._myVal, cloneIn._myVal);
    }

    reverse(cloneIn._myVal);
    reverse(cloneThis._myVal);

    int i = 0, borrow = 0, diff = 0;
    while (i < cloneIn._myVal.length()) {
        diff = (int)cloneThis._myVal[i]- borrow - (int)cloneIn._myVal[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else 
            borrow = 0;
        i++;
        re._myVal += to_string(diff);
    }
    
    while (i < cloneThis._myVal.length()) {
        diff = (int)cloneThis._myVal[i++] - 48 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        re._myVal += to_string(diff);
    }

    reverse(re._myVal);
    removeAllZero(re._myVal);
    return re.toString();
}

string BigInt::operator -(const string& bigInt) {
    BigInt clone(bigInt);
    return *this - clone;
}

string BigInt::operator *(const BigInt& bigInt) {
    if (*this == "0" || bigInt == "0")
        return "0";

    vector<BigInt*> multi;
    BigInt cloneThis = *this;
    BigInt cloneIn = bigInt;

    reverse(cloneThis._myVal);
    reverse(cloneIn._myVal);
    
    for (size_t i = 0; i < cloneIn._myVal.length(); i++) {
        string re = "";
        int carry = 0;
        for (size_t j = 0; j < cloneThis._myVal.length(); j++) {
            int mul = ((int)cloneIn._myVal[i] - 48) * ((int)cloneThis._myVal[j] - 48) + carry;
            re += to_string(mul % 10);
            carry = mul / 10;
        }
        re += to_string(carry);
        reverse(re);
        removeAllZero(re);
        //Concat 0
        string tail(i, '0');
        re += tail;
        multi.push_back(new BigInt(re));
    }

    BigInt r(*multi[0]);

    for (size_t i = 1; i < multi.size(); i++)
        r = r + *multi[i];
    r._sign = _sign * bigInt._sign;
    return r.toString();
}

string BigInt::operator *(const string& bigInt) {
    BigInt clone(bigInt);
    return *this * clone; 
}

string BigInt::operator /(const BigInt& bigInt) {
    BigInt cloneThis(*this);
    BigInt cloneIn(bigInt);   

    if (cloneIn == "0")
        return "ERROR";
    if (cloneThis == "0")
        return "0";
    if (cloneThis.positive() < cloneIn.positive())
        return "0";
    else if (cloneThis == cloneIn)
        return "1";

    cloneThis._sign = cloneIn._sign = 1;
    
    int count = 0;
    while (cloneThis >= cloneIn) {
        string sub = cloneThis - cloneIn;
        count++;
        cloneThis._myVal = sub;
    }
    count *= this->_sign * bigInt._sign;
    return to_string(count);
}

string BigInt::operator /(const string& bigInt) {
    BigInt clone(bigInt);
    return *this / clone;
}

string BigInt::operator %(const BigInt& bigInt) {
    string re = *this / bigInt;
    string mul = BigInt(bigInt) * re;
    return *this - mul;
}

string BigInt::operator %(const string& bigInt) {
    BigInt clone(bigInt);
    return *this % clone;
}


//Arthimetic operators
bool BigInt::operator ==(const BigInt& bigInt) const {
    return (this->_myVal == bigInt._myVal && this->_sign == bigInt._sign);
}

bool BigInt::operator ==(const string& bigInt) const {
    string val = (this->_sign == -1) ? ("-" + this->_myVal) : this->_myVal;
    return val == bigInt;
}

bool BigInt::operator <(const BigInt& bigInt) const {
    if (this->_sign != bigInt._sign)
        return this->_sign < bigInt._sign;

    if (_myVal.size() != bigInt._myVal.size())
        return (this->_sign == 1) ? this->_myVal.size() < bigInt._myVal.size() : this->_myVal.size() > bigInt._myVal.size();

    for (int i = 0; i < this->_myVal.size(); i++) 
        if (_myVal[i] != bigInt._myVal[i])
            return (_sign == 1) ? _myVal[i] < bigInt._myVal[i] : _myVal[i] > bigInt._myVal[i];

    return false;
}

bool BigInt::operator <=(const BigInt& bigInt) const {
    return (*this < bigInt || *this == bigInt);
}

bool BigInt::operator >(const BigInt& bigInt) const {
    return !(*this <= bigInt);
}

bool BigInt::operator >=(const BigInt& bigInt) const {
    return !(*this < bigInt);
}


BigInt::~BigInt() {
    this->_myVal = "0";
}

BigInt& BigInt::toFixed(const size_t& digits) {
    string fix(digits, '0');
    this->_myVal = fix + this->_myVal;
    return *this;
}

BigInt BigInt::negative() {
    BigInt x = *this;
    x._sign *= -1;
    return x;
}

BigInt BigInt::positive() {
    BigInt x;
    x._myVal = this->_myVal;
    x._sign = 1;
    return x;
}

void BigInt::display() {
    cout << this->_myVal << endl;
}

string BigInt::toString() {
    return (this->_sign == -1) ? ("-" + this->_myVal) : this->_myVal;
}