Hra Breakout

První spuštìní hry:
Po prvním spuštìní hry se vám zobrazí menu, kde mùete vidìt 3 hlavní poloky.
Pohybujete se pomocí šipek a potvrzujete volbu pomocí klávesy Enter.

Menu:
1. Start - spustíte hru, mùete rovnou hrát
2. Obtínost - zvolíte jednu ze tøí moností - Lehká, Støední, Tìká
3. Konec - zpusob jak odejít ze hry

Volba obtiznosti:
Obtinost si mùete zvolit v menu, jinak je pøednastavená Støední obtinost.
Obtínost ovlivòuje šíøku plošinky a poèet ivotù.

Start hry:
Pøi spuštìní hry, se vám v horní èásti displaye zobrazí prvnì poèet ivotù
a za ním poèet získanıch bodù.
Pod horní informaèní lištou se Vám vykreslí pole kostek, které máte za úkol rozbít balonkem.
Pod kostkami se nachází plošinka, kterou ovládáte pomoc šipek do leva a do prava.
Hra se ukoèí v pøípadì pokud vám dojdou ivoty nebo odstraníte všechny kostky nebo po stisku klávesy Escape.

========================================================================================

Vnitøní chod hry:
 - start hry - zavolá se funkce main.c, kde se nainicializují samotné okno programu, modul vykreslování grafiky a modul vykreslování fontù
Veškerá inicializace je chránìná kontrolními podmínkami, aby se mohlo zjisti, kde je chyba, pokud by nastala.
Pokud je vše v poøádnu zavolá se funkce menu, kde se vytvoøí menu se všemi jeho monostmi (viz. odstavec Menu).
 - vnitøní chod menu - Prvnì se vytvoøí obtinost, podle které se odehrává další inicializace hry (viz. odstavec Volba obtiznosti).
Menu funguje na základì kostry, kde se vìtví všechny monosti, kde mùe hráè zasáhnout.
Jednotlivé vìtve menu se tvoøí vdy pomocí funkce menuTemplate.
 - vnitøní chod hry - Ze všeho nejdøíve se nainicializují všechny èásti hry (kostky, plošinka, hráè apod.)
Naství se rychlost cyklu pomocí intervalu a spustí se hlavní cyklus, kde se kontrolují kolize balónku s bloky, s plošinkou a se stìnami.
Dále se kontroluje jestli by hra u nemìla skonèit. Jestli hráè znièil všechny balonky nebo mu došly ivoty.
Dále se vyhodnocuje stav ovladání, jak hráè pohl s plošinkou nebo jestli nezmáèku Esc, aby ukonèil hru.
Nakonec se posouvá balónek, tím e se smae jeho ùvodní vykreslení, posunou se souøadnice a vykreslí s novımi souøadnicemi.
Pokud hráè prohrál/vıhrál/ukonèil hru, cyklus hry se ukonèí, uvolní se pamì, smae se obrazovka a hráè se vrací do menu.
 - Soubor gameRender.c - obsahuje funkce, pro vıpis grafiky na display
 - Soubor include.h - obsahuje všechny podstatné knihovny, které se pouívají napøíè programem
Dále obsahuje struktury jednotlivıch herních a programovıch prvkù.
 - Soubor breakoutHead.h - obsahuje všechny definice funkcí, které se pouívají v souboru breakout.c

Pozn.
 - Pro správnou funkci hry je nutno mít knihovnu SDL_ttf.h a k ní sloku fonts, kde jsou uloené písma
 pro vıpis textu ve høe