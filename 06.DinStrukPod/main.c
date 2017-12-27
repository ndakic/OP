#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BRINDEKSA_SIZE 11
#define IME_SIZE 21
#define PREZIME_SIZE 21

typedef struct student{

    char ime[IME_SIZE];
    char prezime[PREZIME_SIZE];
    char brIndeksa[BRINDEKSA_SIZE];
    int godUpisa;
    struct student *next;

}TStudent;


void prikazStudenata(TStudent *glava){

    puts("\nPRIKAZ STUDENATA");
    puts("-------------------------");

    while(glava){
        printf("Student: %s %s %s %d \n", glava->ime, glava->prezime, glava->brIndeksa, glava->godUpisa);
        glava = glava->next;
    }

    puts("-------------------------");

}

int brojStudenata(TStudent *glava){

    int brojStd = 0;

    while(glava){
        brojStd++;
        glava = glava->next;
    }

    return brojStd;
}

int checkIndex(TStudent *glava, char *index){

    int status;

    while(glava){

        if(strcmp(glava->brIndeksa, index) == 0){
           status = 1;
        }

        glava = glava->next;
    }

    return status;

}


void dodajStudenta(TStudent **glava, char *ime, char *prezime, char *brIndeksa, int godUpisa, int pozicija){


    int check = checkIndex(*glava, brIndeksa);

    if((pozicija >=0) && (pozicija<=brojStudenata(*glava)+1) && check != 1){
        int i;

        TStudent *noviS = (TStudent*) malloc(sizeof(TStudent));
        TStudent *tekuci = *glava, *prethodni = *glava;
        strcpy(noviS->ime, ime);
        strcpy(noviS->prezime, prezime);
        strcpy(noviS->brIndeksa, brIndeksa);
        noviS->godUpisa = godUpisa;
        noviS->next = NULL;

        for(i=0; i < pozicija; i++){
            prethodni = tekuci;
            tekuci = tekuci->next;
        }

        noviS->next=tekuci;
        if(tekuci == *glava){
            *glava = noviS;
        }

        else
            prethodni->next = noviS;
    }

}

void dodajStudentaNaKraj(TStudent **glava, char *ime, char *prezime, char *brIndeksa, int godUpisa){

    TStudent *noviS = (TStudent*) malloc(sizeof(TStudent));
    TStudent *tekuci = *glava, *prethodni = *glava;

    strcpy(noviS->ime, ime);
    strcpy(noviS->prezime, prezime);
    strcpy(noviS->brIndeksa, brIndeksa);
    noviS->godUpisa = godUpisa;
    noviS->next = NULL;

    while(tekuci){
        prethodni = tekuci;
        tekuci = tekuci->next;
    }

    if(*glava == NULL)
        *glava = noviS;
    else
        prethodni->next = noviS;

}


void brisanjeStudenta(TStudent **glava, char *brIndexa){

    TStudent *trenutni = *glava;
    TStudent *prethodni = *glava;
    TStudent *temp = NULL;

    while(trenutni){

        if(!strcmp(trenutni->brIndeksa, brIndexa)){
            temp = trenutni;

            trenutni = trenutni->next;
            if(temp == *glava){
                *glava = (*glava)->next;
            }else{
                prethodni->next = trenutni;
            }
            free(temp);
        }else{
            prethodni = trenutni;
            trenutni = trenutni->next;
        }
    }
}

void obrisiSveStudente(TStudent **glava){

    TStudent *temp;

    while(*glava){
        temp = *glava;
        *glava = (*glava)->next;
        free(temp);
    }

}


void ucitajStudenteIzFajla(TStudent **glava){

    FILE *f = fopen("studenti.txt", "r");
    char ime[IME_SIZE], prezime[PREZIME_SIZE], brindeks[BRINDEKSA_SIZE];
    int godUpisa;

    while(fscanf(f, "%s %s %s %d", ime, prezime, brindeks, &godUpisa) != EOF)
        dodajStudenta(glava,ime, prezime, brindeks,godUpisa, brojStudenata(*glava));

    fclose(f);

}


int main()
{

    TStudent *glava = NULL;

    dodajStudenta(&glava, "nikola5", "dakic", "SW55", 2017, 0);
    dodajStudentaNaKraj(&glava, "nikola6", "dakic", "SW56", 2017);
    dodajStudenta(&glava, "nikola7", "dakic", "SW57", 2017, 1);
    dodajStudenta(&glava, "nikola8", "dakic", "SW58", 2017, 2);
    dodajStudenta(&glava, "nikola8", "dakic", "SW58", 2017, 3);

    brisanjeStudenta(&glava, "SW57");

    prikazStudenata(glava);

    int brStud1 = brojStudenata(glava);
    printf("Broj studenata: %d\n", brStud1);

    obrisiSveStudente(&glava);

    int brStud2 = brojStudenata(glava);
    printf("Broj studenata: %d\n", brStud2);

    ucitajStudenteIzFajla(&glava);

    prikazStudenata(glava);

    printf("\nEnd!");
    return 0;
}
