//Kartikey Sharan
//UTA ID 1001659433
#include "House.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cstring>
#include <chrono>
#include <mutex>
#include "TrickOrTreater.h"

int TrickOrTreater::ImDone=0;

TrickOrTreater::TrickOrTreater(std::string TOTnames, std::vector<House*>listhouses)
:name(TOTnames),ListOfHouses(listhouses)
{
    
}
std::string TrickOrTreater::getName()
{
    return name;
}
void TrickOrTreater::startThread()
{
   TOTThreadPtr = new std::thread(&TrickOrTreater::GoTrickOrTreating, this);
}
void TrickOrTreater::joinThread()
{
    this->TOTThreadPtr->join();
    delete this->TOTThreadPtr;
}
void TrickOrTreater::GoTrickOrTreating()
{
    int speed;
    std::string way;
    for(auto &it: ListOfHouses)
    {
        speed=rand()%500+1;
        Walk(speed);
        way=it->ringDoorbell(path);
        Bucket[way]++;
    }
    TrickOrTreater::ImDone++;
}
void TrickOrTreater::Walk(int speed)
{
    int i;
    for(i=0;i<10;i++)
    {
        path<<'.';
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
    }
}
std::string TrickOrTreater::getPath()
{
    return path.str();
}
std::ostream& operator<<(std::ostream& output, TrickOrTreater& TOTObj)
{
    output<<TOTObj.getName()<<"'s - ";
    for(auto &it:TOTObj.Bucket)
    {
        output<<it.first<<" "<<it.second<<" , ";
    }
    output<<"\n";
    return output;
}
