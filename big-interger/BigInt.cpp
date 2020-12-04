#include "BigInt.h"
#include <cstring>
#include <algorithm>

//Global methods
template<class T>
void _swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

void reverse(string& str) { 
    int n = str.length(); 
    for (int i = 0; i < n / 2; i++) 
        _swap(str[i], str[n - i - 1]); 
} 

void removeAllZero(string& str) {
    if (str[0] != '0')
        return;
    size_t pos = str.find_first_not_of("0");
    str.erase(0, pos);
    if (str == "")
        str = "0";
}

void fixedLength(string& left, string& right) {
    size_t n = left.length();
    size_t m = right.length();
    if (n < m) {
        string fix(m - n, '0');
        left = fix + left;
    }
    else {
        string fix(n - m, '0');
        right = fix + right;
    }
}

//--------------------------------------------------------------------------|
//|                                                                         |
//|                               STRING METHODS                            |
//|                                                                         |
//--------------------------------------------------------------------------|

//Arithmetic operators 
bool operator <(const string& left, const string& right) {
    size_t n, m;
    n = left.length();
    m = right.length();

    if (n != m) 
        return n < m;
    for (size_t i = 0; i < n; ++i) {
        if (left[i] != right[i]) 
            return left[i] < right[i];
    }
    return false;
}

bool operator <=(const string& left, const string& right) {
    return (left == right || left < right);
}

bool operator >(const string& left, const string& right) {
    return !(left <= right);
}

bool operator >=(const string& left, const string& right) {
    return !(left < right);
}

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------|
//|                                                                         |
//|                               CONSTRUCTORS                              |
//|                                                                         |
//--------------------------------------------------------------------------|

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
    this->_myVal = (_sign == 1) ? str : str.substr(1, str.length() - 1);
    removeAllZero(this->_myVal);
}

//--------------------------------------------------------------------------|
//|                                                                         |
//|                               ASSIGNMENTS                               |
//|                                                                         |
//--------------------------------------------------------------------------|

BigInt& BigInt::operator =(const BigInt& bigInt) {
    this->_myVal = bigInt._myVal;
    this->_sign = bigInt._sign;
    return *this;
}

BigInt& BigInt::operator =(const string& str) {
    this->_sign = (str[0] == '-') ? -1 : 1;
    this->_myVal = (_sign == 1) ? str : str.substr(1, str.length() - 1);
    removeAllZero(this->_myVal);
    return *this;
}

//--------------------------------------------------------------------------|
//|                                                                         |
//|                          MATHEMATICS OPERATORS                          |
//|                                                                         |
//--------------------------------------------------------------------------|

string BigInt::operator +(const BigInt& bigInt) {
    if (bigInt.isZero()) 
        return this->toString();
    if (this->isZero())
        return bigInt.toString(); 

    BigInt cloneThis = *this;
    BigInt cloneIn = bigInt;
    BigInt re;

    if (cloneThis._sign != cloneIn._sign) {
        if (cloneThis._myVal == cloneIn._myVal)
            return "0";
        return cloneThis - cloneIn.negative();
    }
    
    //Fixed equal length
    fixedLength(cloneThis._myVal, cloneIn._myVal);

    int carry = 0;
    for (int i = cloneThis._myVal.length() - 1; i > -1; i--) {
        int sum = (int)cloneThis._myVal[i] + (int)cloneIn._myVal[i] - 96 + carry;
        carry = sum / 10;
        re._myVal = to_string(sum % 10) + re._myVal;
    }
    if (carry > 0)
        re._myVal = to_string(carry) + re._myVal;
    re._sign = cloneThis._sign;

    return re.toString();
}

//Operator string - string
string operator -(const string& _left, const string& _right) {
    if (_left == "0")
        return _right;
    if (_right == "0")
        return _left;
    
    string left, right;
    left = _left;
    right = _right;
    string re(_left.length(), '0');
    
    fixedLength(left, right);

    int borrow = 0, diff = 0;
    for (int i = left.length() - 1; i > -1; --i) {
        diff = (int)left[i]- borrow - (int)right[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else 
            borrow = 0;
        re[i] = char(diff + 48);
    }
    removeAllZero(re);
    return re;
}

string BigInt::operator +(const string& bigInt) {
    BigInt tmp(bigInt);
    tmp = tmp + *this;
    return tmp.toString();
}

string BigInt::operator -(const BigInt& bigInt) {
    if (*this == bigInt)
        return "0";
    string left, right;
    left = this->_myVal;
    right = bigInt._myVal;

    int sign = 1;
    if (*this < bigInt) {
        _swap(left, right);
        sign = -1;
    }
        
    string re;
    re = left - right;
    if (sign == -1)
        return "-" + re;
    return re;
}

string BigInt::operator -(const string& bigInt) {
    BigInt clone(bigInt);
    return *this - clone;
}

string BigInt::operator *(const BigInt& bigInt) {
    if (this->_myVal == "0" || bigInt._myVal == "0")
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
    if (bigInt.isZero())
        return "ERROR";
    if (this->isZero())
        return "0";
    if (_myVal < bigInt._myVal)
        return "0";
    if (_myVal == bigInt._myVal)
        return "1";
    
    int sign = _sign * bigInt._sign;
    string cloneThis, cloneIn, re;
    re = "";

    cloneThis = _myVal;
    cloneIn = bigInt._myVal;  
    
    int count = 0;
    while (cloneThis >= cloneIn) {
        re = cloneThis - cloneIn;
        cloneThis = re;
        ++count;
    }

    count *= sign;
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


//--------------------------------------------------------------------------|
//|                                                                         |
//|                           ARITHMETIC OPERATORS                          |
//|                                                                         |
//--------------------------------------------------------------------------|

bool BigInt::operator ==(const BigInt& bigInt) const {
    return (this->_sign == bigInt._sign && this->_myVal == bigInt._myVal);
}

bool BigInt::operator <(const BigInt& bigInt) const {
    if (_sign * bigInt._sign < 0) {
        return _sign < 0;
    }
    if (_sign < 0)
        return _myVal > bigInt._myVal;
    return _myVal < bigInt._myVal;
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

//--------------------------------------------------------------------------|
//|                                                                         |
//|                                  METHODS                                |
//|                                                                         |
//--------------------------------------------------------------------------|

BigInt BigInt::negative() {
    BigInt x;
    x._myVal = this->_myVal;
    x._sign *= -1;
    return x;
}

BigInt BigInt::positive() {
    BigInt x;
    x._myVal = this->_myVal;
    x._sign = 1;
    return x;
}

string BigInt::toString() const {
    return (this->_sign == 1) ? this->_myVal : ("-" + this->_myVal);
}

bool BigInt::isZero() const {
    return (_myVal == "" || _myVal == "0");
}