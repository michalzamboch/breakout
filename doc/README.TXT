Hra Breakout

Prvn� spu�t�n� hry:
Po prvn�m spu�t�n� hry se v�m zobraz� menu, kde m��ete vid�t 3 hlavn� polo�ky.
Pohybujete se pomoc� �ipek a potvrzujete volbu pomoc� kl�vesy Enter.

Menu:
1. Start - spust�te hru, m��ete rovnou hr�t
2. Obt�nost - zvol�te jednu ze t�� mo�nost� - Lehk�, St�edn�, T�k�
3. Konec - zpusob jak odej�t ze hry

Volba obtiznosti:
Obti�nost si m��ete zvolit v menu, jinak je p�ednastaven� St�edn� obti�nost.
Obt�nost ovliv�uje ���ku plo�inky a po�et �ivot�.

Start hry:
P�i spu�t�n� hry, se v�m v horn� ��sti displaye zobraz� prvn� po�et �ivot�
a za n�m po�et z�skan�ch bod�.
Pod horn� informa�n� li�tou se V�m vykresl� pole kostek, kter� m�te za �kol rozb�t balonkem.
Pod kostkami se nach�z� plo�inka, kterou ovl�d�te pomoc �ipek do leva a do prava.
Hra se uko�� v p��pad� pokud v�m dojdou �ivoty nebo odstran�te v�echny kostky nebo po stisku kl�vesy Escape.

========================================================================================

Vnit�n� chod hry:
 - start hry - zavol� se funkce main.c, kde se nainicializuj� samotn� okno programu, modul vykreslov�n� grafiky a modul vykreslov�n� font�
Ve�ker� inicializace je chr�n�n� kontroln�mi podm�nkami, aby se mohlo zjisti, kde je chyba, pokud by nastala.
Pokud je v�e v po��dnu zavol� se funkce menu, kde se vytvo�� menu se v�emi jeho mo�nostmi (viz. odstavec Menu).
 - vnit�n� chod menu - Prvn� se vytvo�� obti�nost, podle kter� se odehr�v� dal�� inicializace hry (viz. odstavec Volba obtiznosti).
Menu funguje na z�klad� kostry, kde se v�tv� v�echny mo�nosti, kde m��e hr�� zas�hnout.
Jednotliv� v�tve menu se tvo�� v�dy pomoc� funkce menuTemplate.
 - vnit�n� chod hry - Ze v�eho nejd��ve se nainicializuj� v�echny ��sti hry (kostky, plo�inka, hr�� apod.)
Nastv� se rychlost cyklu pomoc� intervalu a spust� se hlavn� cyklus, kde se kontroluj� kolize bal�nku s bloky, s plo�inkou a se st�nami.
D�le se kontroluje jestli by hra u� nem�la skon�it. Jestli hr�� zni�il v�echny balonky nebo mu do�ly �ivoty.
D�le se vyhodnocuje stav ovlad�n�, jak hr�� pohl s plo�inkou nebo jestli nezm��ku Esc, aby ukon�il hru.
Nakonec se posouv� bal�nek, t�m �e se sma�e jeho �vodn� vykreslen�, posunou se sou�adnice a vykresl� s nov�mi sou�adnicemi.
Pokud hr�� prohr�l/v�hr�l/ukon�il hru, cyklus hry se ukon��, uvoln� se pam�, sma�e se obrazovka a hr�� se vrac� do menu.
 - Soubor gameRender.c - obsahuje funkce, pro v�pis grafiky na display
 - Soubor include.h - obsahuje v�echny podstatn� knihovny, kter� se pou��vaj� nap��� programem
D�le obsahuje struktury jednotliv�ch hern�ch a programov�ch prvk�.
 - Soubor breakoutHead.h - obsahuje v�echny definice funkc�, kter� se pou��vaj� v souboru breakout.c

Pozn.
 - Pro spr�vnou funkci hry je nutno m�t knihovnu SDL_ttf.h a k n� slo�ku fonts, kde jsou ulo�en� p�sma
 pro v�pis textu ve h�e