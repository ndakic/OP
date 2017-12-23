#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string.h>

typedef char Tizraz[31];
#define MAX_SIZE 30


void ucitaniIobrnutiRedosled(){

    int niz[30];
    int i,n;

    printf("Unesite broj elemanata: ");
    scanf("%d", &n);

    for(i=0; i < n; i++){
        printf("niz[%d]=",i);
        scanf("%d", &niz[i]);
    }

    for(i=0; i < n; i++){
        printf("niz[%d]=%d\n", i, niz[i]);
    }

    for(i=n-1; i >= 0; i--){
        printf("niz[%d]=%d\n", i, niz[i]);
    }
}

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void maksVredISortNiza(){

    int niz[20];
    int i,n;
    int maks = 0;

    printf("Unesite broj elemanata: ");
    scanf("%d", &n);

    for(i=0; i < n; i++){
        printf("niz[%d]=",i);
        scanf("%d", &niz[i]);
    }

    for(i=0; i <n; i++){
       if(maks < niz[i]){
        maks = niz[i];
       }
    }

    qsort (niz, n, sizeof(int), compare);

    printf("Maksimalna vrednost: %d\n", maks);

    for(i=0; i <n; i++){
        printf("niz[%d]=%d\n",i, niz[i]);
    }

}

void dinamickoProsirivanjeNiza(){

    int i = 0;
    char c;
    char *input;

    input = (char *) malloc(sizeof(char));

    if(input == NULL){
        printf("Could not allocate memory!");
        exit(1);
    }

    printf("Input a string, press enter when done: ");
    c = getchar(); // It's because when you press Enter, after answering the first question, the enter key gets stored in the next variable C

    while((c = getchar()) != '\n'){
        realloc(input, (sizeof(char)));
        input[i++] = c;
    }

    input[i] = '\0';
    printf("\nYou entered the string: %s\n", input);

}

struct student{
    char *index;
    char *predmet;
    int ocena;
};

void ispisiStudenta(struct student s){
    printf("\n (%s, %s, %d)", s.index, s.predmet, s.ocena);
}


void prosecnaOcenaStudenata(struct student *studenti, int k){

    int i;
    double suma = 0;
    int n = 0;

    for(i=1; i < k; i++){
        suma = suma + studenti[i].ocena;
        n++;
    }
    printf("\nProsek svih studenata: %fl\n", suma/n);
}

void ucitatiStudente(){

    FILE *file;
    char sadrzaj[100];
    struct student studenti[50];

    file=fopen("studenti.txt", "r");

    int i = 0;

    char *index, *predmet;
    int *ocena;

    if(file != NULL){
        while((fgets(sadrzaj, 100, file)) != NULL){
            index = strtok(sadrzaj, ","); //index
            predmet = strtok(NULL, ",");  // predmet
            ocena = atoi(strtok(NULL, ","));  // ocena

            studenti[i].index = index;
            studenti[i].predmet = predmet;
            studenti[i].ocena = ocena;

            i++;

        }
    }

    for(i = 1; i < 4; i++){
        ispisiStudenta(studenti[i]);
    }

    prosecnaOcenaStudenata(studenti, i);

}

void prebrojReci(char *nazivFajla){

    FILE *file;
    char sadrzaj[100];

    file=fopen(nazivFajla, "r");

    int i = 0;
    int najduza = 0;
    char *rec;

    if(file != NULL){
        while((fgets(sadrzaj, 100, file)) != NULL){

            rec = strtok(sadrzaj, " ");
            while(rec != NULL){
                printf("%s\n", rec);
                int duz = strlen(rec);
                rec = strtok(NULL, " ");
                i++;

                if(najduza < duz){
                    najduza = duz;
                }
            }
        }
    }

    printf("Broj reci u fajlu: %d\n", i);
    printf("Najduza rec ima %d slova.\n", najduza);

}


int main()
{

    int n, opcija;

    do{
        printf("Opcije:\n");
        printf("\t 1 - Unos elemenata\n ");
        printf("\t 2 - Izracunavanje sume\n ");
        printf("\t 3 - Dinamisko prosirivanje niza\n ");
        printf("\t 4 - Ucitavanje studenata \n ");
        printf("\t 5 - Prebroj reci iz fajla \n ");
        printf("\t 0 - Izlaz iz programa\n ");
        printf("\t >> ");

        scanf("%d", &opcija);

        switch(opcija){
            case 1: ucitaniIobrnutiRedosled(); break;
            case 2: maksVredISortNiza(); break;
            case 3: dinamickoProsirivanjeNiza(); break;
            case 4: ucitatiStudente(); break;
            case 5: prebrojReci("reci.txt"); break;
        }

    }while(opcija != 0);


    return 0;
}


