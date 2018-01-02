#include <stdio.h>
#include <stdlib.h>

#define faktorBlok 3

typedef struct{
    FILE *file;
    char nazivDatoteke[20];
}Datoteka;

typedef struct{
    int evidencioniBroj;
    char sifraZatvorenika[7];
    char oznakaCelije[5];
    int duzinaKazne;
    char status;
}Zatvorenik;

typedef struct{
    Zatvorenik zatvorenici[faktorBlok];
}Blok;

void ucitajBlok(Datoteka *dat, int adresaBloka, Blok *blok);
void sacuvajBlok(Datoteka *dat, int adresaBloka, Blok *blok);
void formiranjeDatoteke();

void ucitajBlok(Datoteka *dat, int adresaBloka, Blok *blok){

    int status;

    status = fseek(dat->file, adresaBloka*sizeof(Blok), SEEK_SET);
    if(status != 0)
        puts("Greska prilikom pozicioniranja na blok!");

    status = fread(blok, sizeof(Blok), 1, dat->file);
    if(status != 1)
        puts("Greska prilikom citanja bloka!");

}

void sacuvajBlok(Datoteka *dat, int adresaBloka, Blok *blok){

    int status;

    status = fseek(dat->file, adresaBloka*sizeof(Blok), SEEK_SET);
    if(status != 0)
        puts("Greska prilikom pozicioniranja na blok!");

    status = fwrite(blok, sizeof(Blok), 1, dat->file);
    if(status != 1)
        puts("Greska prilikom upisa bloka!");

}

void formiranjeDatoteke(){

    Datoteka dat;

    printf("Unesite naziv datoteke: ");
    scanf("%s", dat.nazivDatoteke);

    dat.file = fopen(dat.nazivDatoteke, "wb+");

    if(dat.file == NULL){
        printf("\nDatoteka %s nije uspesno kreirana!\n", dat.nazivDatoteke);
    }else{

        Blok blok;

        strcpy(blok.zatvorenici[0].sifraZatvorenika, "*");

        sacuvajBlok(&dat, 0, &blok);

        printf("\nDatoteka %s je uspesno kreirana!\n", dat.nazivDatoteke);

    }

    fclose(dat.file);

}


// TO-DO

// formiranje datoteke  x
// unos novog sloga
// ažuriranje sloga
// logicko brisanje sloga
// pretraga po ključu
// reorganizacija datoteke
// ispis svih slogova



int main()
{

    Datoteka dat;
    dat.file = NULL;

    int opcija;

    do{
        printf("\n==============================\n");
        printf("1. Formiraj Datoteku\n");

        printf("0. Exit\n");
        printf(">>");

        scanf("%d", &opcija);

        switch(opcija){

        case 1: formiranjeDatoteke(); break;

        case 0: if(dat.file){
                    fclose(dat.file);
                };
                exit(0);
        }

    }while(opcija != 0);

    return 0;
}

