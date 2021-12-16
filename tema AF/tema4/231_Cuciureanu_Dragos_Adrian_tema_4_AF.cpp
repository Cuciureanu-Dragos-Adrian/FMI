#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("citire.in");
ofstream fout("afisare.out");


class Graph
{
public:
	struct Edge
	{
		int _nrOrd, _startingNode, _destinationNode, _distance, _capacity;

		Edge(int nrOrd, int startingNode, int destinationNode, int distance = 0, int capacity = 0)
		{
			_nrOrd = nrOrd;
			_startingNode = startingNode;
			_destinationNode = destinationNode;
			_distance = distance;
			_capacity = capacity;
		}

		operator int()
		{
			return _distance;
		}
	};

private:
	bool _oriented;
	bool _weighted;
	bool _capacity;

	int _nrNodes;
	int _nrEdges;

	vector < vector <Edge> > _neighborList;

	//does a bfs on the graph
	void BFS(vector<bool>& visitedNodes, vector<int>& distances, int startNode);
	//does a dfs on the graph
	void DFS(vector<bool>& visitedNodes, int currentNode);
	//does a dfs used for biconnected components
	void DFS_biconnectedComponents(vector< vector <int> >& bcc, stack<int>& nodeStack, vector<bool>& visited, vector<int>& depth, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int currentDepth);
	//tarjan's dfs, used for strongly connected components
	void TDFS(vector< vector <int> >& scc, stack<int>& nodeStack, vector<bool>& stackMember, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int& currentTime);
	//tarjan's dfs, used for critical connections
	void TDFS_criticalConnections(vector< vector<int> >& solution, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int& currentTime);
	//does a dfs, used for the toplogical sort
	void DFS_topologicalSort(stack<int>& result, vector<bool>& visitedNodes, int currentNode);
	//does dijkstra's algorithm
	void Dijkstra(priority_queue < pair<int, int>, vector< pair<int, int> >, greater <pair<int, int>> >& heap, vector<bool>& visitedNodes, vector<int>& distances);
	//does BellmanFord's algorithm
	void BellmanFord(queue<int>& nodeOrder, vector<bool>& inQueue, vector<int>& distances, vector<int>& numberOfAparitions, int startNode);
	//used in DisjointSet
	static int getRootDisjointSet(vector<int>& parent, int currentNode);
	//used in DisjointSet
	static void changeColorDisjointSet(vector<int>& parent, vector<int>& height, int node1, int node2);
	//BFS used in Edmonds-Karp's algorithm
	bool BFS_maxFlow(vector<vector<int>>& capacity, vector<vector<int>>& flow, vector<int>& parent, vector<bool>& visitedNodes, int startNode, int destinationNode);
	//Edmonds-Karp's algorithm
	int EdmondsKarp(vector<vector<int>>& capacity, vector<vector<int>>& flow, vector<int>& parent, vector<bool>& visitedNodes, int startNode, int destinationNode);
	//gets an Euler cycle if there is one
	void EulerCycle(vector<bool>& visitedEdges, vector<int>& solution, int& edgeCounter, int sourceNode);
	//cheks if a node is eligible
	bool checkNode_HopcroftKarp(vector<int>& leftGraph, vector<int>& rightGraph, vector<bool>& visitedNodes, int currentNode);
	//returns a vector which is contains the maximum bipartite matching using Hopcroft–Karp's algorithm
	void HopcroftKarp(vector<int>& leftGraph, vector<int>& rightGraph);
	//reads the Graph since the problem requires an unique reading
	void readHamiltonGraph(istream& input);
	//determines the cost of the minimal Hamilton cycle, or returns 2e9 if there isn't one
	int determineMinimalCostHamiltonCycle(vector<vector<int>>& minimalCost);


public:
	Graph(int nrNodes = 0, int nrEdges = 0, bool oriented = false, bool weighted = false, bool capacity = false);
	~Graph() {}

#pragma region Setters&Getters
	void setOrientation(bool orientation)
	{
		_oriented = orientation;
	}
	void setNrNodes(int nrNodes)
	{
		_nrNodes = nrNodes;
	}
	void setNrEdges(int nrEdges)
	{
		_nrEdges = nrEdges;
	}

	bool getOrientation()
	{
		return _oriented;
	}
	int getNrNodes()
	{
		return _nrNodes;
	}
	int getNrEdges()
	{
		return _nrEdges;
	}
#pragma endregion

	//reads and builds the graph
	void buildNeighborList(istream& input);
	//returns a vector of all the edges
	vector<Edge> getEdges();
	//adds an edge to the graph
	void addEdge(Edge newEdge);

	//Function Wrappers

