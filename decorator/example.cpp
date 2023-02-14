#include <memory>
#include <iostream>
// 小時候玩 RO 的時候，總是會藉由穿戴不同裝備、吃特別的料理來撐攻速，然後就可以平A就能超快。
// 所以就用這個來當作範例好了，不過取名會隨便一點。
class Component
{
    public:
        virtual void operation(float& data) = 0;
};
// 攻擊速度
class APSD : public Component
{
    private:
        float apsd_;
    public:
        // APSD(float apsd) : apsd_(apsd) {}
        void operation(float& data) override
        {
            apsd_ = data;
            std::cout << "APSD = " << apsd_ << std::endl;
        }
        float getCurrentAPSD() { return apsd_; }
};
class Decorator : public Component
{
    private:
        std::shared_ptr<Component> component_;
    public:
        Decorator(std::shared_ptr<Component> component) : component_(component) {}
        void operation(float& data) override
        {
            component_->operation(data);
        }
};
// 死靈卡片：攻速+15％
class DippelganderCard : public Decorator
{
    public:
        DippelganderCard(std::shared_ptr<Component> component) : Decorator(component) {}
        void operation(float& data) override
        {
            data *= 1.15;
            Decorator::operation(data);
        }
};
// 攻速增加濃縮汁：攻速+10％（其實這個我不確定，但就先隨便寫，哈哈）
class EnrichCelermineJuice : public Decorator
{
    public:
        EnrichCelermineJuice(std::shared_ptr<Component> component) : Decorator(component) {}
        void operation(float& data) override
        {
            data *= 1.1;
            Decorator::operation(data);
        }
};

void clientTest()
{
    std::cout << "---- Before ----" << std::endl;
    float data = 100;
    auto apsd = std::make_shared<APSD>();
    apsd->operation(data);
    
    std::cout << "---- After ----" << std::endl;
    auto DC = std::make_shared<DippelganderCard>(apsd);
    auto ECJ = std::make_shared<EnrichCelermineJuice>(DC);
    ECJ->operation(data);
}

int main()
{
    clientTest();
    return 0;
}

