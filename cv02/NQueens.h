#include <vector>

class NQueens
{
public:
	struct Queen { int r; int c; };
	std::vector<Queen> solve(int NN);
};
