#ifndef __CIO_H__
#define __CIO_H__
#include<stdio.h>
extern int readline(char *buf, FILE *fp);
extern void print_text(FILE *fp);
extern int copy_file(const char *src, const char *des);
extern int file_size(FILE *fp);
#endif