	//minimal distances from a starting node
	vector<int> minimalDistances(int startNode);
	//returns the number of conex components
	int numberOfConexComponents();
	//returns the biconnected components
	// de modificat numele
	vector< vector <int> > biconnectedComponents();
	//returns the strongly connected componentss
	//de modificat numele
	vector< vector <int> > stronglyConnectedComponents();
	//returns the critical connections
	vector< vector <int> > criticalConnections();
	//does the nodes that exists in all minimal ways between two nodes
	vector<int> minimalDistanceBetweenTwoNodes(int startNode, int finishNode);
	//returns if a graph exists
	bool HavelHakimi(istream& input);
	//returns the topological sort
	vector<int> topologicalSort();
	//returns the minimal positive only weighted distances, using dijkstra's algorithm
	vector<int> minimalWeightedDistances(int startNode);
	//returns minimal negative weighted distances, using BellmanFord's algorithm
	vector<int> minimalNegativeWeightedDistances(int startNode);
	//the function where getRootDisjointSet and changeColorDisjointSet are used in  a disjoint set
	static void disjointSet(istream& input, ostream& output);
	//returns the mst(apm) of the graph
	vector<Edge> minimumSpanningTree();
	//returns the distance from any node to any node
	vector< vector <int> > RoyFloyd();
	//returns the diameter of a tree
	int diameterOfTree();
	//returns the max flow of a network
	int maxFlow();
	//returns the Euler cycle, if there is one
	vector<int> buildEulerCycle();
	//returns the maximum bipartite matching
	vector<int> maximumBipartiteMatching(int nrNodesRightGraph);
	//returns the cost of the minimal Hamilton cycle, or returns 2e9 if there isn't one
	int minimalCostHamiltonCycle(istream& input);
};

Graph::Graph(int nrNodes, int nrEdges, bool oriented, bool weighted, bool capacity)
{
	_nrNodes = nrNodes;
	_nrEdges = nrEdges;

	_oriented = oriented;
	_weighted = weighted;
	_capacity = capacity;

	vector <Edge> emptyVector;

	for (int i = 0; i < nrNodes; i++)
	{
		_neighborList.push_back(emptyVector);
	}
}

void Graph::BFS(vector<bool>& visitedNodes, vector<int>& distances, int startNode)
{
	queue<int> nodeOrder;

	nodeOrder.push(startNode);
	distances[startNode] = 0;

	while (nodeOrder.empty() == false)
	{
		int currentNode = nodeOrder.front();
		visitedNodes[currentNode] = true;

		for (auto& neighbor : _neighborList[currentNode])
		{
			int neighborNode = neighbor._destinationNode;

			if (visitedNodes[neighborNode] == false)
			{
				nodeOrder.push(neighborNode);
				distances[neighborNode] = distances[currentNode] + 1;
				visitedNodes[neighborNode] = true;
			}
		}

		nodeOrder.pop();
	}
}

void Graph::DFS(vector<bool>& visitedNodes, int currentNode)
{
	visitedNodes[currentNode] = true;

	for (auto& neighbor : _neighborList[currentNode])
	{
		int neighborNode = neighbor._destinationNode;

		if (visitedNodes[neighborNode] == false)
		{
			DFS(visitedNodes, neighborNode);
		}
	}
}

void Graph::DFS_biconnectedComponents(vector< vector <int>>& bcc, stack<int>& nodeStack, vector<bool>& visited, vector<int>& depth, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int currentDepth)
{
	depth[currentNode] = currentDepth;														//initializing the depth of the current node
	lowestDepthReacheable[currentNode] = currentDepth;										//initializing the lowest depth reacheble time of the current node
	visited[currentNode] = true;															//insert the current node in the stack and mark it as visited
	nodeStack.push(currentNode);

	for (auto& neighbor : _neighborList[currentNode])
	{
		int neighborNode = neighbor._destinationNode;

		if (neighborNode != parentNode)
		{
			if (visited[neighborNode] == true)
			{
				lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], depth[neighborNode]);						//this is were the back edges are found
			}
			else
			{
				DFS_biconnectedComponents(bcc, nodeStack, visited, depth, lowestDepthReacheable, neighborNode, currentNode, currentDepth + 1);

				lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], lowestDepthReacheable[neighborNode]);		//updating with lowest depth that the descendants can reach

				if (depth[currentNode] <= lowestDepthReacheable[neighborNode])					//if it is true it means that the neighbor has no back edge above the current node
				{																			//current node separates two biconnected components
					vector <int> biconnectedComponent;
					biconnectedComponent.push_back(currentNode);

					int node = nodeStack.top();
					nodeStack.pop();
					biconnectedComponent.push_back(node);

					while (node != neighborNode)												//pop nodes until we reach the neighbor (inclusive) and that is the current biconnected component
					{
						node = nodeStack.top();
						nodeStack.pop();
						biconnectedComponent.push_back(node);
					}

					bcc.push_back(biconnectedComponent);									//adding it to the rest of the components
				}
			}
		}
	}
}

