#include <iostream>
#include <memory>
#include <string>
using namespace std;
class Interface_Player
{
    public:
        virtual void playMusic(string song_name) =0;
};
class Earphone : public Interface_Player
{
    public:
        void playMusic(string song_name) override 
        {
            cout << "Using earphone to play \"" << song_name << "\"." << endl;
        }
};
class Speaker : public Interface_Player
{
    public:
        void playMusic(string song_name) override
        {
            cout << "Using speaker to play \"" << song_name << "\"." << endl;
        }
};
class MusicApp
{
    private:
        shared_ptr<Interface_Player> player_;
    public:
        MusicApp() {}
        void play(string song_name) 
        {
            if (player_ == nullptr)
                cout << "No device connected, fail to play." << endl;
            else
                player_->playMusic(song_name);
        }
        void connectDevice(shared_ptr<Interface_Player> player)
        {
            player_ = player;
        }
};
void clientTest(string song_name)
{
    auto app = make_shared<MusicApp>();
    auto device_speaker = make_shared<Speaker>();
    app->connectDevice(device_speaker);
    app->play(song_name);

    auto device_earphone = make_shared<Earphone>();
    app->connectDevice(device_earphone);
    app->play(song_name);
};
int main()
{
    clientTest("I Really Want to Stay at Your House");
    return 0;
}

