#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <string>
using namespace std;

class InputHandler {
protected: 
    static InputHandler* _instance;
    enum BASE_BITS {
        MIN = 8,
        AVE = 16,
        MAX = 32,
        S_MAX = 64
    };
    InputHandler() {};
public:

    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                           SETUP BASE HANDLER                            |
    //|                                                                         |
    //--------------------------------------------------------------------------|

    //Prevent clone InputHandler
    InputHandler(InputHandler& other) = delete;
    void operator = (const InputHandler& ) = delete;

    //Singleton get instance method
    static InputHandler* getHandler();

    ~InputHandler() {
        delete _instance;
    }

    //---------------------------------------------------------------------------

    //--------------------------------------------------------------------------|
    //|                                                                         |
    //|                             PUBLIC METHODS                              |
    //|                                                                         |
    //--------------------------------------------------------------------------|

    bool start();
    bool inputNumber(string& str, string& base, string& fixed);
    void removeAllZeroHead(string& inputStr);
    bool validateNumber(const string& inputStr, const int& base);

    static void fixedBits(string& inputStr, const int& mode);
};

#endif