void Graph::TDFS(vector< vector <int> >& scc, stack<int>& nodeStack, vector<bool>& stackMember, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int& currentTime)
{
	discoveryOrder[currentNode] = currentTime;										//initializing the discovery time of the current node
	lowestDepthReacheable[currentNode] = currentTime;								//initializing the lowest depth reacheble time of the current node
	stackMember[currentNode] = true;												//insert the current node in the stack and mark it 
	nodeStack.push(currentNode);
	currentTime++;																	//increment the time

	for (auto& neighbor : _neighborList[currentNode])								//visit all neibors
	{
		int neighborNode = neighbor._destinationNode;

		if (discoveryOrder[neighborNode] == -1)																								//if it has not been visited yet
		{
			TDFS(scc, nodeStack, stackMember, discoveryOrder, lowestDepthReacheable, neighborNode, currentTime);							//DFS on that node

			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], lowestDepthReacheable[neighborNode]);				//actualizing on the recursion return path
		}
		else if (stackMember[neighborNode] == true)										//if the neighbor is on the stack is part of the current strongly connected component
		{
			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], discoveryOrder[neighborNode]);
		}
	}

	if (lowestDepthReacheable[currentNode] == discoveryOrder[currentNode])			//if lowestDepthReacheable and discoveryOrder are equal it means the current node is the root of 
	{																				//the current strongly connected component
		vector <int> stronglyConnectedComponent;

		int node = nodeStack.top();
		nodeStack.pop();
		stackMember[node] = false;
		stronglyConnectedComponent.push_back(node);

		while (node != currentNode)													//pop nodes until we reach current node (inclusive) and that is the current strongly connected component
		{
			node = nodeStack.top();
			nodeStack.pop();
			stackMember[node] = false;
			stronglyConnectedComponent.push_back(node);
		}

		scc.push_back(stronglyConnectedComponent);									//adding it to the rest of the components
	}
}

void Graph::TDFS_criticalConnections(vector< vector<int> >& solution, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int& currentTime)
{
	discoveryOrder[currentNode] = currentTime;
	lowestDepthReacheable[currentNode] = currentTime;
	currentTime++;

	for (auto& neighbor : _neighborList[currentNode])
	{
		int neighborNode = neighbor._destinationNode;

		if (discoveryOrder[neighborNode] == -1)
		{
			TDFS_criticalConnections(solution, discoveryOrder, lowestDepthReacheable, neighborNode, currentNode, currentTime);

			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], lowestDepthReacheable[neighborNode]);

			if (lowestDepthReacheable[neighborNode] > discoveryOrder[currentNode])
			{
				vector <int> result;

				result.push_back(currentNode);
				result.push_back(neighborNode);

				solution.push_back(result);
			}

		}
		else if (neighborNode != parentNode)
		{
			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], discoveryOrder[neighborNode]);
		}
	}
}

void Graph::DFS_topologicalSort(stack<int>& result, vector<bool>& visitedNodes, int currentNode)
{
	visitedNodes[currentNode] = true;

	for (auto& neighbor : _neighborList[currentNode])
	{
		int neighborNode = neighbor._destinationNode;

		if (visitedNodes[neighborNode] == false)
		{
			DFS_topologicalSort(result, visitedNodes, neighborNode);
		}
	}

	result.push(currentNode);
}

void Graph::Dijkstra(priority_queue < pair<int, int>, vector< pair<int, int> >, greater <pair<int, int>>>& heap, vector<bool>& visitedNodes, vector<int>& distances)
{
	while (heap.empty() == false)																									//while the heap has elements
	{
		pair <int, int> currentPair = heap.top();
		heap.pop();

		int currentNode = currentPair.second;
		int currentDistance = currentPair.first;

		visitedNodes[currentNode] = true;

		if (currentDistance == distances[currentNode])																				//if the current distance is not the same as the one we have in the distance vector it means that we have 
		{																															//already found a better way
			for (auto& neighborPair : _neighborList[currentNode])																	//visit all neibors
			{
				int neighborNode = neighborPair._destinationNode;
				int edgeDistance = neighborPair._distance;

				if (visitedNodes[neighborNode] == false)																			//if the node has been visited we already know the minimal distance to it
				{
					if (distances[neighborNode] > currentDistance + edgeDistance)													//test if we can find a smaller distance
					{
						distances[neighborNode] = currentDistance + edgeDistance;													//update the minimal distance if we've found a new one
						heap.push(make_pair(distances[neighborNode], neighborNode));												//push the node and it's distance in the heap
					}
				}
			}
		}
	}
}

