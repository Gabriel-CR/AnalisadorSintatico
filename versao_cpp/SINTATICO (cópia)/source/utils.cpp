#include "../headers/utils.h"
#include <iostream>

using namespace std;

vector<string> Utils::split(string str, string token)
{
    vector<string> result;
    while (str.size())
    {
        int index = str.find(token);
        if (index != (int)string::npos)
        {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if ((int)str.size() == 0)
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

string Utils::join(vector<string> v, string token)
{
    string result = "";
    for (int i = 0; i < (int)v.size(); i++)
    {
        result += v[i];
        if (i != (int)v.size() - 1)
            result += token;
    }
    return result;
}