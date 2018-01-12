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
    char status; // a - active, i - inactive
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

int search(TFile *file, int id, int *blockPos, int *prisPos);

void addPrisoner(TFile *file);
void updatePrisoner(TFile *file);
int deletePrisoner(TFile *file);


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

    printf("Enter filename: ");
    char fileName[10];
    scanf("%s", fileName);


    file->file = fopen(fileName, "rb+");

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
    printf("Status: %c\n", prisoner.status);
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

        block_position++;
    }

}

int search(TFile *file, int key, int *blockPos, int *prisPos){

    int block_position = 0;
    int i;

    Block block;

    while(true){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

            if(strcmp(block.prisoners[i].id, "*") == 0){
                puts("End of File");
                *blockPos = block_position;
                *prisPos = i;
                return 0;
            }

            if(block.prisoners[i].recordNumber == key){
                puts("The prisoner was found!");
                *blockPos = block_position;
                *prisPos = i;
                return 1;
            }

        }

        block_position++;

    }

}


void addPrisoner(TFile *file){

    Prisoner newPrisoner;

    printf("Enter key: ");
    scanf("%d", &newPrisoner.recordNumber);

    printf("Enter cell: ");
    scanf("%s", newPrisoner.cellId);

    printf("Enter length of sentence: ");
    scanf("%d", &newPrisoner.lengthOfSentence);

    int blockPos;
    int prisonerPos;

    int i;

    // if prisoner don't exist
    if(search(file, newPrisoner.recordNumber, &blockPos, &prisonerPos) == 0){

        Block block;

        readBlock(file, blockPos, &block);

        block.prisoners[prisonerPos] = newPrisoner;

        if(prisonerPos != factorB-1){
            strcpy(block.prisoners[prisonerPos+1].id, "*"); // set new end
            saveBlock(file, blockPos, &block);
        }

        else{
            saveBlock(file, blockPos, &block);
            Block newBlock;
            strcpy(newBlock.prisoners[0].id, "*");
            saveBlock(file, blockPos+1, &newBlock);

        }

         printf("Prisoner successfully added! \n");

    }else{
        printf("Prisoner already exist! \n");
    }

}


void updatePrisoner(TFile *file){

    printf("Enter key: ");
    int key;
    scanf("%d", &key);

    int block_position;
    int prisoner_position;

    if(search(file, key, &block_position, &prisoner_position) == 1){
        puts("Prisoner is loaded!");

        Block block;
        readBlock(file, block_position, &block);

        Prisoner updPris = block.prisoners[prisoner_position];

        printPrisoner(updPris);


        printf("Do you want to change prisoner id?(y or n): ");
        char opt1;
        scanf(" %c", &opt1);

        if(opt1 == 'y'){
            printf("Enter new id for prisoner: ");
            scanf("%s", &updPris.id);
        }

        printf("Do you want to change prisoner length of sentence?(y or n): ");
        char opt2;
        scanf(" %c", &opt2);

        if(opt2 == 'y'){
            printf("Enter new length of sentence for prisoner:");
            scanf("%d", &updPris.lengthOfSentence);
        }

        printPrisoner(updPris);

        block.prisoners[prisoner_position] = updPris;

        saveBlock(file, block_position, &block);

        puts("Prisoner successfully updated!");

    }else{
        puts("Prisoner does not exist!");
    }

}

int deletePrisoner(TFile *file){

    printf("Enter prisoner key: ");
    int key;
    scanf("%d", &key);

    int block_position;
    int prisoner_position;

    int i;

    if(search(file, key, &block_position, &prisoner_position) == 1){

        Block block;

        while(true){

            readBlock(file, block_position, &block);

            for(i=prisoner_position; i < factorB; i++){

                if(strcmp(block.prisoners[i].id, "*") == 0){
                    saveBlock(file, block_position, &block);
                    return 1;
                }

                if(i != factorB-1)
                    block.prisoners[i] = block.prisoners[i+1];

                if(i == factorB-1){

                    Block nextBlock;
                    readBlock(file, block_position+1, &nextBlock);

                    block.prisoners[i] = nextBlock.prisoners[0];
                    saveBlock(file, block_position, &block);

                }

            }

            prisoner_position = 0;
            block_position++;

        }

    }else{
        puts("Prisoner does not exist!");
        return 0;
    }

}


// sequential

// search
// add
// reorganization
// delete

// load serial and then sort it


int searchSeq(TFile *file, int key, int *blockPosition, int *prisonerPosition){

    int block_count = 0;
    int i;

    Block block;

    while(true){

        readBlock(file, block_count, &block);

        for(i=0; i < factorB; i++){

            if(strcmp(block.prisoners[i].id, "*") == 0){
                *blockPosition = block_count;
                *prisonerPosition = i;

                return 0;
            }

            if(block.prisoners[i].recordNumber > key){
                *blockPosition = block_count;
                *prisonerPosition = i;

                return 1;
            }


            if(block.prisoners[i].recordNumber == key){

                *blockPosition = block_count;
                *prisonerPosition = i;

                return 2;
            }

        }

        block_count++;

    }

}


int callAddNewPrisonerSeq(TFile *file){

    TFile *newPointer = &file;

    Prisoner newPrisoner;
    newPrisoner.status = 'a';
    newPrisoner.lengthOfSentence = 123;

    printf("Enter key: ");
    int key;
    scanf("%d", &newPrisoner.recordNumber);

    addNewPrisonerSeq(file, newPrisoner);

}