void Graph::BellmanFord(queue<int>& nodeOrder, vector<bool>& inQueue, vector<int>& distances, vector<int>& numberOfAparitions, int startNode)
{
	while (nodeOrder.empty() == false)
	{
		int currentNode = nodeOrder.front();
		nodeOrder.pop();

		inQueue[currentNode] = false;
		numberOfAparitions[currentNode]++;

		if (numberOfAparitions[currentNode] == _nrNodes)																		//if we've encountered the same node (number of nodes - 1) times it means we are in a negative loop
		{
			distances[startNode] = -1;
			break;
		}

		for (auto& neighborPair : _neighborList[currentNode])																		//visit all neibors
		{
			int neighborNode = neighborPair._destinationNode;
			int edgeDistance = neighborPair._distance;

			if (distances[neighborNode] > distances[currentNode] + edgeDistance)													//test if we can find a smaller distance
			{
				distances[neighborNode] = distances[currentNode] + edgeDistance;													//update the minimal distance if we've found a new one

				if (inQueue[neighborNode] == false)
				{
					nodeOrder.push(neighborNode);																					//if it's not in the queue to be processed, we push it
					inQueue[neighborNode] = true;																					//and check it
				}
			}
		}
	}
}

int Graph::getRootDisjointSet(vector<int>& parent, int currentNode)
{
	int root = currentNode;

	while (parent[root] != root)
	{
		root = parent[root];
	}

	while (parent[currentNode] != root) {
		int aux = parent[currentNode];
		parent[currentNode] = root;
		currentNode = aux;
	}

	return root;
}

void Graph::changeColorDisjointSet(vector<int>& parent, vector<int>& height, int node1, int node2)
{
	int rootNode1 = Graph::getRootDisjointSet(parent, node1);
	int rootNode2 = Graph::getRootDisjointSet(parent, node2);

	if (rootNode1 == rootNode2)
		return;

	if (height[rootNode1] < height[rootNode2])
	{
		parent[rootNode1] = rootNode2;
		height[rootNode2] += height[rootNode1];
	}
	else
	{
		parent[rootNode2] = rootNode1;
		height[rootNode1] += height[rootNode2];
	}
}

/// <summary>
/// does a BFS on the network to determine the parents
/// </summary>
/// <param name="capacity"></param>
/// <param name="flow"></param>
/// <param name="parent"></param>
/// <param name="visitedNodes"></param>
/// <param name="startNode"></param>
/// <param name="destinationNode"></param>
/// <returns></returns>
bool Graph::BFS_maxFlow(vector<vector<int>>& capacity, vector<vector<int>>& flow, vector<int>& parent, vector<bool>& visitedNodes, int startNode, int destinationNode)
{
	queue<int> nodeOrder;
	nodeOrder.push(startNode);

	for (int i = 0; i < _nrNodes; i++)
	{
		visitedNodes[i] = false;
	}

	while (nodeOrder.empty() == false)
	{
		int node = nodeOrder.front();
		nodeOrder.pop();
		visitedNodes[node] = true;

		if (node != destinationNode)
		{
			for (auto& edge : _neighborList[node])
			{
				if (capacity[node][edge._destinationNode] == flow[node][edge._destinationNode] || visitedNodes[edge._destinationNode] == true)
				{
					continue;
				}

				parent[edge._destinationNode] = node;
				nodeOrder.push(edge._destinationNode);
			}
		}
	}

	return visitedNodes[destinationNode];
}

int Graph::EdmondsKarp(vector<vector<int>>& capacity, vector<vector<int>>& flow, vector<int>& parent, vector<bool>& visitedNodes, int startNode, int destinationNode)
{
	int max_flow = 0;

	while (BFS_maxFlow(capacity, flow, parent, visitedNodes, startNode, destinationNode) == true)						//while there is a way
	{
		for (auto& edge : _neighborList[destinationNode])
		{
			int node = edge._destinationNode;

			if (flow[node][destinationNode] == capacity[node][destinationNode] || visitedNodes[node] == false)
			{
				continue;					//if the flow is already at the amximum or if the node isnot part of out way we skip
			}

			int minflow = 2e9;

			parent[destinationNode] = node;																				//initialize the parent

			for (int vertex = destinationNode; vertex != startNode; vertex = parent[vertex])
			{
				minflow = min(minflow, capacity[parent[vertex]][vertex] - flow[parent[vertex]][vertex]);				//determine the minflow of a way
			}

			if (minflow != 0)
			{
				for (int vertex = destinationNode; vertex != startNode; vertex = parent[vertex])
				{
					flow[parent[vertex]][vertex] += minflow;															//add the minflow to the direct way
					flow[vertex][parent[vertex]] -= minflow;															//substract the reverse way
				}

				max_flow += minflow;																					//add to the overall flow
			}
		}
	}

	return max_flow;
}

