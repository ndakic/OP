#include <stdio.h>
#include <stdlib.h>

#define faktorB 3
#define fiksniKorak 1

typedef struct{

    int evidencioniBroj;
    char sifraZatvorenika[7];
    char oznakaCelije[5];
    int duzinaKazne;
    char status;

}TZatvorenik;


typedef struct{
    TZatvorenik zatvorenici[faktorB];
}Blok;


typedef struct{
    FILE* file;
    char naziv[30];
}Datoteka;


void formiranjeDatoteke();
void odaberiDatoteku(Datoteka *dat);
void prikaziSlog(TZatvorenik zatvorenik);
void prikaziSadrzajDatoteke(Datoteka *dat);
void nadjiKraj(Datoteka *dat, int **pozicijaBloka,int **pozicijaSloga);
void upisiBlok(Datoteka *dat, int adresaBloka, Blok *blok);
void ucitajBlok(Datoteka *dat, int adresaBloka, Blok *blok);
int calculateEvidencioniBroj(Datoteka *dat);
int pretraga(Datoteka *dat, char *sifra, int **BrBloka, int **BrSlog);
void unosSloga(Datoteka *dat);
void brisanjeSloga(Datoteka *dat, char *sifraSloga);

// TO-DO

// Azuriranje sloga
// * Fizicko brisanje sloga


void formiranjeDatoteke(){

    Datoteka dat;

    printf("Unesite naziv datoteke: ");
    scanf("%s", dat.naziv);

    dat.file = fopen(dat.naziv, "wb+");

    if(dat.file == NULL){
        printf("\nDatoteka %s nije uspesno kreirana!\n", dat.naziv);
    }else{

        Blok blok;

        blok.zatvorenici[0].evidencioniBroj = -1;
        strcpy(blok.zatvorenici[0].sifraZatvorenika, "-1");

        upisiBlok(&dat, 0, &blok);

        printf("\nDatoteka %s je uspesno kreirana!\n", dat.naziv);
    }
    fclose(dat.file);
}


void odaberiDatoteku(Datoteka *dat){

    printf("Unesite naziv datoteke: ");
    scanf("%s", dat->naziv);

    dat->file = fopen(dat->naziv, "rb+");

    if(dat->file == NULL){
        printf("\nDatoteka %s nije uspesno ucitana!\n", dat->naziv);
    }else{
        printf("\nDatoteka je uspesno ucitana!\n");
    }

}

void prikaziSlog(TZatvorenik zatvorenik){

    puts("-------------------------------------------------------");
    printf("Evidencioni broj: %d\n", zatvorenik.evidencioniBroj);
    printf("Sifra zatvorenika: %s\n", zatvorenik.sifraZatvorenika);
    printf("Oznaka celije: %s\n", zatvorenik.oznakaCelije);
    printf("duzina kazne: %d\n", zatvorenik.duzinaKazne);
    printf("status: %c\n", zatvorenik.status);
    puts("-------------------------------------------------------");

}

void prikaziSadrzajDatoteke(Datoteka *dat){

    if(dat->file == NULL){
        printf("Ne postoji aktivna datoteka \n");
        return;
    }

    Blok blok;
    int i;
    int redBrBloka = 0;
    int status = 0;

    do{
        ucitajBlok(dat, redBrBloka, &blok);
        for(i=0; i < faktorB; i++){
            if(blok.zatvorenici[i].evidencioniBroj == -1){
                status = 1;
                //printf("Kraj je pronadjen u %d bloku na %d mestu\n", redBrBloka, i);
                break;
            }else{
                //if(blok.zatvorenici[i].status == 'a')
                prikaziSlog(blok.zatvorenici[i]);
            }
        }
        if(status == 0){
            redBrBloka++;
            ucitajBlok(dat, redBrBloka, &blok);
        }

        if(redBrBloka == 5){
            status = 1;
            puts("Greska!");
        }

    }while(status == 0);
}


void nadjiKraj(Datoteka *dat, int **pozicijaBloka,int **pozicijaSloga){

    Blok blok;
    int i;
    int redBrBloka = 0;
    int status = 0;

    do{
        ucitajBlok(dat, redBrBloka, &blok);
        for(i=0; i < faktorB; i++){
            if(blok.zatvorenici[i].evidencioniBroj == -1){
                status = 1;
                printf("Kraj je pronadjen u %d bloku na %d mestu\n", redBrBloka, i);
                break;
            }
        }
        if(status == 0)
            redBrBloka++;

    }while(status == 0);

    *pozicijaBloka = redBrBloka;
    *pozicijaSloga = i;

}


void upisiBlok(Datoteka *dat, int adresaBloka, Blok *blok){

    int status;

    status = fseek(dat->file, adresaBloka*sizeof(Blok), SEEK_SET);
    if(status != 0){
        puts("Greska prilikom pozicioniranja na blok!");
    }

    status = fwrite(blok, sizeof(Blok), 1, dat->file );
    if(status != 1){
        puts("Greska prilikom upisa bloka!");
    }

}

void ucitajBlok(Datoteka *dat, int adresaBloka, Blok *blok){

    int status;

    status = fseek(dat->file, adresaBloka*sizeof(Blok), SEEK_SET);
    if(status != 0){
        puts("Greska prilikom pozicioniranja na blok!");
    }

    status = fread(blok, sizeof(Blok), 1, dat->file );

    if(status != 1){
        puts("Greska prilikom citanja bloka!");
    }
}




