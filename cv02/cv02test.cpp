#define CATCH_CONFIG_MAIN
#include "../tools/cpp/catch.hpp"

#include "NQueens.h"

template <class T>
std::ostream& operator<<(std::ostream&os, const std::vector<T>& v)
{
	os<<"(";
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, ", "));
	return os<<")";
}


std::ostream& operator<<(std::ostream&os, const NQueens::Queen &q)
{
	return os << "(" << q.r << "," << q.c << ")";
}


void testQueens(int N) {
	CAPTURE(N);

	NQueens nqueens;
	auto queens = nqueens.solve(N);
	CAPTURE(queens);

	if (N == 2 || N == 3) {
		INFO("There is not solution for " << N);
		REQUIRE(queens.size() == 0);
	}
	else {
		REQUIRE(queens.size() == N);
		for(auto &q : queens) {
			INFO("Bad coordinates for queen q=" << q);
			REQUIRE(q.r >= 0);
			REQUIRE(q.r < N);
			REQUIRE(q.c >= 0);
			REQUIRE(q.c < N);
		}
		for(auto q1 = queens.begin(); q1 != queens.end(); ++q1) {
			for(auto q2 = q1 + 1; q2 != queens.end(); ++q2) {
				INFO("Queens in the same row/column " << *q1 << " " << *q2);
				REQUIRE(q1->r != q2->r);
				REQUIRE(q1->c != q2->c);
			}
		}
		for(auto q1 = queens.begin(); q1 != queens.end(); ++q1) {
			for(auto q2 = q1 + 1; q2 != queens.end(); ++q2) {
				INFO("Queens on the same diagonal " << *q1 << " " << *q2);
				REQUIRE((q1->r + q2->c) != (q1->c + q2->r));
				REQUIRE((q1->r + q1->c) != (q2->c + q2->r));
			}
		}

	}
}

TEST_CASE("nqueens0") { testQueens(0); }
TEST_CASE("nqueens1") { testQueens(1); }
TEST_CASE("nqueens2") { testQueens(2); }
TEST_CASE("nqueens3") { testQueens(3); }
TEST_CASE("nqueens4") { testQueens(4); }
TEST_CASE("nqueens5") { testQueens(5); }
TEST_CASE("nqueens6") { testQueens(6); }
TEST_CASE("nqueens7") { testQueens(7); }
TEST_CASE("nqueens8") { testQueens(8); }
