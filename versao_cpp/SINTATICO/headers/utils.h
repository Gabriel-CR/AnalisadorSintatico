#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

using namespace std;

class Utils
{
public:
    static vector<string> split(string str, string token);
    static string join(vector<string> v, string token);
};

#endif // UTILS_H