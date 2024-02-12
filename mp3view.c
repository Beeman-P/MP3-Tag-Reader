#include<stdio.h>
#include<string.h>
#include "mp3view.h"
#include "data.h"

Status read_and_validate(char *argv[],mp3Info *info)
{
	if(strstr(argv[2],".mp3")!=NULL)
	{
           info->src_file = argv[2];
	   return v_success;
	}
	else
	{
		printf("ERROR: pass tha mp3 file");
		return v_failure;
	}

}
Status open_file(mp3Info *info)
{
	info->fptr_fname=fopen(info->src_file,"r");
	if(info->fptr_fname != NULL)
	{ 
		return v_success;
	}
}
Status view_the_mp3(mp3Info *info)
{
      	char arr[3];
	fread(arr,1,3,info->fptr_fname);
	arr[3]='\0';
	if(arr[0]=='I' && arr[1]=='D' && arr[2]=='3')
	{
		printf("Version ID3  : ");
	}
	else
	{
		printf("* * * Incorrect version * * *\n");
		return v_failure;
	}
        
	fread(arr,1,2,info->fptr_fname);
	arr[2]='\0';
	if(arr[0]==3 && arr[1]==0)
	{
	         printf(" 2.3 ");
		 return v_success;
	}
	else
	{
		printf("* * *"" pass correct version""* * *\n");
		return v_failure;
	}
}
Status fetch_the_details(char*n,mp3Info *info)
{
	char arr[*n],str[*n];
	fread(arr,1,*n,info->fptr_fname);
	arr[*n]='\0';
	int j=0;
	for(int i=0;i<*n;i++)
	{
	 if((arr[i]>='A' && arr[i]<='Z')||(arr[i]>='a' && arr[i]<='z')||(arr[i]>='0' && arr[i]<='9')||arr[i]=='.'||arr[i]==' '||arr[i]=='_')
	 {
             str[j]=arr[i];
	     j++;
	 }
	}
	str[j]='\0';

	printf("%s \n",str);
}
Status reader_details(mp3Info *info)
{
	fseek(info->fptr_fname,3,SEEK_CUR);
	char num;
	fread(&num,1,1,info->fptr_fname);
           fseek(info->fptr_fname,2,SEEK_CUR);
	   fetch_the_details(&num,info);
}

Status track_details(mp3Info *info)
{
	fseek(info->fptr_fname,5,SEEK_CUR);
         int count=0;
	while(count<=5)
	{
	char arr[4];
	fread(arr,1,4,info->fptr_fname);
        arr[4]='\0';
	  if(strstr(arr,"TIT2")!=NULL)
            {
		strcpy(info->mp3_title,arr);
		printf("Title        : ");
	        reader_details(info);   
		  count++;
	    }
	  else if(strstr(arr,"TALB")!=NULL)
	  {
		  printf("Album        : ");
		 reader_details(info);
		  count++;
	  }
	  else if(strstr(arr,"TYER")!=NULL)
	  {
		  printf("Year         : ");
		  reader_details(info);
		  count++;
	  }
	  else if(strstr(arr,"TCON")!=NULL)
	  {
		  printf("Genre        : ");
		  reader_details(info);
		  count++;
	  }
	  else if(strstr(arr,"TPE1")!=NULL)
	  {
		  printf("Artist       : ");
		  reader_details(info);
		  count++;
	  }
	  else if(strstr(arr,"COMM")!=NULL)
	  {
		  printf("Comments     : ");
		  reader_details(info);
		  count++;
	  }
	  else
	  {
		  fseek(info->fptr_fname,3,SEEK_CUR);
		  char n;
		  fread(&n,1,1,info->fptr_fname);
		  fseek(info->fptr_fname,2,SEEK_CUR);
		  fseek(info->fptr_fname,n,SEEK_CUR);
		  continue;
          }
	}
}
Status view_mp3_reader(mp3Info *info)
{
	if(open_file(info)==v_success)
	{
	        printf("Mp3 Tag Reader & Editor:\n");
	        printf("--------------------------\n");
	}
	else
	{
		printf("ERROR: Given file is empty");
	}
	if(view_the_mp3(info)==v_success)
	{
                printf("\n");
	}
	else
	{
		printf("ERROR: Pass the 2.3 version\n");
	}
	if(track_details(info)==v_success);
	{

         }
	return v_success;
}

