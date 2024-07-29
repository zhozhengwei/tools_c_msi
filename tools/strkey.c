#include <stdio.h>
#include <stdlib.h>

void replace_spaces_with_dash(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    // Temporary file to write modified content
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        perror("Failed to create temporary file");
        fclose(file);
        return;
    }

    // Buffer to read lines
    char buffer[1024];
    
    // Read file line by line, replace spaces with dashes, and write to temp file
    while (fgets(buffer, sizeof(buffer), file)) {
        for (char *p = buffer; *p != '\0'; ++p) {
            if (*p == ' ') {
                *p = '-';
            }
        }
        fputs(buffer, temp_file);
    }

    // Check for reading errors
    if (ferror(file)) {
        perror("Error reading the file");
        fclose(file);
        fclose(temp_file);
        return;
    }

    // Close the original file
    fclose(file);

    // Open the original file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        fclose(temp_file);
        return;
    }

    // Rewind temp file to the beginning
    rewind(temp_file);

    // Write the modified content from temp file to original file
    while (fgets(buffer, sizeof(buffer), temp_file)) {
        fputs(buffer, file);
    }

    // Close files
    fclose(file);
    fclose(temp_file);

    printf("File processing complete.\n");
}

int main(int argc,char* argv[]) {
    const char *filename = argv[1];
    replace_spaces_with_dash(filename);
    return 0;
}