int calculateEvidencioniBroj(Datoteka *dat){

    int count = 0;
    int i;

    int adresaBloka = 0;

    Blok blok;

    int status = 0;

    while(status == 0){

        ucitajBlok(dat, adresaBloka, &blok);

        for(i=0; i< faktorB; i++){
            if(blok.zatvorenici[i].evidencioniBroj >=0)
                count++;

            if(blok.zatvorenici[i].evidencioniBroj == -1){
                status = 1;
                break;
            }
        }

        adresaBloka++;

        if(adresaBloka == 5){
            status = 1;
        }
    }

    return count;
}

int pretraga(Datoteka *dat, char *sifra, int **BrBloka, int **BrSlog){

    Blok blok;
    int i;
    int status = 0;
    int redBrBloka = 0;
    int redBrSloga;
    int postoji = 0;

    do{

        ucitajBlok(dat, redBrBloka, &blok);
        for(i=0; i < faktorB; i++){
            if((strcmp(blok.zatvorenici[i].sifraZatvorenika, sifra)) == 0){
                printf("Slog je pronadjen u %d bloku na %d mestu.\n", redBrBloka, i);
                status = 1;
                postoji = 1;
                redBrSloga = i;
                break;

            }

            if(blok.zatvorenici[i].evidencioniBroj == -1){
                printf("Nema sloga sa tom sifrom.\n");
                status = 1;
                break;

            }
        }

        if(status == 0)
            redBrBloka++;

        if(redBrBloka == 20){
            puts("Greska!");
            status = 1;
        }

    }while(status == 0);

    *BrBloka = redBrBloka;
    *BrSlog = redBrSloga;

    return postoji;
}

void unosSloga(Datoteka *dat){

    TZatvorenik zatvorenik;
    zatvorenik.evidencioniBroj =  calculateEvidencioniBroj(dat);
    zatvorenik.status = 'a';

    printf("\nUnesi sifru zatvorenika: ");
    scanf("%s", zatvorenik.sifraZatvorenika);

    int brBlok, brSloga;

    if(pretraga(dat, zatvorenik.sifraZatvorenika, &brBlok, &brSloga) == 1){
        puts("Ne mere dalje!");
        return;
    }

    printf("\nUnesi oznaku celije: ");
    scanf("%s", zatvorenik.oznakaCelije);

    printf("\nUnesi duzinu kazne: (max. 480meseci)");
    scanf("%d", &zatvorenik.duzinaKazne);

    int pozicijaBloka, pozicijaSloga;

    Blok blok;

    nadjiKraj(dat, &pozicijaBloka, &pozicijaSloga);

    ucitajBlok(dat, pozicijaBloka, &blok);

    if(pozicijaSloga == 2){
        // upisi novi slog na kraj bloka
        blok.zatvorenici[pozicijaSloga] = zatvorenik;
        upisiBlok(dat, pozicijaBloka, &blok);

        //dodaj novi blok sa krajem na prvom mestu
        Blok blok2;
        blok2.zatvorenici[0].evidencioniBroj = -1;
        upisiBlok(dat, pozicijaBloka+1, &blok2);

    }else{
        blok.zatvorenici[pozicijaSloga] = zatvorenik;
        blok.zatvorenici[pozicijaSloga+1].evidencioniBroj = -1; // dodajem kraj
        upisiBlok(dat, pozicijaBloka, &blok);
    }

}


void brisanjeSloga(Datoteka *dat, char *sifraSloga){

    int brBloka;
    int brSloga;

    if(pretraga(dat, sifraSloga, &brBloka, &brSloga) != 1){
        puts("Ne postoji zatvorenik sa tom sifrom");
        return;
    }

    //printf("Blok: %d, Slog: %d", brBloka, brSloga);

    Blok blok;

    ucitajBlok(dat, brBloka, &blok);

    blok.zatvorenici[brSloga].status = 'n';

    upisiBlok(dat,brBloka,&blok);

    puts("Zatvorenik je uspesno obrisan!");

}

int main()
{
    Datoteka dat;
    dat.file = NULL;

    int opcija;

    do{
        printf("\n==============================\n");
        printf("1. Formiraj Datoteku\n");
        printf("2. Izaberi aktivnu datoteku\n");
        printf("3. Prikazi sadrzaj datoteke\n");
        printf("4. Unos novog sloga(zatvorenika)\n");
        printf("5. Pretraga sloga(zatvorenika)\n");
        printf("6. Logicko brisanje sloga(zatvorenika)\n");

        printf("0. Exit\n");
        printf(">>");

        scanf("%d", &opcija);

        switch(opcija){

        case 1: formiranjeDatoteke(); break;
        case 2: odaberiDatoteku(&dat); break;
        case 3: prikaziSadrzajDatoteke(&dat); break;
        case 4: unosSloga(&dat); break;
        case 5: if(dat.file){
                    int brBloka;
                    int brSloga;
                    char sifra[10];
                    printf("Unesite sifru: ");
                    scanf("%s", sifra);
                    pretraga(&dat, sifra, &brBloka, &brSloga);
                } break;
        case 6: if(dat.file){
                    char sifra[10];
                    printf("Unesite sifru: ");
                    scanf("%s", sifra);
                    brisanjeSloga(&dat, &sifra);
                }; break;

        case 0: if(dat.file){
                    fclose(dat.file);
                };
                exit(0);
        }

    }while(opcija != 0);


    return 0;
}
