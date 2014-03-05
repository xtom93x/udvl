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
`formula.java`.


