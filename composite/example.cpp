#include <iostream>
#include <list>
#include <memory>
using namespace std;
class ProductComposite
{
    public:
        virtual float getPrice() = 0;
};
class PackedProduct : public ProductComposite
{
    private:
        list<shared_ptr<ProductComposite>> products_;
        float box_price_;
    public:
        PackedProduct(float box_price) : box_price_(box_price){}
        float getPrice() override
        {
            float price_sum = box_price_;
            for(auto& product : products_)
                price_sum += product->getPrice();
            return price_sum;
        }
        void addProduct(shared_ptr<ProductComposite> products)
        {
            products_.push_back(products);
        }
};
class UnpackedProduct : public ProductComposite
{
    private:
        float price_;
    public:
        UnpackedProduct(float price) : price_(price){};
        float getPrice() override
        {
            return price_;
        }
};
int main()
{   // price = 2 box + 3 product = 2 + 300 = 302.
    auto package = make_shared<PackedProduct>(1);
    auto unpacked_product_1 = make_shared<UnpackedProduct>(100);
    auto packed_product_1 = make_shared<PackedProduct>(1);
    auto unpacked_product_2 = make_shared<UnpackedProduct>(100);
    auto unpacked_product_3 = make_shared<UnpackedProduct>(100);
    packed_product_1->addProduct(unpacked_product_2);
    packed_product_1->addProduct(unpacked_product_3);
    package->addProduct(unpacked_product_1);
    package->addProduct(packed_product_1);
    printf("Package price: %f", package->getPrice());
    return 0;
}