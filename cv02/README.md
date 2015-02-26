Cvičenie 2
==========

Riešenie prvého cvičenia odovzdávajte do **Stredy 4.3. 8:09:59**.

Riešenie tohoto cvičenia odovzdávajte do **Nedele 8.3. 23:59:59**.

## Odovzdanie cvičenia 1

Podľa návodu na [odovzdávanie riešení](../odovzdavanie.md) odovzdajte
riešenie prvého cvičenia. Riešenie odovzdajte do vetvy (branch) `cv01`
v adresári `cv01`.

Odovzdajte súbor `spy.txt` ktorý obsahuje "textovú" verzia vstupu pre SAT solver
(s názvami premenných "MG", "MR" atď.) vrátane správne znegovaného tvrdenia,
ktoré chcete dokázať.

## N-queens (4b)

Pomocou SAT solvera vyriešte problém N-dám:

Máme šachovnicu rozmerov `NxN`. Na ňu chceme umiestniť `N` šachových dám
tak, aby sa navzájom neohrozovali. Ohrozovanie dám je v zmysle
štandardných šachových pravidiel:

-  žiadne dve dámy nemôžu byť v rovnakom riadku
-  žiadne dve dámy nemôžu byť v rovnakom stĺpci
-  žiadne dve dámy nemôžu byť na tej istej uhlopriečke

Vyriešená úloha bez poslednej podmienky (uhlopriečky) je za 3b, aj s uhlopriečkami za 4b.

*Pomôcka*: Použite výrokovologické premenné `q_i_j`, <code>0 &le; i,j &lt; N</code>,
ktorých pravdivostná hodnota bude hovoriť, či je alebo nie je na pozícii `i,j`
umiestnená dáma.

*Pomôcka 2*: Pre SAT solver musíme premenné `q_i_j` zakódovať na čísla.
Keďže platí <code>0 &le; i, j &lt; N</code>, premennú `q_i_j` môžete zakódovať ako číslo
`N*i + j + 1`. **Napíšte si na to funkciu! Ideálne s názvom `q`. Jednoduchšie
sa vám budú opravovať chyby a ľahšie sa to číta / opravuje.**

*Pomôcka 3*: Nemusíme počítať počet dám. Stačí požadovať, že v každom riadku
musí byť nejaká dáma (určite nemôžu byť dve dámy v tom istom riadku, keďže ich
má byť `N`, musí byť v každom riadku práve jedna).

*Pomôcka 4*: Ostatné podmienky vyjadrujte vo forme jednoduchých implikácií:<br/>
<code>q_X_Y &rarr; &not;q_X_Z</code> pre <code>X,Y,Z &isin; &lt;0,N), Y&ne;Z</code>
(ak je v riadku `X` dáma na pozícii `Y`, tak nemôže byť iná dáma v tom istom
riadku), atď.

*Pomocka 5*: V adresári [examples/party](../examples/party) je ukážkový program
(c++ a python) ktorý môžete použiť ako kostru vášho riešenia.

### Technické detaily riešenia

Riešenie odovzdávajte do vetvy `cv02` v adresári `cv02`.

Všetky ukážkové a testovacie súbory k tomuto cvičeniu si môžete stiahnuť
ako jeden zip súbor
[cv02.zip](https://github.com/FMFI-UK-1-AIN-411/udvl/archive/cv02.zip).

Riešenie implementujte ako triedu `NQueens` s metódou `solve`, ktorá má jediný
argument - počet dám (resp. veľkosť šachovnice) a vracia zoznam súradníc
jednotlivých dám.  Ak pre daný počet dám rozloženie neexistuje, metóda vráti
prázdny zoznam.

### Python
Odovzdajte súbor `nqueens.py` v ktorom je implementovaná trieda `NQueens`
obsahujúca metódu `solve`. Metóda `solve` má jediný argument N (číslo - počet dám)
a vracia zoznam dvojíc čísel (súradnice dám).

Program [`cv02test.py`](cv02test.py) musí korektne zbehnúť s vašou knižnicou
(súborom `nqueens.py`, ktorý odovzdáte).

### C++
Odovzdajte súbor `NQueens.cpp` v ktorom implementujete triedu `NQueens` definovanú
v hlavičkovom súbore `NQueens.h`. Testovací program [`cv02test.cpp`](cv02test.cpp) musí ísť
skompilovať s vaším riešením príkazom `g++ -Wall --std=c++11 -o cv02test *.cpp`
a korektne zbehnúť.

Ak si neviete ináč rady a potrebujete doplniť ďaľšie veci do `NQueens.h`
(pomocné metódy atď), môžete tento súbor zmeniť (nezabudnite ho odovzdať).

###Java
Odovzdajte súbor `NQueens.java` ktorý obsahuje implementáciu triedy `NQueens`
s metódou `int[][] solve(int N)` (bohužiaľ testy sa nám z časových dôvodov
neoplatilo vyrábať).

