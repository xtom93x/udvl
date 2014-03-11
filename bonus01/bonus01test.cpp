#include <iostream>
#include <string>
#include "formula.h"

struct Case {
	Case(const Interpretation &i_, bool result_)
		: i(i_)
		, result(result_)
	{}
	Interpretation i;
	bool result;
};

/**
 * Pekny vypis interpretatcie
 */
std::ostream& operator<< (std::ostream& stream, const Interpretation &i)
{
	stream << "{ ";
	for(auto p : i) {
		stream << p.first << ": " << p.second << " ";
	}
	stream << "}";
	return stream;
}

class Tester {
	int m_tested = 0;
	int m_passed = 0;
public:
	template<typename T>
	void compare(const T &result, const T &expected, const std::string &msg)
	{
		m_tested++;
		if (result == expected) {
			m_passed++;
		}
		else {
			std::cerr << "    Failed: " << msg << ":" << std::endl;
			std::cerr << "      got " << result << " expected: " << expected << std::endl;
		}
	}

	// typeid(x).name() is not that reliable
	std::string formulaType(Formula *a)
	{
		if (dynamic_cast<Variable*>(a))
			return "Variable";
		if (dynamic_cast<Negation*>(a))
			return "Negation";
		if (dynamic_cast<Disjunction*>(a))
			return "Disjunction";
		if (dynamic_cast<Conjunction*>(a))
			return "Conjunction";
		if (dynamic_cast<Implication*>(a))
			return "Implication";
		if (dynamic_cast<Equivalence*>(a))
			return "Equivalence";
		if (dynamic_cast<Formula*>(a))
			return "Formula";
		return "UNKNOWN";
	}

	bool compareFormulas(Formula *a, Formula *b)
	{
		if (formulaType(a) != formulaType(b)) {
			std::cerr << "    Failed: Formulas do not match" << std::endl;
			std::cerr << "      parsed: " << formulaType(a) << " expected: " << formulaType(b) << std::endl;
			return false;
		}
		if (a->subf().size() != b->subf().size()) {
			std::cerr << "    Failed: different subformula list sizes" << std::endl;
			std::cerr << "      parsed: " << a->subf().size() << " expected: " << b->subf().size() << std::endl;
			return false;
		}
		for(int i=0; i<a->subf().size(); ++i) {
			if (!compareFormulas(a->subf()[i], b->subf()[i]))
				return false;
		}
		return true;
	}

	void test(Formula *f, std::string str, const std::vector<Case> &cases)
	{
		std::cerr << "Testing " << str << std::endl;

		Formula *parsed = Formula::parse(str);
		compare(parsed->toString(), str, "Formula::parse(XXX).toString() == XXX");

		// This expects subf() to work correctly, if it doesn't
		// we still will catch the difference in toplevel formulas
		// or evals below.
		compareFormulas(parsed, f);

		for (const auto &c : cases) {
			std::cerr << "Interpretation " << c.i << std::endl;
			compare(parsed->eval(c.i), c.result, "eval");
		}

		delete parsed;
		delete f;
	}
	void status()
	{
		std::cerr << "TESTED " << m_tested << std::endl;
		std::cerr << "PASSED " << m_passed << std::endl;
		std::cerr << ( m_tested == m_passed ? "OK" : "ERROR" ) << std::endl;
	}
};


int main()
{
	Tester t;

	Interpretation ia1, ia2;
	ia1["a"] = true;  ia2["a"] = false;
	t.test(
			new Variable("a"),
			"a",
			{
				Case(ia1, true),
				Case(ia2, false),
			});

	t.test(
			new Negation(new Variable("a")), "-a",
			{
				Case(ia1, false),
				Case(ia2, true),
			});


	std::vector<Interpretation> interps2;
	{ Interpretation i; i["a"] = false; i["b"] = false ; interps2.push_back(i); }
	{ Interpretation i; i["a"] = false; i["b"] = true  ; interps2.push_back(i); }
	{ Interpretation i; i["a"] = true ; i["b"] = false ; interps2.push_back(i); }
	{ Interpretation i; i["a"] = true ; i["b"] = true  ; interps2.push_back(i); }

	t.test(
			new Conjunction( { new Variable("a"), new Variable("b") } ),
			"(a&b)",
			{
				Case(interps2[0], false),
				Case(interps2[1], false),
				Case(interps2[2], false),
				Case(interps2[3], true),
			});

	t.test(
			new Disjunction( { new Variable("a"), new Variable("b") } ),
			"(a|b)",
			{
				Case(interps2[0], false),
				Case(interps2[1], true),
				Case(interps2[2], true),
				Case(interps2[3], true),
			});

	t.test(
			new Implication( new Variable("a"), new Variable("b") ),
			"(a=>b)",
			{
				Case(interps2[0], true),
				Case(interps2[1], true),
				Case(interps2[2], false),
				Case(interps2[3], true),
			});

	t.test(
			new Equivalence( new Variable("a"), new Variable("b") ),
			"(a<=>b)",
			{
				Case(interps2[0], true),
				Case(interps2[1], false),
				Case(interps2[2], false),
				Case(interps2[3], true),
			});

	t.test(
			new Disjunction({
				new Negation(new Implication(new Variable("a"),new Variable("b"))),
				new Negation(new Implication(new Variable("b"),new Variable("a")))
			}),
			"(-(a=>b)|-(b=>a))",
			{
				Case(interps2[0], false),
				Case(interps2[1], true),
				Case(interps2[2], true),
				Case(interps2[3], false),
			});

	std::vector<Interpretation> interps3;
	{ Interpretation i; i["a"] = false; i["b"] = false, i["c"] = false ; interps3.push_back(i); }
	{ Interpretation i; i["a"] = true ; i["b"] = false, i["c"] = false ; interps3.push_back(i); }
	{ Interpretation i; i["a"] = false; i["b"] = true , i["c"] = false ; interps3.push_back(i); }
	{ Interpretation i; i["a"] = true ; i["b"] = true , i["c"] = false ; interps3.push_back(i); }
	{ Interpretation i; i["a"] = false; i["b"] = false, i["c"] = true  ; interps3.push_back(i); }
	{ Interpretation i; i["a"] = true ; i["b"] = false, i["c"] = true  ; interps3.push_back(i); }
	{ Interpretation i; i["a"] = false; i["b"] = true , i["c"] = true  ; interps3.push_back(i); }
	{ Interpretation i; i["a"] = true ; i["b"] = true , i["c"] = true  ; interps3.push_back(i); }

	t.test(
			new Conjunction({
				new Implication(new Variable("a"),new Variable("b")),
				new Implication(new Negation(new Variable("a")),new Variable("c"))
			}),
			"((a=>b)&(-a=>c))",
			{
				Case(interps3[0], false),
				Case(interps3[1], false),
				Case(interps3[2], false),
				Case(interps3[3], true),
				Case(interps3[4], true),
				Case(interps3[5], false),
				Case(interps3[6], true),
				Case(interps3[7], true),
			});

	t.test(
			new Equivalence(
				new Conjunction({
					new Variable("a"),
					new Negation(new Variable("b"))
				}),
				new Disjunction({
					new Variable("a"),
					new Implication(
						new Variable("b"),
						new Variable("a")
					)
				})
			),
			"((a&-b)<=>(a|(b=>a)))",
			{
				Case(interps2[0], false),
				Case(interps2[1], true),
				Case(interps2[2], true),
				Case(interps2[3], false),
			});

	t.status();
	return 0;
}
