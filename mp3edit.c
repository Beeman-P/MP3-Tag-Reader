#include<stdio.h>
#include<string.h>
#include "mp3edit.h"
#include "data.h"

Status read_and_validates(char *argv[],editinfo *edit)
{
	if(strstr(argv[2],".mp3")!=NULL)
	{
           edit->src_string = argv[2];
	}
	else
	{
		printf("ERROR: pass tha mp3 file");
		return e_failure;
	}
	if(strstr(argv[3],"-")!=NULL)
	{
           edit->mp3_modi = argv[3];
	}
	else
	{
		printf("ERROR : pass the modifier function\n");
		return e_failure;
	}
	if(argv[4]!=NULL)
	{
		edit->Title=argv[4];
		return e_success;
        }
}
Status open_files(editinfo *edit)
{
	edit->fptr_fedit=fopen(edit->src_string,"r+");
	if(edit->fptr_fedit != NULL)
	{
		return e_success;
	}
}
Status edit_the_mp3(char *argv[],editinfo *edit)
{
      	char arr[3];
	fread(arr,1,3,edit->fptr_fedit);
	arr[3]='\0';
	if(arr[0]=='I' && arr[1]=='D' && arr[2]=='3')
	{
		printf("Version ID3  : ");
	}
	else
	{
		printf("* * * Incorrect version * * *\n");
		return e_failure;
	}
        
	fread(arr,1,2,edit->fptr_fedit);
	arr[2]='\0';
	if(arr[0]==3 && arr[1]==0)
	{
	         printf(" 2.3 ");
		 return e_success;
	}
	else
	{
		printf("* * *"" pass correct version""* * *\n");
		return e_failure;
	}
}

