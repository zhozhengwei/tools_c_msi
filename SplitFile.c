#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

// 开关
int currentLine = 1;

// 将内容写入文件中
void writeToFile(FILE *file, const char *line) {
    fprintf(file, "%s", line);
    currentLine++;
}

// 读取AddPoint.xml中的方法
void insertContent(FILE *targetFile, const char *sourceFilename, const int targetLine) {
    FILE *sourceFile = fopen(sourceFilename, "r");
    if (sourceFile == NULL) {
        printf("Error opening file %s.\n", sourceFilename);
        return;
    }
    char line[MAX_LINE_LENGTH];
    int currentLine = 0;
    while (fgets(line, MAX_LINE_LENGTH, sourceFile) != NULL) {
        currentLine++;
        if (currentLine >= 1 && currentLine <= 26) {
            fprintf(targetFile, "%s", line); 
        }
    }
    fclose(sourceFile);
}

// 解析unattend.xml文件并将其内容拆分为unattendok.xml
void splitXML(const char *filename,const char *dokname) {
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }
    FILE *unattendokFile = fopen(dokname, "w");
    if (unattendokFile == NULL) {
        printf("Error creating output files.\n");
        fclose(inputFile);
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        
        if (currentLine >= 71 && currentLine <= 96) {
            currentLine++;
            continue;
        }
        writeToFile(unattendokFile, line);

        // 将AddPoint.xml的三个标签内容追加到unattendok.xml中
        if (currentLine == 71) {
            insertContent(unattendokFile, "AddPoint.xml", currentLine);
        }
    }
    currentLine = 1;
    fclose(inputFile);
    fclose(unattendokFile);
}

// 解析unattend.xml文件并将其内容拆分为msi-oobe.xml
void splitXML01(const char *filename, const char *msiname){
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }
    FILE *msiOobeFile = fopen(msiname, "w");

     if (msiOobeFile == NULL) {
        printf("Error creating output files.\n");
        fclose(inputFile);
        return;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        
        if (currentLine >= 3 && currentLine <= 70) {
            currentLine++;
            continue;
        }
        writeToFile(msiOobeFile, line);

    }
    currentLine = 1;
    fclose(inputFile);
    fclose(msiOobeFile);
}

int main(int argc,char* argv[]) {
    const char *filename = argv[1];
    const char *dokname = argv[2];
    const char *msiname = argv[3];
    splitXML(filename,dokname);
    splitXML01(filename,msiname);
    return 0;
}
