Cvičenie 2
==========

Riešenie prvého cvičenia odovzdávajte do **Pondelka 3.3. 23:59:59**.

Riešenie tohoto cvičenia odovzdávajte do **Nedele 9.3. 23:59:59**.

## Odovzdanie cvičenia 1

Podľa návodu na [odovzdávanie riešení](../odovzdavanie.md) odovzdajte
riešenie prvého cvičenia. Riešenie odovzdajte do vetvy (branch) `cv01`
v adresári `cv01`.

Odovzdajte dva súbory:
- `spy-text.txt` - textová verzia vstupu (s názvami premenných "MG", "MR"
  atď.)
- `spy-cnf.txt` - reálny vstup pre SAT solver (DIMACS CNF formát s
  číselnými premennými atď.)

Ak nemáte odložené obidve verzie riešenia, odovzdajte aspoň jednu.

## N-queens (4b)

Pomocou SAT solvera vyriešte problém N-dám:

Máme šachovnicu rozmerov `NxN`. Na ňu chceme umiestniť `N` šachových dám
tak, aby sa navzájom neohrozovali. Ohrozovanie dám je v zmysle
štandardných šachových pravidiel:

-  žiadne dve dámy nemôžu byť v rovnakom riadku
-  žiadne dve dámy nemôžu byť v rovnakom stĺpci
-  žiadne dve dámy nemôžu byť na tej istej uhlopriečke

Vyriešená úloha bez poslednej podmienky (uhlopriečky) je za 3b, aj s uhlopriečkami za 4b.

*Pomôcka*: Použite výrokovologickú premennú `q_i_j`, <code>0 &le; i,j &lt; N</code>,
ktorej pravdivostná hodnota bude hovoriť, či je alebo nie je na pozícii `i,j`
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
(c++, možno časom pribudnú ďalšie), ktorý môžete použiť ako kostru vášho riešenia.

### Technické detaily riešenia

Riešenie odovzdávajte do vetvy `cv02` v adresári `cv02`.
Odovzdávajte program, ktorý:
- zo štandardného vstupu načíta jediné číslo `N` - rozmer šachovnice
  (a počet dám)
- vypíše na štandardný výstup `N` dvojíc čísel `r s`oddelených medzerou, každú dvojicu
  na samostatnom riadku, pričom každá dvojica reprezentuje pozíciu (riadok, stĺpec) jednej
  dámy, súradnice sú od `0` po `N-1`.

#### Príklad vstupu:
```
4
```
#### Príklad výstupu:
```
1 0
3 1
0 2
2 3
```

