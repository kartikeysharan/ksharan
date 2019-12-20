// Created by Kartikey Sharan on 05/10/19.
//1001659433
#ifndef SNACK_MACHINE_H
#define SNACK_MACHINE_H
#include<iostream>
class SnackMachine
{
friend std::ostream& operator<<(std::ostream& output, SnackMachine snack);
friend std::string CreateSnackOutputLine(const SnackMachine& snack);
public:
    SnackMachine(std :: string name="New Machine",int cost=50, int change=500,int inventory=100) : machineName{name},SnackPrice{cost},changeLevel{change},inventoryLevel{inventory}
    {
        
    }
    bool buyASnack(int, std::string&, int&);
    std:: string getMachineName();
    int getInventoryLevel();
    int getMaxInventoryCapacity();
    bool incrementInventory(int);
    std :: string getChangeLevel();
    bool incrementChangeLevel(int);
    std :: string getMaxChangeCapacity();
    std :: string getSnackPrice();
    std :: string displayMoney(int);
    void setMachineName(std::string);
    void setSnackPrice(int);

private:
    std :: string machineName;
    int changeLevel;
    int maxChangeCapacity=5000;
    int SnackPrice;
    int inventoryLevel;
    int maxInventoryCapacity=100;
};

#endif
