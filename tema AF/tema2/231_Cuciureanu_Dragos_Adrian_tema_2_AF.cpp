#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");


class Graph
{
public:
	struct Edge
	{
		int _startingNode, _destinationNode, _distance, _capacity;

		Edge(int startingNode, int destinationNode, int distance = 0, int capacity = 0) : _startingNode(startingNode), _destinationNode(destinationNode), _distance(distance), _capacity(capacity) {}
		operator int()
		{
			return _distance;
		}
	};

private:
	bool _oriented;
	bool _weighted;
	bool _flux;

	int _nrNodes;
	int _nrEdges;

	vector <int> _nodes;
	vector < vector <Edge> > _neighborList;

	void BFS(vector<bool>& visitedNodes, vector<int>& distances, int startNode);
	void DFS(vector<bool>& visitedNodes, int currentNode);
	void DFS_biconnectedComponents(vector< vector <int> >& bcc, stack<int>& nodeStack, vector<bool>& visited, vector<int>& depth, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int currentDepth);
	void TDFS(vector< vector <int> >& scc, stack<int>& nodeStack, vector<bool>& stackMember, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int& currentTime);
	void TDFS_criticalConnections(vector< vector<int> >& solution, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int& currentTime);
	void DFS_topologicalSort(stack<int>& result, vector<bool>& visitedNodes, int currentNode);
	void Dijkstra(priority_queue < pair<int, int>, vector< pair<int, int> >, greater <pair<int, int>> >& heap, vector<bool>& visitedNodes, vector<int>& distances);
	void BellmanFord(queue<int>& nodeOrder, vector<bool>& inQueue, vector<int>& distances, vector<int>& numberOfAparitions, int startNode);
	static int getRootDisjointSet(vector<int>& parent, int currentNode);
	static void changeColorDisjointSet(vector<int>& parent, vector<int>& height, int node1, int node2);

public:
	Graph(int nrNodes = 0, int nrEdges = 0, bool oriented = false, bool weighted = false, bool flux = false);
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

	void buildNeighborList(istream& input);
	vector<Edge> getEdges();
	void addEdge(Edge newEdge);

	vector<int> minimalDistances(int startNode);
	int numberOfConexComponents();
	vector< vector <int> > BiconnectedComponents();
	vector< vector <int> > StronglyConnectedComponents();
	vector< vector <int> > criticalConnections();
	vector<int> minimalDistanceBetweenTwoNodes(int startNode, int finishNode);
	bool HavelHakimi(istream& input);
	vector<int> topologicalSort();
	vector<int> minimalWeightedDistances(int startNode);
	vector<int> minimalNegativeWeightedDistances(int startNode);
	static void DisjointSet(istream& input, ostream& output);
	vector<Edge> minimumSpanningTree();
	vector< vector <int> > RoyFloyd();
	int diameterOfTree();
};

Graph::Graph(int nrNodes, int nrEdges, bool oriented, bool weighted, bool flux)
{
	_nrNodes = nrNodes;
	_nrEdges = nrEdges;

	_oriented = oriented;
	_weighted = weighted;
	_flux = flux;

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

		for (auto &neighbor : _neighborList[currentNode])
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

	for (auto &neighbor : _neighborList[currentNode])
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

	for (auto &neighbor : _neighborList[currentNode])
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

	for (auto &neighbor : _neighborList[currentNode])								//visit all neibors
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

	for (auto &neighbor : _neighborList[currentNode])
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

	for (auto &neighbor : _neighborList[currentNode])
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
			for (auto &neighborPair : _neighborList[currentNode])																	//visit all neibors
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

		for (auto &neighborPair : _neighborList[currentNode])																		//visit all neibors
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

		if (_flux == true)
		{
			fin >> capacity;
		}
		else
		{
			capacity = 0;
		}

		Edge newEdge(node1, node2, distance, capacity);

		_neighborList[node1].push_back(newEdge);

		if (_oriented == false)
		{
			Edge newEdge(node2, node1, distance, capacity);

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
			for (auto &edge : _neighborList[node])
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
			for (auto &edge : _neighborList[node]) 
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

vector< vector <int> > Graph::BiconnectedComponents()								//initializing all data structures needed for the Biconnected DFS Algorithm
{
	vector< vector<int> > bcc;														//this will contain all Biconnected Components

	stack<int> nodeStack;															//will store the connected ancestors

	vector<bool> visited(_nrNodes, false);											//will check whether a node has been visited or not
	vector<int> depth(_nrNodes, -1);												//will cotain the depth of every node
	vector<int> lowestDepthReacheable(_nrNodes, -1);								//will contain the lowest depth a node can reach through its descendants					

	DFS_biconnectedComponents(bcc, nodeStack, visited, depth, lowestDepthReacheable, 0, -1, 0);

	return bcc;
}

vector< vector <int> > Graph::StronglyConnectedComponents()							//initializing all data structures needed for the Tarjan's DFS Algorithm
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

void Graph::DisjointSet(istream& in, ostream& out)
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




int main()
{
	//cod problema

	fin.close();
	fout.close();

	return 0;
}