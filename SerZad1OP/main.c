#include <stdio.h>
#include <stdlib.h>

#define factorB 3 // blocking factor

#define true 1
#define false 0

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


void saveBlock(TFile *file, int blockAddress, Block *block);
void readBlock(TFile *file, int blockAddress, Block *block);
void createFile();
void chooseFile(TFile *file);

void printPrisoner(Prisoner prisoner);
void printAll(TFile *file);

int search(TFile *file, char *id);


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

void chooseFile(TFile *file){

    file->file = fopen("test.txt", "rb+");

     if(file->file == NULL)
        return;

    puts("File is active!");

}

void printPrisoner(Prisoner prisoner){

    puts("-------------------------------------------------------");
    printf("Record Number: %d\n", prisoner.recordNumber);
    printf("Prisoner id: %s\n", prisoner.id);
    printf("Cell id: %s\n", prisoner.cellId);
    printf("Length Of Sentence: %d\n", prisoner.lengthOfSentence);
    puts("-------------------------------------------------------");

}

void printAll(TFile *file){

    int block_position = 0;
    int i;

    Block block;

    while(true){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

            if(strcmp(block.prisoners[i].id, "*") == 0)
                return;

            printPrisoner(block.prisoners[i]);

        }
    }

}

int search(TFile *file, char *id){

    int block_position = 0;
    int i;

    Block block;

    while(true){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

            if(strcmp(block.prisoners[i].id, "*") == 0){
                puts("End of File");
                return 0;
            }

            if(strcmp(block.prisoners[i].id, id) == 0){
                puts("The prisoner was found!");
                return 1;
            }

        }

        block_position++;

    }

}



int main()
{
    TFile file;
    file.file = NULL;

    while(true){
        printf("\n===================\n");
        printf("1. Create a File\n");
        printf("2. Choose a File\n");

        printf("0. Exit\n");
        printf(">>");

        int option;
        scanf("%d", &option);

        switch(option){

            case 1: createFile(&file); break;

            case 2: chooseFile(&file); break;

            case 3: printAll(&file); break;


            case 0: exit(0); break;

        }

    };

    return 0;
}
