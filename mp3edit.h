#ifndef MP3EDIT_H
#define MP3EDIT_H

#include "data.h"
#define MAX_SIZE 4
#define SIZE 3

typedef struct _editinfo
{
	char *src_string;
	FILE *fptr_fedit;
        char *Title;
	char *mp3_modi;
	char *mp3_setpoint;
	FILE *New_file;

}editinfo;

Operation check_operation(char *argv[]);

Status read_and_validates(char *argv[],editinfo *edit);

Status edit_mp3_reader(char *argv[],editinfo *edit);

Status find_the_tag(char *argv[],editinfo *edit);

Status lenth_of_string(editinfo *edit);

Status content_of_tags(char* ,editinfo *edit);

Status change_the_tags(char *argv[],editinfo *edit);

Status else_change_bits(editinfo *edit);

Status track_detail(editinfo *edit);
#endif

