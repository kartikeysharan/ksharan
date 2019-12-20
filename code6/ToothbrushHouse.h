//Kartikey Sharan
//1001659433

#ifndef ToothbrushHouse_hpp
#define ToothbrushHouse_hpp
#include <stdio.h>
#include <iostream>
#include "House.h"
class ToothbrushHouse : public House
{
public:
    ToothbrushHouse(std::string, std::map<int, std::string>);
    ~ToothbrushHouse();
    std::string ringDoorbell(std::ostringstream &);
};

#endif /* Header_h */
