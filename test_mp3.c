#include<stdio.h>
#include<string.h>
#include "mp3view.h"
#include "mp3edit.h"
#include "data.h"


int main(int argc,char *argv[])
{ 	  
 if(argc>1)
   {
   mp3Info info;
   if(check_operation(argv) == mp3_file)
   {
          printf("1  <<<<<<<<   YOU SELECTED VIEW  >>>>>>>>>>\n");
	  if(read_and_validate(argv,&info)==v_success)
	     {
		  if(view_mp3_reader(&info)==v_success)
		  {
			  printf("Extracting Album Art - Done\n");
		  }
		  else
		  {
			  printf("Extracting Album Art - Fail\n");
		  }
	     }
	  else
	  {
		  printf("Read and validate fail\n");
	  }

   }
   else if(check_operation(argv)==mp3_help)
   {
	   printf("Help menu for mp3 Tag Reader and Editor:\n");
           printf("\n");
	   printf("For viewing the tags-     ./mp3_tag_reader -v <filename.mp3>\n");
	   printf("\n");
	   printf("For editing the tags-     ./mp3_tag_reader -e <modifier>\n");
	   printf("\n");
	   printf("Modifier Function\n");
	   printf("-t	    Modify Title Tag\n");
	   printf("-T	    Modify Track Tag\n");
	   printf("-a	    Modify Artist Tag\n");
	   printf("-A	    Modify Album Tag\n");
	   printf("-y	    Modify year Tag\n");
	   printf("-c	    Modify comment Tag\n");
	   printf("-g	    Modify Genre Tag\n");
   }
   else if(check_operation(argv)==mp3_edit)
   {
    editinfo edit;
	 if(argc>=4)
	 {
	   printf("1. <<<<<<< YOU SELECTED EDITING >>>>>>>> \n");
	   if(read_and_validates(argv,&edit)==e_success)
	   {
		   if(edit_mp3_reader(argv,&edit)==e_success)
		   {
			   printf("Modification is done\n");
		   }
		   else
		   {
			   printf("ERROR : Modification \n");
		   }
	   }
	   else
		   printf("Read and validate is fail\n");
          }
           else
           {
              printf("ERROR: Incorrect format of command line arguments.\n");
              printf("Use ""./mp3_tag_reader -h"" for help\n");
   
            }
  }
      else
         {
             printf("ERROR: Incorrect format of command line arguments.\n");
              printf("Use ""./mp3_tag_reader -h"" for help\n");
          }
  
    }
}
Operation check_operation(char *argv[])
{
      if(argv[1]!=NULL)
      {
          if(strcmp(argv[1],"-v")==0)
	  return mp3_file;
	  else if(strcmp(argv[1],"-h")==0)
	  return mp3_help;
	  else if(strcmp(argv[1],"-e")==0)
          return mp3_edit;
	  else
	  return unsupport;
      }
}