void Graph::EulerCycle(vector<bool>& visitedEdges, vector<int>& solution, int& edgeCounter, int sourceNode)
{
	while (_neighborList[sourceNode].empty() == false)
	{
		Edge edge = _neighborList[sourceNode].back();

		int destinationNode = edge._destinationNode;
		int edgeNrOrd = edge._nrOrd;

		_neighborList[sourceNode].pop_back();

		if (visitedEdges[edgeNrOrd] == false)
		{
			visitedEdges[edgeNrOrd] = true;

			EulerCycle(visitedEdges, solution, edgeCounter, destinationNode);
		}
	}

	solution.push_back(sourceNode);
	edgeCounter++;
}

bool Graph::checkNode_HopcroftKarp(vector<int>& leftGraph, vector<int>& rightGraph, vector<bool>& visitedNodes,  int currentNode)
{
	if (visitedNodes[currentNode] == true)
	{
		return false;
	}

	visitedNodes[currentNode] = true;

	for (auto& edge : _neighborList[currentNode])
	{
		int destinationNode = edge._destinationNode;
		
		if (rightGraph[destinationNode] == -1)
		{
			leftGraph[currentNode] = destinationNode;
			rightGraph[destinationNode] = currentNode;
			
			return true;
		}
	}

	for (auto& edge : _neighborList[currentNode])
	{
		int destinationNode = edge._destinationNode;
		
		if (checkNode_HopcroftKarp(leftGraph, rightGraph, visitedNodes, rightGraph[destinationNode]) == true)
		{
			leftGraph[currentNode] = destinationNode;
			rightGraph[destinationNode] = currentNode;
			
			return true;
		}
	}

	return false;
}

void Graph::HopcroftKarp(vector<int>& leftGraph, vector<int>& rightGraph)
{
	bool change = true;

	while (change == true)
	{
		change = false;

		int size = max(leftGraph.size(), rightGraph.size());
		vector<bool> visitedNodes(size, false);

		for (int i = 0; i < _nrNodes; i++)
		{
			if (leftGraph[i] == -1) 
			{ 
				if (checkNode_HopcroftKarp(leftGraph, rightGraph, visitedNodes, i) == true)
				{
					change = true;
				}
			}
		}
	}
}

void Graph::readHamiltonGraph(istream& input)
{
	int node1, node2, cost;

	for (int i = 0; i < _nrEdges; i++)
	{
		input >> node1 >> node2 >> cost;

		Edge newEdge(i, node2, node1, cost, 0);

		_neighborList[node2].push_back(newEdge);
	}
}

int Graph::determineMinimalCostHamiltonCycle(vector<vector<int>>& minimalCost)
{
	for (int i = 0; i < (1 << _nrNodes); i++)					//every combination of nodes (if the current bit is set to 1, it is part of the chain)
	{
		for (int j = 0; j < _nrNodes; j++)						//the node we wish to add to the current chain
		{
			if ( (i & (1 << j)) != 0)							//check if the node j is in the current chain
			{
				for (auto& edge : _neighborList[j]) 
				{
					int node = edge._destinationNode;
					int cost = edge._distance;

					if ( (i & (1 << node)) != 0)				//check if the node is in the current chain
					{
						minimalCost[i][j] = min(minimalCost[i][j], minimalCost[i ^ (1 << j)][node] + cost);
						//update the minimal cost using i nodes that end in j
					}
				}
			}
		}
	}

	int minCost = 2e9;																		//initialize the minimal cost
	for (auto& edge : _neighborList[0])
	{
		int node = edge._destinationNode;
		int cost = edge._distance;

		minCost = min(minCost, minimalCost[((1 << _nrNodes) - 1)][node] + cost);			//determine the minimal cost
	}

	return minCost;
}




void Graph::buildNeighborList(istream& input)
{
	int node1, node2, distance, capacity;

	for (int i = 0; i < _nrEdges; i++)
	{
		input >> node1 >> node2;

		node1--;
		node2--;

		if (_weighted == true)
		{
			fin >> distance;
		}
		else
		{
			distance = 0;
		}

		if (_capacity == true)
		{
			fin >> capacity;
		}
		else
		{
			capacity = 0;
		}

		Edge newEdge(i, node1, node2, distance, capacity);

		_neighborList[node1].push_back(newEdge);

		if (_oriented == false)
		{
			Edge newEdge(i, node2, node1, distance, capacity);

			_neighborList[node2].push_back(newEdge);
		}
	}
}

