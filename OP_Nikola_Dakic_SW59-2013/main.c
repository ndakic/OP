#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define serial_factorB 5
#define factorB 3
#define FILENAME_MAX 30
#define MAX_CREDITS 40

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
    Credit credits[serial_factorB];
}SerialBlock;

typedef struct{
    Credit credits[factorB];
}Block;

typedef struct{
    Credit credit;
    int filePosition;
    int nextOverflowPosition;
}Overflow;

typedef struct{
    Credit credits[factorB];
    Overflow overflow;
}PZBlock;

                        // SAVE-READ

// ==========================================================

void saveSerialBlock(TFile *file, int blockPosition, SerialBlock *block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(SerialBlock), SEEK_SET);
    if(status != 0)
        puts("Seek Serial BlockError!");

    status = fwrite(block, sizeof(SerialBlock), 1, file->file);
    if(status != 1)
        puts("Write Serial Block Error!");

}

void readSerialBlock(TFile *file, int blockPosition, SerialBlock *block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(SerialBlock), SEEK_SET);
    if(status != 0)
        puts("Seek Serial Block Error!");

    status = fread(block, sizeof(SerialBlock), 1, file->file);
    if(status != 1)
        puts("Read Serial Block Error!");
}

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
        puts("Seek Block Error!");

    status = fread(block, sizeof(Block), 1, file->file);
    if(status != 1)
        puts("Read Block Error!");
}

void savePZBlock(TFile *file, int blockPosition, PZBlock *pz_block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(PZBlock), SEEK_SET);
    if(status != 0)
        puts("Seek PZBlock Error!");

    status = fwrite(pz_block, sizeof(PZBlock), 1, file->file);
    if(status != 1)
        puts("Write PZBlock Error!");

    printf("Block saved at position: %d\n", blockPosition);

}

void readPZBlock(TFile *file, int blockPosition, PZBlock *pz_block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(PZBlock), SEEK_SET);
    if(status != 0)
        puts("Seek PZBlock Error!");

    status = fread(pz_block, sizeof(PZBlock), 1, file->file);
    if(status != 1)
        puts("Read PZBlock Error!");
}

void readOverflow(int overflowPosition, Overflow *overflow){

    TFile file;
    file.file = fopen("overflows", "rb+");

    int status;

    status = fseek(file.file, overflowPosition * sizeof(Overflow), SEEK_SET);
    if(status != 0)
        puts("Seek Overflow Error!");

    status = fread(overflow, sizeof(Overflow), 1, file.file);
    if(status != 1)
        puts("Read Overflow Error!");

     fclose(file.file);
}

void saveOverflow(int overflowPosition, Overflow *overflow){

    TFile file;
    file.file = fopen("overflows", "rb+");

    int status;

    status = fseek(file.file, overflowPosition * sizeof(Overflow), SEEK_SET);
    if(status != 0)
        puts("Seek Overflow Error!");

    status = fwrite(overflow, sizeof(Overflow), 1, file.file);
    if(status != 1)
        puts("Write Overflow Error!");


    fclose(file.file);


    printf("Overflow saved at position : %d\n", overflowPosition);

}

                         // TREE
// ==========================================================

struct Node{
    int key;
    int block_address;
    int file_position;
    struct Node *left;
    struct Node *right;
};

typedef struct Node TreeNode;

TreeNode* new(TreeNode new_node){

    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    node->key = new_node.key;
    node->block_address = new_node.block_address;
    node->left = NULL;
    node->right = NULL;

    return node;

}

TreeNode* bst(TreeNode nodes[20], int first, int last){

    int mid;

    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));

    if (first > last)
        return NULL;

    mid = (first + last) / 2;
    temp = new(nodes[mid]);


    temp->left = bst(nodes, first, mid - 1);
    temp->right = bst(nodes, mid + 1, last);

    return temp;

}

TreeNode* searchTree(int key, TreeNode *temp, int *block){

    TreeNode *empty = (TreeNode*)malloc(sizeof(TreeNode));

    if(temp != NULL){
        if(temp->key > key || temp->key == key){
            *block = temp->block_address;
        }
    }

    if(temp == NULL || temp->key == key){

        if(temp == NULL){
            empty->block_address = block;
            empty->key = -1;
            return empty;
        }else{
            return temp;
        }

    }

    // go left
    if(key < temp->key)
        return searchTree(key, temp->left, block);

    // go right
    return searchTree(key, temp->right, block);
}

