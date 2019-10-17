#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<regex>
#include<iostream>
#include<sstream>
#include<cstdio>
#include"file.h"
//#include<list>
using namespace std;
#ifdef _WIN32
#include<windows.h>


bool file_exists(const char *name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

void change_file_suffix(char * lpPath,char *src,char *des)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind, lpPath);
	strcat(szFind, "*.*");
	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
		return;
	while (TRUE)
	{
		//目录
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
			{
				char szFile[256] = { 0 };
				strcpy(szFile, lpPath);
				strcat(szFile, "");
				strcat(szFile, FindFileData.cFileName);
				strcat(szFile, "\\");
				printf("dir:%s \n", FindFileData.cFileName);
				change_file_suffix(szFile, src, des);
			}
		}
		else
		{//文件
			printf("   %s  \n", FindFileData.cFileName);
			string newname = FindFileData.cFileName;
			
			newname=newname.replace(newname.find_last_of(".")+1,strlen(src),des);
			string oldfile = string(lpPath) + FindFileData.cFileName;
			newname = string(lpPath) + newname;
			printf("change to----%s \n",newname.c_str());
			//char tofile[512] = "@\"";
			//strcat(tofile, lpPath);
			//strcat(FindFileData.cFileName, "\";\n");
			//strcat(tofile, FindFileData.cFileName);
			//fputs(tofile, fp);
			rename(oldfile.c_str(), newname.c_str());
		}
		if (!FindNextFile(hFind, &FindFileData))
			break;
	}
	FindClose(hFind);
}

void traversal_dir(char * lpPath)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind, lpPath);
	strcat(szFind, "*.*");
	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
		return;
	while (TRUE)
	{
		//目录
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
			{
				char szFile[256] = { 0 };
				strcpy(szFile, lpPath);
				strcat(szFile, "");
				strcat(szFile, FindFileData.cFileName);
				strcat(szFile, "\\");
				printf("dir:%s \n",FindFileData.cFileName);
				traversal_dir(szFile);
			}
		}
		else
		{//文件
			printf("   %s  \n",FindFileData.cFileName);
			//char tofile[512] = "@\"";
			//strcat(tofile, lpPath);
			//strcat(FindFileData.cFileName, "\";\n");
			//strcat(tofile, FindFileData.cFileName);
			//fputs(tofile, fp);
		}
		if (!FindNextFile(hFind, &FindFileData))
			break;
	}
	FindClose(hFind);
}


//将一个目录里的文件合并到一个文件中
void merge_file(char * lpPath,FILE* outFile)
{
	char szFind[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	strcpy(szFind, lpPath);
	strcat(szFind, "*.*");
	HANDLE hFind = ::FindFirstFile(szFind, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
		return;
	while (TRUE)
	{
		//目录
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
			{
				char szFile[256] = { 0 };
				strcpy(szFile, lpPath);
				strcat(szFile, "");
				strcat(szFile, FindFileData.cFileName);
				strcat(szFile, "\\");
				printf("dir:%s \n", FindFileData.cFileName);
				merge_file(szFile, outFile);
			}
		}
		else
		{//文件
			
			char szFile[256] = { 0 };
			strcpy(szFile, lpPath);
			strcat(szFile, "");
			strcat(szFile, FindFileData.cFileName);
			printf("   %s  \n", szFile);
			char buf[1024] = { 0 };
			FILE* sfp = fopen(szFile, "r");
			while (!feof(sfp))
			{
				size_t rlen = fread(buf, sizeof(char), sizeof(buf), sfp);
				size_t wlen = fwrite(buf, sizeof(char), rlen, outFile);
				memset(buf, 0, sizeof(buf));
			}
			fclose(sfp);
		}
		if (!FindNextFile(hFind, &FindFileData))
			break;
	}
	FindClose(hFind);
}
#endif // WIN32

void replace_file_string(const char *filepath)
{
	FILE *file = fopen(filepath,"a+");
	FILE *fileout = fopen("D:\\output.sql", "a");
	char sbuf[1024] = { 0 }; 
	//regex pattern("^alter table (\\w+) add column (\\w+) (\\w+) ([\\w\\s]+)");
	const regex pattern("^alter table ([\\w`]+) ADD COLUMN ([\\w`]+) (\\w+) ([\\w\\s']+)", regex::icase);

	smatch result;
	int linenum = 1;
	
	while (fgets(sbuf, sizeof(sbuf), file) != NULL)
	{
		string line = sbuf;
		bool match = regex_search(line, result, pattern);
		stringstream ss;
		if (match)
		{
			ss << "call mysql_sp_add_column(";
			for (size_t i = 1; i < result.size(); ++i)
			{
				
				if (i != result.size() - 1)
					ss << "\""<<result[i] << "\",";
				else
					ss << "\"" << result[i]<<"\"";
			}
			ss << ")";
			cout << linenum << " " << sbuf << endl;
			
			cout << ss.str() << endl;
			fputs(ss.str().c_str(),fileout);
		}
		
		
		//printf("%s", sbuf);
		memset(sbuf, 0, sizeof(sbuf));
		++linenum;
	}
	fclose(file);
	fclose(fileout);
}

long GetFileSize(std::string filename)
{
	struct stat stat_buf;
	int rc = stat(filename.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

bool file_exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

int main673422()
{
	/*测试合并文件的
	FILE *fp = fopen("F:\\stpfull1.sql", "a");
	merge_file("F:\\stp2\\Documents\\D2.Designs\\数据库脚本\\", fp);
	fclose(fp);*/
	change_file_suffix("D:/politics/马克思主义基本原理强化（视频） 最新动态 讲师：阮晔 课时：18.0/","mp4","mp3");

	//replace_file_string("D:\\stpfull.sql");
	system("pause");
	return 0;
}

