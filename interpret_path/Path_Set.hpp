#include <string>
#include <map>
#include <vector>

class path_set
{
    private:
        std::vector<std::string>    pathset;//ここにlocationのパスをどんどん入れていく
    public:
        path_set();
        ~path_set();
        std::vector<std::string>    get_pathset();
};

path_set::path_set()
{
    //locationで設定されそうなパスをここに書いてね
    this->pathset.push_back("/sample/go");
    this->pathset.push_back("/sample");
}

std::vector<std::string>    path_set::get_pathset()
{
    return (this->pathset);
}

path_set::~path_set()
{

}