void saveTreeNode(TFile *file, int nodePosition, TreeNode *treeNode){

    int status;

    status = fseek(file->file, nodePosition * sizeof(TreeNode), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fwrite(treeNode, sizeof(TreeNode), 1, file->file);
    if(status != 1)
        puts("Write Error!");
}

void readTreeNode(TFile *file, int nodePosition, TreeNode *treeNode){

    int status;

    status = fseek(file->file, nodePosition * sizeof(TreeNode), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fread(treeNode, sizeof(TreeNode), 1, file->file);
    if(status != 1)
        puts("Read Error!");

}

// ================ Serial and Sequential ====================== //

void createFile(){

    TFile file;

    printf("Enter filename: ");
    scanf("%s", file.fileName);

    file.file = fopen(file.fileName, "wb+");

    SerialBlock block;
    block.credits[0].record_number = -1;

    saveSerialBlock(&file, 0, &block);

    fclose(file.file);

    puts("File is successfully created!");


}

void chooseFile(TFile *file, TreeNode **root){

    printf("Enter filename: ");
    scanf("%s", file->fileName);

    // load balanced binary tree
    if(strcmp(file->fileName, "primary_zone") == 0 || strcmp(file->fileName, "reorg") == 0 ){

        createIndexZone(file->fileName, root);

    }

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

    SerialBlock block;
    int i;

    // find end position
    while(true){

        readSerialBlock(file, block_position, &block);

        for(i=0; i < serial_factorB; i++){

            //end
            if(block.credits[i].record_number == -1){
                *blockPos = block_position;
                *creditPos = i;
                return 0;
            }

            if(block.credits[i].record_number == key && block.credits[i].status == 'a'){
                *blockPos = block_position;
                *creditPos = i;
                return 1;
            }

            if(block.credits[i].record_number == key && block.credits[i].status == 'i'){
                *blockPos = block_position;
                *creditPos = i;
                return 2;
            }
        }
        block_position++;
    }

}

int searchSequential(TFile *file, int key, int *blockPos, int *creditPos){

    int block_position = 0;

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

            if(block.credits[i].record_number == key && block.credits[i].status == 'a'){
                *blockPos = block_position;
                *creditPos = i;
                return 1;
            }

            if(block.credits[i].record_number == key && block.credits[i].status == 'i'){
                *blockPos = block_position;
                *creditPos = i;
                return 2;
            }
        }
        block_position++;
    }

}

int callAddNewCredit(TFile *file){

    if(file->file == NULL){
        puts("First choose file!");
        return 99;
    }

    printf("Enter record number: ");
    int key;
    scanf("%d", &key);

    if(key < 0 || key > 999999){
        puts("Key must be between 1 and 999999");
        return 99;
    }

    Credit credit;
    credit.record_number = key;
    credit.status = 'a';

    printf("Loan amount: ");
    scanf("%d", &credit.loan_amount);

    addNewCreditSerial(file, credit);

}

int addNewCreditSerial(TFile *file, Credit new_credit){

    int block_position = 0;
    int credit_position;

    int status = searchSerial(file, new_credit.record_number, &block_position, &credit_position);

    if(status == 1){
        puts("Credit with that record number already exist!");
        return 99;
    }

    if(status == 0){

        SerialBlock block;
        readSerialBlock(file, block_position, &block);
        block.credits[credit_position] = new_credit;

        if(credit_position == serial_factorB-1){
            saveSerialBlock(file, block_position, &block);
            SerialBlock new_block;
            new_block.credits[0].record_number = -1;
            saveSerialBlock(file, block_position+1, &new_block);
            return 1;
        }else{
            block.credits[credit_position+1].record_number = -1;
            saveSerialBlock(file, block_position, &block);
        }

         puts("Credit successfully added!");

    }

    if(status == 2){
        SerialBlock block;
        readSerialBlock(file, block_position, &block);
        block.credits[credit_position] = new_credit;
        saveSerialBlock(file, block_position, &block);
    }

}

