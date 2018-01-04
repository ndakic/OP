#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define faktorBlok 5

#define true 1
#define false 0

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
void izaberiDatoteku(Datoteka *dat);
void prikaziSlog(Zatvorenik zatvorenik);
void prikaziSadrzajDatoteke(Datoteka *dat);
int nadjiPoziciju(Datoteka *dat, int evidBr, int *redBrBloka, int *redBrSloga);
void unosSloga(Datoteka *dat);
void brisanjeSloga(Datoteka *dat);


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

void izaberiDatoteku(Datoteka *dat){

    printf("Unesite naziv datoteke: ");
    scanf("%s", dat->nazivDatoteke);

    dat->file = fopen(dat->nazivDatoteke, "rb+");

    if(dat->file == NULL)
        printf("\nDatoteka %s nije uspesno ucitana!\n", dat->nazivDatoteke);
    else
        printf("\nDatoteka je uspesno ucitana!\n");

}

void prikaziSlog(Zatvorenik zatvorenik){

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
        puts("Izaberite datoteku!");
        return;
    }

    int adresaBloka = 0;
    int i;

    Blok blok;

    while(true){
        ucitajBlok(dat, adresaBloka, &blok);

        for(i=0; i < faktorBlok; i++){

            int kraj = strcmp(blok.zatvorenici[i].sifraZatvorenika, "*");

            if(!kraj){
                return;
            }

            prikaziSlog(blok.zatvorenici[i]);

        }
        adresaBloka++;
    }

}

int nadjiPoziciju(Datoteka *dat, int evidBr, int *redBrBloka, int *redBrSloga){

    if(dat->file == NULL){
        puts("Izaberite datoteku!");
        return;
    }

    int adresaBloka = 0;
    int i;

    Blok blok;

    while(true){

        ucitajBlok(dat, adresaBloka, &blok);

        for(i=0; i < faktorBlok; i++){

            int kraj = strcmp(blok.zatvorenici[i].sifraZatvorenika, "*");
            // ako ne postoji veci, novi slog dodajem na kraj
            if(kraj == 0){

                *redBrBloka = adresaBloka;
                *redBrSloga = i;

                return 0; // ne vrsi se pomeranje, samo na kraj dodam novi slog
            }

            // ako postoji broj koji je veci, znaci da mora negde izmedju da se uglavi novi broj
            if(blok.zatvorenici[i].evidencioniBroj > evidBr){
                *redBrBloka = adresaBloka;
                *redBrSloga = i;

                return 1; // vrsi se pomeranje svih slogova za jedno mestu u desno
            }
        }
        adresaBloka++;
    }

}

