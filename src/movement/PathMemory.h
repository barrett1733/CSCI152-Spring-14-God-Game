#ifndef PATH_MEMORY_H_
#define PATH_MEMORY_H_

#include "position.h"
#include <vector>
#include "grid.h"

typedef std::vector<Position> Path;

//
// This entire class should be on its own rather than
// inherited by MobileEntity
// - SB
//

class PathMemory
{
public:
	enum PathMapState { UNKNOWN, OBSERVED, VISITED };
	PathMemory();
	~PathMemory();
	void shareMemories(PathMemory*, PathMemory*);
	Position moveOnPath(Position current, Position next, Position end);
	bool goalReached(Position goal);
	Grid<PathMapState> pathMap; // Should not be public

private:
	struct Memory{
		Position target;
		Position start;
		Path path; // first element is closest to the start
		bool pathComplete;
	};
	std::vector<Memory*> pathMemories;
	Memory* currentPath;
	Position* currentPos;

	void switchMemoryDirection(Memory*);
	void startPath(Position start, Position target);
	Memory* getMemory(Position start, Position target);
	bool existsPath(Position start, Position target);
	Position getNextPosition(Position);
};

#endif