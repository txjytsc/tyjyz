#include <string>
#include <iostream>
#include "mystring.h"
using namespace std;

string ChineseStringSubstr(const string& str, int start, int end){
    /*
     * function:�ü������ĵ��ַ���.����1�����ü��ַ���. ����2:�ü���ʼ����ֵ. ����3:�ü��������ֵ
     * ˼·:���ַ���ͷ������Ѱ��ÿ���ַ���idex,ֱ��������Ҫ�ü���λ��,���Բü�λ�õ�����ֵ���н���,��ֹ�������ַ�����ռ�ֽ��м��ж�.
     */
    string hanzi = "��";
    int hanziSize = hanzi.length(); //�ж�һ������ռ�����ֽ�
 
    //===����start������ֵ(��ֹ�����ĵ��ֽ�)
    if(start != 0){     //start==0ʱ�������
        int startIdex = 0;
        for (int i = 0; i < str.size(); i++) {
            if (startIdex >= start) {   //���������idexʱ,����
                break;
            }
 
            if (str[i] & 0x80) {    //��ǰ����λ��Ϊ����
 
                startIdex += hanziSize;     //����λ��Ϊ����ʱ,����ǰ��hanziSize���ֽ�
                i = i + hanziSize - 1;  //i����i++,���Լ�ȥ1
            }
            else {
                startIdex += 1; //����λ��ΪӢ��ʱ,����ǰ��1���ֽ�
            }
        }
        start = startIdex;
    }
 
    //===����end������ֵ(��ֹ�����ĵ��ֽ�)
    if(end != str.length()){    //endΪ�ַ�����βʱ�������
        int endIdex = 0;
        for (int i = 0; i < str.size(); i++) {
            if (endIdex >= end) {   //���������idexʱ,����
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
 
    //===�����ַ���
    string str_caijian = "";
    if(start < 0 || end > str.length()|| end <= start){  //Խ�籣��
        str_caijian = str;  //start��end����,�ü�ʧ��,ֱ�ӽ�ȡ�����ַ���
        start = 0;
        end = str.length();
        // std::cout<<"idex����ʧ�ܣ�"<<std::endl;
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
 ����˵�������ַ���������ָ�����Ӵ������滻
 ������
string resource_str            //Դ�ַ���
string sub_str                //���滻�Ӵ�
string new_str                //�滻�Ӵ�
����ֵ: string
 */
string subreplace(string resource_str, string sub_str, string new_str)
{
    string::size_type pos = 0;
    while((pos = resource_str.find(sub_str)) != string::npos)   //�滻����ָ���Ӵ�
    {
        resource_str.replace(pos, sub_str.length(), new_str);
		cout<<new_str<<endl;
		break;
    }
    return resource_str;
}
