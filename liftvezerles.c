#include "lift.h"
#include <stdlib.h>
#include <stdio.h>


void liftvezerlo(Emelet *ulista,Utas *plift, int szint){
    int timestep=0;                                      // 1 timestep 6 masodpercnek felel meg.
    Irany irany=fel;                                                     // algoritmus mukodesi elve: addig megy fel, amig a szinthez tartozo
    int limit=0;                                                         // u(k) valtozo nagyobb mint 0. A u(k) valtozo az adott szinten,
    while (szint>=0 && ukszamol(ulista,plift,szint) > 0){                // vagy alatta levo utasokat szamolja ossze, akik magasabbra mennenek, mint
    while (irany==fel){                                                  // mint az adott szint(u(k)): utasok akik <=k szinten vannak és >k-ra mennek.)
        lifturit(ulista,&plift,szint);                                   // A lift akkor valt iranyt, hogyha ez a valtozo 0-val lesz egyenlo, innentol kezdve
        kiszalltstat(ulista,szint,&timestep);                            // az algoritmus az 1-el alatti u(k) valtozot fogja vizsgalni, azaz u(k)(k-1)-et.
        while(limit<3 && (feljebbmenok(ulista,szint)>0)){                // Ha ez nagyobb mint nulla, akkor a lift lefele halad. Ha nulla lesz, és az adott szint
            ubeszall_fel(ulista,&plift,szint,&timestep);                 // u(k-1)-ja és az (u(k)-ja is nulla, akkor is lefele halad tovabb, kulonben megfordul
            limit++;}                                                    // es felfele megy megint. Ez az algortimus arra torekszik, hogy a legrovidebb ido alatt
        limit=0;                                                         // szallitsa el az OSSZES utast a celjaba. Emiatt elofordulhat, hogy valaki nem azon a szinten
        /*emelet_lista(ulista);                                          // szall ki, ami a celja, de ezt a kozjo erdekeben teszi.
        printf("-----------\n");
        lift_lista(plift);
        printf("-----------\n");*/          //teszteleshez
        if (ukszamol(ulista,plift,szint)>0)
            irany=fel;
        else{
            irany=le;
            break;}
        szint++;
        timestep++;
        }
    while(irany==le){
        lifturit(ulista,&plift,szint);
        kiszalltstat(ulista,szint,&timestep);
        while(limit<3 && (lejjebbmenok(ulista,szint)>0)){
            ubeszall_le(ulista,&plift,szint,&timestep);
            limit++;}
        limit=0;
        /*emelet_lista(ulista);
        printf("-----------\n");
        lift_lista(plift);
        printf("-----------\n");*/          //teszteleshez
        if (ukszamol(ulista,plift,szint-1)>0 && szint!=0)
            irany=le;
        else if (ukszamol(ulista,plift,szint-1)==0 && ukszamol(lista,plift,szint)==0 &&szint!=0)
            irany=le;
        else{
            irany=fel;
            break;}
        szint--;
        timestep++;
    }
}
}



void lifturit(Emelet *ulista,Utas **plift,int szint){                       //kiszallitja a liftbol az osszes utast
    Emelet *eiter;
    Utas *uiter;
    for (eiter = ulista; eiter->szint != szint; eiter = eiter->kov);
    if (eiter->sor != NULL){
        for (uiter = eiter->sor; uiter->kov != NULL; uiter = uiter->kov);
        uiter->kov = *plift;}
    else
        eiter->sor = *plift;
    *plift = NULL;
    }

Utas *max_le(Emelet *ulista, Utas *plift, int szint){                           //segedfuggveny a legmesszebb utazo utas kiszamitasahoz
    Emelet *eiter;
    Utas *uiter;
    for(eiter = ulista; eiter->szint != szint ;eiter = eiter->kov);
    Utas *max = eiter->sor;
    for(uiter=eiter->sor; uiter!=NULL ;uiter = uiter->kov)
        if (uiter->hova < max->hova)
            max = uiter;
    return max;
    }

Utas *max_fel(Emelet *ulista, Utas *plift, int szint){                          //segedfuggveny a legmesszebb utazo utas kiszamitasahoz
    Emelet *eiter;
    Utas *uiter;
    for(eiter = ulista; eiter->szint != szint; eiter = eiter->kov);
    Utas *max = eiter->sor;
    for(uiter = eiter->sor; uiter != NULL; uiter = uiter->kov)
        if (uiter->hova > max->hova)
            max = uiter;
    return max;
    }

