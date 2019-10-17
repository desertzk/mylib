#define _CRT_SECURE_NO_WARNINGS

#ifndef __cplusplus
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<ctype.h>
#else
#include<iostream>
#include<vector>
#include<list>
#include<string>
using namespace std;
#endif


#ifdef __cplusplus
vector<string> split(string src,string regexstr)
{
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = src.find(regexstr, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(src.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		tokens.push_back(src.substr(start));
	}
	return tokens;
}

vector<string> splitwithrexstr(string src, string regexstr)
{
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = src.find(regexstr, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(src.substr(start, end + strlen(regexstr.c_str()) - start));
		}
		start = end + strlen(regexstr.c_str());
	}
	if (start <= strlen(src.c_str()) && end != start) {
		tokens.push_back(src.substr(start));
	}
	return tokens;
}

#else

vector<char *>* splite(char *str, char* fstr,char ***arrstr,int *strnum)//省内存法  堆版本
{
	char* copystr = (char *)malloc(strlen(str) + 1);
	memset(copystr,0, sizeof(copystr));
	strcpy(copystr,str);//最后还原
	char* i = str;//前指针
	//char **tmparr;
	vector<char *> *tmparr = new vector<char *>();
	char* chnext = 0;
	for (; chnext = strstr(i, fstr);)
	{
		//if (chnext == 0)//第一个为找到的
		//	continue;
		int size = chnext-i + 1;//string  end \0 so +1
		char *tmpstr =(char *) calloc(size, sizeof(char));
		
		memcpy_s(tmpstr, size - 1, i, size - 1);
		tmparr->push_back(tmpstr);
		//int chnext = strstr(str, fstr);
		i = chnext + strlen(fstr);
	}
	int size=str + strlen(str) - i + 1;//last
	char *tmpstr = (char *)calloc(size, sizeof(char));

	memcpy_s(tmpstr, size - 1, i, size - 1);
	tmparr->push_back(tmpstr);
	str = copystr;
	return tmparr;
	
}
#endif // c_plus_plus
/*
静态区的字符串也会报错
*/
char * substring(char *str, int beginindex, int endindex,char *ret)
{
	strcpy(ret, str);
	char *start = ret;
	char *end = start + strlen(str);
	start += beginindex;
	end -= endindex;
	*end = '\0';
	return start;
}

//not finish
char * substring_h(char *str, int beginindex, int endindex)  //堆版本
{
	int len = strlen(str) + 1 - endindex - beginindex;
	char *start = (char *)malloc(len);

	char *end = start + strlen(str);
	start += beginindex;
	end -= endindex;
	*end = '\0';
	return start;
}



//不能传静态区的 常量字符串
char * trim(char *str)
{
	char *start = str;
	char *end = start + strlen(str);
	while (*start == ' ')
		start++;
	str = start;
	while (*end == ' ')
		end--;
	*end = '\0';
	return str;
}

//不能传静态区字符串,用户自己要防止溢出问题
char *replace(char *str, char *oldstr, char *newstr)
{
	if (NULL == str || NULL == oldstr || NULL == newstr)
		return str;
	if (!strcmp(oldstr, newstr))
	{
		return str;
	}
	int len = strlen(str);
	char * tmp = strstr(str, oldstr);
	if (NULL == tmp)
	{
		return NULL;
	}
	int oldlen=strlen(oldstr);
	int newlen = strlen(newstr);
	if (oldlen == newlen)
	{
		while (oldlen--)
			*tmp++ = *newstr++;
	}
	else
	{
		//char after[len + 1];
		char *behind = (char *)malloc(len+1);//这里可能会多分配点内存可以优化
		strcpy(behind, tmp + strlen(oldstr));

		*tmp = '\0';
		strcat(str, newstr);
		strcpy(str + strlen(str), behind);
		free(behind);
	}
	return str;
}

char *replaceall(char *str, char *oldstr, char *newstr)
{
	if (!strcmp(oldstr, newstr))
	{
		return str;
	}
	char *tmp = str;
	char *first = strstr(tmp, oldstr);
	do{
		
		replace(tmp, oldstr, newstr);
		//
		/**/if (first)
		{
			tmp = first + strlen(newstr);//从第一次修改后的那个指针开始
			first = NULL;
		}
		else{
			tmp += strlen(newstr);
		}
		

	} while (tmp = strstr(tmp, oldstr));
	return str;
}

#ifdef __cplusplus
int start_with(string str, string start)
{
	if (str.find(start) == 0)
	{
		return 1;
	}
	else
		return 0;
}
#else
int start_with(char *str, char *start)
{
	char *equalstr = strstr(str, start);
	if (!equalstr)
		return 0;
	if (strcmp(str, equalstr))//not equal
		return 0;
	else
		return 1;
}
#endif