int addNewCreditSequential(TFile *file, Credit new_credit){

    int block_position = 0;
    int credit_position;

    int status = searchSequential(file, new_credit.record_number, &block_position, &credit_position);

    if(status == 1){
        puts("Credit with that record number already exist!");
        return 99;
    }

    if(status == 0){

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

    if(status == 2){

        Block block;
        readBlock(file, block_position, &block);
        block.credits[credit_position] = new_credit;

        saveBlock(file, block_position, &block);
    }

}

void loadData(){

    TFile txtFile;
    char max_lenght[100];

    Credit credits[MAX_CREDITS];

    txtFile.file = fopen("podaci.txt", "r");
    int count = 0;

    int *record_number;
    char *name;
    char *date;
    int *loan_amount;
    int *interest;
    int *installments;
    char *status;

    if(txtFile.file != NULL){

        while((fgets(max_lenght, 100, txtFile.file)) != NULL){

            record_number = atoi(strtok(max_lenght, ","));

            name = strtok(NULL, ",");
            date = strtok(NULL, ",");
            loan_amount = atoi(strtok(NULL, ","));
            interest = atoi(strtok(NULL, ","));
            installments = atoi(strtok(NULL, ","));
            status = strtok(NULL, ",");

            credits[count].record_number = record_number;
            strcpy(credits[count].name, name);
            credits[count].date = date;
            credits[count].loan_amount = loan_amount;
            credits[count].interest = interest;
            credits[count].installments = installments;
            credits[count].status = *status;

            count++;

        }

    }

    fclose(txtFile.file);

    TFile serial;
    printf("Enter new filename: ");
    scanf("%s", serial.fileName);
    serial.file = fopen(serial.fileName, "wb+");

    SerialBlock block;
    block.credits[0].record_number = -1;

    saveSerialBlock(&serial, 0, &block);

    fclose(serial.file);

    serial.file = fopen(serial.fileName, "rb+");


    int i;
    for(i = 0; i < count; i++){
        printCredit(credits[i]);
        addNewCreditSerial(&serial, credits[i]);
    }

    puts("Serial file is created!");

    fclose(serial.file);

}

// ====================== PRINT ================================= //

void printCredit(Credit credit){

    puts("-------------------------------------------------------");
    printf("Record Number: %d\n", credit.record_number);
    //printf("Name: %s\n", credit.name);
    //printf("Date: %s\n", credit.date);
    printf("Loan Amount: %d\n", credit.loan_amount);
    //printf("Loan Interest: %d\n", credit.interest);
    //printf("Number of Installments: %d\n", credit.installments);
    printf("Status: %c\n", credit.status);
    puts("-------------------------------------------------------");

}

void printOverflow(Overflow overflow){

    printf("Record Number: %d\n", overflow.credit.record_number);
    //printf("Name: %s\n", overflow.credit.name);
    //printf("Date: %s\n", overflow.credit.date);
    printf("Loan Amount: %d\n", overflow.credit.loan_amount);
    //printf("Loan Interest: %d\n", overflow.credit.interest);
    //printf("Number of Installments: %d\n", overflow.credit.installments);
    //printf("File position: %d\n", overflow.filePosition);
    //printf("Next position: %d\n", overflow.nextOverflowPosition);
    printf("Status: %c\n", overflow.credit.status);




}

int printSerial(TFile *file){

    if(file->file == NULL || strcmp(file->fileName,"serial") != 0 ){
        puts("First choose serial file!");
        return 99;
    }

    int block_position = 0;
    int i;

    SerialBlock block;

    while(true){

        readSerialBlock(file, block_position, &block);

        for(i=0; i < serial_factorB; i++){

            if(block.credits[i].record_number == -1)
                return 0;

            puts("-------------------------------------------------------");
            printf("Block position: %d, credit position: %d\n", block_position+1, i+1);
            printCredit(block.credits[i]);
        }

        block_position++;
    }
}

int printAllCredits(TFile *file){

    if(file->file == NULL || strcmp(file->fileName,"seq") != 0){
        puts("First choose sequential file!");
        return 99;
    }

    int block_position = 0;
    int i;

    Block block;

    while(true){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

            if(block.credits[i].record_number == -1)
                return 0;

            puts("-------------------------------------------------------");
            printf("Block position: %d, credit position: %d\n", block_position+1, i+1);
            printCredit(block.credits[i]);
        }

        block_position++;
    }
}

int compare(const void *c1, const void *c2){

    Credit *credit1 = (Credit*)c1;
    Credit *credit2 = (Credit*)c2;

    if(credit1->record_number > credit2->record_number)
        return 1;
    else
        return -1;

}

int loadSerialAndMakeSequential(TFile *file){

    if(file->file == NULL){
        puts("First choose file!");
        return 99;
    }

    Credit credits[MAX_CREDITS];

    int block_position = 0;
    int credits_count = 0;

    int status = 0;
    int i;

    SerialBlock block;

    while(status == 0){

        readSerialBlock(file, block_position, &block);

        for(i=0; i < serial_factorB; i++){

            if(block.credits[i].record_number == -1){
                status = 1;
                break;
            }

            credits[credits_count] = block.credits[i];
            credits_count++;
        }

        block_position++;
    }

    qsort(credits, credits_count, sizeof(Credit), compare);


    // create seq file

    TFile new_file;

    printf("Enter filename for sequential file: ");
    scanf("%s", new_file.fileName);

    new_file.file = fopen(new_file.fileName, "wb+");

    Block init_block;
    init_block.credits[0].record_number = -1;

    saveBlock(&new_file, 0, &init_block);

    for(i=0; i<credits_count; i++){
        addNewCreditSequential(&new_file, credits[i]);
    }

    fclose(new_file.file);

    puts("Sequential file successfully created!");

    return 1;

}

int printPrimaryZone(TFile *file){

    int pz_block_position = 0;
    int i;

    PZBlock pzBlock;

    while(true){

        readPZBlock(file, pz_block_position, &pzBlock);

        for(i=0; i < factorB; i++){

            if(pzBlock.credits[i].record_number == -1){
                return 11;
            }


        // print primary zone

        printf("Block position: %d, credit position: %d\n", pz_block_position+1, i+1);
        printCredit(pzBlock.credits[i]);
        }

        // print overflow zone

        //puts("-------------------------------------------------------");
        puts("--------------------OVERFLOW --------------------------");
        puts("-------------------------------------------------------");

        Overflow over = pzBlock.overflow;

        printOverflow(over);

        while(over.nextOverflowPosition != -1){

             readOverflow(over.nextOverflowPosition, &over);
             puts("-------------------------------------------------------");
             printOverflow(over);

        }


        puts("-------------------------------------------------------");
        puts("---------------------END-------------------------------");
        puts("-------------------------------------------------------");
        pz_block_position++;

    }

}

