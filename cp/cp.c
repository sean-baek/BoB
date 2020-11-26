#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_SIZE 1024

int main(int argc, char **argv)
{
    int i;

    if(argc < 3)
    {
        printf("Usage : %s <filename1> <filename2> <filename3>\n", argv[0]);
        printf("or\nUsage : %s <filename1> <filename2> ... <directory name>\n", argv[0]);
    }

    const char *dir = argv[argc-1];
    DIR *isdir = opendir(dir);

    if(isdir)
    {
        for(i=1; i < argc - 1; i++)
        {
            if(access(argv[i], F_OK) != -1)
            {
                int len = strlen(dir) + strlen("/") + strlen(argv[i]);

                char *file = (char*)calloc(sizeof(char), len);
                strncpy(file, dir, strlen(dir));
                strncat(file, "/", strlen("/"));
                strncat(file, argv[i], strlen(argv[i]));
                
                FILE *src = fopen(argv[i], "r");
                FILE *dst = fopen(file, "w");
                char buf[MAX_SIZE] ={0, };
                
                while(fread(buf, 1, sizeof(buf), src))
                {
                    buf[strlen(buf)] = '\0';
                    fwrite(buf, 1, sizeof(buf), dst);
                }

                if(file)
                {
                    memset(file, 0, len);
                    free(file);
                }

                fclose(dst);
                fclose(src);
            }

            else
            {
                printf("Cannot found '%s' file\n", argv[i]);
            }
        }
    }

    else
    {
        printf("Cannot found '%s' directory\n", dir);
    }
    
    closedir(isdir);
    return 0;
}
