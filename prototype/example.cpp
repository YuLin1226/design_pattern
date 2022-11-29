#include <iostream>
#include <string>
#include <unordered_map>
#include <thread>
#include <memory>
using namespace std;

enum TeaType{BLACK_TEA, GREEN_TEA, MILK_TEA};
class PrototypeTea
{
    protected:
        string prototype_name_;
        int sugar_;
        int ice_;
        bool is_adjusted_;
    public:
        PrototypeTea(){}
        PrototypeTea(string prototype_name)
        : prototype_name_(prototype_name), sugar_(100), ice_(100), is_adjusted_(false){}
        virtual ~PrototypeTea(){}
        virtual unique_ptr<PrototypeTea> clone() const = 0;
        virtual void PrintRecipe() 
        {
            cout << "Recipe (" << prototype_name_ << "): " << (is_adjusted_ ? "new":"old");
            cout << "\n - Sugar: " << sugar_;
            cout << "\n - Ice: " << ice_ << endl;
        }
        virtual void adjustRecipe(int sugar, int ice)
        {
            sugar_ = sugar;
            ice_ = ice;
            is_adjusted_ = true;
        }
};
class BlackTea : public PrototypeTea
{
    public:
        BlackTea(string tea_type) : PrototypeTea(tea_type)
        {   // sleep 5s to represent that this initialization is time-consuming.
            this_thread::sleep_for(chrono::milliseconds(5000));
        }
        unique_ptr<PrototypeTea> clone() const override 
        { 
            return make_unique<BlackTea>(*this);
        }
};
class GreenTea : public PrototypeTea
{
    public:
        GreenTea(string tea_type) : PrototypeTea(tea_type)
        {   // sleep 5s to represent that this initialization is time-consuming.
            this_thread::sleep_for(chrono::milliseconds(5000));
        }
        unique_ptr<PrototypeTea> clone() const override 
        { 
            return make_unique<GreenTea>(*this); 
        }
};
class MilkTea : public PrototypeTea
{
    public:
        MilkTea(string tea_type) : PrototypeTea(tea_type)
        {   // sleep 5s to represent that this initialization is time-consuming.
            this_thread::sleep_for(chrono::milliseconds(5000));
        }
        unique_ptr<PrototypeTea> clone() const override 
        { 
            return make_unique<MilkTea>(*this); 
        }
};
class TeaFactory 
{
    private:
        std::unordered_map<TeaType, unique_ptr<PrototypeTea>, std::hash<int>> prototypes_;
    public:
        TeaFactory() 
        {   // this initialization blocks 15s (5s for each).
            prototypes_[TeaType::BLACK_TEA] = make_unique<BlackTea>("Ceylon Uva");
            prototypes_[TeaType::GREEN_TEA] = make_unique<GreenTea>("TAZO");
            prototypes_[TeaType::MILK_TEA] = make_unique<MilkTea>("BubbleTea");
        }
    unique_ptr<PrototypeTea> cloneTea(TeaType type) 
    {
        return prototypes_[type]->clone();
    }
};
int main()
{
    auto tea_factory = make_unique<TeaFactory>();
    {   // Adjust the recipe of black_tea_1 and check the difference.
        auto black_tea_1 = tea_factory->cloneTea(TeaType::BLACK_TEA);
        auto black_tea_2 = tea_factory->cloneTea(TeaType::BLACK_TEA);
        black_tea_1->adjustRecipe(50, 100);
        black_tea_1->PrintRecipe();
        black_tea_2->PrintRecipe();
    }
    auto green_tea_1 = tea_factory->cloneTea(TeaType::GREEN_TEA);
    auto milk_tea_1  = tea_factory->cloneTea(TeaType::MILK_TEA);
    return 0;
}