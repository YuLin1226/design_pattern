// Example of normal adapter.
#include<iostream>
#include<memory>
#include<string>
using namespace std;
class KeyboardAndMouse
{
    public:
        virtual string outputSignal()
        {
            return "Output Signal Detected: Keyboard + Mouse";
        }
};
class PS4_ControllerSocket
{
    public:
        virtual string outputSignal()
        {
            return "Output Signal Detected: PS4 Controller";
        }
};
class Adapter : public PS4_ControllerSocket
{
    private:
        shared_ptr<KeyboardAndMouse> kb_and_mouse_;
    public:
        Adapter(shared_ptr<KeyboardAndMouse> kb_and_mouse)
        : kb_and_mouse_(kb_and_mouse) {}
        string outputSignal() override
        {
            return kb_and_mouse_->outputSignal();
        }
};
class PS4
{
    private:
        shared_ptr<PS4_ControllerSocket> controller_socket_;
    public:
        PS4(shared_ptr<PS4_ControllerSocket> controller_socket)
        : controller_socket_(controller_socket) {}
        void inputSignal()
        {
            auto signal = controller_socket_->outputSignal();
            cout << signal << endl;
        }
        void switchDevice(shared_ptr<PS4_ControllerSocket> controller_socket)
        {
            controller_socket_ = controller_socket;
        }
};
int main()
{
    auto ps4_controller = make_shared<PS4_ControllerSocket>();
    auto ps4 = make_shared<PS4>(ps4_controller);
    // Using ps4 controller
    ps4->inputSignal();
    // Using keyboard and mouse to simulate controller signal
    auto kb_mouse = make_shared<KeyboardAndMouse>();
    auto adapter = make_shared<Adapter>(kb_mouse);
    ps4->switchDevice(adapter);
    ps4->inputSignal();
    return 0;
}