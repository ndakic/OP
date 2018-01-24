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
        puts("Seek Error!");

    status = fread(block, sizeof(Block), 1, file->file);
    if(status != 1)
        puts("Read Error!");
}

void savePZBlock(TFile *file, int blockPosition, PZBlock *pz_block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(PZBlock), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fwrite(pz_block, sizeof(PZBlock), 1, file->file);
    if(status != 1)
        puts("Write Error!");

    printf("block sacuvan na poziciju: %d\n", blockPosition);

}

void readPZBlock(TFile *file, int blockPosition, PZBlock *pz_block){

    int status;

    status = fseek(file->file, blockPosition * sizeof(PZBlock), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fread(pz_block, sizeof(PZBlock), 1, file->file);
    if(status != 1)
        puts("Read Error!");
}

void readOverflow(int overflowPosition, Overflow *overflow){

    TFile file;
    file.file = fopen("overflows", "rb+");

    int status;

    status = fseek(file.file, overflowPosition * sizeof(Overflow), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fread(overflow, sizeof(Overflow), 1, file.file);
    if(status != 1)
        puts("Read Error!");

     fclose(file.file);
}

void saveOverflow(int overflowPosition, Overflow *overflow){

    TFile file;
    file.file = fopen("overflows", "rb+");

    int status;

    status = fseek(file.file, overflowPosition * sizeof(Overflow), SEEK_SET);
    if(status != 0)
        puts("Seek Error!");

    status = fwrite(overflow, sizeof(Overflow), 1, file.file);
    if(status != 1)
        puts("Write Error!");


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


    printf("Cvor sacuvan na poziciji : %d\n", nodePosition);

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

        TreeNode node;
        int count_pos = 0;
        int status = 0;

        TFile file;
        file.file = fopen("treeNodes", "rb+");

        TreeNode nodes[20];
        while(status == 0){

            readTreeNode(&file, count_pos, &node);

            if(node.key == -1){
                status = 1;
                break;
            }

            nodes[count_pos] = node;
            printf("tree nodes: %d\n", nodes[count_pos].key);
            count_pos++;

        }

        fclose(file.file);

        int n = count_pos;

        TreeNode *p;
        p = bst(nodes, 0, n-1);

        *root = p;

        printf("root: %d\n", p->key);

        puts("Tree is loaded!");

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

    puts("-------------------------------------------------------");
    puts("--------------------OVERFLOW CREDIT--------------------");
    puts("-------------------------------------------------------");
    printf("Record Number: %d\n", overflow.credit.record_number);
    printf("Name: %s\n", overflow.credit.name);
    printf("Date: %s\n", overflow.credit.date);
    printf("Loan Amount: %d\n", overflow.credit.loan_amount);
    printf("Loan Interest: %d\n", overflow.credit.interest);
    printf("Number of Installments: %d\n", overflow.credit.installments);
    printf("Status: %c\n", overflow.credit.status);
    puts("-------------------------------------------------------");
    puts("---------------------END-------------------------------");
    puts("-------------------------------------------------------");

    if(overflow.nextOverflowPosition != -1){

        Overflow next;
        int position = overflow.nextOverflowPosition;

        while(true){

            readOverflow(position, &next);
            printCredit(next.credit);


            if(next.nextOverflowPosition == -1){
                return;
            }

            position = next.nextOverflowPosition;

        }

    }



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

    if(strcmp(file->fileName, "primary_zone") != 0){

        puts("Choose primary zone!");
        return;
    }

    int pz_block_position = 0;
    int i;

    PZBlock pzBlock;

    while(true){

        readPZBlock(file, pz_block_position, &pzBlock);

        for(i=0; i < factorB; i++){

            if(pzBlock.credits[i].record_number == -1){
                puts("Kraj");
                return 11;
            }

            puts("-------------------------------------------------------");
            printf("Block position: %d, credit position: %d\n", pz_block_position+1, i+1);
            printCredit(pzBlock.credits[i]);
        }
        printOverflow(pzBlock.overflow);
        pz_block_position++;

    }

}

// ===================== Index-Sequential ========================= //

int searchNextPositionForSavingOverflow(){

    TFile file;
    file.file = fopen("overflows", "rb+");

    int position = 0;

    Overflow overflow;

    while(true){

        readOverflow(position, &overflow);

        if(overflow.credit.record_number == -1){

            fclose(file.file);
            return position;
        }

        position++;
    }
}

void createIndexZone(TreeNode **root){

    TFile pzFile;
    pzFile.file = fopen("primary_zone", "rb+");

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

            // ako se doslo do kraja,
            if(blockPZ.credits[i].record_number == -1 && i != 0){

                TreeNode node;
                node.key = credit.record_number;
                node.block_address = block_pos;

                nodes[block_pos] = node;
                index_status = 1;

                TreeNode end;
                end.key = -1;
                end.block_address = -1;
                block_pos++;
                nodes[block_pos] = end;

                break;

            }

            // ako se doslo do kraja, samo dodaj kraj
            if(blockPZ.credits[i].record_number == -1){
                index_status = 1;

                TreeNode end;
                end.key = -1;
                end.block_address = -1;
                block_pos++;
                nodes[block_pos] = end;
                break;
            }

            if(blockPZ.credits[i].record_number > credit.record_number){
                credit = blockPZ.credits[i];
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

    createIndexZone(root);


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

/*
int addNewCreditInPrimaryZone(TFile *file, TreeNode *root, TreeNode **root2){

    // proveriti pretragom stabla da li vec postoji

    Credit newCredit;

    printf("Enter credit id: ");
    scanf("%d", &newCredit.record_number);

    int block_pos;
    int credit_pos;

    int status = searchCreditPosition(file, root, newCredit.record_number, &block_pos, &credit_pos);

    printf("status: %d\n", status);

    printf("block pos: %d\n", block_pos);
    printf("credi pos: %d\n", credit_pos);

    if(status == 5){

        PZBlock pz_block;
        readPZBlock(file, block_pos+1, &pz_block);
        credit_pos = 0;

        if(pz_block.credits[credit_pos].record_number == -1){

            puts("aaa");

            Credit temp = pz_block.credits[credit_pos];

            pz_block.credits[credit_pos] = newCredit;

            pz_block.credits[credit_pos+1] = temp;

            savePZBlock(file, block_pos+1, &pz_block);
            //createIndexZone(root2);
            return 12;

        }

    }


    if(status == 0){

        PZBlock pz_block;
        readPZBlock(file, block_pos, &pz_block);

        Credit temp = pz_block.credits[credit_pos];

        printf("temp: %d\n", temp.record_number);

        pz_block.credits[credit_pos] = newCredit;

        printf("current: %d\n", pz_block.credits[credit_pos].record_number);

        if(credit_pos == factorB-1){

            savePZBlock(file, block_pos, &pz_block);

            PZBlock new_block;
            new_block.credits[0] = temp;
            new_block.overflow.credit.record_number = -1;
            new_block.overflow.next.block_address = -1;
            savePZBlock(file, block_pos+1, &new_block);

            puts("Dovde doslo!");
            //createIndexZone(root2);
            return 44;
        }

        pz_block.credits[credit_pos+1] = temp;

        savePZBlock(file, block_pos, &pz_block);
        createIndexZone(root2);
        return 112;

    }


    if(status == 4){

        PZBlock pz_block;
        readPZBlock(file, block_pos, &pz_block);
        int i;

        Credit temp;

        for(i = credit_pos; i <factorB; i++){

            temp = pz_block.credits[i];

            pz_block.credits[i] = newCredit;


            newCredit = temp;


             if(temp.record_number == -1 && i == factorB-1){

                saveBlock(file, block_pos, &pz_block);

                PZBlock new_block;
                new_block.credits[0].record_number = -1;
                new_block.overflow.credit.record_number = -1;
                new_block.overflow.next.block_address = -1;
                saveBlock(file, block_pos+1, &new_block);
                puts("aloo");
                createIndexZone(root2);
                return 13;

             }

             if(temp.record_number == -1 && i != factorB-1){

                pz_block.credits[i+1].record_number = -1;

                saveBlock(file, block_pos, &pz_block);
                puts("alo12");
                createIndexZone(root2);
                return 11;

             }
        }

    }


    if(status == 1){

        PZBlock pz_block;
        readPZBlock(file, block_pos, &pz_block);
        int i;

        Credit temp;

        for(i = credit_pos; i <  factorB; i++){

            temp = pz_block.credits[i];

            pz_block.credits[i] = newCredit;


            if(i == factorB-1){

                // ako ne postoji prvi prekoracioc u tom bloku - postavi novi
                if(pz_block.overflow.credit.record_number == -1){

                     pz_block.overflow.credit = temp;
                     pz_block.overflow.next.block_address = -1;
                     savePZBlock(file, block_pos, &pz_block);

                    return 22;

                }
                // ako postoji prvi prekoracioc, proveriti sledece preoracioce
                else{
                    // ako nema sledeceg, dodaj novi kao sledeci
                    if(pz_block.overflow.next.block_address == -1){

                        Overflow next;
                        next.credit = temp;
                        next.next.block_address = -1;

                        int pozicija = searchNextPositionForSavingOverflow();
                        saveOverflow(pozicija, &next);

                        Overflow end;
                        end.credit.record_number = -1;
                        end.next.block_address = -1;
                        saveOverflow(pozicija+1, &end);

                        pz_block.overflow.next.block_address = pozicija; // pokazivac na sledeci

                        savePZBlock(file, block_pos, &pz_block);

                        return 213;

                    }
                    // ako ima sledeci, njemu dodaj sledeci
                    else{

                        Overflow over;
                        readOverflow(pz_block.overflow.next.block_address, &over);

                        int last_one = pz_block.overflow.next.block_address;

                        // naci poslednji koji nema sledeceg
                        while(over.next.block_address != -1){
                            last_one = over.next.block_address;
                            readOverflow(over.next.block_address, &over);
                        }

                        // sacuvaj novi prekoracilac
                        int pozicija = searchNextPositionForSavingOverflow();
                        Overflow newOver;
                        newOver.credit = temp;
                        newOver.next.block_address = -1;

                        saveOverflow(pozicija, &newOver);

                        Overflow end;
                        end.credit.record_number = -1;
                        end.next.block_address = -1;
                        saveOverflow(pozicija+1, &end);

                        // izmeni prethodni
                        over.next.block_address = pozicija;
                        saveOverflow(last_one, &over);

                        Overflow test;
                        readOverflow(last_one, &test);

                        savePZBlock(file, block_pos, &pz_block);

                        return 4;

                    }

                }

            }

            newCredit = temp;
        }

        //savePZBlock(file, block_pos, &pz_block);
        puts("Blok sacuvan!");

    }

    return 123;
}

*/

int searchUsingIndexAndPrimaryZone(TreeNode *root){

    printf("Unesite kljuc:");
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

    for(i=0; i < factorB; i++){

        if(pz_block.credits[i].record_number == key){
            status = 1;
            poz = i;
        }

    }

    if(status == 1){
        printf("Kredit je pronadjen u bloku: %d na poziciji %d \n", block, poz);
    }else{
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

int reorganization(TFile *file){

    int block_count = 0;

    PZBlock pz_block;

    int i;

    while(true){


        readPZBlock(file, block_count, &pz_block);

        for(i=0; i < factorB; i++){

            if(pz_block.credits[i].record_number == -1){
                puts("Reorganizacije je zavrsena!");
                return 1;
            }

            //addNewCreditInPrimaryZone()

        }


    }



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

            if(pz_block.credits[i].loan_amount > 25000 && pz_block.credits[i].loan_amount < 750000){
                printf("Credit: %d , amount: %d\n", pz_block.credits[i].record_number, pz_block.credits[i].loan_amount);
                total += pz_block.credits[i].loan_amount;
                n++;
            }

            if(i == factorB-1 && pz_block.overflow.filePosition != -1){
                printf("Overflow Block: %d\n", block_count);
                printf("Overflow Credit: %d , amount: %d\n", pz_block.overflow.credit.record_number, pz_block.overflow.credit.loan_amount);

                Overflow overflow = pz_block.overflow;

                while(overflow.nextOverflowPosition != -1){

                    if(overflow.credit.loan_amount > 25000 && overflow.credit.loan_amount < 750000){

                        printf("Credit: %d , amount: %d\n", overflow.credit.record_number, overflow.credit.loan_amount);
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

            //case 9: addNewCreditInPrimaryZone(&file, root, &root); break;

            case 10: searchUsingIndexAndPrimaryZone(root); break;

            case 11: logicalDeleteCredit(&file, root); break;

            case 12: reorganization(&file); break;

            case 13: averageCredit(&file); break;

            case 0: exit(EXIT_FAILURE);
        }


    }while(option != 0);

    puts("End of program!");
    return 0;
}
