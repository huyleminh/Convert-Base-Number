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
        MAX = 32
    };
    InputHandler() {};
public:
    //Prevent clone InputHandler
    InputHandler(InputHandler& other) = delete;
    void operator = (const InputHandler& ) = delete;

    //Singleton get instance method
    static InputHandler* getHandler();

    ~InputHandler() {
        delete _instance;
    }

    void removeAllZeroHead(string& inputStr);
    bool validateNumber(const string& inputStr);

    static void fixedBits(string& inputStr, const char& mode);
};

#endif