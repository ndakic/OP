#include <stdio.h>
#include <stdlib.h>

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

    printf("block sacuvan na poziciju: %d\n", blockPosition);

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


    printf("Prekoracioc sacuvan na poziciji : %d\n", overflowPosition);

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
        printf("kljuc: %d\n", temp->key);
        *block = temp->block_address;
    }

    if(temp == NULL || temp->key == key){

        if(temp == NULL){
            empty->block_address = block;
            empty->key = -1;
            puts("empty");
            return empty;
        }else{
            puts("temp");
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


    //printf("Cvor sacuvan na poziciji : %d\n", nodePosition);

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

    Block block;
    block.credits[0].record_number = -1;

    saveBlock(&file, 0, &block);

    fclose(file.file);

    puts("File is successfully created!");


}

void chooseFile(TFile *file, TreeNode **root){

    printf("Enter filename: ");
    scanf("%s", file->fileName);

    // load balanced binary tree
    if(strcmp(file->fileName, "primary_zone") == 0){

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

    addNewCredit(file, credit);

}

int addNewCredit(TFile *file, Credit new_credit){

    int block_position = 0;
    int credit_position;

    int status = searchSerial(file, new_credit.record_number, &block_position, &credit_position);

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

         puts("Credit successfully added!");

    }

}


// ====================== PRINT ================================= //

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

void printOverflow(Overflow overflow){

    printf("Record Number: %d\n", overflow.credit.record_number);
    printf("Name: %s\n", overflow.credit.name);
    printf("Date: %s\n", overflow.credit.date);
    printf("Loan Amount: %d\n", overflow.credit.loan_amount);
    printf("Loan Interest: %d\n", overflow.credit.interest);
    printf("Number of Installments: %d\n", overflow.credit.installments);
    printf("File position: %d\n", overflow.filePosition);
    printf("Next position: %d\n", overflow.nextOverflowPosition);
    printf("Status: %c\n", overflow.credit.status);




}

int printAllCredits(TFile *file){

    if(file->file == NULL){
        puts("First choose file!");
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

    Block block;

    while(status == 0){

        readBlock(file, block_position, &block);

        for(i=0; i < factorB; i++){

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
        addNewCredit(&new_file, credits[i]);
    }

    fclose(new_file.file);

    puts("Sequential file successfully created!");

    return 1;

}

int printPrimaryZone(TFile *file){

    /*
    if(strcmp(file->fileName, "primary_zone") != 0 || strcmp(file->fileName, "reorg") != 0){

        puts("Choose primary zone!");
        return;
    }
    */

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

        puts("-------------------------------------------------------");
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

        //printf("blok poz: %d\n", block_pos);

        readPZBlock(&pzFile, block_pos, &blockPZ);

        //printf("blok: %d, prva pozicija: %d\n",block_pos, blockPZ.credits[0].record_number);
        //printf("blok: %d, psoeldnja pozicija: %d\n",block_pos, blockPZ.credits[2].record_number);

        for(i=0; i < factorB; i++){

            // ako se doslo do kraja,
            if(blockPZ.credits[i].record_number == -1 && i != 0){
                puts("2222");
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

            // ako se doslo do kraja, samo dodaj kraj
            if(blockPZ.credits[i].record_number == -1 && i == 0){
                index_status = 1;
                puts("sadasd");
                TreeNode end;
                end.key = -1;
                end.block_address = -1;
                end.file_position = -1;
                //block_pos++;
                nodes[block_pos] = end;
                break;
            }

            if(blockPZ.credits[i].record_number > credit.record_number){
                credit = blockPZ.credits[i];
            }

            if(blockPZ.overflow.filePosition != -1){
                printf("test: %d\n", i);
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
        printf("Najveci elem. bloka: %d je %d\n", nodes[i].block_address, nodes[i].key);
        saveTreeNode(&nodeFile, i, &nodes[i]);
    }

    puts("11");
    TreeNode *p;
    p = bst(nodes, 0, n-1);
    puts("12");
    *root = p;

    TreeNode end;
    end.block_address = -1;
    end.file_position = -1;
    end.key = -1;
    puts("13");
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
                overflow.nextOverflowPosition = -1; // nepostoji sledeci prekoracilac
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
                overflow.nextOverflowPosition = -1; // nepostoji sledeci prekoracilac
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

    // create index zone
    printf("Unesite naziv zone indeksa: ");
    char fileName[FILENAME_MAX];
    scanf("%s", fileName);
    createIndexZone(fileName, root);


}

int searchCreditPosition(TFile *file, TreeNode *root, int key, int *blockPosition, int *creditPosition){

    int block;

    TreeNode* result = searchTree(key, root, &block);

    printf("blocka: %d\n", block);

    int pz_block_position = block;
    int i;

    PZBlock pzBlock;

    readPZBlock(file, pz_block_position, &pzBlock);

    for(i=0; i < factorB; i++){

            // provera primarne zone

            // pronadjen tacan kredit (za potrebe brisanja i pretrage recimo)
            if(pzBlock.credits[i].record_number == key){
                puts("Kredit je nadjen!");

                *blockPosition = block;
                *creditPosition = i;

                return 1;
            }


            // provera zone prekoracioca

            if(i == factorB-1 && pzBlock.overflow.filePosition != -1){

                Overflow overflow = pzBlock.overflow;
                int status = 0;

                if(overflow.credit.record_number == key){
                    *blockPosition = pz_block_position;
                    *creditPosition = overflow.filePosition;

                    return 3;
                }

                //dokle god postoji sledeci prekoracioc
                while(overflow.nextOverflowPosition != -1){

                    if(overflow.credit.record_number == key){
                        *blockPosition = pz_block_position;
                        *creditPosition = overflow.filePosition;

                        return 3;
                    }

                    // ucitati sledeceg prekoracioca
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

    int block;

    TreeNode* result = searchTree(key, root, &block);

    printf("blocka: %d\n", block);

    int pz_block_position = block;
    int i;

    PZBlock pzBlock;

    readPZBlock(file, pz_block_position, &pzBlock);

    for(i=0; i < factorB; i++){

            // provera primarne zone

            printf("key: %d\n", pzBlock.credits[i].record_number);

            // naisao na kraj
            if(pzBlock.credits[i].record_number == -1){
                puts("krajj!");
                *blockPosition = pz_block_position;
                *creditPosition = i;

                return 99;

            }

            // pronadjen tacan kredit (za potrebe brisanja i pretrage recimo)
            if(pzBlock.credits[i].record_number == key){
                puts("Kredit je nadjen!");

                *blockPosition = pz_block_position;
                *creditPosition = i;

                return 0; // ne sme da postoji kredit sa istim kljucem
            }

            if(pzBlock.credits[i].record_number > key){

                *blockPosition = pz_block_position;
                *creditPosition = i;

                return 1;
            }


            // provera zone prekoracioca

            if(i == factorB-1 && pzBlock.overflow.filePosition != -1){

                Overflow overflow = pzBlock.overflow;
                int status = 0;

                if(overflow.credit.record_number == key){
                    *blockPosition = pz_block_position;
                    *creditPosition = overflow.filePosition;

                    return 0; // ne sme da postoji kredit sa istim kljucem
                }

                if(overflow.credit.record_number > key){
                    *blockPosition = pz_block_position;
                    *creditPosition = overflow.filePosition;

                    return 2;
                }

                //dokle god postoji sledeci prekoracioc
                while(overflow.nextOverflowPosition != -1){

                    if(overflow.credit.record_number > key){
                        *blockPosition = pz_block_position;
                        *creditPosition = overflow.filePosition;

                        return 2;
                    }

                    // ucitati sledeceg prekoracioca
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

    // ako nema kraja u zadnjem bloku, onda je u sledecem na prvom mestu
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
            printf("count: %d\n", count);
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

    printf("status: %d\n", status);

    printf("block pos: %d\n", block_pos);
    printf("credi pos: %d\n", credit_pos);


    if(status == 0){
        puts("Kredit sa tim kljucem vec postoji!");
        return 0;
    }

    // dodavanje na kraj
    if(status == 99){

        puts("na kraj");


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

    // ako se prvi veci kljuc nalazi u zoni prekoracioca
    if(status == 2){

        puts("prekoraciocii!");
    }


    // ako treba negde izmedju da se uglavi
    if(status == 1){

        PZBlock pz_block;
        readPZBlock(file, block_pos, &pz_block);
        int i;

        Credit temp;

        for(i = credit_pos; i <  factorB; i++){

            temp = pz_block.credits[i];

            pz_block.credits[i] = newCredit;

            printf("i: %d, temp: %d\n",i,  temp.record_number);

            if(i == factorB-1){
                puts("123");
                // ako ne postoji prvi prekoracioc u tom bloku - postavi novi
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


                    return 22;

                }

                // ako postoji prvi prekoracioc, proveriti sledece preoracioce
                 if(pz_block.overflow.filePosition != -1 && temp.record_number != -1){

                    puts("$$$$$");
                    // ako nema sledeceg, dodaj novi kao sledeci
                    if(pz_block.overflow.nextOverflowPosition == -1){


                        int pozicija = getOverflowPosition();

                        Overflow next;
                        next.credit = temp;
                        next.nextOverflowPosition = -1;
                        next.filePosition = pozicija;

                        saveOverflow(pozicija, &next);

                        Overflow end;
                        end.credit.record_number = -1;
                        end.nextOverflowPosition = -1;
                        end.filePosition = -1;
                        saveOverflow(pozicija+1, &end);

                        pz_block.overflow.nextOverflowPosition = pozicija; // pokazivac na sledeci

                        savePZBlock(file, block_pos, &pz_block);

                        return 213;

                    }
                    // ako ima sledeci, njemu dodaj sledeci
                    else{

                        puts("aaaa");

                        printf("pos: %d\n", pz_block.overflow.nextOverflowPosition);

                        Overflow over;
                        readOverflow(pz_block.overflow.nextOverflowPosition, &over);

                        printf("over: %d\n", over.nextOverflowPosition);



                        int last_one = pz_block.overflow.nextOverflowPosition;

                        // naci poslednji koji nema sledeceg
                        while(over.nextOverflowPosition != -1){
                            last_one = over.nextOverflowPosition;
                            puts("asadasdasd12312312312");
                            readOverflow(over.nextOverflowPosition, &over);
                            puts("Srbija!!");
                        }


                        // sacuvaj novi prekoracilac
                        int pozicija = getOverflowPosition();
                        //return 1111;
                        Overflow newOver;
                        newOver.credit = temp;
                        newOver.nextOverflowPosition = -1;
                        newOver.filePosition = pozicija;

                        saveOverflow(pozicija, &newOver);

                        Overflow end;
                        end.credit.record_number = -1;
                        end.nextOverflowPosition = -1;
                        newOver.filePosition = -1;
                        saveOverflow(pozicija+1, &end);

                        // izmeni prethodni
                        over.nextOverflowPosition = pozicija;
                        saveOverflow(last_one, &over);

                        savePZBlock(file, block_pos, &pz_block);

                        return 4;

                    }


                }

                // ako se u tempu nalazi kraj

                if(temp.record_number == -1){

                    puts("ASrbijasadasd");

                    savePZBlock(file, block_pos, &pz_block);

                    PZBlock newBlockk;
                    newBlockk.credits[0].record_number = -1;
                    Overflow block_over;
                    block_over.credit.record_number = -1;
                    block_over.filePosition = -1;
                    block_over.nextOverflowPosition = -1;
                    newBlockk.overflow = block_over;

                    savePZBlock(file, block_pos+1, &newBlockk);

                    return 11;
                }


            }

            if(temp.record_number == -1){
                puts("444");
                pz_block.credits[i+1] = temp;
                savePZBlock(file, block_pos, &pz_block);
                return 113;
            }

            newCredit = temp;
        }

    }



    return 123;
}


int searchUsingIndexAndPrimaryZone(TreeNode *root){

    printf("Unesite kljuc:");
    int key;
    scanf("%d", &key);

    int block;

    TreeNode* result = searchTree(key, root, &block);

    printf("bloccck: %d\n", block);

    TFile file;
    file.file = fopen("primary_zone", "rb+");

    PZBlock pz_block;
    readPZBlock(&file, block, &pz_block);

    int i;

    int status = 0;
    int poz = 0;
    int prekPoz;

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
            prekPoz = over.filePosition;
        }

        while(over.nextOverflowPosition != -1){
            readOverflow(over.nextOverflowPosition, &over);

            if(over.credit.record_number == key){
                status = 2;
                prekPoz = over.filePosition;
            }

        }

    }

    if(status == 2){
         printf("Kredit je pronadjen u bloku: %d i nalazi se u prekoraciocima na poziciji %d \n", block, prekPoz);
    }

    if(status == 1){
        printf("Kredit je pronadjen u bloku: %d na poziciji %d \n", block, poz);
    }
    if(status == 0){
        puts("Ne postoji trazeni kredit!");
    }

    fclose(file.file);

    return 11;
}

int logicalDeleteCredit(TFile *file, TreeNode *root){

    printf("Unesite kljuc: ");
    int key;

    scanf("%d", &key);

    int blockPos;
    int creditPos;

    int status = searchCreditPosition(file, root, key, &blockPos, &creditPos);

    printf("status: %d\n", status);
    printf("bl: %d, cre: %d\n", blockPos, creditPos);


    if(status == 99){
        puts("Ne postoji kredit sa tim kljucem!");
        return 0;
    }

    if(status == 1){

        PZBlock block;

        readPZBlock(file, blockPos, &block);

        block.credits[creditPos].status = 'i';

        savePZBlock(file, blockPos, &block);


    }


    if(status == 2){
        puts("Prekoracioc!");
    }



    puts("Kredit je uspesno obrisan!");
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
                status = 1;
                break;
            }

            credits[credit_count] = pz_block.credits[i];

            // ako postoji prvi prekoracioc
            if(i == factorB-1 && pz_block.overflow.filePosition != -1){

                Overflow overflows = pz_block.overflow;

                credit_count++;
                credits[credit_count] = overflows.credit;


                // ako postoje ostali

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


    puts("End!!");

    qsort(credits, credit_count, sizeof(Credit), compare);

    TFile new_file;
    printf("Unesite naziv novog fajla:");
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

    //createIndexZone(new_file.fileName, root);

    new_file.file = fopen(new_file.fileName, "rb+");

    *root = NULL;

    PZBlock pz_blockk;

    for(i=0; i < credit_count; i++){
        //printCredit(credits[i]);

        int block_pos;
        int credit_pos;

        getCreditPosition(&new_file, &block_pos, &credit_pos);

        readPZBlock(&new_file, block_pos, &pz_blockk);

        if(credit_pos != factorB-1){

            pz_blockk.credits[credit_pos] = credits[i];
            pz_blockk.credits[credit_pos+1].record_number = -1;
            savePZBlock(&new_file, block_pos, &pz_blockk);

        }



        if(credit_pos == factorB-1){
            pz_blockk.credits[credit_pos] = credits[i];
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

    puts("Reorganizacije je zavrsena!");

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

    printf("Prosek: %d\n", total / n);
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
        printf("1. Create a file\n");
        printf("2. Choose a file\n");
        printf("3. Print active file\n");
        printf("4. Add new Credit\n");
        printf("5. Print all Credits\n");
        printf("6. Create Sequential file\n");
        printf("7. Create Primary, Overflow and Index Zone\n");
        printf("8. Print Primary And Overflow Zone\n");
        printf("9. Add New in Primary And Overflow Zone\n");
        printf("10. Search Index Zone\n");
        printf("11. Logical Delete from Primary Zone\n");
        printf("12. Reorganization\n");
        printf("13. Average credit amount\n");
        printf("0. Exit\n");
        printf("\n===================\n");

        printf(">>");

        scanf("%d", &option);

        switch(option){
            case 1: createFile(); break;

            case 2: chooseFile(&file, &root); break;

            case 3: printActiveFile(&file); break;

            case 4: callAddNewCredit(&file); break;

            case 5: printAllCredits(&file); break;

            case 6: loadSerialAndMakeSequential(&file); break;

            case 7: createPrimaryZoneOverflowIndexZone(&file, &root); break;

            case 8: printPrimaryZone(&file); break;

            case 9:
                    printf("Enter credit id: ");
                    scanf("%d", &newCredit.record_number);

                    printf("Loan amount: ");
                    scanf("%d", &newCredit.loan_amount);

                    addNewCreditInPrimaryZone(&file, root, newCredit);
                    fclose(file.file);
                    createIndexZone(file.fileName, &root);
                    file.file = fopen("primary_zone", "rb+");
                    break;

            case 10: searchUsingIndexAndPrimaryZone(root); break;

            case 11: logicalDeleteCredit(&file, root); break;

            case 12: reorganization(&file, &root); break;

            case 13: averageCredit(&file); break;

            case 0: exit(EXIT_FAILURE);
        }


    }while(option != 0);

    fclose(file.file);

    puts("End of program!");
    return 0;
}
