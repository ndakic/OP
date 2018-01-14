#include <stdio.h>
#include <stdlib.h>

#define factorB 3
#define FILENAME_MAX 30

#define true 1
#define false 0

typedef struct{

    FILE *file;
    char fileName[FILENAME_MAX];

}TFile;

typedef struct{

    int record_number; // 6 digits, record_number > 000000
    char name[50];
    char date;
    int loan_amount;  // max 100 000
    int interest;     // max 20
    int installments; // max 72
    char status;      // a - active, i - inactive

}Credit;

typedef struct{
    Credit credits[factorB];
}Block;


void saveBlock(TFile *file, int blockPosition, Block *block);
void readBlock(TFile *file, int blockPosition, Block *block);

void createFile();
void chooseFile(TFile *file);
void printActiveFile(TFile *file);

int addNewCredit(TFile *file);

void printCredit(Credit credit);
int printAllCredits(TFile *file);




void saveBlock(TFile *file, int blockPosition, Block *block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(Block), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fwrite(block, sizeof(Block), 1, file->file);
    if(status != 1)
        puts("Write Error!");

}

void readBlock(TFile *file, int blockPosition, Block *block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(Block), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fread(block, sizeof(Block), 1, file->file);
    if(status != 1)
        puts("Read Error!");
}

void createFile(){

    TFile file;

    printf("Enter filename: ");
    scanf("%s", file.fileName);

    file.file = fopen(file.fileName, "wb+");

    Block block;
    block.credits[0].record_number = -1;

    saveBlock(&file, 0, &block);

    fclose(file.file);

    puts("File is successfully created!");


}

void chooseFile(TFile *file){

    printf("Enter filename: ");
    scanf("%s", file->fileName);

    file->file = fopen(file->fileName, "rb+");

    if(file->file == NULL){
        printf("There is no file with %s name!\n", file->fileName);
    }else{
        puts("File is now active!");
    }
}

void printActiveFile(TFile *file){

    if(file->file == NULL){
        puts("First choose file!");
    }else{
        printf("Active file: %s\n", file->fileName);
    }
}


int searchSerial(TFile *file, int key, int *blockPos, int *creditPos){

    int block_position = 0;
    int credit_position;

    Block block;
    int i;

    // find end position
    while(true){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

            //end
            if(block.credits[i].record_number == -1){
                *blockPos = block_position;
                *creditPos = i;
                return 0;
            }

            if(block.credits[i].record_number == key){
                *blockPos = block_position;
                *creditPos = i;
                return 1;
            }
        }
        block_position++;
    }

}


int addNewCredit(TFile *file){

    if(file->file == NULL){
        puts("First choose file!");
        return 99;
    }

    int block_position = 0;
    int credit_position;

    printf("Enter record number: ");
    int key;
    scanf("%d", &key);

    if(key < 0 || key > 999999){
        puts("Key must be between 1 and 999999");
        return 99;
    }

    int status = searchSerial(file, key, &block_position, &credit_position);

    if(status == 1){
        puts("Credit with that record number already exist!");
        return 99;
    }

    if(status == 0){

        Credit new_credit;
        new_credit.record_number = key;

        Block block;
        readBlock(file, block_position, &block);
        block.credits[credit_position] = new_credit;

        if(credit_position == factorB-1){
            saveBlock(file, block_position, &block);
            Block new_block;
            new_block.credits[0].record_number = -1;
            saveBlock(file, block_position+1, &new_block);
            return 1;
        }else{

            block.credits[credit_position+1].record_number = -1;
            saveBlock(file, block_position, &block);
        }

    }

    puts("Credit successfully added!");

}

void printCredit(Credit credit){

    puts("-------------------------------------------------------");
    printf("Record Number: %d\n", credit.record_number);
    printf("Name: %s\n", credit.name);
    printf("Date: %s\n", credit.date);
    printf("Loan Amount: %d\n", credit.loan_amount);
    printf("Loan Interest: %d\n", credit.interest);
    printf("Number of Installments: %d\n", credit.installments);
    printf("Status: %c\n", credit.status);
    puts("-------------------------------------------------------");


}

int printAllCredits(TFile *file){

    int block_position = 0;
    int i;

    Block block;

    while(true){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

            if(block.credits[i].record_number == -1)
                return 0;

            printCredit(block.credits[i]);
        }

        block_position++;
    }
}

int main()
{

    TFile file;
    file.file = NULL;

    int option = 99;

    do{

        printf("\n===================\n");
        printf("1. Create a file\n");
        printf("2. Choose a file\n");
        printf("3. Print active file\n");
        printf("4. Add new Credit\n");
        printf("5. Print all Credits\n");
        printf("0. Exit\n");
        printf("\n===================\n");


        printf(">>");

        scanf("%d", &option);

        switch(option){
            case 1: createFile(); break;

            case 2: chooseFile(&file); break;

            case 3: printActiveFile(&file); break;

            case 4: addNewCredit(&file); break;

            case 5: printAllCredits(&file); break;

            case 0: exit(EXIT_FAILURE);
        }


    }while(option != 0);

    puts("End of program!");
    return 0;
}
