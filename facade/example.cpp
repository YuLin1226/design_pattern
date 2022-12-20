#include <iostream>
#include <memory>
#include <string>
using namespace std;
class Manufacturer
{
    public:
        string makeShoes()
        {
            return "1 pair of shoes from manufacturer.";
        }
};
class Warehouse
{
    private:
        bool shoes_available_;
    public:
        Warehouse(bool shoes_available):shoes_available_(shoes_available) {}
        bool isShoesInStock() 
        { 
            return shoes_available_; 
        }
        string getShoes() 
        { 
            return "1 pair of shoes from warehouse."; 
        }
};
class ShoesShop
{
    private:
        shared_ptr<Warehouse> warehouse_;
        shared_ptr<Manufacturer> manufacturer_;
    public:
        ShoesShop(bool shoes_available)
        {
            warehouse_ = make_shared<Warehouse>(shoes_available);
            manufacturer_ = make_shared<Manufacturer>();
        }
        string buyShoes()
        {
            if(warehouse_->isShoesInStock())
                return warehouse_->getShoes();
            else
                return manufacturer_->makeShoes();
        }
};
void clientTest(bool shoes_available)
{
    auto shop = make_shared<ShoesShop>(shoes_available);
    cout << shop->buyShoes() << endl;
    // client only knows the shoesShop.
}
int main()
{
    bool shoes_available = false;
    clientTest(shoes_available);
    return 0;
}
