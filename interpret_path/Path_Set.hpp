#include <string>
#include <map>
#include <vector>

class path_set
{
    private:
        std::map<std::string, int>          prifex_pathset;

    public:
        path_set();
        ~path_set();
        std::map<std::string, int>    get_pathset();
};

//1が= 2が^~ 3がなし

path_set::path_set()
{
    this->prifex_pathset["/sample/go"] = 3;
    this->prifex_pathset["/sample/bianchi/towl"] = 3;
    this->prifex_pathset["/sample/go/ambulance"] = 3;
    this->prifex_pathset["/"] = 3;
}

std::map<std::string, int>    path_set::get_pathset()
{
    return (this->prifex_pathset);
}

path_set::~path_set()
{

}