#include "path-searching.h"


Node* PathSearching::searchAStar(Position start, Position goal, ObstructionMap* obsMap)
{
	indexGraph.set(start, NULL, 0, DiagonalDistance(start, goal));
	openList.push(&indexGraph[start]);

	while (!openList.empty())
	{
		current = openList.pop();
		if (current->pos == goal)
			return current; // need to construct the path

		closedList.push(current);
		for (int direction = D_NORTH; direction < D_COUNT; direction++)
		{
			Position neighbor = current->pos.getNeighbor(direction);
			if (neighbor.checkSanity()) // check obsmap here
			{
				if (closedList.exists(neighbor))
					continue;
				double tempgcost = current->gcost + EuclideanDistance(current->pos, neighbor);
				if (!openList.exists(neighbor) || tempgcost < indexGraph[neighbor].gcost)
				{
					indexGraph.set(neighbor, current, tempgcost, tempgcost + DiagonalDistance(neighbor, goal));
					if (openList.exists(neighbor))
						openList.push(&indexGraph[neighbor]);
				}
			}
		}
	}
	return NULL;
}

Node* PathSearching::searchDijkstra(Position start, Position goal, ObstructionMap* obsMap)
{
	/* From wikipedia
	1  function Dijkstra(Graph, source):
	2      dist[source]  := 0                     // Distance from source to source
	3      for each vertex v in Graph:            // Initializations
	4          if v ≠ source
	5              dist[v]  := infinity           // Unknown distance function from source to v
	6              previous[v]  := undefined      // Previous node in optimal path from source
	7          end if
	8          add v to Q                         // All nodes initially in Q (unvisited nodes)
	9      end for
	10
	11      while Q is not empty:                  // The main loop
	12          u := vertex in Q with min dist[u]  // Source node in first case
	13          remove u from Q
	14
	15          for each neighbor v of u:           // where v has not yet been removed from Q.
	16              alt := dist[u] + length(u, v)
	17              if alt < dist[v]:               // A shorter path to v has been found
	18                  dist[v]  := alt
	19                  previous[v]  := u
	20              end if
	21          end for
	22      end while
	23      return dist[], previous[]
	24  end function
	*/
	return NULL;
}

Node* PathSearching::searchFloydWarshall(Position start, Position goal, ObstructionMap* obsMap)
{
	/* From wikipedia
	1 let dist be a |V| × |V| array of minimum distances initialized to ∞ (infinity)
	2 for each vertex v
	3    dist[v][v] ← 0
	4 for each edge (u,v)
	5    dist[u][v] ← w(u,v)  // the weight of the edge (u,v)
	6 for k from 1 to |V|
	7    for i from 1 to |V|
	8       for j from 1 to |V|
	9          if dist[i][j] > dist[i][k] + dist[k][j] 
	10             dist[i][j] ← dist[i][k] + dist[k][j]
	11         end if
	*/

}

Path PathSearching::constructPath(Node* goal)
{
	Node* node = goal;
	Path path;
	path.reserve(Position::max_x * Position::max_y);

	if (node->parentNode == NULL)
	{
		path.push_back(node->pos);
		return path;
	}

	while (node->parentNode != NULL)
	{
		path.push_back(node->pos);
		node = node->parentNode;
	}
	std::reverse(path.begin(), path.end());

	clearContents();

	return path;
}

Path PathSearching::findPath(Algorithm alg, Position start, Position goal, ObstructionMap* obsMap)
{
	switch (alg)
	{
	case AStar:
		return constructPath(searchAStar(start, goal, obsMap));
	case Dijkstra:
		return constructPath(searchAStar(start, goal, obsMap));
	case FloydWarshall:
		return constructPath(searchAStar(start, goal, obsMap));
	default:
		std::cout << "Critical Error in Search::findPath()" << std::endl;
	}
}

Position PathSearching::findPosition(Algorithm alg, Position start, Position goal, ObstructionMap* obsMap)
{
	return findPath(alg, start, goal, obsMap)[0];
}

void PathSearching::clearContents()
{
	openList.clear();
	closedList.clear();
	indexGraph.clear();
	current = NULL;
}