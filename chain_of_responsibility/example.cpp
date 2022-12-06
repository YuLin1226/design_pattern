#include <iostream>
#include <memory>
#include <string>
using namespace std;

class I_Handler
{
    public:
        virtual shared_ptr<I_Handler> setNextHandler(shared_ptr<I_Handler> handler) = 0;
        virtual std::string requestHandle(std::string request) = 0;
};
class BaseHandler : public I_Handler
{
    protected:
        shared_ptr<I_Handler> next_handler_;
    public:
        shared_ptr<I_Handler> setNextHandler(shared_ptr<I_Handler> handler) override
        {
            next_handler_ = handler;
            return handler;
        }
        std::string requestHandle(std::string request) override
        {
            return "Default handle";
        }
};

int main()
{
    return 0;
}
