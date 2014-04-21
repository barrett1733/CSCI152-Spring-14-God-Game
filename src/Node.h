#ifndef NODE_H_
#define NODE_H_

#include <cmath>

class Node{
public:

	int x_Pos;
	int y_Pos;
	int id;

	Node* parent;

	int G; //traversal challenge
	int H; //heuristic
	


	Node() { parent = 0; }

	Node(int x, int y, Node* p = 0){
		
		x_Pos = x;
		y_Pos = y;
		id = y * WORLD_SIZE + x;
		G = 0;
		H = 0;

	}
	
	double getF() { return G + H; }

	double goalDistance(Node* goalNode){
	
		double x = abs(this->x_Pos - goalNode->x_Pos);
		double y = abs(this->y_Pos - goalNode->y_Pos);

		return x + y;
	
	}

};



#endif 