# Lift szimulátor: Programozás Alapjai 1 NHF

## Leírás
A lift szimulátor működése egy olyan algoritmuson alapszik, amelynek célja a leghatékonyabb,
azaz a legrövidebb időn belül elrendezni az adatokat (jelen esetben egy lift segítségével).
Működésének kulcsa egy változó (u(k)), amelyet egy bizonyos időpillanatban egy szinthez (k)
tudunk rendelni. Ez a változó azt határozza meg, hogy abban a pillanatban hány olyan utas
található az épületben, amely az adott szinten található, vagy lejjebb (<=k) és az adott szintnél
feljebb (>k) van az úticélja.
Amíg u(k) nagyobb mint 0, addig felfele mozog a lift.
Amint u(k) egyenlő lesz nullával, az algoritmus az eggyel alatti szintnek fogja vizsgálni ezt a
változóját (u(k-1)), és addig fog lefele haladni a lift, amíg ez nagyobb mint nulla.
Amint u(k-1) nulla lesz, két lehetőségünk van: hogyha u(k-1)=0 és uk=0, akkor továbbra is lefele
fog haladni a lift. Hogyha u(k-1)=0 és u(k)>0, akkor a lift felfele fog haladni, és újra a u(k) szerint
fog tesztelni és haladni a megfelelő irányba.
A lift megáll, hogyha minden utas a helyére kerül és a földszinten van.
A lift vezérléséhez fontos hozzáfűzni, hogy a hatékonyság érdekében megtörténhet az, hogy egy
utas aki a liftben tartózkodik előbb száll ki, mint az úticélja, hiszen a működési elvbe
beletartozik az, hogy a lift az adott szintről mindig a legtávolabbi úticélú utasokat viszi el a
céljukhoz.
## Adatszerkezetek
Az utasok és adataiknak kezeléséhez egy fésűs listás adatszerkezetet hoztam létre, melyben az
Emelet láncolt listából (eleje: ulista pointer) oldalra nyíló ágak az adott szinten található, nem
liftben tartózkodó utasokat tartalmazza. A liftben tartózkodó utasok egy egyszerű láncolt
listában vannak elhelyezve, melynek az elejére egy pointer mutat (plift). Ehhez két struktúrára
volt szükségem, melyeket typedefeltem: Emelet struktúra és Utas struktúra.
A statisztika készítés egyik fő szempontja a programnak, és a lift szimulátor a két
legkézenfekvőbb statisztikát számolja ki: várakozási idő, utazási idő, és ezeknek a az átlagai.
A programban timestepet használtam az idővel kapcsolatos értékek kiszámításhoz. Egy
timestep 6 másodpercnek felel meg (pl. 6 másodpercet tölt átlagosan egy lift egy emeleten).
Az Utas struktúrában öt változó található, melyből a program hármat fájlból olvas be. A honnan,
hova, mikor változók rendre az indulási szintet, az úticélt, és a lifthez érkezés pillanatát jelzik. A 
beszallt és a kiszallt változók a lift szimulációja során értékelődnek ki, és ezek segítségével a
végén táblázatba kiírja az utazás statisztikáit.
## Függvények
A program függvényei két típusra oszthatók, az egyik a liftvezérlést segítő, a másik a statisztikát
készítő függvények.
A liftvezérlő függvények a következők:

**void liftvezerlo(Emelet \*ulista,Utas \*plift, int szint)**
Ez a függvény a lift vezérléséért felelős, a két while loop közül az aktuális u(k) szerint választ és
hajtja végre az utasításokat.

**int ukszamol(Emelet \*ulista,Utas \*plift, int szint)**
Ez a függvény a szinthez tartozó u(k)-t számolja ki.

**int feljebbmenok(Emelet \*ulista, int szint) , int lejjebbmenok(Emelet \*ulista, int szint)**
Ez a két függvény azt számolja ki, hogy hány utas van az adott szinten aki feljebb/lejjebb menne.

**Utas \*max_le(Emelet \*ulista, Utas \*plift, int szint) , Utas \*max_fel(Emelet \*ulista, Utas \*plift,**
int szint)
Ez a két segédfüggvény az aktuális szinten legtávolabb utazót utast adja meg, fel vagy le módtól
függően.

**void ubeszall_fel(Emelet \*ulista, Utas \*\*plift, int szint,int \*timestep) , void ubeszall_le(Emelet
\*ulista, Utas \*\*plift, int szint,int \*timestep)**
Ez a két függvény a legtávolabb utazó utast szállítja be a liftbe, fel vagy le módtól függően.

**void lifturit(Emelet \*ulista,Utas \*\*plift,int szint)**
Ez a függvény kiüríti a liftet, azaz kiszállítja az összes liftben utazó utast az adott szintre.

***A statisztikakészítő függvények a következők:***

**void kiszalltstat(Emelet \*ulista, int szint, int \*timestep)**
Ez a segédfüggény a utas->kiszallt adatát segít adja meg.

**void stat_kiir(Emelet \*ulista)**
Ez a függvény kiírja a statisztikát a szabványos kimenetre.

**void stat_fajlbair(Emelet \*ulista, char const \*fajlnev)**
Ez a függvény fájlba írja az elkészült statisztikákat.

***Egyéb függvények:***
**Emelet \*fajlbeolvas(char const \*fajlnev)**
Ez a függvény beolvassa az utasok.txt-ből az utasok adatait és létrehozza a fésűs listát. Itt
történik az összes malloc hívás, innentől kezdve csak pointerek átállításával kezeli a program az
utasokat.

**void felszabadit(Emelet \*\*ulista)**
Ez a függvény értelemszerűen felszabadítja az előző függvény által dinamikusan foglalt
memóriát a program lefutása után.

**void emelet_lista(Emelet |*ulista)**
Ez a függvény kilistázza az összes emeleten éppen nem liftben tartózkodó utasait.
**void lift_lista(Utas \*plift)**
Ez a függvény a liftben tartózkodó utasokat listázza ki. Csak a tesztelés során volt használatos.

## A program működése:
A program először beolvassa az utasokat, dinamikusan memóriát foglalt nekik és fésűs listába
rendezi őket. Ezután a liftvezérlés ciklusa az érkezés után (iránytól függetlenül) ezekből a
lépésekből áll:
1. Kiüríti a benne tartózkodó utasokat.
2. Amíg vannak feljebbmenők és a lift nincs túlterhelve (a lift kapacitása 3 ember), addig
betölti az adott irányba haladó, legtávolabbi úticéllal rendelkező utasokat.
3. Kiértékeli az adott szint u(k)-ját vagy u(k-1)-ét (az iránytól függően), és az adott irányba
halad egy szintet, növelve közben a timestepet eggyel (6 másodperc).
Megjegyzés: ha irányt vált a lift a 3. lépésnél, akkor megismétli az 1. és a 2. lépéseket.


***Készítette: Jurin Maxim, 2016 BME*** 