int addNewPrisonerSeq(TFile *file, Prisoner newPrisoner){

    int block_pos;
    int pris_pos;

    int result = searchSeq(file, newPrisoner.recordNumber, &block_pos, &pris_pos);

    if(result == 2){
        puts("Prisoner with that key already exist!");
        return;
    }

    if(result == 0){

        Block block;
        readBlock(file, block_pos, &block);

        block.prisoners[pris_pos] = newPrisoner;

        if(pris_pos != factorB-1){
            strcpy(block.prisoners[pris_pos+1].id, "*");
            saveBlock(file, block_pos, &block);
            return 12;
        }

        if(pris_pos == factorB-1){
            saveBlock(file, block_pos, &block);
            Block newBlock;
            strcpy(newBlock.prisoners[0].id, "*");
            saveBlock(file, block_pos+1, &newBlock);
            return 13;
        }

    }

    // between keys
    if(result == 1){

        Block block2;

        printf("blok: %d, slog: %d", block_pos, pris_pos);

        Prisoner temp;

        int i;

        while(true){

            readBlock(file, block_pos, &block2);

            for(i=pris_pos; i < factorB; i++){

                if(strcmp(newPrisoner.id, "*") == 0){
                    block2.prisoners[i] = newPrisoner;
                    saveBlock(file, block_pos, &block2);
                    return 44;
                }

                temp = block2.prisoners[i];

                block2.prisoners[i] = newPrisoner;

                newPrisoner = temp;

                // when is end of block and in newPrisoner is mark for end (*)
                if(strcmp(newPrisoner.id, "*") == 0 && i == factorB-1){

                    saveBlock(file, block_pos, &block2);
                    Block new_block;
                    strcpy(new_block.prisoners[0].id, "*");
                    block_pos++;
                    saveBlock(file, block_pos, &new_block);
                    return 33;

                }

                // when is end of block and in newPrisoner s not mark for end (*)
                if(strcmp(newPrisoner.id, "*") != 0 && i == factorB-1){

                    saveBlock(file, block_pos, &block2);
                    block_pos++;

                }

            }

            pris_pos = 0;

        }


    }

}


int logicalDelete(TFile *file){

    printf("Enter key: ");
    int key;
    scanf("%d", &key);

    int blockPos;
    int prisPos;

    int status = searchSeq(file, key, &blockPos, &prisPos);

    printf("status: %d", status);

    if(status == 2){

        Block block;

        readBlock(file, blockPos, &block);

        block.prisoners[prisPos].status = 'i'; // inactive

        saveBlock(file, blockPos, &block);

    }

}


void reogranization(TFile *file){

    int block_count = 0;
    int i;

    // new File

    createFile(); // enter filename reorg,txt

    TFile new_file;
    new_file.file = fopen("reorg.txt", "rb+");

    if(new_file.file != NULL)
        puts("New File is loaded!");
    else
        puts("New File is empty");


    while(true){

        Block block;
        readBlock(file, block_count, &block);

        for(i=0; i < factorB; i++){

            if(strcmp(block.prisoners[i].id, "*") == 0){
                fclose(new_file.file);
                return 1;
            }

            if(block.prisoners[i].status == 'a'){

                printPrisoner(block.prisoners[i]);
                int status = addNewPrisonerSeq(&new_file, block.prisoners[i]);
                printf("stat: %d\n", status);

            }

        }

        block_count++;

    }

}


int physicalDeletionSeq(TFile *file){

    printf("Enter key: ");
    int key;
    scanf("%d", &key);

    int block_pos;
    int pris_pos;

    int status = searchSeq(file, key, &block_pos, &pris_pos);

    Block block;
    int i;

    if(status == 2){

        while(true){

            readBlock(file, block_pos, &block);

            for(i=pris_pos; i < factorB; i++){

                if(strcmp(block.prisoners[i].id, "*") == 0){
                    saveBlock(file, block_pos, &block);
                    return 123;

                }

                if(i != factorB-1){
                    block.prisoners[i] = block.prisoners[i+1];
                }

                if(i == factorB-1){

                    Block nextBlock;
                    readBlock(file, block_pos+1, &nextBlock);

                    block.prisoners[i] = nextBlock.prisoners[0];
                    saveBlock(file, block_pos, &block);

                    block_pos++;

                }

            }
            pris_pos = 0;

        }


    }

}



int main()
{
    TFile file;
    file.file = NULL;

    int option = 99;

    while(option != 0){
        printf("\n===================\n");
        printf("1. Create a file\n");
        printf("2. Choose a file\n");
        printf("3. Print all prisoners\n");

        printf("\n-. Serial\n");

        printf("\t4. Add new prisoner\n");
        printf("\t5. Update prisoner\n");
        printf("\t6. Physical deletion\n");
        printf("\n===================\n");

        printf("-. Sequential\n");

        printf("\t7. Add new prisoner\n");
        printf("\t8. Reorganization\n");
        printf("\t9. Physical deletion\n");
        printf("\t10. Logical deletion\n");

        printf("\n===================\n");

        printf("0. Exit\n");
        printf(">>");

        scanf("%d", &option);

        switch(option){

            case 1: createFile(); break;

            case 2: chooseFile(&file); break;

            case 3: printAll(&file); break;

            case 4: addPrisoner(&file); break;

            case 5: updatePrisoner(&file); break;

            case 6: deletePrisoner(&file); break;

            case 7: callAddNewPrisonerSeq(&file); break;

            case 8: reogranization(&file); break;

            case 9: physicalDeletionSeq(&file); break;

            case 10: logicalDelete(&file); break;

            case 0: exit(0); break;

        }

    };

    return 0;
}
