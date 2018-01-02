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
int izracunajEvidencioniBroj(Datoteka *dat);
int pretraga(Datoteka *dat, char *sifra, int **BrBloka, int **BrSlog);
void unosSloga(Datoteka *dat);
void logickoBrisanjeSloga(Datoteka *dat);
void izmenaSloga(Datoteka *dat);
void fizickoBrisanje(Datoteka *dat);


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


int izracunajEvidencioniBroj(Datoteka *dat){

    int pozBloka;
    int pozSloga;

    int evidBroj;

    nadjiKraj(dat, &pozBloka, &pozSloga);

    Blok blok;

    if(pozSloga != 0 ){
        ucitajBlok(dat, pozBloka, &blok);
        evidBroj = blok.zatvorenici[pozSloga-1].evidencioniBroj;
    }

    if(pozSloga == 0 && pozBloka > 0){
        ucitajBlok(dat, pozBloka-1, &blok);
        evidBroj = blok.zatvorenici[2].evidencioniBroj;
    }
    if(pozSloga == 0 && pozBloka == 0){
        evidBroj = 1; // ako ne postoji ni jedan slog
    }


    return evidBroj;
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
    zatvorenik.evidencioniBroj =  izracunajEvidencioniBroj(dat) + 1;
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


void logickoBrisanjeSloga(Datoteka *dat){

    char sifraSloga[10];
    printf("Unesite sifru: ");
    scanf("%s", sifraSloga);

    int brBloka;
    int brSloga;

    if(pretraga(dat, sifraSloga, &brBloka, &brSloga) != 1){
        puts("Ne postoji zatvorenik sa tom sifrom");
        return;
    }

    Blok blok;

    ucitajBlok(dat, brBloka, &blok);

    blok.zatvorenici[brSloga].status = 'n';

    upisiBlok(dat,brBloka,&blok);

    puts("Zatvorenik je uspesno obrisan!");

}

void izmenaSloga(Datoteka *dat){

    if(dat->file == NULL){
        puts("Izaberite datoteku!");
        return;
    }

    int brBloka;
    int brSloga;

    char sifraSloga[10];

    printf("Unesite sifru zatvorenika: ");
    scanf("%s", sifraSloga);

    if(pretraga(dat, sifraSloga, &brBloka, &brSloga) != 1){
        return;
    }

    Blok blok;

    ucitajBlok(dat, brBloka, &blok);

    printf("Zelite li da promenite oznaku celije?(da/ne)");

    char odg1[2];
    scanf("%s", odg1);

    if(strcmp(odg1, "da") == 0){
        printf("Unesite novu oznaku celije: ");
        char oznakaCel[5];
        scanf("%s", oznakaCel);

        strcpy(blok.zatvorenici[brSloga].oznakaCelije, oznakaCel);
    }


    printf("Zelite li da promenite duzinu kazne?");

    char odg2[2];
    scanf("%s", odg2);

    if(strcmp(odg2, "da") == 0){
        printf("Unesite novu duzinu kazne: ");
        int duzinaKazna;
        scanf("%d", &duzinaKazna);

        blok.zatvorenici[brSloga].duzinaKazne = duzinaKazna;
    }

    upisiBlok(dat, brBloka, &blok);

    puts("Uspesno ste izmenili podatke!");
}


void fizickoBrisanje(Datoteka *dat){

    char sifraZatvornika[10];
    printf("Unesite sifru zatvorenika: ");
    scanf("%s",sifraZatvornika);

    Blok blok;

    int brBloka;
    int brSloga;

    int status = 0;
    int blokBrisanja = 1;

    if(pretraga(dat,sifraZatvornika,&brBloka, &brSloga) == 1){

        while(status == 0){

            ucitajBlok(dat, brBloka, &blok);
            int i;

            for(i = brSloga; i <faktorB; i++){

                if(blok.zatvorenici[i].evidencioniBroj == -1){
                    puts("Kraj!");
                    status = 1;
                    break;
                }

                //ako se nalazi na prva dva mesta, izpomeraj sve od sloga koji se brise

                if(i != 2){
                    blok.zatvorenici[i] = blok.zatvorenici[i+1];
                }

                // ako se nalazi na 3 mestu, ucitaj sledeci blok i postavi prvi element sledeceg bloka na 3 mesto

                if(i == 2){
                    Blok temp;
                    ucitajBlok(dat, brBloka+1, &temp);
                    blok.zatvorenici[2] = temp.zatvorenici[0];
                }

            }

             upisiBlok(dat, brBloka, &blok);
             brSloga = 0;
             brBloka++;

        }

    }

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
        printf("7. Izmena sloga(zatvorenika)\n");
        printf("8. Fizicko brisanje sloga(zatvorenika)\n");

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
        case 6: logickoBrisanjeSloga(&dat); break;
        case 7: izmenaSloga(&dat); break;
        case 8: fizickoBrisanje(&dat); break;

        case 0: if(dat.file){
                    fclose(dat.file);
                };
                exit(0);
        }

    }while(opcija != 0);


    return 0;
}
