#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "Path_Set.hpp"

//想定するケース
//リクエストが飛んできたとき、pathの部分だけ取り外せたとする
//そのpathにあわせてpathsetから適切なpathを返すとする
//この挙動をnginxに準拠させる

std::string check_fullmatch(std::vector<std::string> set, std::string path)
{
    std::vector<std::string>::iterator it = set.begin();
    while (it != set.end())
    {
        if (*it == path)
            return ("FULL MATCH ! | " + *it);
        it++;
    }
    return ("");
}

std::string interpret_path(std::vector<std::string> set, std::string substring)
{
    std::string anser;
    //完全一致するものがあるか確認
    anser = check_fullmatch(set, substring);
    if (anser != "")
        return (anser);
    return ("NOT MATCH");
}

int main()
{
    std::string subjectpath = "/aaa";
    path_set set;
    std::cout << interpret_path(set.get_pathset(), subjectpath) << std::endl;
}