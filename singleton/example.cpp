#include <iostream>
#include <vector>
#include <thread>
namespace Example
{
    class Singleton
    {
        // design singleton
        public:
            static Singleton& getInstance()
            {
                static Singleton unitInstance;
                return unitInstance;
            }
        public:
            Singleton(Singleton const&) =delete;
            void operator=(Singleton const&) =delete;
        private:
            Singleton(){};
    };
}
void singletonThreadTest()
{
    auto& ST = Example::Singleton::getInstance();
    std::cout << "Address: " << &ST << std::endl;
}
int main()
{
    std::vector<std::thread> threads;
    for(auto i = 0; i<10; i++)
    {
        // std::thread objects are move only 
        // i.e. we can not copy them, only move them.
        std::thread thread(singletonThreadTest);
        threads.emplace_back(std::move(thread));
    }
    for(auto it = threads.begin(); it != threads.end(); ++it)
    {
        if(it->joinable())
            it->join();
    }
    return 0;
}