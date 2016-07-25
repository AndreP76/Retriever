#include "Retriever.h"
/* NOTES
    argv[0] is the program name
END OF NOTES*/

int main(int argc, char *argv[]){
    if(argc >=3){
        char *FromDirectoryPath = realpath(argv[1],NULL);
        char *FileName = argv[2];//Hoping the compiler optimizes
        short unsigned int cp = (argc == 4 && strcmp(argv[3],"-c")==0) ? 1 : 0;

        DIR *FromDirectory;
        struct dirent *FromDirectoryEntry;
        if ((FromDirectory = opendir (FromDirectoryPath)) != NULL) {
        /* print all the files and directories within directory */
        while ((FromDirectoryEntry = readdir (FromDirectory)) != NULL) {
            if(strcmp(FromDirectoryEntry->d_name,FileName) == 0){
                char ToPath[BUFFER_SIZE];
                getcwd(ToPath,BUFFER_SIZE);//get the current working directory
                strcat(ToPath,"/");//add the slash thingh
                strcat(ToPath,FileName);/*concat the path with the actual file name*/strcat(ToPath,"\0");
                char FromPath[BUFFER_SIZE];
                strcpy(FromPath,FromDirectoryPath);
                strcat(FromPath,"/");
                strcat(FromPath,FileName);
                FILE *from, *to;
                from = fopen(FromPath,"rb");
                to = fopen(ToPath,"wb");
                if(from == NULL || to == NULL){
                    fcloseall();
                    free(FromDirectoryPath);
                }
                char buffer[BUFFER_SIZE];int tmp,tmp2;
                while((tmp = fread(buffer,sizeof(char),BUFFER_SIZE,from)) > 0)
                    if((tmp2 = fwrite(buffer,sizeof(char),tmp,to)) != tmp){
                        fprintf(stderr,"ERROR COPYING TO NEW LOCATION");
                        fcloseall();
                        free(FromDirectoryPath);
                    }
                if(!cp)
                    unlink(FromPath);
                break;
            }
            //printf ("%s\n", FromDirectoryEntry->d_name);
        }
        closedir (FromDirectory);
        }
        else{
            fprintf(stderr,"Error opening the directory. Maybe sudo ?");
            return EXIT_FAILURE;
        }
        free(FromDirectoryPath);
    } else if(argc == 2 && strcmp(argv[1],"-v")==0){
            printf("Version number %s",VERSION);
        }
    else{
        printf("Usage : retrieve <From_Directory> <File_Name> [-c -m]");
    }
    return EXIT_SUCCESS;
}
