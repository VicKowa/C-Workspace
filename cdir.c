#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#define MAX_PATH_LENGTH 4096

int main(int argc, char** argv) 
{   
    DIR *dir;
    struct dirent *entry;
    struct stat temp;
    
    
    
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    dir = opendir(cwd);
    if(dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while((entry = readdir(dir)) != NULL)
    {
        char *filename = entry->d_name; 
        // Ignoriere "." und ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Erstelle den vollständigen Pfad zur Datei
        char filePath[PATH_MAX];
        snprintf(filePath, MAX_PATH_LENGTH, "%s/%s", cwd, filename);
        if(stat(filePath, &temp) == -1)
        {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        printf("type: %c\t size: %lld\t lastmodified: %ld\t mod: %o\t name: %s\n", 
                entry->d_type, (long long)temp.st_size, temp.st_mtime, temp.st_mode, filename);
    }
    closedir(dir);
    return 0;
}