void ubeszall_fel(Emelet *ulista, Utas **plift, int szint,int *timestep){ //beszallit egy utast felfele
    Utas *uiter, *lemarado=NULL;
    Emelet *eiter;
    Utas *max=max_fel(ulista,*plift,szint);
    for(eiter=ulista; eiter->szint!=szint ;eiter = eiter->kov);
    for(uiter=eiter->sor; uiter!=NULL && !(uiter->hova == max->hova);uiter = uiter->kov)
        lemarado = uiter;
    if (uiter->mikor > *timestep || uiter==NULL);
    else{
    if (*plift==NULL){
        if (uiter->beszallt==-1){
         uiter->beszallt=*timestep;}
        *plift=uiter;
    }else{
        Utas *liftiter;
        for(liftiter = *plift; liftiter->kov != NULL; liftiter = liftiter->kov);
        liftiter->kov = uiter;}
    if (lemarado==NULL){
        eiter->sor=uiter->kov;
   }else{
        lemarado->kov = uiter->kov;}
    uiter->kov = NULL;
    if (uiter->beszallt==-1){
        uiter->beszallt=*timestep;}
}
}
void ubeszall_le(Emelet *ulista, Utas **plift, int szint,int *timestep){ //beszallit egy utast felfele
    Utas *uiter, *lemarado=NULL;
    Emelet *eiter;
    Utas *max=max_le(ulista,*plift,szint);
    for(eiter=ulista; eiter->szint!=szint ;eiter = eiter->kov);
    for(uiter=eiter->sor; uiter!=NULL && !(uiter->hova == max->hova);uiter = uiter->kov)
        lemarado = uiter;
    if (uiter->mikor > *timestep || uiter==NULL);
    else{
    if (*plift==NULL){
        *plift=uiter;
        if (uiter->beszallt==-1){
        uiter->beszallt=*timestep;}
    }else{
        Utas *liftiter;
        for(liftiter = *plift; liftiter->kov != NULL; liftiter = liftiter->kov);
        liftiter->kov = uiter;}
    if (lemarado==NULL){
        eiter->sor=uiter->kov;
   }else
        lemarado->kov = uiter->kov;
    uiter->kov = NULL;
    if (uiter->beszallt==-1){
    uiter->beszallt=*timestep;}
}
}

int ukszamol(Emelet *ulista,Utas *plift, int szint){ //vezerloalgoritmus elve
    int osszeg=0;
    Emelet *eiter;
    Utas *uiter;
    if (szint==9){
        for (eiter = ulista; eiter!=NULL; eiter = eiter->kov)
            for (uiter = eiter->sor; uiter!=NULL; uiter=uiter->kov)
                if (uiter->hova > szint)
                    osszeg++;
    }else{
    for (eiter = ulista; eiter->szint!=szint+1; eiter = eiter->kov)
        for (uiter = eiter->sor; uiter!=NULL; uiter=uiter->kov)
            if (uiter->hova > szint)
                osszeg++;
    }
    Utas *liftiter;
    for (liftiter = plift; liftiter!=NULL; liftiter = liftiter->kov)
        if (liftiter->hova > szint)
            osszeg++;
    return osszeg;

}
int feljebbmenok(Emelet *ulista, int szint){         // megszamolja az adott szinten levo utasokat akik feljebb mennenek
     int osszeg=0;
     Emelet *eiter;
     Utas *uiter;
     for (eiter = ulista; eiter->szint!=szint; eiter = eiter->kov);
        for (uiter = eiter->sor; uiter!=NULL; uiter=uiter->kov)
            if (uiter->hova > szint)
                osszeg++;

    return osszeg;}

int lejjebbmenok(Emelet *ulista, int szint){        // megszamolja az adott szinten levo utasokat akik lejjebb mennenek
     int osszeg=0;
     Emelet *eiter;
     Utas *uiter;
     for (eiter = ulista; eiter->szint!=szint; eiter = eiter->kov);
        for (uiter = eiter->sor; uiter!=NULL; uiter=uiter->kov)
            if (uiter->hova < szint)
                osszeg++;

    return osszeg;}

