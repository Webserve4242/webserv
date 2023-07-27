#include <string>
#include <map>
#include <vector>

class path_set
{
    private:
        std::vector<std::string>    perfectpath_set;
        std::vector<std::string>    forwardconstent_set;
        std::vector<std::string>    noprefex_set;

    public:
        path_set();
        ~path_set();
        std::vector<std::string>    get_perfectpath();
        std::vector<std::string>    get_forwardconstent();
        std::vector<std::string>    get_noprefex();
};

//1が= 2が^~ 3がなし

path_set::path_set()
{
    this->perfectpath_set.push_back("/sample/go");
    this->perfectpath_set.push_back("/sampleple/index.html");
    this->forwardconstent_set.push_back("/sample/cinema/mayo");
    this->noprefex_set.push_back("/aba/ee");
    this->noprefex_set.push_back("/sample/go");
    this->noprefex_set.push_back("/sample/cinema/mayo/fanta");
    this->noprefex_set.push_back("/sample/go");
    this->noprefex_set.push_back("/sampleple/index.html");
    this->noprefex_set.push_back("/aaa/cc");
    this->noprefex_set.push_back("/aaa/dd");
    this->noprefex_set.push_back("/aaa");
}

std::vector<std::string>    path_set::get_perfectpath()
{
    return (this->perfectpath_set);
}

std::vector<std::string>    path_set::get_forwardconstent()
{
    return (this->forwardconstent_set);
}

std::vector<std::string>    path_set::get_noprefex()
{
    return (this->noprefex_set);
}

path_set::~path_set()
{

}