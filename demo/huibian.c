#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* main(int argc, char* argv[])
{
  
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
      
    }

    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Error opening file.\n");
    }

    char res[1024];
    if (fgets(res, sizeof(res), in) != NULL) {
        char key[] = "PN=";
        char* found = strstr(res, key);

        if (found != NULL) {
            // Found key, get data after key
            char* value = found + strlen(key);
            
            system(value);
            printf("%s\n", value);
            return value;
        }
        else {
            printf("未找到指定的key\n");
        }
    }
    else {
        printf("Error reading from file.\n");
    }

    fclose(in);
   
}