vector<Graph::Edge> Graph::getEdges()
{
	vector<Edge> edges;

	if (_oriented == true)
	{
		for (int node = 0; node < _nrNodes; node++)
		{
			for (auto& edge : _neighborList[node])
			{
				edges.push_back(edge);
			}
		}
	}
	else
	{
		vector<bool> visited(_nrNodes, false);

		for (int node = 0; node < _nrNodes; node++)
		{
			for (auto& edge : _neighborList[node])
			{
				if (visited[edge._destinationNode] == false)
				{
					edges.push_back(edge);
				}
			}

			visited[node] = true;
		}
	}

	return edges;
}

void Graph::addEdge(Edge newEdge)
{
	_neighborList[newEdge._startingNode].push_back(newEdge);

	if (_oriented == false)
	{
		Edge newEdge2(newEdge._destinationNode, newEdge._startingNode, newEdge._distance, newEdge._capacity);

		_neighborList[newEdge._destinationNode].push_back(newEdge2);
	}

	_nrEdges++;
}

vector<int> Graph::minimalDistances(int startNode)
{
	vector <bool> visited(_nrNodes, false);
	vector <int> distances(_nrNodes, -1);

	BFS(visited, distances, startNode);

	return distances;
}

int Graph::numberOfConexComponents()
{
	int numberOfConexComponents = 0;

	vector <bool> visited(_nrNodes, false);

	for (int i = 0; i < _nrNodes; i++)
	{
		if (visited[i] == false)
		{
			DFS(visited, i);
			numberOfConexComponents++;
		}
	}

	return numberOfConexComponents;
}

vector< vector <int> > Graph::biconnectedComponents()								//initializing all data structures needed for the Biconnected DFS Algorithm
{
	vector< vector<int> > bcc;														//this will contain all Biconnected Components

	stack<int> nodeStack;															//will store the connected ancestors

	vector<bool> visited(_nrNodes, false);											//will check whether a node has been visited or not
	vector<int> depth(_nrNodes, -1);												//will cotain the depth of every node
	vector<int> lowestDepthReacheable(_nrNodes, -1);								//will contain the lowest depth a node can reach through its descendants					

	DFS_biconnectedComponents(bcc, nodeStack, visited, depth, lowestDepthReacheable, 0, -1, 0);

	return bcc;
}

vector< vector <int> > Graph::stronglyConnectedComponents()							//initializing all data structures needed for the Tarjan's DFS Algorithm
{
	vector< vector<int> > scc;														//this will contain all Strongly Connected Components

	stack<int> nodeStack;															//will store the connected ancestors

	vector<bool> stackMember(_nrNodes, false);										//will check whether a node is in stack
	vector<int> discoveryOrder(_nrNodes, -1);										//contains the order in which the nodes are dicovered
	vector<int> lowestDepthReacheable(_nrNodes, -1);								//the lowest ancestor that can be reached

	int currentTime = 0;															//a timer used for discoveryOrder and lowestDepthReacheable

	for (int i = 0; i < _nrNodes; i++)
	{
		if (discoveryOrder[i] == -1)												//if the node hasn't been discovered yet, we start the DFS from him
		{
			TDFS(scc, nodeStack, stackMember, discoveryOrder, lowestDepthReacheable, i, currentTime);		//the tarjan's algorithm
		}
	}

	return scc;
}

vector<vector<int>> Graph::criticalConnections()
{
	vector< vector<int> > solution;

	vector<int> discoveryOrder(_nrNodes, -1);
	vector<int> lowestDepthReacheable(_nrNodes, -1);

	int currentTime = 0;

	for (int i = 0; i < _nrNodes; i++)
	{
		if (discoveryOrder[i] == -1)
		{
			TDFS_criticalConnections(solution, discoveryOrder, lowestDepthReacheable, i, -1, currentTime);
		}
	}

	return solution;
}

vector<int> Graph::minimalDistanceBetweenTwoNodes(int startNode, int finishNode)
{
	vector<int> normalWay(_nrNodes, -1);										//will contain the values from the bfs starting from the starting node
	vector<int> reverseWay(_nrNodes, -1);										//will contain the values from the bfs starting from the finishing node
	vector<int> frequency(_nrNodes, 0);										//will contain the frequency of the nodes, if a node is on all of the minimal ways between the starting node and the finishing node,	
	vector<int> result;															//then his distance will be the same from those nodes			

	normalWay = minimalDistances(startNode);									//getting the minimal distances in the normal way
	reverseWay = minimalDistances(finishNode);									//getting the minimal distances in the reverse way

	int minimWay = normalWay[finishNode];										//the minimal distance between the starting node and the finishing node

	for (int i = 0; i < _nrNodes; i++)
		if (normalWay[i] + reverseWay[i] == minimWay)
			frequency[normalWay[i]]++;

	for (int i = 0; i < _nrNodes; i++)
		if (normalWay[i] + reverseWay[i] == minimWay && frequency[normalWay[i]] == 1)
			result.push_back(i);

	return result;
}

