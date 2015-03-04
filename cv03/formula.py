## created by Tomáš Žitňanský
class Formula():
    def __init__(self):
        self.podform=[]
    def toString(self):
        raise NotImplementedError
    def eval(self,i):
        raise NotImplementedError
    def subf(self):
        return self.podform

class Variable(Formula):
    def __init__(self,name):
        self.podform=[]
        self._name=name
    def name(self):
        return self._name
    def toString(self):
        return self.name()
    def eval(self,i):
        if self.name() not in i:
            raise ValueError
        return i[self.name()]

class Negation(Formula):
    def __init__(self,originalFormula):
        self.podform=[originalFormula]
    def originalFormula(self):
        return self.podform[0]
    def toString(self):
        return "-{}".format(self.originalFormula().toString())
    def eval(self,i):
        return not self.originalFormula().eval(i)

class Implication(Formula):
    def __init__(self,leftSide,rightSide):
        self.podform=[leftSide,rightSide]
    def leftSide(self):
        return self.podform[0]
    def rightSide(self):
        return self.podform[1]
    def toString(self):
        return "({}=>{})".format(self.leftSide().toString(),self.rightSide().toString())
    def eval(self,i):
        return ((not self.leftSide().eval(i))or self.rightSide().eval(i))

class Disjunction(Formula):
    def __init__(self,disjuncts):
        self.podform=disjuncts
    def toString(self):
        ret="("
        for podformula in self.podform:
            if ret!="(":
                ret+="|"
            ret+=podformula.toString()
        return ret+")"
    def eval(self,i):
        index=0
        ret=True
        while index<len(self.podform) and not self.podform[index].eval(i):
            index+=1
        return index<len(self.podform)

class Conjunction(Formula):
    def __init__(self,conjuncts):
        self.podform=conjuncts
    def toString(self):
        ret="("
        for podformula in self.podform:
            if ret!="(":
                ret+="&"
            ret+=podformula.toString()
        return ret+")"
    def eval(self,i):
        index=0
        ret=True
        while index<len(self.podform) and self.podform[index].eval(i):
            index+=1
        return index==len(self.podform)

class Equivalence(Formula):
    def __init__(self,leftSide,rightSide):
        self.podform=[leftSide,rightSide]
    def leftSide(self):
        return self.podform[0]
    def rightSide(self):
        return self.podform[1]
    def toString(self):
        return "({}<=>{})".format(self.leftSide().toString(),self.rightSide().toString())
    def eval(self,i):
        left=self.leftSide().eval(i)
        right=self.rightSide().eval(i)
        return ((not left)and (not right))or(left and right)
