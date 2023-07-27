#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "Path_Set.hpp"

//想定するケース
//リクエストが飛んできたとき、pathの部分だけ取り外せたとする
//そのpathにあわせてpathsetから適切なpathを返すとする
//この挙動をnginxに準拠させる

std::string check_fullmatch(std::map<std::string, int> set, std::string path)
{
    std::map<std::string, int>::iterator it = set.begin();
    while (it != set.end())
    {
        if (it->first == path)
            return ("FULL MATCH ! | " + it->first);
        it++;
    }
    return ("");
}

size_t  compare_twowords(std::string locationpath, std::string path)
{
    size_t  location_pathlen = locationpath.length();
    size_t  pos = 0;
    while (pos != location_pathlen)
    {
        if (locationpath[pos] != path[pos])
            break;
        pos++;
    }
    return (pos);
}

std::string check_longestmatchpath(std::map<std::string, int> set, std::string path)
{
    std::string ans = "";
    size_t  longestmatch_length = 0;
    size_t  tmp_len = 0;
    std::map<std::string, int>::iterator it = set.begin();
    while (it != set.end())
    {
        if ((it->first).length() < path.length())
        {
            tmp_len = compare_twowords((it->first), path);
            if ((it->first).length() == tmp_len && tmp_len >= longestmatch_length)
            {
                longestmatch_length = tmp_len;
                ans = (it->first);
            }
        }
        it++;
    }
    if (ans != "")
        return ("TEMP MATCH ! | " + ans);
    else
        return ("");
}

std::string interpret_path(std::map<std::string, int> set, std::string substring)
{
    std::string anser;
    //完全一致するものがあるか確認
    anser = check_fullmatch(set, substring);
    if (anser != "")
        return (anser);
    anser = check_longestmatchpath(set, substring);
    if (anser != "")
        return (anser);
    return ("NOT MATCH");
}

int main()
{
    std::string subjectpath = "/mogumogu";
    path_set    set;
    std::cout << interpret_path(set.get_pathset(), subjectpath) << std::endl;
}