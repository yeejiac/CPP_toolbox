#ifndef GAMEBASICRULE_H_
#define GAMEBASICRULE_H_

#include <iostream>
#include <string>
#include <vector>

class GameBase
{
public:
    GameBase();
    ~GameBase();
    void setgamecheck(int);
    bool getgamecheck();
    void shuffle(std::vector <int>&);
    std::string getCardName(int);
    int getCardVal(std::vector<std::pair<int, std::string>>&);
    virtual void startStick(int, int);
    virtual int gettotal() = 0;
    enum Mark{Heart=3, Spade=4, Club = 2, Diamond = 1};
    const std::string Mark[4] = {"Diamond", "Club", "Heart", "Spade"};
	const std::string Point[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
private:
};

#endif