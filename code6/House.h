// House class header file

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
#include <thread>

#ifndef _House_hpp
#define _House_hpp

class House
{
	
	public :
		House(std::string, std::map<int, std::string>);
		virtual std::string ringDoorbell(std::ostringstream &)=0;
        virtual ~House();
    
	protected :
		std::string houseName;
		std::mutex door;
		std::map<int,std::string>CandyRankingMap;
};


#endif	