bool Graph::HavelHakimi(istream& input)
{
	vector<int> degrees;
	int totalDegree = 0;

	for (int i = 0; i < _nrNodes; i++)
	{
		int degree;
		fin >> degree;

		if (degree < 0 || degree > _nrNodes - 1)
		{
			return false;
		}

		degrees.push_back(degree);
		totalDegree += degree;
	}

	sort(degrees.begin(), degrees.end(), greater<int>());

	if (totalDegree % 2 == 1 || _nrNodes == 1)
	{
		return false;
	}

	while (degrees[1] != 0)
	{
		for (auto degree : degrees)
			fout << degree << " ";
		fout << "\n";

		for (int i = 1; i <= degrees[0]; i++)
		{
			if (degrees[i] != 0)
			{
				degrees[i]--;
			}
			else
			{
				return false;
			}
		}

		degrees[0] = 0;

		sort(degrees.begin(), degrees.end(), greater<int>());
	}

	if (degrees[0] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<int> Graph::topologicalSort()
{
	vector <bool> visited(_nrNodes + 1, false);
	vector<int> solution;

	stack<int> result;

	for (int i = 0; i < _nrNodes; i++)
	{
		if (visited[i] == false)
		{
			DFS_topologicalSort(result, visited, i);
		}
	}

	while (result.empty() == 0)
	{
		solution.push_back(result.top());
		result.pop();
	}

	return solution;
}

/// <summary>
/// complexity O(N + MlogN), using priority queue
/// </summary>
/// <param name="startNode"></param>
/// <returns></returns>
vector<int> Graph::minimalWeightedDistances(int startNode)
{
	priority_queue < pair<int, int>, vector< pair<int, int> >, greater<pair<int, int>> > heap;

	vector <bool> visited(_nrNodes, false);
	vector <int> distances(_nrNodes, 2e9);

	distances[startNode] = 0;

	heap.push(make_pair(0, startNode));

	Dijkstra(heap, visited, distances);

	return distances;
}

/// <summary>
/// complexity O(n * m), using queue
/// </summary>
/// <param name="startNode"></param>
/// <returns></returns>
vector<int> Graph::minimalNegativeWeightedDistances(int startNode)
{
	queue<int> nodeOrder;

	vector <bool> inQueue(_nrNodes, false);
	vector <int> distances(_nrNodes, 2e9);
	vector <int> numberOfAparitions(_nrNodes, 0);

	distances[startNode] = 0;																										//initialize the distance from the starting node to himself
	nodeOrder.push(startNode);																										//push it in the queue
	inQueue[startNode] = true;																										//and check it

	BellmanFord(nodeOrder, inQueue, distances, numberOfAparitions, startNode);

	return distances;
}

void Graph::disjointSet(istream& in, ostream& out)
{
	int nrNodes, nrRequests;

	in >> nrNodes >> nrRequests;

	vector<int> parent(nrNodes);
	vector<int> height(nrNodes, 1);

	for (int i = 0; i < nrNodes; i++)
		parent[i] = i;

	for (int i = 0; i < nrRequests; i++)
	{
		int node1, node2, request;

		in >> request >> node1 >> node2;

		node1--;
		node2--;

		if (request == 1)
		{
			Graph::changeColorDisjointSet(parent, height, node1, node2);
		}
		else
		{
			if (Graph::getRootDisjointSet(parent, node1) == Graph::getRootDisjointSet(parent, node2))
			{
				out << "DA\n";
			}
			else
			{
				out << "NU\n";
			}
		}
	}
}

vector<Graph::Edge> Graph::minimumSpanningTree()
{
	vector<Edge> mst;
	vector<Edge> sortedEdges = getEdges();
	vector<int> parent(_nrNodes);
	vector<int> height(_nrNodes, 1);

	for (int i = 0; i < _nrNodes; i++)
		parent[i] = i;

	sort(sortedEdges.begin(), sortedEdges.end());

	int i = 0, nrEdges = 0;

	while (i < _nrEdges && nrEdges < _nrEdges - 1)
	{

		if (getRootDisjointSet(parent, sortedEdges[i]._startingNode) != getRootDisjointSet(parent, sortedEdges[i]._destinationNode))
		{
			changeColorDisjointSet(parent, height, sortedEdges[i]._startingNode, sortedEdges[i]._destinationNode);
			mst.push_back(sortedEdges[i]);

			nrEdges++;
		}

		i++;
	}

	return mst;
}

/// <summary>
/// complexity O(n^3)
/// </summary>
/// <returns></returns>
vector<vector<int>> Graph::RoyFloyd()
{
	vector<vector<int>> minimalDistances(_nrNodes, vector<int>(_nrNodes, 2e8));

	for (int i = 0; i < _nrNodes; i++)
	{
		int j = 0;

		for (auto edge : _neighborList[i])
		{
			if (edge._distance != 0)
			{
				minimalDistances[i][j] = edge._distance;
			}

			j++;
		}
	}

	for (int k = 0; k < _nrNodes; k++)
	{
		for (int i = 0; i < _nrNodes; i++)
		{
			for (int j = 0; j < _nrNodes; j++)
			{
				if (minimalDistances[i][j] > minimalDistances[i][k] + minimalDistances[k][j])
				{
					minimalDistances[i][j] = minimalDistances[i][k] + minimalDistances[k][j];
				}
			}
		}
	}

	for (int i = 0; i < _nrNodes; i++)
	{
		for (int j = 0; j < _nrNodes; j++)
		{
			if (minimalDistances[i][j] == 2e8 || i == j)
			{
				minimalDistances[i][j] = 0;
			}
		}
	}

	return minimalDistances;
}

int Graph::diameterOfTree() {

	vector<int> distances = minimalDistances(0);

	int maxIndex = 0, maximum = distances[0];

	for (int i = 0; i < _nrNodes; i++)
	{
		if (distances[i] > maximum)
		{
			maximum = distances[i];
			maxIndex = i;
		}
	}

	distances = minimalDistances(maxIndex);

	for (int i = 0; i < _nrNodes; i++)
	{
		if (distances[i] > maximum)
		{
			maximum = distances[i];
		}
	}

	return maximum + 1;
}

/// <summary>
/// will determine the max flow of a network, using Edmonds Krap's algorithm
/// complexity O((N + M) * N * M)
/// </summary>
/// <returns></returns>
int Graph::maxFlow()
{
	vector<vector<int>> capacity(_nrNodes, vector<int>(_nrNodes, 0));										//matrix of capacities
	vector<vector<int>> flow(_nrNodes, vector<int>(_nrNodes, 0));											//matrix of flows
	vector<int> parent(_nrNodes, -1);																		//vector of parents
	vector<bool> visitedNodes(_nrNodes, false);																//vector of the visited nodes

	int maxFlow = 0;

	for (auto& edge : getEdges())																			//add the capacity of all the edges to the matrix of capacities
	{
		capacity[edge._startingNode][edge._destinationNode] = edge._capacity;
	}

	for (auto& edge : getEdges())
	{
		Edge newEdge(edge._destinationNode, edge._startingNode, edge._distance, edge._capacity);			//add the reverse way

		addEdge(newEdge);
	}

	maxFlow = EdmondsKarp(capacity, flow, parent, visitedNodes, 0, _nrNodes - 1);							//obtains the max flow of the network

	return maxFlow;
}

vector<int> Graph::buildEulerCycle()
{
	vector<bool> visitedEdges(_nrEdges, false);
	vector<int> solution;
	int edgeCounter = 0;

	for (int i = 0; i < _nrNodes; i++)
	{
		if (_neighborList[i].size() % 2 == 1)
		{
			solution.push_back(-1);
			return solution;
		}
	}

	EulerCycle(visitedEdges, solution, edgeCounter, 0);

	if (edgeCounter != _nrEdges + 1)
	{
		solution[0] = -1;
		return solution;
	}
	else
	{
		return solution;
	}
}

vector<int> Graph::maximumBipartiteMatching(int nrNodesRightGraph)
{
	vector<int> leftGraph(_nrNodes, -1);
	vector<int> rightGraph(nrNodesRightGraph, -1);
	
	HopcroftKarp(leftGraph, rightGraph);
	
	return leftGraph;
}

int Graph::minimalCostHamiltonCycle(istream& input)
{
	vector<vector<int>> minimalCost((1 << _nrNodes), vector<int>(_nrNodes, 2e9));		
	//minimalCost[i][j] contains the minimal cost that end in j and has all the nodes that are set in i 
	minimalCost[1][0] = 0;

	int minCost;

	readHamiltonGraph(input);													//read the graph

	minCost = determineMinimalCostHamiltonCycle(minimalCost);					//determine the minimal cost

	return minCost;
}




int main()
{
	//cod problema

	fin.close();
	fout.close();

	return 0;
}