#include <stdio.h>
#include <stdlib.h>
#include "lift.h"

Emelet *fajlbeolvas(char const *fajlnev){           //beolvassa a fajlbol az utasok adatait
    Emelet *ulista = NULL;
    Utas temp;
    FILE *fp;
    fp = fopen(fajlnev, "rt");
    if (fp == NULL) {
        perror(fajlnev);
        return NULL;
    }
    while (fscanf(fp, "%d %d %d",
            &temp.honnan, &temp.hova, &temp.mikor)==3) {
        Emelet *iter,*lemarado;
        Utas *ujutas, *elozoutas;


        for (iter=ulista; iter!=NULL && iter->szint!=temp.honnan; iter=iter->kov)
            lemarado = iter;

        if (iter==NULL) {
            iter = (Emelet*) malloc(sizeof(Emelet));
            iter->szint = temp.honnan;
            iter->kov = NULL;
            iter->sor = NULL;
           if (ulista == NULL) ulista = iter;
           else lemarado->kov = iter;
        }

        ujutas = (Utas*) malloc(sizeof(Utas));
        *ujutas = temp;
        ujutas->beszallt=-1;
        ujutas->kov = NULL;

        if (iter->sor == NULL) iter->sor = ujutas;
        else {
            for (elozoutas=iter->sor;elozoutas->kov != NULL;elozoutas=elozoutas->kov);
            elozoutas->kov=ujutas;
        }
    }
    return ulista;
}

void felszabadit(Emelet **ulista){                  // felszabaditja a dinamikusan foglalt memoriateruletet
    Emelet *eiter;
    Utas *uiter;
    for(eiter=*ulista;eiter!=NULL;eiter=eiter->kov){
    uiter=eiter->sor;
    while(uiter!=NULL){
        Utas *temp=uiter->kov;
        free(uiter);
        uiter=temp;}
    eiter->sor = NULL;
    }
    Emelet *iter=*ulista;
    while(iter!=NULL){
        Emelet *temp=iter->kov;
        free(iter);
        iter=temp;}
    *ulista=NULL;
}

void emelet_lista(Emelet *ulista){                  // kilistazza az epuletben levo utasokat
    Emelet *eiter;
    Utas *uiter;
    for (eiter = ulista; eiter!=NULL; eiter = eiter->kov) {
        printf("%d. emelet \n", eiter->szint);
        for (uiter = eiter->sor; uiter!=NULL; uiter=uiter->kov)
            printf("honnan: %d hova: %d mikor: %d\n", uiter->honnan, uiter->hova, uiter->mikor);
    }
}

void lift_lista(Utas *plift){                       // kilistazza a liftben tartozkodo utasokat (csak teszteléshez)
    Utas *liftiter;
        for (liftiter = plift; liftiter!=NULL; liftiter=liftiter->kov)
            printf("honnan: %d hova: %d mikor: %d\n", liftiter->honnan, liftiter->hova, liftiter->mikor);
    }

int main() {
    Emelet *ulista=fajlbeolvas("utasok.txt");
    Utas *plift=NULL;
    int szint=0;
    printf("inicializalas:\n");
    emelet_lista(ulista);
    printf("vezerles...\n");
    liftvezerlo(ulista,plift,szint);
    printf("program lefutasa utan:\n");
    emelet_lista(ulista);
    stat_kiir(ulista);
    stat_fajlbair(ulista,"statisztika.txt");
    printf("felszabaditas...\n");
    felszabadit(&ulista);
    printf("fajlba kiirva. (statisztika.txt).\n bye bye...");
    return 0;
}
