#include "../headers/utils.h"
#include <iostream>

using namespace std;

vector<string> Utils::split(string str, string token)
{
    vector<string> result;
    while (str.size())
    {
        int index = str.find(token);
        if (index != string::npos)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0)
                result.push_back(str);
        }
        else
        {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}