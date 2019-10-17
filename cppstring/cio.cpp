#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cio.h"

int readline(char *buf, FILE *fp)
{
	int i = 0;
	int c = 0;
	for (; (c = fgetc(fp)) != EOF; i++)
	{
		if (c == '\n')
			break;
		buf[i] = c;
	}
	buf[i] = '\0';
	return i;
}

void print_text(FILE *fp)
{
	char buf[1024];
	while (fgets(buf,1024,fp) != NULL)
	{
		printf("%s", buf);
		memset(buf, 0, sizeof(buf));
	}
}

int copy_file(const char *src, const char *des)
{
	if (src == NULL || des == NULL)
		return -1;
	unsigned long total = 0;
	FILE *sfp = fopen(src,"rb");
	FILE *dfp = fopen(des, "wb");
	char buf[1024] = { 0 };
	while (!feof(sfp))
	{
		size_t rlen=fread(buf,sizeof(char),sizeof(buf),sfp);
		size_t wlen = fwrite(buf, sizeof(char), rlen, dfp);
		total += rlen;
		//printf("%d\n", total);
	}
	fclose(sfp);
	fclose(dfp);
	return total;
}

int file_size(FILE *fp)
{
	int cur=ftell(fp);
	fseek(fp, 0, SEEK_END);
	long num = ftell(fp);
	fseek(fp, cur, SEEK_SET);
	return num;
}

int main2()
{
	printf("%d\n",copy_file("D:\\BaiduYunDownload\\The.Dark.Knight.2008.BluRay.1080p\\òùòðÏÀÇ°´«2.The.Dark.Knight.2008.BluRay.1080p.x264.rmvb", "D:\\444.rmvb"));
	FILE *fp=fopen("C:\\Users\\admin\\Desktop\\New Text Document (3).txt", "r");
	printf("%d\n", file_size(fp));
	char buf[100];
	printf("%d,%s\n", readline(buf, fp), buf);
	print_text(fp);
	fclose(fp);
	system("pause");
	return 0;
}