// ===================== Index-Sequential ========================= //

void createIndexZone(char *fileName, TreeNode **root){

    TFile pzFile;
    pzFile.file = fopen(fileName, "rb+");

    int block_pos = 0;
    PZBlock blockPZ;

    int index_status = 0;

    TreeNode nodes[50];

    Credit credit;
    credit.record_number = -1;

    int i;

    while(index_status == 0){

        readPZBlock(&pzFile, block_pos, &blockPZ);

        for(i=0; i < factorB; i++){

            if(blockPZ.credits[i].record_number == -1 && i != 0){

                TreeNode node;
                node.key = credit.record_number;
                node.block_address = block_pos;

                nodes[block_pos] = node;
                index_status = 1;

                TreeNode end;
                end.key = -1;
                end.block_address = -1;
                end.file_position = -1;
                block_pos++;
                nodes[block_pos] = end;

                break;

            }

            if(blockPZ.credits[i].record_number == -1 && i == 0){
                index_status = 1;

                TreeNode end;
                end.key = -1;
                end.block_address = -1;
                end.file_position = -1;
                nodes[block_pos] = end;
                break;
            }

            if(blockPZ.credits[i].record_number > credit.record_number){
                credit = blockPZ.credits[i];
            }

            if(blockPZ.overflow.filePosition != -1){
                if(blockPZ.overflow.credit.record_number > credit.record_number){
                    credit = blockPZ.overflow.credit;
                }
            }

        }

        if(index_status == 0){
            TreeNode node;
            node.key = credit.record_number;
            node.block_address = block_pos;

            nodes[block_pos] = node;
            block_pos++;
        }

    }

    fclose(pzFile.file);

    int n = block_pos;

    int filePosition = 0;

    TFile nodeFile;
    nodeFile.file = fopen("treeNodes", "wb+");

    for(i=0; i < block_pos; i++){
        printf("Max element of block: %d is %d\n", nodes[i].block_address, nodes[i].key);
        saveTreeNode(&nodeFile, i, &nodes[i]);
    }

    TreeNode *p;
    p = bst(nodes, 0, n-1);

    *root = p;

    TreeNode end;
    end.block_address = -1;
    end.file_position = -1;
    end.key = -1;

    saveTreeNode(&nodeFile, block_pos, &end); // add end

    fclose(nodeFile.file);

}

int createPrimaryZoneOverflowIndexZone(TFile *file, TreeNode **root){

    if(file->file == NULL){
        puts("First choose file!");
        return 99;
    }

    // load all credits from sequential file

    Credit credits[MAX_CREDITS];
    int credit_count = 0;
    int block_position = 0;

    Block block;

    int status = 0;
    int i;

    while(status == 0){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

            if(block.credits[i].record_number == -1){
                credits[credit_count] = block.credits[i]; // end
                status = 1;
                break;
            }

            credits[credit_count] = block.credits[i];

            credit_count++;

        }
        block_position++;
    }

    // Create Primary Zone From Sequential File

    PZBlock pz_block;

    int count = 0;
    int end = 0;

    int block_pos_pz = 0;

    TFile pz_file;
    pz_file.file = fopen("primary_zone", "wb+");

    while(end == 0){

        for(i=0; i < factorB; i++){

            if(count == credit_count){

                pz_block.credits[i] = credits[count]; // end

                Overflow overflow;
                overflow.credit.record_number = -1;
                overflow.nextOverflowPosition = -1;
                overflow.filePosition = -1;

                pz_block.overflow = overflow;

                savePZBlock(&pz_file, block_pos_pz, &pz_block);

                end = 1;
                break;
            }


            pz_block.credits[i] = credits[count];

            count++;

            if(i == factorB-1){
                Overflow overflow;
                overflow.credit.record_number = -1;
                overflow.nextOverflowPosition = -1;
                overflow.filePosition = -1;

                pz_block.overflow = overflow;

                savePZBlock(&pz_file, block_pos_pz, &pz_block);
                block_pos_pz++;
            }
        }
    }

    fclose(pz_file.file);


    // create overflow zone with end

    Overflow overflow;
    overflow.credit.record_number = -1;
    overflow.filePosition = -1;
    overflow.nextOverflowPosition = -1;

    TFile over_file;
    over_file.file = fopen("overflows", "wb+");

    int over_status;

    over_status = fseek(over_file.file, 0 * sizeof(Overflow), SEEK_SET);
    if(over_status != 0)
        puts("Seek Error!");

    over_status = fwrite(&overflow, sizeof(Overflow), 1, over_file.file);
    if(over_status != 1)
        puts("Write Error!");


    fclose(over_file.file);

    createIndexZone("primary_zone", root);


}

