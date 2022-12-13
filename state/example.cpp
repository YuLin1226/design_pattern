#include <iostream>
#include <memory>
using namespace std;
// Forward Declaration
class Context;
class InterfaceState;
class CommonState;
class StateA;
class StateB;
// Implementation
class InterfaceState
{
    protected:
        shared_ptr<Context> context_;
    public:
        virtual void handle(int& num) = 0;
        void setContext(shared_ptr<Context> context)
        {
            context_ = context;
        }
};

class Context : public enable_shared_from_this<Context>
{
    private:
        shared_ptr<InterfaceState> state_;
    public:
        void setNewState(shared_ptr<InterfaceState> state)
        {
            state_ = state;
            state_->setContext(this->shared_from_this());
        }
        void triggerStateAction(int& num)
        {
            state_->handle(num);
            cout << "Num: " << num << endl;
        }
};

class CommonState : public InterfaceState
{
    public:
        virtual void handle(int& num) override
        {
            cout << "This is a common operation." << endl;
            num -= 5;
        }
};

class StateA : public CommonState
{
    public:
        void handle(int& num) override;
};

class StateB : public CommonState
{
    public:
        void handle(int& num) override;
};

void StateA::handle(int& num)
{
    while(num > 10)
    CommonState::handle(num);
    cout << "This is the operation in A." << endl;
    num += 10;
    auto state_b = make_shared<StateB>();
    context_->setNewState(state_b);
};

void StateB::handle(int& num)
{
    if(num > 100)
        CommonState::handle(num);
    cout << "This is the operation in B." << endl;
    num *= -1;
    auto state_a = make_shared<StateA>();
    context_->setNewState(state_a);
};

void clientTest(int num)
{
    auto init_state = make_shared<StateA>();
    auto context = make_shared<Context>();
    // cuz we use shared_from_this() that can only be called after construction,
    // we have to call setNewState() outside the constructor.
    context->setNewState(init_state);
    // Do actions.
    context->triggerStateAction(num);
    context->triggerStateAction(num);
    context->triggerStateAction(num);
    context->triggerStateAction(num);
}

int main()
{
    int num = 50;
    clientTest(num);
    return 0;
}
