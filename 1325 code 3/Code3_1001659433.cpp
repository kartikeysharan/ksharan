//  Created by Kartikey Sharan Student ID: 1001659433
#include <iostream>
#include<fstream>
#include<vector>
#include<stdexcept>
#include <stdio.h>
#include "SnackMachine.h"
#include "SnackLib.h"
using namespace std;
enum
{
    inventory_fail,
    change_fail,
    payment_pass,
    payment_fail,
    snack_ok
};

void get_command_line_params(int argc, char* argv[], string &inputfile, string &outputfile)
{
    if(argc != 3)
    {
        throw invalid_argument("\nMissing command line parameters – - Usage : input^filename output^filename\n");
    }
    else
    {
        inputfile = argv[1];
        outputfile = argv[2];
    }
}
int displaymenu()
{
    int choice=-1;
    while(choice<0 || choice>6)
    {
    cout<<"\n\n0. Walk away\n1. Buy a Snack\n2. Restock Machine\n3. Add Change\n4. Display Machine Info\n5. Update machine name\n6. Update snack Price"<<endl;
    cout<<"Choice: ";
    cin>> choice;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(50,'\n');
        cout<<"Input must be a numeric. Please reenter ";
        cin>>choice;
    }
    while(choice<0 || choice>6)
    {
        cout<<"You must enter a value between 0 and 6. Reenter your choice ";
        cin>>choice;
    }
        if(choice==0)
        {
            cout<<"\n\nAre you sure you are not really hungry and need a snack?\n";
        }
    }
    return choice;
}
int main(int argc , char *argv[])
{
    string inputfile;
    string outputfile;
    try
    {
        get_command_line_params(argc,argv,inputfile,outputfile);
    }
    catch(invalid_argument& say)
    {
        cerr<<"\nExiting Program-- \n"<<say.what();
        exit(0);
    }
    ifstream SnackInputFile(inputfile);
    ofstream SnackOutputFile(outputfile,ios::out);
    
    int mychoice=1;
    int payment=0;
    string change="";
    int restocknum=0;
    int restockchange=0;
    int status=0;
    string newMachineName="";
    int newSnackPrice=0;
    int menu;
    string SnackMachineLine;
    vector<SnackMachine> SetOfSnackMachines;
    vector<string> ConstructorValues(4);
    SnackMachine MySnackMachine{"CSE 1325 Snack Machine", 50, 500, 100};
    if(SnackInputFile.is_open())
    {
        while(getline(SnackInputFile,SnackMachineLine))
        {
            if(ParseSnackLine(SnackMachineLine,ConstructorValues))
            {
                SnackMachine temp{ConstructorValues.at(0),stoi(ConstructorValues.at(1)),stoi(ConstructorValues.at(2)),stoi(ConstructorValues.at(3))};
                SetOfSnackMachines.push_back(temp);
            }
        }
    }
    else
    {
        cout<<"\nUnable to open file"<<endl;
        exit(0);
    }
    do
    {
        cout<<"\nPick a Snack Machine\n"<<endl;
        cout<<"\n0.Exit\n";
        for(int b=0; b<(SetOfSnackMachines.size());b++)
        {
            cout<<b+1<<" "<<SetOfSnackMachines.at(b).getMachineName()<<endl;
        }
        cout<<(SetOfSnackMachines.size()+1)<<" "<< "Add a new machine"<<endl;
        cout<<"\nEnter Choice ";
        cin>>menu;
        menu=menu-1;
        if(menu==-1)
        {
            for(int b=0; b<(SetOfSnackMachines.size());b++)
            {
                SnackOutputFile<<CreateSnackOutputLine(SetOfSnackMachines.at(b));
            }
            return 0;
        }
        else
        {
            if(menu==SetOfSnackMachines.size())
            {
                SnackMachine hard;
                SetOfSnackMachines.push_back(hard);
                cout<<"\nnew machine added\n"<<endl;
            }
            else
            {
               cout<<"\n\n";
               cout<<SetOfSnackMachines.at(menu).getMachineName()<<endl;
               mychoice =  displaymenu();
               while(mychoice!=0)
               {
                   switch (mychoice)
                   {
                       case 0:
                           cout<<"\nAre you sure you aren't really hungry and need a snack?\n";
                           break;
                       case 1:
                            {
                             if(SetOfSnackMachines.at(menu).getInventoryLevel()>0)
                            {
                                cout<<"\nA Snack costs "<<SetOfSnackMachines.at(menu).getSnackPrice()<<endl;
                                cout<<"\n\n";
                                cout<<"Insert payment (in cents) ";
                                cin>>payment;
                                cout<<"\n\n";
                                while(cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore();
                                    cout<<"input must be a numeric. Please reenter ";
                                    cin>>payment;
                                }
                                if(SetOfSnackMachines.at(menu).buyASnack(payment,change,status))
                                {
                                    switch(status)
                                    {
                                        case snack_ok:
                                        {
                                            cout<<"Here's your Snack and here's your change of ";
                                            cout<<change;
                                            cout<<"\n\n";
                                            break;
                                        }
                                        case payment_pass:
                                        {
                                            cout<<"Thank you for exact change\nHere is your Snack\n\n";
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    switch(status)
                                    {
                                        case inventory_fail:
                                        {
                                            cout<<"out of snacks  - call 1800RESTOCK to request a restock...returning your payment\n\n";
                                            break;
                                        }
                                        case change_fail:
                                        {
                                            cout<<"Unable to give change at this time...returning your payment\n\n";
                                            break;
                                        }
                                        case payment_fail:
                                        {
                                            cout<<"Insufficient Payment...returning your payment\n\n";
                                            break;
                                        }
                                    }
                                }
                          }
                          else
                          {
                            cout<<"out of snacks  - call 1800RESTOCK to request a restock...returning your payment\n\n";
                          }
                                break;
                            }
                       case 2:
                           cout<<"How much product are you adding to the machine? ";
                           cout<<"\n\n";
                           cin>>restocknum;
                           if(SetOfSnackMachines.at(menu).incrementInventory(restocknum))
                           {
                               cout<<"Your machine has been restocked"<<endl;
                               cout<<"\n\n";
                           }
                           else
                           {
                               cout<<"You have exceeded your machine's max capacity"<<endl;
                               cout<<"\n\n";
                           }
                           cout<<"The Inventory level now is "<<SetOfSnackMachines.at(menu).getInventoryLevel()<<endl;
                           cout<<"\n\n";
                           break;
                       case 3:
                           cout<<"How much change are you adding to the machine? ";
                           cout<<"\n\n";
                           cin>>restockchange;
                           if(SetOfSnackMachines.at(menu).incrementChangeLevel(restockchange))
                           {
                               cout<<"Your change has beeen updated"<<endl;
                               cout<<"\n\n";
                           }
                           else
                           {
                               cout<<"Not enough space"<<endl;
                           }
                           cout<<"The Change level now is "<<SetOfSnackMachines.at(menu).getChangeLevel()<<endl;
                           cout<<"\n\n";
                           break;
                       case 4:
                           cout<<SetOfSnackMachines.at(menu);
                           break;
                       case 5:
                           cout<<"\nEnter a new machine name\n";
                           cin.ignore(50,'\n');
                           getline(cin,newMachineName);
                           SetOfSnackMachines.at(menu).setMachineName(newMachineName);
                           cout<<"\nMachine Name has been updated\n";
                           break;
                       case 6:
                           cout<<"\nEnter a new snack price\n";
                           cin>>newSnackPrice;
                           SetOfSnackMachines.at(menu).setSnackPrice(newSnackPrice);
                           cout<<"\nSnack price has been updated\n";
                           break;
                       default:
                           cout<<"Invalid menu choice. Please choose again\n\n";
                           break;
                   }
                   mychoice =  displaymenu();
                   
               }
            }
            
        }
    }while(menu!=-1);
    
    SnackInputFile.close();
    SnackOutputFile.close();
    return 0;
}
