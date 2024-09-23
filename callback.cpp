/* 
== TESTING CALLBACK PASSING ==
== Testing the callback function passing from class A to class B
== The lambda function call back created in A and pass to B
== B will use it whenever neccessary 
*/

#include <iostream>
#include <functional>
#include <memory>

class B {
public:
    using OnSendCallback = std::function<void(int val)>;
    B(OnSendCallback cb) : mSender(cb) {}

    void triggerSendingMessage(int val) {
        mSender(val);
    }

private:
    OnSendCallback mSender;
};


class A {
public:
    A () {
        b = std::make_shared<B>([] (int val) {
            std::cout << "Value is: " << val << std::endl;
        });
    }

    void triggerBSendingMessage(int val) {
        std::cout << "Trigerring B sending message..." << std::endl;
        b->triggerSendingMessage(val);
    }
private:
    std::shared_ptr<B> b;
};
