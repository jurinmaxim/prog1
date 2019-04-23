#include <stdio.h>
#include <stdlib.h>
#include "lift.h"

void kiszalltstat(Emelet *ulista, int szint, int *timestep){                    //segedfuggveny a statisztikahoz
    Emelet *eiter;
    Utas *uiter;
    for(eiter=ulista; eiter->szint!=szint ;eiter = eiter->kov);
    for(uiter=eiter->sor; uiter!=NULL;uiter = uiter->kov){
        if (uiter->hova == szint){
            uiter->kiszallt=*timestep;}
    }
    }
void stat_kiir(Emelet *ulista){                //kiirja a statisztikakat egy fajlba
    Emelet *eiter;
    Utas *uiter;
    int osszeg=0;
    int db=0;
    printf("                            STATISZTIKA\n");
    printf("-------------------------------------------------------------------\n");
    printf("------------------------------Utazasi ido: ------------------------\n");
    printf("honnan  hova    beszallt        kiszallt        utazasi ido:       \n");
    for(eiter=ulista; eiter!=NULL;eiter = eiter->kov)
        for(uiter=eiter->sor; uiter!=NULL;uiter = uiter->kov){
            db++;
            osszeg+=uiter->kiszallt-uiter->beszallt;
            printf("|%d     |%d   |%3d secnel       |%3d secnel     |%3d sec.   |\n",uiter->honnan, uiter->hova, uiter->beszallt*6,uiter->kiszallt*6,(uiter->kiszallt-uiter->beszallt)*6);}
    double atlag=osszeg/db;
    printf("-------------------------------------------------------------------\n");
    printf("------------------Atlagos utazasi ido: %.1f sec. ------------------\n", atlag*6);
    printf("-------------------------------------------------------------------\n");
    int osszeg2=0;
    int db2=0;
    Emelet *eiter2;
    Utas *uiter2;
    printf("-------------------------------------------------------------------\n");
    printf("---------------------------Varakozasi ido: ------------------------\n");
    printf("honnan  hova    erkezett        beszallt        utazasi ido:       \n");
    for(eiter2=ulista; eiter2!=NULL;eiter2 = eiter2->kov)
        for(uiter2=eiter2->sor; uiter2!=NULL;uiter2 = uiter2->kov){
            db2++;
            osszeg2+=uiter2->beszallt-uiter2->mikor;
            printf("|%d     |%d   |%3d secnel       |%3d secnel     |%3d sec.   |\n",uiter2->honnan, uiter2->hova, uiter2->mikor*6,uiter2->beszallt*6,(uiter2->beszallt-uiter2->mikor)*6);}
    double atlag2=osszeg2/db2;
    printf("-------------------------------------------------------------------\n");
    printf("-----------------Atlagos varakozasi ido: %.1f sec. ----------------\n", atlag2*6);
    printf("-------------------------------------------------------------------\n");
    }

void stat_fajlbair(Emelet *ulista, char const *fajlnev){                //kiirja a statisztikakat egy fajlba
    FILE *fp;
    Emelet *eiter;
    Utas *uiter;

    fp = fopen(fajlnev, "wt");
    if (fp == NULL) {
        perror("Nem sikerult fajlba menteni a listat");
        return;}
    int osszeg=0;
    int db=0;
    fprintf(fp,"                            STATISZTIKA\n");
    fprintf(fp,"-------------------------------------------------------------------\n");
    fprintf(fp,"------------------------------Utazasi ido: ------------------------\n");
    fprintf(fp,"honnan  hova    beszallt        kiszallt        utazasi ido:       \n");
    for(eiter=ulista; eiter!=NULL;eiter = eiter->kov)
        for(uiter=eiter->sor; uiter!=NULL;uiter = uiter->kov){
            db++;
            osszeg+=uiter->kiszallt-uiter->beszallt;
            fprintf(fp,"|%d     |%d   |%3d secnel       |%3d secnel     |%3d sec.   |\n",uiter->honnan, uiter->hova, uiter->beszallt*6,uiter->kiszallt*6,(uiter->kiszallt-uiter->beszallt)*6);}
    double atlag=osszeg/db;
    fprintf(fp,"-------------------------------------------------------------------\n");
    fprintf(fp,"------------------Atlagos utazasi ido: %.1f sec. ------------------\n", atlag*6);
    fprintf(fp,"-------------------------------------------------------------------\n");
    int osszeg2=0;
    int db2=0;
    Emelet *eiter2;
    Utas *uiter2;
    fprintf(fp,"-------------------------------------------------------------------\n");
    fprintf(fp,"---------------------------Varakozasi ido: ------------------------\n");
    fprintf(fp,"honnan  hova    erkezett        beszallt        utazasi ido:       \n");
    for(eiter2=ulista; eiter2!=NULL;eiter2 = eiter2->kov)
        for(uiter2=eiter2->sor; uiter2!=NULL;uiter2 = uiter2->kov){
            db2++;
            osszeg2+=uiter2->beszallt-uiter2->mikor;
            fprintf(fp,"|%d     |%d   |%3d secnel       |%3d secnel     |%3d sec.   |\n",uiter2->honnan, uiter2->hova, uiter2->mikor*6,uiter2->beszallt*6,(uiter2->beszallt-uiter2->mikor)*6);}
    double atlag2=osszeg2/db2;
    fprintf(fp,"-------------------------------------------------------------------\n");
    fprintf(fp,"-----------------Atlagos varakozasi ido: %.1f sec. ----------------\n", atlag2*6);
    fprintf(fp,"-------------------------------------------------------------------\n");
    fclose(fp);
}
