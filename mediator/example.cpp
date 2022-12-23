#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class BaseComponent;
class Mediator
{
    public:
        virtual void notify(shared_ptr<BaseComponent> sender, string event) const = 0;
};
class BaseComponent : public enable_shared_from_this<BaseComponent>
{
    protected:
        shared_ptr<Mediator> mediator_;
    public:
        BaseComponent(shared_ptr<Mediator> mediator = nullptr) : mediator_(mediator) {}
        void setMediator(shared_ptr<Mediator> mediator) 
        {
            mediator_ = mediator;
        }
};
class Airplane : public BaseComponent
{
    public:
        void prepareLanding()
        {   
            cout << "Airplane " << this->shared_from_this() << " asks landing permission." << endl;
            mediator_->notify(this->shared_from_this(), "landing");
        }
        void doLanding()
        {
            cout << "Airplane " << this->shared_from_this() << " is landing." << endl;
        }
        void doHovering()
        {
            cout << "Airplane " << this->shared_from_this() << " is hovering." << endl;
        }
};
class AirTrafficControlTower : public BaseComponent
{
    private:
        bool isRunwayOccupied_;
    public:
        AirTrafficControlTower() : isRunwayOccupied_(false) {}
        bool getLandingPermission()
        {
            return !isRunwayOccupied_;
        }
        void setRunwayOccupied()
        {
            isRunwayOccupied_ = true;
        }
};
class ConcreteMediator : public Mediator
{
    private:
        vector<shared_ptr<Airplane>> airplanes_;
        shared_ptr<AirTrafficControlTower> tower_;

    public:
        void addAirplane(shared_ptr<Airplane> airplane)
        {
            if(airplane != nullptr)
                airplanes_.emplace_back(airplane);
        }

        void setATCTower(shared_ptr<AirTrafficControlTower> tower)
        {
            tower_ = tower;
        }

        void notify(shared_ptr<BaseComponent> sender, string event) const override
        {
            if(event == "landing")
            {
                if(!tower_->getLandingPermission())
                {
                    cout << "Permission denied." << endl;
                    auto airplane_it = find(airplanes_.begin(), airplanes_.end(), sender);
                    (*airplane_it)->doHovering();
                    return;
                }
                cout << "Permission accepted." << endl;
                for(auto& airplane : airplanes_)
                    if(airplane != sender)
                        airplane->doHovering();
                    else
                        airplane->doLanding();
                tower_->setRunwayOccupied();
            }
        }
};

void clientTest()
{
    auto m = make_shared<ConcreteMediator>();
    auto ap1 = make_shared<Airplane>();
    ap1->setMediator(m);
    auto ap2 = make_shared<Airplane>();
    ap2->setMediator(m);
    auto ap3 = make_shared<Airplane>();
    ap3->setMediator(m);
    auto tower = make_shared<AirTrafficControlTower>();
    tower->setMediator(m);
    m->addAirplane(ap1);
    m->addAirplane(ap2);
    m->addAirplane(ap3);
    m->setATCTower(tower);

    ap1->prepareLanding();
    ap2->prepareLanding();
}
int main()
{
    clientTest();
    return 0;
}