int searchCreditPosition(TFile *file, TreeNode *root, int key, int *blockPosition, int *creditPosition){

    int block;

    TreeNode* result = searchTree(key, root, &block);

    int pz_block_position = block;
    int i;

    PZBlock pzBlock;

    readPZBlock(file, pz_block_position, &pzBlock);

    for(i=0; i < factorB; i++){

            // check primary zone

            if(pzBlock.credits[i].record_number == key){

                *blockPosition = block;
                *creditPosition = i;

                return 1;
            }


            // check overflow zone

            if(i == factorB-1 && pzBlock.overflow.filePosition != -1){

                Overflow overflow = pzBlock.overflow;
                int status = 0;

                if(overflow.credit.record_number == key){
                    *blockPosition = pz_block_position;
                    *creditPosition = overflow.filePosition;

                    return 3;
                }

                //while next overflow exist
                while(overflow.nextOverflowPosition != -1){

                    if(overflow.credit.record_number == key){
                        *blockPosition = pz_block_position;
                        *creditPosition = overflow.filePosition;

                        return 3;
                    }

                    // load next overflow
                    if(overflow.nextOverflowPosition != -1){
                        Overflow next;
                        readOverflow(overflow.nextOverflowPosition, &next);
                        overflow = next;
                    }else{
                        break;
                    }

                }

            }

    }

    return 99;
}

int searchCreditNextPosition(TFile *file, TreeNode *root, int key, int *blockPosition, int *creditPosition){

    int block = -1;

    TreeNode* result = searchTree(key, root, &block);

    int credit;

    if(block == -1)
        getCreditPosition(file, &block, &credit);

    int pz_block_position = block;
    int i;

    PZBlock pzBlock;

    readPZBlock(file, pz_block_position, &pzBlock);

    for(i=0; i < factorB; i++){

            // check primary zone

            // end
            if(pzBlock.credits[i].record_number == -1){
                *blockPosition = pz_block_position;
                *creditPosition = i;

                return 99;
            }

            // active credit is found
            if(pzBlock.credits[i].record_number == key && pzBlock.credits[i].status == 'a'){

                *blockPosition = pz_block_position;
                *creditPosition = i;

                return 0;
            }
            // inactive credit is found
            if(pzBlock.credits[i].record_number == key && pzBlock.credits[i].status == 'i'){

                *blockPosition = pz_block_position;
                *creditPosition = i;

                return 3;
            }

            if(pzBlock.credits[i].record_number > key){

                *blockPosition = pz_block_position;
                *creditPosition = i;

                return 1;
            }

            // check overflow zone

            if(i == factorB-1 && pzBlock.overflow.filePosition != -1){

                Overflow overflow = pzBlock.overflow;
                int status = 0;

                if(overflow.credit.record_number == key && overflow.credit.status == 'a'){
                    *blockPosition = pz_block_position;
                    *creditPosition = overflow.filePosition;

                    return 0;
                }

                if(overflow.credit.record_number == key && overflow.credit.status == 'i'){
                    *blockPosition = pz_block_position;
                    *creditPosition = overflow.filePosition;

                    return 4;
                }


                // while next overflow exist
                while(overflow.nextOverflowPosition != -1){

                    if(overflow.credit.record_number == key && overflow.credit.status == 'a'){
                        *blockPosition = pz_block_position;
                        *creditPosition = overflow.filePosition;

                        return 0;
                    }

                    if(overflow.credit.record_number == key && overflow.credit.status == 'i'){
                        *blockPosition = pz_block_position;
                        *creditPosition = overflow.filePosition;

                        return 4;
                    }

                    // load next overflow
                    if(overflow.nextOverflowPosition != -1){
                        Overflow next;
                        readOverflow(overflow.nextOverflowPosition, &next);
                        overflow = next;
                    }else{
                        puts("End!");
                    }

                }


                *blockPosition = pz_block_position;
                *creditPosition = overflow.filePosition;

                return 2; // add new credit to overflow


            }

    }

    // if end is not in current block, then it is in next one
    *blockPosition = pz_block_position+1;
    *creditPosition = 0;

    return 99;
}

int getOverflowPosition(){

    int count = 0;

    Overflow overflow;

    while(true){

        readOverflow(count, &overflow);

        if(overflow.filePosition == -1){
            return count;
        }
        count++;
    }

}

int getCreditPosition(TFile *file, int *blockPos, int *creditPos){

    int count = 0;

    PZBlock pzblock;

    while(true){

        readPZBlock(file, count, &pzblock);

        int i;

        for(i=0; i < factorB; i++){

            if(pzblock.credits[i].record_number == -1){

                *blockPos = count;
                *creditPos = i;

                 return 1;
            }

        }

        count++;
    }
}

