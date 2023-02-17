#include <iostream>
#include <memory>
#include <vector>

class Strategy
{
    public:
        virtual void doAlgorithm(int data) = 0;
};

class DirectAddingMethod : public Strategy
{
    public:
        void doAlgorithm(int data) override
        {
            std::cout << "By directly adding method," << std::endl;
            int result = 0;
            for(int i=1; i<=data; i++)
            {
                std::cout << i;
                result += i;
                if(i == data) break;
                else std::cout<<" + ";
            }
            std::cout <<" = " << result << std::endl;
        }
};

class FormulaMethod : public Strategy
{
    public:
        void doAlgorithm(int data) override
        {
            int result = data * (data + 1) / 2 ;
            std::cout << "By formula method, " << std::endl;
            std::cout << data << " * ( "<< data << " + 1 ) / 2 = " << result <<std::endl;
        }
};

class Calculator
{
    private:
        std::shared_ptr<Strategy> strategy_;
    public:
        Calculator() {}
        void setCalculationMethod(std::shared_ptr<Strategy> strategy)
        { strategy_ = std::move(strategy); }
        void sumFromOneToN(int n)
        {
            if(!strategy_)
                std::cout << "[Error] No method specified." << std::endl;
            else
                strategy_->doAlgorithm(n);
        }
};

void clientTest(int n)
{
    auto calculator = std::make_shared<Calculator>();
    std::cout <<">>> First Method: " << std::endl;
    auto method1 = std::make_shared<DirectAddingMethod>();
    calculator->setCalculationMethod(method1);
    calculator->sumFromOneToN(n);
    std::cout <<">>> Second Method: " << std::endl;
    auto method2 = std::make_shared<FormulaMethod>();
    calculator->setCalculationMethod(method2);
    calculator->sumFromOneToN(n);
}
int main()
{
    clientTest(7);
    return 0;
}