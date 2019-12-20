//
//  SnackMachine.cpp
//  1325 code 2
//
//  Created by Kartikey Sharan on 20/10/19.
//  Copyright © 2019 Kartikey Sharan. All rights reserved.

#include "SnackMachine.h"
#include <sstream>


std::string SnackMachine::getMachineName()
{
    return machineName;
}
bool SnackMachine::buyASnack(int payment, std :: string &change, int& status)
{

    if(payment!=SnackPrice)
    {
        if(payment>SnackPrice)
        {
            if (changeLevel>(payment-SnackPrice))
            {
                inventoryLevel-=1;
                changeLevel-=(payment-SnackPrice);
                changeLevel+=payment;
                change = displayMoney(payment-SnackPrice);
                status=4;
                return true;
            }
            else
            {
                status=1;
                return false;
            }
        }
        else
        {
            status=3;
            return false;
        }
    }
    else
    {
        inventoryLevel-=1;
        changeLevel+=payment;
        status=2;
        return true;
    }
 
}
int SnackMachine::getInventoryLevel()
{
    return inventoryLevel;
}
int SnackMachine::getMaxInventoryCapacity()
{
    return maxInventoryCapacity;
}
bool SnackMachine::incrementInventory(int amountToAdd)
{
    if(amountToAdd <= (maxInventoryCapacity-inventoryLevel))
    {
        inventoryLevel += amountToAdd;
        return true;
    }
    else
    {
        return false;
    }

}
std :: string SnackMachine::getChangeLevel()
{
    return displayMoney(changeLevel);
}
bool SnackMachine::incrementChangeLevel(int amountToAdd)
{
    if(amountToAdd<(maxChangeCapacity-changeLevel))
    {
        changeLevel += amountToAdd;
        return true;
    }
    else
    {
        return false;
    }
}
std :: string SnackMachine::getMaxChangeCapacity()
{
    return displayMoney(maxChangeCapacity);

}
std :: string SnackMachine::getSnackPrice()
{
    return displayMoney(SnackPrice);

}
std :: string SnackMachine::displayMoney(int amount)
{
    std :: string dollars{std :: to_string(amount / 100)};
    std :: string cents{std :: to_string(abs(amount % 100))};
    return "$" + dollars + "." + (cents.size() == 1 ? "0" : "") + cents;
}
void SnackMachine::setMachineName(std :: string newMachineName)
{
    machineName=newMachineName;
}
void SnackMachine::setSnackPrice(int newSnackPrice)
{
    SnackPrice=newSnackPrice;
}
std::ostream& operator<<(std::ostream& output, SnackMachine snack )
{
    
    output << "\n" << snack.machineName
           << "\n\nCurrent Inventory Level: "<<snack.inventoryLevel
           << "\nMax Inventory Capacity: "<<snack.maxInventoryCapacity
           << "\n\nCurrent Change Level: "<<snack.displayMoney(snack.changeLevel)
           << "\nMax Change Capacity: " <<snack.maxChangeCapacity
           << "\n\nCurrent Snack Price: " << snack.displayMoney(snack.SnackPrice);
    return output;
 }
std::string CreateSnackOutputLine(const SnackMachine& snack)
{
    std::ostringstream output;
    output<<snack.machineName<<'|'<<std::to_string(snack.SnackPrice)<<'|'<<std::to_string(snack.changeLevel)<<'|'<<std::to_string(snack.inventoryLevel)<<'\n';
    return output.str();
}
