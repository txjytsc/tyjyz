#ifndef __mystring_h__
#define __mystring_h__

#include <string>
using namespace std;

string ChineseStringSubstr(const string& str, int start, int end);
long long int to_int(string s);
string to_String(long long int val);
string subreplace(string resource_str, string sub_str, string new_str);

#endif