int addNewCreditInPrimaryZone(TFile *file, TreeNode *root, Credit newCredit){

    int block_pos;
    int credit_pos;

    int status = searchCreditNextPosition(file, root, newCredit.record_number, &block_pos, &credit_pos);

    //printf("status: %d\n", status);
    //printf("block pos: %d\n", block_pos);
    //printf("credi pos: %d\n", credit_pos);

    if(status == 0){
        puts("Credit with that key already exist!");
        return 0;
    }

    // add new credit to end
    if(status == 99){

        PZBlock pz_blockk;
        readPZBlock(file, block_pos, &pz_blockk);

        if(credit_pos != factorB-1){

            pz_blockk.credits[credit_pos] = newCredit;
            pz_blockk.credits[credit_pos+1].record_number = -1; // add end
            savePZBlock(file, block_pos, &pz_blockk);

            return 1;
        }

        if(credit_pos == factorB-1){

            pz_blockk.credits[credit_pos] = newCredit;
            savePZBlock(file, block_pos, &pz_blockk);
            PZBlock newBl;
            newBl.credits[0].record_number = -1;
            Overflow over;
            over.credit.record_number = -1;
            over.filePosition = -1;
            over.nextOverflowPosition = -1;
            newBl.overflow = over;
            savePZBlock(file, block_pos+1, &newBl);

        }

    }

    // add new to overflow zone
    if(status == 2){

        PZBlock pz_blockk;
        readPZBlock(file, block_pos, &pz_blockk);

        Overflow last_over = pz_blockk.overflow;

        while(last_over.nextOverflowPosition != -1){
            readOverflow(last_over.nextOverflowPosition, &last_over);
        }

        int position = last_over.filePosition;

        Overflow new_over;
        new_over.filePosition = position+1;
        new_over.nextOverflowPosition = -1;
        new_over.credit = newCredit;

        saveOverflow(position+1, &new_over);


        last_over.nextOverflowPosition = position+1;
        saveOverflow(position, &last_over);


        Overflow end;

        end.credit.record_number = -1;
        end.filePosition = -1;
        end.nextOverflowPosition = -1;

        saveOverflow(position+2, &end);


    }


    // add between credits in block, shift credits
    if(status == 1){

        PZBlock pz_block;
        readPZBlock(file, block_pos, &pz_block);
        int i;

        Credit temp;

        for(i = credit_pos; i <  factorB; i++){

            temp = pz_block.credits[i];
            pz_block.credits[i] = newCredit;

            if(i == factorB-1){

                // if first overflow don't exist, make it
                if(pz_block.overflow.filePosition == -1 && temp.record_number != -1){

                     int overflowPosition = getOverflowPosition();
                     pz_block.overflow.credit = temp;
                     pz_block.overflow.nextOverflowPosition = -1;
                     pz_block.overflow.filePosition = overflowPosition;
                     savePZBlock(file, block_pos, &pz_block);

                     saveOverflow(overflowPosition, &pz_block.overflow);
                     Overflow end;
                     end.credit.record_number = -1;
                     end.filePosition = -1;
                     end.nextOverflowPosition = -1;

                     saveOverflow(overflowPosition+1, &end);

                    return 1;

                }

                // if first overflow exist, check next overflows
                 if(pz_block.overflow.filePosition != -1 && temp.record_number != -1){

                    // if next overflow don't exist, make it
                    if(pz_block.overflow.nextOverflowPosition == -1){

                        int position = getOverflowPosition();

                        Overflow next;
                        next.credit = temp;
                        next.nextOverflowPosition = -1;
                        next.filePosition = position;

                        saveOverflow(position, &next);

                        Overflow end;
                        end.credit.record_number = -1;
                        end.nextOverflowPosition = -1;
                        end.filePosition = -1;
                        saveOverflow(position+1, &end);

                        pz_block.overflow.nextOverflowPosition = position; // pointer to next overflow

                        savePZBlock(file, block_pos, &pz_block);

                        return 1;

                    }
                    // if next overflow exist, just add new to the end
                    else{

                        Overflow over;
                        readOverflow(pz_block.overflow.nextOverflowPosition, &over);

                        int last_one = pz_block.overflow.nextOverflowPosition;

                        // find last one who does not have next overflow
                        while(over.nextOverflowPosition != -1){
                            last_one = over.nextOverflowPosition;
                            readOverflow(over.nextOverflowPosition, &over);
                        }

                        // save new

                        int position = getOverflowPosition();

                        Overflow newOver;
                        newOver.credit = temp;
                        newOver.nextOverflowPosition = -1;
                        newOver.filePosition = position;

                        saveOverflow(position, &newOver);

                        Overflow end;
                        end.credit.record_number = -1;
                        end.nextOverflowPosition = -1;
                        newOver.filePosition = -1;
                        saveOverflow(position+1, &end);

                        // update last one
                        over.nextOverflowPosition = position;
                        saveOverflow(last_one, &over);

                        savePZBlock(file, block_pos, &pz_block);

                        return 1;

                    }


                }

                // if end is in temp

                if(temp.record_number == -1){

                    savePZBlock(file, block_pos, &pz_block);

                    PZBlock newBlockk;
                    newBlockk.credits[0].record_number = -1;
                    Overflow block_over;
                    block_over.credit.record_number = -1;
                    block_over.filePosition = -1;
                    block_over.nextOverflowPosition = -1;
                    newBlockk.overflow = block_over;

                    savePZBlock(file, block_pos+1, &newBlockk);

                    return 1;
                }


            }

            if(temp.record_number == -1){
                pz_block.credits[i+1] = temp;
                savePZBlock(file, block_pos, &pz_block);
                return 113;
            }

            newCredit = temp;
        }

    }


    // add new credit to inactive credit with same key in primary zone
    if(status == 3){

        PZBlock pz_blockk;
        readPZBlock(file, block_pos, &pz_blockk);

        pz_blockk.credits[credit_pos] = newCredit;

        savePZBlock(file, block_pos, &pz_blockk);

        return 1;

    }

    // add new credit to inactive credit with same key in overflow zone
    if(status == 4){
        Overflow over;
        readOverflow(credit_pos, &over);

        over.credit = newCredit;
        saveOverflow(credit_pos, &over);

        return 1;
    }


    return 0;
}