Status content_of_tags(char*n,editinfo *edit)
{
	char arr[*n],str[*n];
	fread(arr,1,*n,edit->fptr_fedit);
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
Status lenth_of_string(editinfo *edit)
{
	fseek(edit->fptr_fedit,3,SEEK_CUR);
	char num;
	fread(&num,1,1,edit->fptr_fedit);
           fseek(edit->fptr_fedit,2,SEEK_CUR);
	   content_of_tags(&num,edit);
}

Status else_change_bits(editinfo *edit)
{
	long int a;
	char n;
	fseek(edit->fptr_fedit,3,SEEK_CUR);
        fread(&n,1,1,edit->fptr_fedit);
	a=n;
	fseek(edit->fptr_fedit,2,SEEK_CUR);
	fseek(edit->fptr_fedit,a,SEEK_CUR);
	return e_success;
}

Status change_the_tags(char *argv[],editinfo *edit)
{
	int l=strlen(argv[4]);
	char arg[l];
	strcpy(arg,argv[4]);
	fseek(edit->fptr_fedit,3,SEEK_CUR);
	char n;
	fread(&n,1,1,edit->fptr_fedit);
	fseek(edit->fptr_fedit,2,SEEK_CUR);
	int set = ftell(edit->fptr_fedit);
	char str[n],arr[n];
	fread(str,1,n,edit->fptr_fedit);
	 for(int i=0;arg[i]!='\0';i++)
	 {
		arr[i]=arg[i];
	 }
	 for(int i=l;i<=n;i++)
	 {
		 arr[i]='.';
	 }
	 for(int i=0;i<n;i++)
	 {
		 str[i]=str[i]&0 | arr[i];
	 }
	 fseek(edit->fptr_fedit,set,SEEK_SET);
	 fwrite(str,1,n,edit->fptr_fedit);
	 return e_success;
}

Status find_the_tag(char *argv[],editinfo *edit)
{
	long int s;
	fseek(edit->fptr_fedit,5,SEEK_CUR);
	while(1)
	{
		char arr[4];
		fread(arr,1,4,edit->fptr_fedit);
		if(strstr(arr,"TIT2")!=NULL)
		{
			if(strstr(edit->mp3_modi,"-t")!=NULL)
			{
                            if(change_the_tags(argv,edit)==e_success)
				    break;
			}
			else
			{
			   else_change_bits(edit);
			}
		}
		else if(strstr(arr,"TALB")!=NULL)
		{
			if(strstr(edit->mp3_modi,"-A")!=NULL)
			{
			  if(change_the_tags(argv,edit)==e_success)
			         break;
			}
			else
			{
			  else_change_bits(edit);
			}
		}
		else if(strstr(arr,"TYER")!=NULL)
		{
			if(strstr(edit->mp3_modi,"-y")!=NULL)
			{
                            if(change_the_tags(argv,edit)==e_success)
				    break;
			}
			else
			{
			   else_change_bits(edit);
			}
		}
	    else if(strstr(arr,"TCON")!=NULL)
		{
			if(strstr(edit->mp3_modi,"-g")!=NULL)
			{
                           if(change_the_tags(argv,edit)==e_success)
				   break;
			}
			else
			{
			   else_change_bits(edit);
			}
		}
	    else if(strstr(arr,"TPE1")!=NULL)
		{
			if(strstr(edit->mp3_modi,"-a")!=NULL)
			{
                            if(change_the_tags(argv,edit)==e_success)
				    break;
			}
			else
			{
		            else_change_bits(edit);
			}
		}
	    else if(strstr(arr,"COMM")!=NULL)
		{
			if(strstr(edit->mp3_modi,"-c")!=NULL)
	                {
                            if(change_the_tags(argv,edit)==e_success)
				    break;
			}
			else
			{
			  else_change_bits(edit);
			}
		}
		else
		{
			fseek(edit->fptr_fedit,3,SEEK_CUR);
			char num;
			fread(&num,1,1,edit->fptr_fedit);
			s=num;
			fseek(edit->fptr_fedit,2,SEEK_CUR);
			fseek(edit->fptr_fedit,s,SEEK_CUR);	

		}
	}
return e_success;
}

Status track_detail(editinfo *edit)
{
        fseek(edit->fptr_fedit,10,SEEK_SET);
         int count=0;
        while(count<=5)
        {
        char arr[4];
        fread(arr,1,4,edit->fptr_fedit);
        arr[4]='\0';
          if(strstr(arr,"TIT2")!=NULL)
            {
                printf("Title        : ");
                lenth_of_string(edit);
                  count++;
            }
          else if(strstr(arr,"TALB")!=NULL)
          {
                  printf("Album        : ");
                lenth_of_string(edit);
                  count++;
          }
          else if(strstr(arr,"TYER")!=NULL)
          {
                  printf("Year         : ");
                  lenth_of_string(edit);
                  count++;
          }
          else if(strstr(arr,"TCON")!=NULL)
          {
                  printf("Genre        : ");
                  lenth_of_string(edit);
                  count++;
          }
          else if(strstr(arr,"TPE1")!=NULL)
          {
                  printf("Artist       : ");
                  lenth_of_string(edit);
                  count++;
          }
          else if(strstr(arr,"COMM")!=NULL)
          {
                  printf("Comments     : ");
                  lenth_of_string(edit);
                  count++;
          }
          else
          {
                  fseek(edit->fptr_fedit,3,SEEK_CUR);
                  char n;
                  fread(&n,1,1,edit->fptr_fedit);
                  fseek(edit->fptr_fedit,2,SEEK_CUR);
                  fseek(edit->fptr_fedit,n,SEEK_CUR);
          }
        }
	return e_success;
}

Status edit_mp3_reader(char *argv[],editinfo *edit)
{
	if(open_files(edit)==e_success)
	{
            printf("MP3 Tag Reader and editor \n");
	    printf("-----------------------------\n");
	}
	else
	{
		printf("ERROR: Given file is empty");
	}
	if(edit_the_mp3(argv,edit)==e_success)
	{
                printf("\n");
	}
	else
	{
		printf("ERROR: Pass the 2.3 version\n");
	}
	if(find_the_tag(argv,edit)==e_success);
	{
		
		if(track_detail(edit)==e_success)
		{
			printf("Tag  ");
		}
		else
        	{
		printf("Error : Modifing  \n");
        	}
	}
	
	return e_success;

}
