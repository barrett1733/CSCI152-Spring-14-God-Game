#ifndef NODE_H
#define NODE_H

class Node{

	int xPos;
	int yPos;

public:
	// total distance already travelled to reach the node
	int level;

	// priority = level+remaining distance estimate
	int priority;

	Node(int xp, int yp, int d, int p){
		xPos = xp;
		yPos = yp;
		level = d;
		priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int& xDest, const int& yDest){

		priority = level + estimate(xDest, yDest) * 10;

	}

	//better priority for going straight instead of diagonal
	void nextLevel(const int& i){ // i is direction

		level += (dir == 8 ? (1 % 2 == 0 ? 10 : 4) : 10);

	}

	//estimation function for the remaining distance to the goal
	const int& estimate(const int& xDest, const int& yDest){

		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		//Euclidean 
		//d = static_cast<int>(sqrt(xd*xd + yd*yd));

		//Manhatttan distance
		d = abs(xd) + abs(yd);

		//Chebyshev distance
		//d = max(abs(xd), abs(yd));

		return d;

	}


};



#endif 