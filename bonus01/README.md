Bonus 1 (2b)
============

**Riešenie odovzdávajte podľa
[pokynov na konci tohoto zadania](#technické-detaily-riešenia)
do Štvrtka 12.3.  23:59:59.**

Do triedy `Formula` z cvičenia 3 doprogramujte statickú metódu
`parse`, ktorá dostane ako argument reťazec vo formáte, aký vyrába
metóda `toString`, a vráti formulu, ktorú reprezentuje. Volanie
`Formula::parse("a=>-b")` resp. `Formula.parse('a=>-b')` by teda
mala vrátiť to isté ako
```c++
new Implication(new Variable("a"), new Negation( new Variable("b")));
```
respektíve
```python
Implication(Variable('a'), Negation(Variable('b')))
```

## Technické detaily riešenia
Riešenie odovzdajte do vetvy `bonus01` v adresári `bonus01`.  Rovnako ako pri
cvičení 3 odovzdávajte súbor `formula.h`/`formula.cpp`, `formula.py`, alebo
`Formula.java`.

### Python
Program [`bonus01test.py`](bonus01test.py) musí korektne zbehnúť s vašou knižnicou
(súborom `formula.py`, ktorý odovzdáte).

### C++
Program [`bonus01test.cpp`](bonus01test.cpp) musí byť skompilovateľný keď k nemu priložíte vašu knižnicu
(súbory `formula.h`/`formula.cpp`, ktoré odovzdáte).

### Java
Program [`Bonsu01Test.java`](Bonsu01Test.java) musí byť skompilovateľný, keď sa k
nemu priloží vaša knižnica (súbor `Formula.java`).
