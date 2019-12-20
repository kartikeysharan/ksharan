//Kartikey Sharan
//1001659433
#ifndef CandyHouse_cpp
#define CandyHouse_cpp
class CandyHouse : public House
{
    public:
    CandyHouse(std::string, std::map<int, std::string>);
    ~CandyHouse();
    std::string ringDoorbell(std::ostringstream &);
};

#endif /* Header_h */
