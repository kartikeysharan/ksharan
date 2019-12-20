//Kartikey Sharan
//UTA ID:1001659433
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
House::House(std::string nameofhouse, std::map<int, std::string>mapname)
:houseName(nameofhouse),CandyRankingMap(mapname)
{
    
}
House::~House()
{
    std::cout<<"House"<<std::endl;
}
