Cvičenie 3
==========

**Riešenie odovzdávajte podľa
[pokynov na konci tohoto zadania](#technické-detaily-riešenia)
do Štvrtka 12.3.  23:59:59.**

Vytvorte objektovú hierarchiu na reprezentáciu výrokovologických formúl.
Zadefinujte základnú triedu `Formula` a 6 od nej odvodených tried určených
na reprezentáciu jednotlivých druhov atomických a zložených formúl.

Všetky triedy naprogramujte ako knižnicu podľa
[pokynov na konci tohoto zadania](#technické-detaily-riešenia).

```
class Formula
	constructor()
	String toString()	// vrati textovu reprezentaciu formule
	Bool eval(Interpretation i)	// vrati true, ak je formula
					// pravdiva pri interpretacii i
	Array of Formula subf()	// vrati vsetky priame podformuly ako pole

class Variable(Formula)
	constructor(String name)
	String name()	// vrati meno premennej

class Negation(Formula)
	constructor(Formula originalFormula)
	Formula originalFormula()	// vrati povodnu formulu
					// (jedinu priamu podformulu)

class Implication(Formula)
	constructor(Formula leftSide, Formula rightSide)
	Formula leftSide()	// vrati lavu priamu podformulu
	Formula rightSide()	// vrati pravu priamu podformulu

class Disjunction(Formula)
	constructor(Array of Formula disjuncts)

class Conjunction(Formula)
	constructor(Array of Formula conjuncts)

class Equivalence(Formula)
	constructor Create(leftSide, rightSide)
	Formula leftSide()
	Formula rightSide()
```
Samozrejme použite syntax a základné typy jazyka ktorý používate (viď
príklady použitia knižnice na konci).

Metódy `toString` a `eval` budú virtuálne metódy predefinované v každej
podtriede tak, aby robili *správnu vec*<sup>TM</sup> pre dotyčný typ formuly.

Metóda `toString` vráti textovú reprezentáciu formuly podľa nasledovných
pravidiel:
- `Variable`: reťazec `a`, kde `a` je meno premennej (môže byť
  viacpísmenkové)
- `Negation`: reťazez `-A`, kde `A` je reprezentácia podformuly
- `Conjunction`:  reťazec `(A&B&C....)`, kde `A`, `B`, `C`, ... sú
  reprezentácie podformúl (konjunktov)
- `Disjunction`:  reťazec `(A|B|C....)`, kde `A`, `B`, `C`, ... sú
  reprezentácie podformúl (disjunktov)
- `Implication`:  reťazec `(A=>B)`, kde `A` a `B` sú reprezentácie
  ľavej a pravej podformuly
- `Equivalence`: reťazec `(A<=>B)`, kde `A` a `B` sú reprezentácie
  ľavej a pravej podformuly

Teda napríklad v objektovej štruktúre

![GitHub branch](../images/formula.png)

metóda `toString` koreňového objektu triedy `Implikacia` vráti reťazec
`(-(A&C)=>(--B|(D&F)))`.

Metóda `eval` vráti `True` alebo `False` podľa toho, či je formula pravdivá
pri danej interpretácii. Ak sa stane, že ohodnotenie neobsahuje nejakú
premennú, ktorá sa vyskytne vo formule, tak môžete buď vygenerovať chybu /
výnimku alebo ju považovať za `False`.

## Interpretácia
Interpretácia je mapa z reťazcov na Bool, použite správny typ podľa vášho
jazyka:

### C++
Vaša knižnica by mala definovať nasledovný `typedef`:
```c++
typedef std::map<std::string, bool> Interpretation;
```
  príklad použitia:
```c++
Interpretation i;
i["a"] = true;
Formula *f = new Variable("a");
if (f->eval(i) != i["a"]) { /* nieco je zle */ }
```

### Python
Slovnik (`dict`, `{}`), v ktorom sú reťazce mapované na `True` alebo `False`:
```python
i = { 'a':True, 'b':False }
f = Variable('a')
if f.eval(i) != i['a']:
	# nieco je zle
```

### Java:
Použite implementacie rozhrania java.util.Map, napr. java.util.HashMap na
reprezentovanie interpretácie.

príklad použitia:
```java
Map<String,Boolean> i = new HashMap<String,Boolean>();
i.put(a,true);
Formula f = new Variable("a");
if (f.eval(i) != i.get("a")) { /* nieco je zle */ }
```

## Technické detaily riešenia

Riešenie odovzdajte do vetvy `cv03` v adresári `cv03`.  Odovzdávajte súbor
`formula.h`/`formula.cpp`, `formula.py`, alebo `formula.java`.

Odovzdávanie riešení v iných jazykoch konzultujte s cvičiacimi.

### C++
Odovzdajte súbory `formula.h` a `formula.cpp`. 
Testovací program [`cv03test.cpp`](cv03test.cpp) musí ísť skompilovať s vaším
riešením príkazom `g++ -Wall --std=c++11 -o cv03test *.cpp` a korektne zbehnúť.

Poznámka: formula vždy vlastní svoje podformuly. Príkaz `delete f` v
programe zmaže zároveň aj všetky podformuly.

### Python
Odovzdajte súbor `formula.py`.
Program [`cv03test.py`](cv03test.py) musí korektne zbehnúť s vašou knižnicou.


###Java:
Odovzdajte súbor `Formula.java`.
Testovací program [`Cv03Test.java`](Cv03Test.java) musí byť skompilovateľný a
korektne zbehnúť, keď sa k nemu priloží vaša knižnica.
