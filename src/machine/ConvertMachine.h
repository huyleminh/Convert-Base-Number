#ifndef _CONVERT_MACHINE_
#define _CONVERT_MACHINE_

#include <string>
using namespace std;


class ConvertMachine {
protected: 
    static ConvertMachine* _instance;
    ConvertMachine() {};  
  
public:
    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                           SETUP BASE MACHINE                            |
    //|                                                                         |
    //--------------------------------------------------------------------------|

    //Prevent clone new instance
    ConvertMachine(ConvertMachine& other) = delete;
    void operator = (const ConvertMachine& ) = delete;

    ~ConvertMachine() {
        delete _instance;
    }

    //Create a machine to convert number
    static ConvertMachine* createConvertMachine();

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
    void convertStandardNumber(const string& str, const int& base);


    //--------------------------------------------------------------|
    //|                       REPRESENT NUMBER                      |
    //--------------------------------------------------------------|

    /**
     * @params: fixed (fixed 8 or 16 or 32 or 64 bit)
    */
    void representNumber(const string& str, const int& base, const int& fixed);

    //--------------------------------------------------------------


    /**
     * @return: a string after convert base
     * @params: from (base of str), to (base str will be)
    */
    string convertNumber(const string& str, const int& from, const int& to);



    //---------------------------------------------------------------------------

    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                             PRIVATE METHODS                             |
    //|                                                                         |
    //--------------------------------------------------------------------------|
private:

    string convertToDecimal(const string& str, const int& from);
    string fromDecimalToHex(const string& str);
    string fromHexToBinary(const string& str);
    string fromBinaryToHex(const string& str);

    /**
     * @return: one's complement of a binary string
     * @params: str (binary string)
    */
    string convertOneComplement(const string& str);

    /**
     * @return: two's complement of a binary string
     * @params: str (binary string)
    */
    string convertTwoComplement(const string& str);

    //---------------------------------------------------------------


    //--------------------------------------------------------------|
    //|                      CONVERT BASE NUMBER                    |
    //--------------------------------------------------------------|
    
    void convertStandardDecimal(const string& str);
    void convertStandardHexa(const string& str);
    void convertStandardBinary(const string& str);

    //---------------------------------------------------------------


    //--------------------------------------------------------------|
    //|                       REPRESENT NUMBER                      |
    //--------------------------------------------------------------|

    void representDecimal(const string& str, const int& fixed);
    void representHexa(const string& str, const int& fixed);
    void representBinary(const string& str, const int& fixed);

    //---------------------------------------------------------------

    /**
     * @return: string displayed with padding (seperated 4 bits)
     * example: 11001001 => 1100 1001
    */
    string padding(const string& str);

    //---------------------------------------------------------------------------

};

#endif