void unosSloga(Datoteka *dat){

    int redBrBloka;
    int redBrSloga;

    Zatvorenik zatvorenik;

    strcpy(zatvorenik.sifraZatvorenika, "113d");
    strcpy(zatvorenik.oznakaCelije, "F4");
    zatvorenik.duzinaKazne = 33;
    zatvorenik.status = 'a';

    printf("Unesite evidencioni broj: ");
    int evidBroj;
    scanf("%d", &evidBroj);
    zatvorenik.evidencioniBroj = evidBroj;

    int pomeranje = nadjiPoziciju(dat, evidBroj, &redBrBloka, &redBrSloga);
    printf("Zatvorenika treba postavi na: blok: %d, slog: %d\n", redBrBloka, redBrSloga);

    Blok blok;

    ucitajBlok(dat, redBrBloka, &blok);

    printf("Pomeranje: %d\n", pomeranje);

    // ako upisujemo na kraj tj. evidBr. novog zatvorenika je najveci
    if(pomeranje == 0){

        if(redBrSloga != faktorBlok-1){
            blok.zatvorenici[redBrSloga] = zatvorenik;
            strcpy(blok.zatvorenici[redBrSloga+1].sifraZatvorenika, "*");
            sacuvajBlok(dat, redBrBloka, &blok);
        }else{
            blok.zatvorenici[redBrSloga] = zatvorenik;
            sacuvajBlok(dat, redBrBloka, &blok);

            Blok novi_blok;
            strcpy(novi_blok.zatvorenici[0].sifraZatvorenika, "*");
            sacuvajBlok(dat, redBrBloka+1, &novi_blok);
        }
    }

    // ako postoji veci broj, potrebno je novi ubaciti na njegovo mesto a sve ostale pomeriti za jedno mestu u desno
    if(pomeranje == 1){

        int status = 0;

        while(status == 0){

            Zatvorenik temp1 = zatvorenik;
            Zatvorenik temp2;

            int i;

            for(i=redBrSloga; i<faktorBlok; i++){

                // ako se u temp1 nalazi slog sa oznakom za kraj
                if(strcmp(temp1.sifraZatvorenika, "*") == 0){

                    blok.zatvorenici[i] = temp1;    // upisivanje kraja na i-to mesto
                    sacuvajBlok(dat, redBrBloka, &blok);

                    status = 1;
                    break;

                }

                temp2 = blok.zatvorenici[i];    // trenutni slog stavi u privremeni 2

                blok.zatvorenici[i] = temp1;    // postavi novi slog na trenutni

                temp1 = temp2;                  // prabaci privremeni slog 2 u privremeni 1

                // kada se doslo do kraja bloka i kad je u tempu znak za kraj
                if(strcmp(temp1.sifraZatvorenika, "*") == 0 && i == faktorBlok-1){
                    sacuvajBlok(dat, redBrBloka, &blok);
                    Blok noviB;
                    noviB.zatvorenici[0] = temp1;
                    redBrBloka++;
                    sacuvajBlok(dat, redBrBloka, &noviB);

                    status = 1;
                    break;

                }
                // kada se doslo do kraja bloka i kada u tempu nije znak za kraj
                if(strcmp(temp1.sifraZatvorenika, "*") != 0 && i == faktorBlok-1){

                    sacuvajBlok(dat, redBrBloka, &blok);
                    redBrBloka++;
                    ucitajBlok(dat, redBrBloka, &blok);

                    zatvorenik = temp1; // * slog koji se prenosi iz jednog u drugi blok se postavlja za novi(zatvorenik) jer je na pocetku temp == zatvorenik
                }

            }

            redBrSloga = 0;
        }

    }
}


void brisanjeSloga(Datoteka *dat){

    int kljuc;
    printf("Unesite sifru: ");
    scanf("%d", &kljuc);

    int status = 0;
    int redBrBloka = 0;

    Blok blok;

    int i;

    while(!status){

        ucitajBlok(dat, redBrBloka, &blok);

        for(i=0; i < faktorBlok; i++){

            if(blok.zatvorenici[i].evidencioniBroj == kljuc){

                blok.zatvorenici[i].status = 'n';
                sacuvajBlok(dat, redBrBloka, &blok);

                printf("Slog je uspesno obrisan!");
                status = 1;
                break;

            }

            if(blok.zatvorenici[i].evidencioniBroj > kljuc || strcmp(blok.zatvorenici[i].sifraZatvorenika, "*") == 0){
                printf("Ne postoji slog sa tom sifrom! Mesto zaustavljanja: Blok: %d, Slog: %d\n", redBrBloka, i);
                status = 1;
                break;
            }

        }

        redBrBloka++;
    }

}


int main()
{
    Datoteka dat;
    dat.file = NULL;

    int opcija;

    do{
        printf("\n==============================\n");
        printf("1. Formiraj datoteku\n");
        printf("2. Izaberi datoteku\n");
        printf("3. Prikazi sadrzaj\n");
        printf("4. Unos sloga (zatvorenika)\n");
        printf("5. Logicko brisanje sloga (zatvorenika)\n");

        printf("0. Exit\n");
        printf(">>");

        scanf("%d", &opcija);

        switch(opcija){

        case 1: formiranjeDatoteke(); break;

        case 2: izaberiDatoteku(&dat); break;

        case 3: prikaziSadrzajDatoteke(&dat); break;

        case 4: unosSloga(&dat); break;

        case 5: brisanjeSloga(&dat); break;

        case 0: if(dat.file){
                    fclose(dat.file);
                };
                exit(0);
        }

    }while(opcija != 0);

    return 0;
}