int searchUsingIndexAndPrimaryZone(TreeNode *root){

    printf("Enter key:");
    int key;
    scanf("%d", &key);

    int block;

    TreeNode* result = searchTree(key, root, &block);

    TFile file;
    file.file = fopen("primary_zone", "rb+");

    PZBlock pz_block;
    readPZBlock(&file, block, &pz_block);

    int i;

    int status = 0;
    int poz = 0;
    int overPos;

    for(i=0; i < factorB; i++){

        if(pz_block.credits[i].record_number == key){
            status = 1;
            poz = i;
        }

    }

    if(pz_block.overflow.filePosition != -1){

        Overflow over = pz_block.overflow;

        if(over.credit.record_number == key){
            status = 2;
            overPos = over.filePosition;
        }

        while(over.nextOverflowPosition != -1){
            readOverflow(over.nextOverflowPosition, &over);

            if(over.credit.record_number == key){
                status = 2;
                overPos = over.filePosition;
            }

        }

    }

    if(status == 2){
         printf("Credit is found in block: %d at overflow zone in position %d \n", block, overPos);
    }

    if(status == 1){
        printf("\nCredit is found in block: %d at position %d \n", block, poz);
        printCredit(pz_block.credits[poz]);
    }
    if(status == 0){
        puts("Credit does not exist!");
    }

    fclose(file.file);

    return 1;
}

int logicalDeleteCredit(TFile *file, TreeNode *root){

    printf("Enter key: ");
    int key;

    scanf("%d", &key);

    int blockPos;
    int creditPos;

    int status = searchCreditPosition(file, root, key, &blockPos, &creditPos);

    if(status == 99){
        puts("Credit with that key don't exist!");
        return 0;
    }

    if(status == 1){

        PZBlock block;

        readPZBlock(file, blockPos, &block);

        if(block.credits[creditPos].status == 'i'){
            puts("Credit is already inactive!");
            return 1;
        }

        block.credits[creditPos].status = 'i';

        savePZBlock(file, blockPos, &block);


    }

    if(status == 3){

        Overflow over;
        readOverflow(creditPos, &over);

        if(over.credit.status == 'i'){
            puts("Credit is already inactive!");
            return 11;
        }

        over.credit.status = 'i';
        saveOverflow(creditPos, &over);

    }


    puts("Credit is successfully deleted!");
    return 0;


}

int reorganization(TFile *file, TreeNode **root){

    int block_count = 0;
    int credit_count = 0;

    PZBlock pz_block;

    int i;

    Credit credits[MAX_CREDITS];

    int status = 0;

    while(status == 0){

        readPZBlock(file, block_count, &pz_block);

        for(i=0; i < factorB; i++){

            if(pz_block.credits[i].record_number == -1){
                credits[credit_count].record_number = -1;
                status = 1;
                break;
            }


            credits[credit_count] = pz_block.credits[i];

            // if first overflow exist
            if(i == factorB-1 && pz_block.overflow.filePosition != -1){

                Overflow overflows = pz_block.overflow;

                credit_count++;
                credits[credit_count] = overflows.credit;


                // if next exist overflows exist
                while(overflows.nextOverflowPosition != -1){

                    readOverflow(overflows.nextOverflowPosition, &overflows);

                    credit_count++;
                    credits[credit_count] = overflows.credit;

                }

            }

            credit_count++;
        }

        block_count++;

    }


    int cnt = 0;
    Credit activeCredits[MAX_CREDITS];

    i = 0;

    // add only active credits
    while(credits[i].record_number != -1){
        if(credits[i].status == 'a'){
            activeCredits[cnt] = credits[i];
            cnt++;
        }

        i++;
    }

    puts("Inactive credits are removed!");

    qsort(activeCredits, cnt, sizeof(Credit), compare);

    TFile new_file;
    printf("Enter new filename:");
    scanf("%s", new_file.fileName);

    new_file.file = fopen(new_file.fileName, "wb+");

    PZBlock block;
    block.credits[0].record_number = -1;
    Overflow over;
    over.credit.record_number = -1;
    over.filePosition = -1;
    over.nextOverflowPosition = -1;
    block.overflow = over;
    savePZBlock(&new_file, 0, &block);

    fclose(new_file.file);

    new_file.file = fopen(new_file.fileName, "rb+");

    *root = NULL;

    PZBlock pz_blockk;

    for(i=0; i < cnt; i++){

        int block_pos;
        int credit_pos;

        getCreditPosition(&new_file, &block_pos, &credit_pos);

        readPZBlock(&new_file, block_pos, &pz_blockk);

        if(credit_pos != factorB-1){

            pz_blockk.credits[credit_pos] = activeCredits[i];
            pz_blockk.credits[credit_pos+1].record_number = -1;
            savePZBlock(&new_file, block_pos, &pz_blockk);

        }

        if(credit_pos == factorB-1){
            pz_blockk.credits[credit_pos] = activeCredits[i];
            savePZBlock(&new_file, block_pos, &pz_blockk);

            PZBlock newBl;
            newBl.credits[0].record_number = -1;
            Overflow over;
            over.credit.record_number = -1;
            over.filePosition = -1;
            over.nextOverflowPosition = -1;
            newBl.overflow = over;
            savePZBlock(&new_file, block_pos+1, &newBl);

        }

    }

    puts("Reorganization is successfully completed!");

    fclose(new_file.file);
    createIndexZone(new_file.fileName, root);

    return 1;

}

