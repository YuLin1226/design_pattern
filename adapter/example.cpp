// Example of normal adapter.
#include<iostream>
#include<memory>
using namespace std;
class MotorDriver
{
    public:
        virtual void rotateMotor(int command)
        {   
            cout << "Rotate motor with command : " << command << " RPS.\n";
        }
};
class Adapter : public MotorDriver
{
    private:

    public:
        void rotateMotor(int command) override
        {
            cout << "Rotate motor with command : " << command << " RPS.\n";
        }
};
int main()
{

    return 0;
}