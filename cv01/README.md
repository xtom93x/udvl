Cvičenie 1
==========

SAT solverov je veľa, budeme používať [MiniSAT](http://minisat.se/).
Binárka pre windows sa dá stiahnuť priamo na ich stránke, ale potrebuje ešte 2 knižnice
(cygwin1.dll, cygz.dll), všetky tri súbory sa nachádzajú v adresári s [nástrojmi](../tools/).

Vašou hlavnou úlohou na tomto cvičení je:
* vytvoriť si konto na https://github.com/ (ak ešte nemáte) a poslať mailom na
  adresu `siska@ii.fmph.uniba.sk` vaše univerzitné prihlasovacie id (login do
  AIS-u, v tvare priezviskoCISLO) a prihlasovacie meno do github-u.
  **Do predmetu uveďdte "UdVL registracia"**.
* po vyriešení týchto cvík si odložiť riešenie 2. príkladu (dva textové súbory),
  na budúcich cvičeniach si ukážeme, ako sa odovzdajú v github-e.


1. príklad
----------
Cheme na párty pozvať niekoho z trojice Jim, Kim a Sára, bohužiaľ každý z nich
má nejaké svoje podmienky.

* Sára nepôjde na párty ak pôjde Kim.
* Jim pôjde na párty, len ak pôjde Kim.
* Sára nepôjde bez Jima.

Zapísané v provorádovej logike (premenná `kim` znamená, že Kim pôjde na párty, atď):
<pre>
kim &rarr; &not;sarah
jim &rarr; kim
sarah &rarr; jim
kim &or; jim &or; sarah
</pre>

Prerobené do CNF (konjunktívnej normálnej formy):
<pre>
&not;kim &or; &not;sarah<br/>
&not;jim &or; kim<br/>
&not;sarah &or; jim<br/>
kim &or; jim &or; sarah
</pre>

### DIMACS CNF formát ###
```
p cnf VARS CLAUSES
1 2 -3 0
...
```
```
p cnf 3 4
c -kim v -sarah
-1 -3 0
c -jim v kim
-2 1 0
c -sarah v jim
-3 2 0
c k v j v s
1 2 3 0
```

Aby bola práca s DIMACS CNF súbormi vo windows jednoduchšia, budeme im dávať príponu `.txt`,
t.j. budeme sa tváriť ako by to boli obyčajné textové súbory.

### SAT solver ###

Spustíme sat solver, ako parameter dáme meno vstupného súboru. MiniSAT normálne iba vypíše,
či je vstup splniteľný, ak chceme aj nejaký výstup, tak dáme ešte meno výstupného súboru (MiniSAT ho
vytvorí/prepíše.)
```
$ minisat party.cnf party.out
...
SATISFIABLE
$ cat party.out
SAT
1 -2 -3 0
```

MiniSAT nájde len nejaké riešenie, ak chceme nájsť ďašie, môžeme mu povedať, že toto konkrétne 
nechceme (nemajú naraz platiť tieto premenné). Toto riešenie je kim &and; &not;jim &and; &not;sarah, znegovaním
dostaneme &not;kim &or; jim &or; sarah, čo je priamo disjunktívna klauza a môžeme ju pridať k zadaniu:

```
p cnf 3 5
-1 -3 0
-2 1 0
-3 2 0
1 2 3 0
c nechceme riesenie 1 -2 -3
-1 2 3 0
```
```
$ minisat party.cnf party.out
...
SATISFIABLE
$ cat party.out
SAT
1 2 -3 0
```

Ak to zopakujeme ešte raz, nenájdeme už žiadne riešenie:
```
p cnf 3 6
-1 -3 0
-2 1 0
-3 2 0
1 2 3 0
c nechceme riesenie 1 -2 -3
-1 2 3 0
c nechceme riesenie 1 2 -3
-1 -2 3 0
```
```
$ minisat party.cnf party.out
...
UNSATISFIABLE
$ cat party.out
UNSAT
```

2. Russian spy puzzle (4b)
--------------------------
(Andrei Voronkov, http://www.voronkov.com/lics.cgi)

There are three persons: Stirlitz, Muller, and
Eismann. It is known that exactly one of them is
Russian, while the other two are Germans.
Moreover, every Russian must be a spy.

When Stirlitz meets Muller in a corridor, he
makes the following joke: "you know, Muller,
you are as German as I am Russian". It is
known that Stirlitz always tells the truth when
he is joking.

We have to establish that Eismann is not a Russian spy.


