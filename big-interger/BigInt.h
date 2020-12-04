#ifndef _BIG_INT_H
#define _BIG_INT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt {
private: 
    string _myVal;
    int _sign; //-1: negative, 1: positive
public: 

    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                               CONSTRUCTORS                              |
    //|                                                                         |
    //--------------------------------------------------------------------------|
    
    BigInt();
    BigInt(const BigInt& bigInt);
    BigInt(const string& str);

    //---------------------------------------------------------------------------

    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                               ASSIGNMENTS                               |
    //|                                                                         |
    //--------------------------------------------------------------------------|

    BigInt& operator =(const BigInt& bigInt);
    BigInt& operator =(const string& str);

    //---------------------------------------------------------------------------

    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                          MATHEMATICS OPERATORS                          |
    //|                                                                         |
    //--------------------------------------------------------------------------|
    
    string operator +(const BigInt& bigInt);
    string operator +(const string& bigInt);

    string operator -(const BigInt& bigInt);
    string operator -(const string& bigInt);

    string operator *(const BigInt& bigInt);
    string operator *(const string& bigInt);

    string operator /(const BigInt& bigInt);
    string operator /(const string& bigInt);

    string operator %(const BigInt& bigInt);
    string operator %(const string& bigInt);
    
    //---------------------------------------------------------------------------
    
    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                           ARITHMETIC OPERATORS                          |
    //|                                                                         |
    //--------------------------------------------------------------------------|

    bool operator ==(const BigInt& bigInt) const;
    bool operator <(const BigInt& bigInt) const;
    bool operator <=(const BigInt& bigInt) const;
    bool operator >(const BigInt& bigInt) const;
    bool operator >=(const BigInt& bigInt) const;

    //---------------------------------------------------------------------------

    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                                  METHODS                                |
    //|                                                                         |
    //--------------------------------------------------------------------------|

    BigInt negative();
    BigInt positive();

    string toString() const;
    bool isZero() const;

    //---------------------------------------------------------------------------
};

#endif