//可能隐含越界问题
int end_with(char *str, char *end)
{
	char *tmp = str;
	char *last = str + strlen(str)-strlen(end);

	char *equalstr = strstr(str, end);
	if (!equalstr)
		return 0;
	if (strcmp(last, end))//not equal
		return 0;
	else
		return 1;
}

char * to_upper_case(char *str, int start, int offset)
{
	char *tmp = str;
	char *sstr = tmp + start;
	//char *estr=tmp
	for (; *sstr&&offset--;)
	{
		*sstr = toupper(*sstr);
		sstr++;
	}
		
	return str;

}

char * to_lower_case(char *str, int start, int offset)
{
	char *tmp = str;
	char *sstr = tmp + start;
	//char *estr=tmp
	for (; *sstr&&offset--;)
	{
		*sstr = tolower(*sstr);
		sstr++;
	}
	return str;
}

//int ret_ascii(char * str,int index)
//{
//	
//}

//提取内部所有数字
int extract_num(char *str,char *outdigit)
{
	char *ps;
	int i = 0;
	ps = str;
	while (*ps != '\0')
	{
		if (*ps >= '0'&&*ps <= '9')
		{
			outdigit[i] = *ps;//充入digit中
			i++;
		}
		ps++;//ps后移
	}
	outdigit[i] = '\0';//在字符串最后填一个'\0'作为结束符
	return 0;
}


string hsGetCol(const char* ASourceStr, int AColNo, char AChar)
{
	int curCol = 0;
	char const *beginStr = ASourceStr;
	char const *endStr = ASourceStr;
	while (beginStr)
	{
		endStr = strchr(beginStr, AChar);
		if (endStr)
		{
			if (curCol == AColNo)
			{
				break;
			}
			else
			{
				curCol++;
				endStr++;
				beginStr = endStr;
			}
		}
		else
		{
			if (curCol == AColNo)
			{
				endStr = ASourceStr + strlen(ASourceStr);
			}
			else
			{
				beginStr = NULL;
			}
			break;
		}

	}

	string retStr;
	if (beginStr)
	{
		for (char const *p = beginStr; p < endStr; ++p)
		{
			retStr.push_back(*p);
		}
	}
	return retStr;
}

int main()
{
	string smsg = "{\"message\":{\"head\":{\"user\":\"\",\"timestamp\":\"\",\"guid\":\"{648034D3 - C191 - 4FBC - 97EE - F7B6E711CA03}\",\"type\":99,\"functionid\":990002},\"body\":{\"fields\":[\"log_info\",\"log_level\"],\"data\":[[\"zk genius\",\"0\"]]}}}\r\n{\"message\":{\"head\":{\"user\":\"\", \"timestamp\" : \"\", \"guid\" : \"{4B5D3027-17CA-4006-A5ED-027B2E9FE9DD}\", \"type\" : 99, \"functionid\" : 990002}, \"body\" : {\"fields\":[\"log_info\", \"log_level\"], \"data\" : [";
	splitwithrexstr(smsg, "\r\n");
	char uptest[50] = "aaaaaa12bdfdsf";
	printf("%d\n", end_with(uptest,"df"));
	printf("%c\n", toupper(uptest[3]));
	printf("%s\n", to_upper_case(uptest, 1, 12));
	printf("%s\n", to_lower_case(uptest, 1, 12));
	char teststr[150] = "1112123311444111115551116661122222222221";
	printf("start_with:%d\n", start_with(teststr, "666"));
	printf("%s\n", replaceall(teststr, "2", "22225562"));
	char tstr[50] = { 0 };
	strcpy(tstr, "      134254234   df     ");
	printf("%s\n", trim(tstr));
	printf("replace:%s\n", replace(tstr, "34", "9999999"));
	strcpy(tstr, "1214321445");
	printf("strstr:%s\n", strstr(tstr, "14"));
	printf(tstr);
	printf("\n");
	char *sstr = "123456789";
	char mystr[50] = { 0 };
	printf("%s\n", substring(sstr, 1, 0, mystr));
	char *str = ",,dga,sfga,sfda,,,111,";
	//test splite
#ifdef __cplusplus
	vector<string> v = split(str, ",");
	auto it = v.begin();
	while (it != v.end())
	{
		printf("%s\n", it->c_str());
		++it;
	}/**/
#else
	vector<char *>* v = splite(str, ",", NULL, NULL);
	vector<char *>::iterator it = v->begin();
	while (it != v->end())
	{
		printf("%s\n", *it++);
	}/**/
#endif
	//int count = v.size();
//	char **codes = (char **)new (char *)[sizeof(mystr)];
	//const char *codes[count] = { 0 };
	char direction[64] = { 0 };
	char test1str[8] = "1";
	char c2 = '1';
	strcat(direction, test1str);
	strcat(direction,"#");
	strcat(direction,&c2);
	printf("%s", direction);
	system("pause");
	return 0;
}