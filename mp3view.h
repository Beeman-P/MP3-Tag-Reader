#ifndef MP3VIEW_H
#define MP3VIEW_H

#include "data.h"
#define MAX_SIZE 4
#define SIZE 3

typedef struct _mp3Info
{
	char *src_file;
	FILE *fptr_fname;
	char *dest_file;
	char file[MAX_SIZE];
	char mp3_view[SIZE];
	char mp3_title[4];


}mp3Info;

Operation check_operation(char *argv[]);

Status read_and_validate(char *argv[],mp3Info *info);

Status view_mp3_reader(mp3Info *info);

Status open_file(mp3Info *info);

Status view_the_mp3(mp3Info *info);

Status track_details(mp3Info *info);

Status reader_details(mp3Info *info);

Status fetch_the_details(char*,mp3Info *info);
#endif
