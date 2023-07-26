#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "Path_Set.hpp"

//想定するケース
//リクエストが飛んできたとき、pathの部分だけ取り外せたとする
//そのpathにあわせてpathsetから適切なpathを返すとする
//この挙動をnginxに準拠させる

std::string interpret_path(std::vector<std::string> set, std::string substring)
{
    //完全一致するものがあるか確認
    
}

int main()
{
    std::string subjectpath = "/sample";
    path_set set;
    std::cout << interpret_path(set.get_pathset(), subjectpath) << std::endl;
}