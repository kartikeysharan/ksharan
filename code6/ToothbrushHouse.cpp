//Kartikey Sharan
//1001659433
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
#include "House.h"
#include "ToothbrushHouse.h"
#include "CandyHouse.h"
ToothbrushHouse::ToothbrushHouse(std::string nameofhouse, std::map<int, std::string>mapname)
:House(nameofhouse,mapname)
{
    
}
ToothbrushHouse::~ToothbrushHouse()
{
    std::cout<<"ToothbrushHouse"<<std::endl;
    
}
std::string ToothbrushHouse::ringDoorbell(std::ostringstream& stream)
{
    int key;
    door.lock();
    stream<<'-';
    std::this_thread::sleep_for(std::chrono::seconds(3));
    key=rand()%CandyRankingMap.size()+1;
    door.unlock();
    return "Toothbrush";
}
