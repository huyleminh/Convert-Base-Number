#ifndef _CONVERT_MACHINE_
#define _CONVERT_MACHINE_

#include <string>
using namespace std;


class ConvertMachine {
protected: 
    static ConvertMachine* _instance;
    ConvertMachine() {};    
public:
    //Prevent clone new instance
    ConvertMachine(ConvertMachine& other) = delete;
    void operator = (const ConvertMachine& ) = delete;

    ~ConvertMachine() {
        delete _instance;
    }

    //Create a machine to convert number
    static ConvertMachine* createConvertMachine();

    //Convert between base x and base y
    //@params: from (base of str), to (base str will be)
    string convertNumber(const string& str, const int& from, const int& to);

};

#endif