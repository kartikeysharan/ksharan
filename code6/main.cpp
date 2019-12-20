//Kartikey Sharan
//UTA ID: 1001659433

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "TrickOrTreater.h"
#include "House.h"
#include "ToothbrushHouse.h"
#include "CandyHouse.h"

using namespace std;

void get_command_line_params(int argc, char* argv[], string &TOTnames, string &housefile, string &candyranking)
{
    if(argc != 4)
    {
        throw invalid_argument("\nMissing command line parameters – - Usage : Three input^filenames\n");
    }
    else
    {
        TOTnames = argv[1];
        housefile = argv[2];
        candyranking = argv[3];
    }
}
int main(int argc, char * argv[])
{
    string TOTnames;
    string housefile;
    string candyranking;
    string candyline;
    string nameofhouse;
    string TOTname;
    int key2;
    char *char_array;
    char temp[132];
    char *key;
    int random;
    srand((int)time(0));
    vector<House*>housename;
    vector<TrickOrTreater>TrickOrTreaters;
    try
    {
        get_command_line_params(argc, argv, TOTnames, housefile, candyranking);
    }
    catch(invalid_argument& say)
    {
        cerr<<"\nExiting Program-- \n"<<say.what();
        exit(0);
    };
    ifstream TOT(TOTnames);
    ifstream HOUSES(housefile);
    ifstream CANDY(candyranking);
    map<int, string>mymap;
    if(CANDY.is_open())
    {
        while(getline(CANDY,candyline))
        {
            strcpy(temp,candyline.c_str());
            char_array=strtok(temp,"|");
            if(char_array!=NULL)
            {
                key=strtok(NULL, "|");
                key2=atoi(key);
            }
            mymap.insert(make_pair(key2, char_array));
        }
    }
    ostringstream head;
    head<<left<<setw(11)<<" ";
    if(HOUSES.is_open())
    {
        while(getline(HOUSES,nameofhouse))
        {
            int random=rand()%2;
               if(random==1)
               {
                   House *temp=new CandyHouse{nameofhouse,mymap};
                   housename.push_back(temp);
               }
               else
               {
                   House*temp=new ToothbrushHouse{nameofhouse,mymap};
                   housename.push_back(temp);
               }
            head<<left<<setw(11)<<nameofhouse;
        }
    }
   if(TOT.is_open())
    {
        while (getline(TOT,TOTname))
        {
            TrickOrTreaters.push_back(TrickOrTreater{TOTname, housename});
        }
    }
    
    TOT.close();
    HOUSES.close();
    CANDY.close();
    for(auto &it:TrickOrTreaters)
    {
        it.startThread();
    }
   
    while(TrickOrTreater::ImDone!=TrickOrTreaters.size())
    {
        for(int j=0;j<34;j++)
        {
            cout<<"\n";
        }
        cout<<head.str();
        for(auto &it:TrickOrTreaters)
        {
            cout<<'\n'<<it.getPath()<<it.getName();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    
    for(auto &it:TrickOrTreaters)
    {
        it.joinThread();
    }
    cout<<"\n";
    for(auto &it:TrickOrTreaters)
    {
        cout<<it;
    }
    for(auto &it: housename)
    {
        delete it;
    }
    return 0;
}
