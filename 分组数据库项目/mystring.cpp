#include <string>
#include <iostream>
#include "mystring.h"
using namespace std;

string ChineseStringSubstr(const string& str, int start, int end){
    /*
     * function:裁剪带中文的字符串.参数1：待裁剪字符串. 参数2:裁剪起始索引值. 参数3:裁剪结果索引值
     * 思路:从字符串头部往后寻找每个字符的idex,直到到达需要裁剪的位置,并对裁剪位置的索引值进行矫正,防止将中文字符从所占字节中间切断.
     */
    string hanzi = "汉";
    int hanziSize = hanzi.length(); //判断一个中文占多少字节
 
    //===矫正start的索引值(防止将中文的字节)
    if(start != 0){     //start==0时无需矫正
        int startIdex = 0;
        for (int i = 0; i < str.size(); i++) {
            if (startIdex >= start) {   //到达待矫正idex时,结束
                break;
            }
 
            if (str[i] & 0x80) {    //当前索引位置为中文
 
                startIdex += hanziSize;     //索引位置为中文时,索引前进hanziSize个字节
                i = i + hanziSize - 1;  //i含有i++,所以减去1
            }
            else {
                startIdex += 1; //索引位置为英文时,索引前进1个字节
            }
        }
        start = startIdex;
    }
 
    //===矫正end的索引值(防止将中文的字节)
    if(end != str.length()){    //end为字符串结尾时无需矫正
        int endIdex = 0;
        for (int i = 0; i < str.size(); i++) {
            if (endIdex >= end) {   //到达待矫正idex时,结束
                break;
            }
 
            if (str[i] & 0x80) {
                endIdex += hanziSize;
                i = i + hanziSize - 1;
 
            }
            else {
                if (endIdex >= end) {
                    break;
                }
                endIdex += 1;
            }
        }
        end = endIdex;
    }
 
    //===剪切字符串
    string str_caijian = "";
    if(start < 0 || end > str.length()|| end <= start){  //越界保护
        str_caijian = str;  //start或end有误,裁剪失败,直接截取整个字符串
        start = 0;
        end = str.length();
        // std::cout<<"idex矫正失败！"<<std::endl;
    }
    else{
        str_caijian = str.substr(start, end - start);
    }
 
    return str_caijian;
}

long long int to_int(string s)  
{  
    int i = 0,n = 0;  
    int point_index = s.find('.');  
    long long int result = 0; 
        for (i = 0; i <= s.size() - 1;i++)  
        {  
            if (s[i] >= '0'&&s[i] <= '9')  
            {  
                result= result * 10 + s[i] - 48;  
            }  
        }      
    return result;  
} 

string to_String(long long int val) {
    char buf[20];
	sprintf(buf, "%lld", val);
	return string(buf);
}

/*
 函数说明：对字符串中所有指定的子串进行替换
 参数：
string resource_str            //源字符串
string sub_str                //被替换子串
string new_str                //替换子串
返回值: string
 */
string subreplace(string resource_str, string sub_str, string new_str)
{
    string::size_type pos = 0;
    while((pos = resource_str.find(sub_str)) != string::npos)   //替换所有指定子串
    {
        resource_str.replace(pos, sub_str.length(), new_str);
		cout<<new_str<<endl;
		break;
    }
    return resource_str;
}
