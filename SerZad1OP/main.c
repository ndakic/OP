#include <stdio.h>
#include <stdlib.h>

#define factorB 3 // blocking factor

typedef struct{
    char date[10]; // 01-01-2018
    char time[5]; // 12:15
}Date;

typedef struct{
    int recordNumber;
    char id[7];
    Date date;
    char cellId[5];
    int lengthOfSentence;
}Prisoner;


typedef struct{
    FILE *file;
    char fileName[15];
}TFile;

typedef struct{
    Prisoner prisoners[factorB];
}Block;



void saveBlock(TFile *file, int blockAddress, Block *block){

    int status;

    status = fseek(file->file, blockAddress * sizeof(Block), SEEK_SET);
    if(status != 0){
        puts("Seek Error!");
    }

    status = fwrite(block, sizeof(Block), 1, file->file);

    if(status != 1){
        puts("Write Error!");
    }

}


void readBlock(TFile *file, int blockAddress, Block *block){

    int status;

    status = fseek(file->file, blockAddress * sizeof(Block), SEEK_SET);
    if(status != 0){
        puts("Seek Error!");
    }

    status = fread(block, sizeof(Block), 1, file->file);
    if(status != 1){
        puts("Write Error!");
    }

}

void printPrisoner(Prisoner prisoner){

    puts("-------------------------------------------------------");
    printf("Record Number: %d\n", prisoner.recordNumber);
    printf("Prisoner id: %s\n", prisoner.id);
    printf("Cell id: %s\n", prisoner.cellId);
    printf("Length Of Sentence: %d\n", prisoner.lengthOfSentence);
    puts("-------------------------------------------------------");

}

void createFile(){

    TFile file;

    printf("Enter filename: ");
    scanf("%s", file.fileName);

    file.file = fopen(file.fileName, "wb+");

    Block block;
    strcpy(block.prisoners[0].id, "*");

    saveBlock(&file, 0, &block);

    fclose(file.file);

}


int main()
{
    TFile file;
    file.file = NULL;

    //createFile();


    file.file = fopen("test.txt", "rb");

    Block block;

    readBlock(&file.file, 0, &block);

    printPrisoner(block.prisoners[0]);


    printf("End\n");
    return 0;
}
