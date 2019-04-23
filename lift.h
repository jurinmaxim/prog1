#ifndef LIFT_H_INCLUDED
#define LIFT_H_INCLUDED

typedef struct Utas{                                                   //utas struktura
    int honnan;
    int hova;
    int mikor;
    int beszallt;
    int kiszallt;
    struct Utas *kov;
}Utas;

typedef struct Emelet{                                                  //emelet struktura (fesus lista)
    int szint;
    Utas *sor;
    struct Emelet *kov;
}Emelet;

typedef enum Irany {                                                       //irany tipus
    fel,
    le
}Irany;

void kiszalltstat(Emelet *ulista, int szint, int *timestep);
void stat_kiir(Emelet *ulista);
void stat_fajlbair(Emelet *ulista, char const *fajlnev);
void liftvezerlo(Emelet *ulista,Utas *plift, int szint);
void lifturit(Emelet *ulista,Utas **plift,int szint);
Utas *max_le(Emelet *ulista, Utas *plift, int szint);
Utas *max_fel(Emelet *ulista, Utas *plift, int szint);
void ubeszall_fel(Emelet *ulista, Utas **plift, int szint,int *timestep);
void ubeszall_le(Emelet *ulista, Utas **plift, int szint,int *timestep);
int ukszamol(Emelet *ulista,Utas *plift, int szint);
int feljebbmenok(Emelet *ulista, int szint);
int lejjebbmenok(Emelet *ulista, int szint);
void emelet_lista(Emelet *ulista);
void lift_lista(Utas *plift);

#endif // LIFT_H_INCLUDED
