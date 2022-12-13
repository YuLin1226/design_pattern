#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
using namespace std;
class IMemento
{
    public:
        virtual string getMementoInfo() = 0;
        virtual string getDate() = 0;
        virtual string getState() = 0;
};
class ConcreteMemento : public IMemento
{
    private:
        string date_;
        string state_;
    public:
        ConcreteMemento(string state)
        {
            std::time_t now = std::time(0);
            this->date_ = std::ctime(&now);
            this->state_ = state;
        }
        string getMementoInfo()
        {
            return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
        }
        string getDate() override { return this->date_; }
        string getState() override { return this->state_; }
};
class Originator
{
    private:
        string state_;
    public:
        Originator(string fisrt_state) : state_(fisrt_state) {}
        shared_ptr<IMemento> saveMemento()
        {
            return make_shared<ConcreteMemento>(this->state_);
        }
        void restore(shared_ptr<IMemento> memento)
        {
            if(this->state_ != memento->getState())
                this->state_ = memento->getState();
            cout << "In state: " << this->state_ << endl;
        }
        void setState(string state)
        {
            this->state_ = state;
        }
        
};
class Caretaker
{
    private:
        vector<shared_ptr<IMemento>> mementos_;
        shared_ptr<Originator> originator_;
    public:
        Caretaker(shared_ptr<Originator> originator) : originator_(originator) {}
        void backUp()
        {
            cout << "Back Up..." << endl;
            mementos_.emplace_back(originator_->saveMemento());
        }
        void unDo()
        {
            if(mementos_.empty()) return;
            cout << "Undo..." << endl;
            originator_->restore(mementos_.back());
            mementos_.pop_back();
        }
        void showHistory()
        {
            for(auto& memento : mementos_)
            {
                cout << "[History] " <<memento->getMementoInfo() << endl;
            }
        }
        void doSomething(string type_anything)
        {
            originator_->setState(type_anything);
            cout << "doing something: " << type_anything << endl;; 
        }
};

void clientTest()
{
    auto originator = make_shared<Originator>("First state");
    auto caretaker = make_shared<Caretaker>(originator);
    caretaker->doSomething("1st thing.");
    caretaker->backUp();
    this_thread::sleep_for(chrono::seconds(3));

    caretaker->doSomething("2nd thing.");
    caretaker->backUp();

    this_thread::sleep_for(chrono::seconds(3));
    caretaker->doSomething("3rd thing.");
    caretaker->backUp();

    caretaker->doSomething("4th thing.");
    this_thread::sleep_for(chrono::seconds(3));

    caretaker->doSomething("5th thing.");
    caretaker->backUp();
    
    caretaker->showHistory();
    caretaker->unDo();
    caretaker->showHistory();
    caretaker->unDo();
    caretaker->unDo();
    caretaker->showHistory();
}

int main()
{
    clientTest();
    return 0;
}