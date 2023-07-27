#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "Path_Set.hpp"

typedef struct pair_s{
    std::string location;
    int         rank;
}pair_t;

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

pair_t check_longestmatchpath(\
std::vector<std::string> forwardconstent_set, \
std::vector<std::string> noprefex_set, \
std::string path)
{
    std::string                         ans = "";
    size_t                              longestmatch_length = 0;
    size_t                              tmp_len = 0;
    pair_t                              return_val;
    std::vector<std::string>::iterator  it = forwardconstent_set.begin();

    while (it != forwardconstent_set.end())
    {
        if ((*it).length() < path.length())
        {
            tmp_len = compare_twowords((*it), path);
            if ((*it).length() == tmp_len && tmp_len >= longestmatch_length)
            {
                longestmatch_length = tmp_len;
                return_val.location = *it;
                return_val.rank = 2;
            }
        }
        it++;
    }
    std::vector<std::string>::iterator  it = noprefex_set.begin();

    while (it != noprefex_set.end())
    {
        if ((*it).length() < path.length())
        {
            tmp_len = compare_twowords((*it), path);
            if ((*it).length() == tmp_len && tmp_len >= longestmatch_length)
            {
                longestmatch_length = tmp_len;
                return_val.location = *it;
                return_val.rank = 1;
            }
        }
        it++;
    }
    return (return_val);
}

std::string interpret_path(std::vector<std::string> perfectmatch_set, \
std::vector<std::string> forwardconstent_set, \
std::vector<std::string> noprefex_set, std::string substring)
{
    pair_t      anser_struct;
    std::string anser;
    // 完全一致するものがあるか確認
    anser = check_fullmatch(perfectmatch_set, substring);
    // 完全一致の場合は内部リダイレクトがあればそれを評価する
    // return (eval_perfectmatch())
    if (anser != "")
        return (anser);
    anser_struct = check_longestmatchpath(forwardconstent_set, noprefex_set, substring);
    if (anser_struct != "")
        return (anser);
    return ("NOT MATCH");
}

int main()
{
    std::string subjectpath = "/sample/go/further";
    path_set    set;
    std::cout << interpret_path(set.get_perfectpath(), set.get_forwardconstent(), set.get_noprefex(), subjectpath) << std::endl;
}