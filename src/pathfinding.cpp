#include "pathfinding.h"



Pathfinding::Pathfinding(void){
	
	initializedStartGoal = false;
	foundGoal = false;

}

void Pathfinding::findPath( vector2 currentPos, vector2 targetPos ){
	
	if (!initializedStartGoal){
		
		for (int i = 0; i < openList.size(); i++) { delete openList[i]; }

		openList.clear();

		for (int i = 0; i < visitedList.size(); i++) { delete visitedList[i]; }

		visitedList.clear();

		for (int i = 0; i < pathToGoal.size(); i++) { delete pathToGoal[i]; }

		pathToGoal.clear();

		//Initialize start
		Node start;
		start.x_Pos = currentPos.x;
		start.y_Pos = currentPos.y;

		//initialize goal
		Node goal;
		goal.x_Pos = targetPos.x;
		goal.y_Pos = targetPos.y;

		set_Start_Goal(start, goal);
		initializedStartGoal = true;

	}
	
	if (initializedStartGoal) { continuePath(); }


}

void Pathfinding::set_Start_Goal(Node start, Node goal)
{

	startNode = new Node(start.x_Pos, start.y_Pos, NULL);
	goalNode = new Node(goal.x_Pos, goal.y_Pos, &goal);

	startNode->G = 0;
	startNode->H = startNode->goalDistance(goalNode);
	startNode->parent = 0;

	openList.push_back(startNode);

}

Node* Pathfinding::getNextNode()
{
	
	double bestF = 999999.0;
	int nodeIndex = -1;
	Node* nextNode = NULL;

	for (int i = 0; i < openList.size(); i++)
	{

		if (openList[i]->getF() < bestF)
		{
			
			bestF = openList[i]->getF();
			nodeIndex = i;

		}

	}

	if (nodeIndex >= 0)
	{
		nextNode = openList[nodeIndex];
		visitedList.push_back(nextNode);
		openList.erase(openList.begin() + nodeIndex);

	}

	return nextNode;
}

void Pathfinding::pathOpened(int x, int y, double newCost, Node* parent)
{

	//if(CELL_BLOCKED) { return; }

	int id = y * 150 + x;

	for (int i = 0; i < visitedList.size(); i++)
	{
		if (id == visitedList[i]->id)
		{
			return;
		}

	}
	
	Node* newChild = new Node(x, y, parent);
	newChild->G = newCost;
	newChild->H = parent->goalDistance(goalNode);

	for (int i = 0; i < openList.size(); i++)
	{

		if (id == openList[i]->id)
		{

			double newF = newChild->G + newCost + openList[i]->H;

			if (openList[i]->getF() > newF)
			{

				openList[i]->G = newChild->G + newCost;
				openList[i]->parent = newChild;

			}
			else
			{

				delete newChild;
				return;

			}

		}

	}

	openList.push_back(newChild);
}

void Pathfinding::continuePath()
{

	if (openList.empty()) { return; }
	
	Node* currentNode = getNextNode();

	if (currentNode->id == goalNode->id)
	{

		goalNode->parent = currentNode->parent;

		Node* getPath;

		for (getPath = goalNode; getPath != NULL; getPath = getPath->parent)
		{

			pathToGoal.push_back(new vector2(getPath->x_Pos, getPath->y_Pos));

		}

		foundGoal = true;
		return;
	}

	else
	{

		//right
		pathOpened(currentNode->x_Pos + 1, currentNode->y_Pos, currentNode->G + 1, currentNode);
		//left
		pathOpened(currentNode->x_Pos - 1, currentNode->y_Pos, currentNode->G + 1, currentNode);
		//up
		pathOpened(currentNode->x_Pos, currentNode->y_Pos + 1, currentNode->G + 1, currentNode);
		//down
		pathOpened(currentNode->x_Pos, currentNode->y_Pos - 1, currentNode->G + 1, currentNode);
		//left-up
		pathOpened(currentNode->x_Pos - 1, currentNode->y_Pos + 1, currentNode->G + 1.414, currentNode);
		//right-up
		pathOpened(currentNode->x_Pos + 1, currentNode->y_Pos + 1, currentNode->G + 1.414, currentNode);
		//left-down
		pathOpened(currentNode->x_Pos - 1, currentNode->y_Pos - 1, currentNode->G + 1.414, currentNode);
		//right-down
		pathOpened(currentNode->x_Pos + 1, currentNode->y_Pos - 1, currentNode->G + 1.414, currentNode);

		for (int i = 0; i < openList.size(); i++)
		{

			if (currentNode->id == openList[i]->id)
			{
				openList.erase(openList.begin() + i);
			}

		}
	}
}

//TODO: Implement structure for storing paths