int averageCredit(TFile *file){

    int block_count = 0;

    PZBlock pz_block;

    int i;

    int total = 0;
    int n = 0;

    int status = 0;

    while(status == 0){

        readPZBlock(file, block_count, &pz_block);

        for(i=0; i < factorB; i++){

            if(pz_block.credits[i].record_number == -1){
                status = 1;
                break;
            }

            if(pz_block.credits[i].loan_amount > 25000 && pz_block.credits[i].loan_amount < 75000){
                printf("Credit: %d , amount: %d\n", pz_block.credits[i].record_number, pz_block.credits[i].loan_amount);
                total += pz_block.credits[i].loan_amount;
                n++;
            }

            if(i == factorB-1 && pz_block.overflow.filePosition != -1){

                Overflow overflow = pz_block.overflow;

                while(overflow.nextOverflowPosition != -1){

                    if(overflow.credit.loan_amount > 25000 && overflow.credit.loan_amount < 75000){

                        printf("Overflow Credit: %d , amount: %d\n", overflow.credit.record_number, overflow.credit.loan_amount);
                        total += overflow.credit.loan_amount;
                        n++;
                    }

                    readOverflow(overflow.nextOverflowPosition, &overflow);
                }
            }
        }

        block_count++;
    }

    printf("Average: %d\n", total / n);
}


int main()
{

    TFile file;
    file.file = NULL;

    TreeNode *root = NULL;

    int option = 99;


    Credit newCredit;
    newCredit.status = 'a';

    do{

        printf("\n===================\n");
        printf("1. Load data from File\n");
        printf("2. Create a file\n");
        printf("3. Choose a file\n");
        printf("4. Print active file\n");
        printf("5. Add new Credit\n");
        printf("6. Print Credits (serial)\n");
        printf("7. Print Credits (sequential)\n");
        printf("8. Create Sequential file\n");
        printf("9. Create Primary, Overflow and Index Zone\n");
        printf("10. Print Primary And Overflow Zone\n");
        printf("11. Add New in Primary And Overflow Zone\n");
        printf("12. Search Index Zone\n");
        printf("13. Logical Delete from Primary Zone\n");
        printf("14. Reorganization\n");
        printf("15. Average credit amount\n");
        printf("0. Exit\n");
        printf("\n===================\n");

        printf(">>");

        scanf("%d", &option);

        switch(option){

            case 1: loadData(); break;

            case 2: createFile(); break;

            case 3: chooseFile(&file, &root); break;

            case 4: printActiveFile(&file); break;

            case 5: callAddNewCredit(&file); break;

            case 6: printSerial(&file); break;

            case 7: printAllCredits(&file); break;

            case 8: loadSerialAndMakeSequential(&file); break;

            case 9: createPrimaryZoneOverflowIndexZone(&file, &root); break;

            case 10: printPrimaryZone(&file); break;

            case 11:
                    printf("Enter credit id: ");
                    scanf("%d", &newCredit.record_number);

                    printf("Loan amount: ");
                    scanf("%d", &newCredit.loan_amount);

                    addNewCreditInPrimaryZone(&file, root, newCredit);
                    fclose(file.file);
                    createIndexZone(file.fileName, &root);
                    file.file = fopen("primary_zone", "rb+");
                    break;

            case 12: searchUsingIndexAndPrimaryZone(root); break;

            case 13: logicalDeleteCredit(&file, root); break;

            case 14: reorganization(&file, &root);
                     createIndexZone(file.fileName, &root);
                     break;

            case 15: averageCredit(&file); break;


            case 0: exit(EXIT_FAILURE);
        }


    }while(option != 0);

    fclose(file.file);

    puts("End of program!");
    return 0;
}
