#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("bellmanford.in");
ofstream fout("bellmanford.out");


auto cmp = [](pair <int, int> x, pair <int, int> y)																				//this is used for sorting the min heap in Dijkstra's Algorithm
{
	return x.second > y.second;
};


class Graph
{
public:
	struct Edge 
	{
		int m_destinationNode, m_distance;

		Edge(int destinationNode, int distance = 0) : m_destinationNode(destinationNode), m_distance(distance) {}

		operator int() 
		{ 
			return m_distance; 
		}
	};

private:
	bool m_oriented;
	bool m_weighted;

	int m_nrNodes;
	int m_nrEdges;
	
	vector < vector <Edge> > m_neighborList;

	void BFS(vector<bool>& visitedNodes, vector<int>& distances, int startNode);
	void DFS(vector<bool>& visitedNodes, int currentNode);
	void BCDFS(vector< vector <int> >& bcc, stack<int>& nodeStack, vector<bool>& visited, vector<int>& depth, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int currentDepth);
	void TDFS(vector< vector <int> >& scc, stack<int>& nodeStack, vector<bool>& stackMember, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int& currentTime);
	void TDFS_criticalConnections(vector< vector<int> >& solution, stack<int>& nodeStack, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int& currentTime);
	void STDFS(stack<int>& result, vector<bool>& visitedNodes, int currentNode);
	void Dijkstra(priority_queue < pair<int, int>, vector< pair<int, int> >, decltype(cmp) >& heap, vector<bool>& visitedNodes, vector<int>& distances);
	void BellmanFord(queue<int>& nodeOrder, vector<bool>& inQueue, vector<int>& distances, vector<int>& numberOfAparitions, int startNode);

public:
	Graph(int nrNodes = 0, int nrEdges = 0, bool oriented = false, bool weighted = false);
	~Graph() {}

#pragma region Setters&Getters
	void setOrientation(bool orientation)
	{
		m_oriented = orientation;
	}
	void setNrNodes(int nrNodes)
	{
		m_nrNodes = nrNodes;
	}
	void setNrEdges(int nrEdges)
	{
		m_nrEdges = nrEdges;
	}

	bool getOrientation()
	{
		return m_oriented;
	}
	int getNrNodes()
	{
		return m_nrNodes;
	}
	int getNrEdges()
	{
		return m_nrEdges;
	}
#pragma endregion

	void buildNeighborList(istream& input);

	vector<int> minimalDistances(int startNode);
	int numberOfConexComponents();
	vector< vector <int> > BiconnectedComponents();
	vector< vector <int> > StronglyConnectedComponents();
	vector<vector<int>> criticalConnections();
	vector<int> minimalDistanceBetweenTwoNodes(int startNode, int finishNode);
	bool HavelHakimi(istream& input);
	vector<int> topologicalSort();
	vector<int> minimalWeightedDistances(int startNode);
	vector<int> minimalNegativeWeightedDistances(int startNode);
};

Graph::Graph(int nrNodes, int nrEdges, bool oriented, bool weighted)
{
	m_nrNodes = nrNodes;
	m_nrEdges = nrEdges;

	m_oriented = oriented;
	m_weighted = weighted;

	vector <Edge> emptyVector;

	for (int i = 0; i < nrNodes; i++)
	{
		m_neighborList.push_back(emptyVector);
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

		for (auto neighbor : m_neighborList[currentNode])
		{
			if (visitedNodes[neighbor] == false)
			{
				nodeOrder.push(neighbor);
				distances[neighbor] = distances[currentNode] + 1;
				visitedNodes[neighbor] = true;
			}
		}

		nodeOrder.pop();
	}
}

void Graph::DFS(vector<bool>& visitedNodes, int currentNode)
{
	visitedNodes[currentNode] = true;

	for (auto neighbor : m_neighborList[currentNode])
	{
		if (visitedNodes[neighbor] == false)
		{
			DFS(visitedNodes, neighbor);
		}
	}
}

void Graph::BCDFS(vector< vector <int>>& bcc, stack<int>& nodeStack, vector<bool>& visited, vector<int>& depth, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int currentDepth)
{
	depth[currentNode] = currentDepth;														//initializing the depth of the current node
	lowestDepthReacheable[currentNode] = currentDepth;										//initializing the lowest depth reacheble time of the current node
	visited[currentNode] = true;															//insert the current node in the stack and mark it as visited
	nodeStack.push(currentNode);

	for (auto neighbor : m_neighborList[currentNode])
	{
		if (neighbor != parentNode)
		{
			if (visited[neighbor] == true)																				
			{
				lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], depth[neighbor]);						//this is were the back edges are found
			}
			else
			{
				BCDFS(bcc, nodeStack, visited, depth, lowestDepthReacheable, neighbor, currentNode, currentDepth + 1);

				lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], lowestDepthReacheable[neighbor]);		//updating with lowest depth that the descendants can reach

				if (depth[currentNode] <= lowestDepthReacheable[neighbor])					//if it is true it means that the neighbor has no back edge above the current node
				{																			//current node separates two biconnected components
					vector <int> biconnectedComponent;
					biconnectedComponent.push_back(currentNode);

					int node = nodeStack.top();
					nodeStack.pop();
					biconnectedComponent.push_back(node);

					while (node != neighbor)												//pop nodes until we reach the neighbor (inclusive) and that is the current biconnected component
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

	for (auto neighbor : m_neighborList[currentNode])								//visit all neibors
	{
		if (discoveryOrder[neighbor] == -1)																								//if it has not been visited yet
		{
			TDFS(scc, nodeStack, stackMember, discoveryOrder, lowestDepthReacheable, neighbor, currentTime);							//DFS on that node

			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], lowestDepthReacheable[neighbor]);				//actualizing on the recursion return path
		}
		else if (stackMember[neighbor] == true)										//if the neighbor is on the stack is part of the current strongly connected component
		{
			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], discoveryOrder[neighbor]);
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

void Graph::TDFS_criticalConnections(vector< vector<int> >& solution, stack<int>& nodeStack, vector<int>& discoveryOrder, vector<int>& lowestDepthReacheable, int currentNode, int parentNode, int& currentTime)
{
	discoveryOrder[currentNode] = currentTime;
	lowestDepthReacheable[currentNode] = currentTime;
	nodeStack.push(currentNode);
	currentTime++;

	for (auto neighbor : m_neighborList[currentNode])
	{
		if (discoveryOrder[neighbor] == -1)
		{
			TDFS_criticalConnections(solution, nodeStack, discoveryOrder, lowestDepthReacheable, neighbor, currentNode, currentTime);

			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], lowestDepthReacheable[neighbor]);

			if (lowestDepthReacheable[neighbor] > discoveryOrder[currentNode])
			{
				vector <int> result;

				result.push_back(currentNode);
				result.push_back(neighbor);

				solution.push_back(result);
			}

		}
		else if (neighbor != parentNode)
		{
			lowestDepthReacheable[currentNode] = min(lowestDepthReacheable[currentNode], discoveryOrder[neighbor]);
		}
	}
	if (lowestDepthReacheable[currentNode] == discoveryOrder[currentNode])
	{

		int node = nodeStack.top();
		nodeStack.pop();

		while (node != currentNode)
		{
			node = nodeStack.top();
			nodeStack.pop();
		}
	}
}

void Graph::STDFS(stack<int>& result, vector<bool>& visitedNodes, int currentNode)
{
	visitedNodes[currentNode] = true;
	
	for (auto neighbor : m_neighborList[currentNode])
	{
		if (visitedNodes[neighbor] == false)
		{
			STDFS(result, visitedNodes, neighbor);
		}
	}

	result.push(currentNode);
}

void Graph::Dijkstra(priority_queue < pair<int, int>, vector< pair<int, int> >, decltype(cmp) > &heap, vector<bool>& visitedNodes, vector<int>& distances)
{
	while (heap.empty() == false)																									//while the heap has elements
	{
		pair <int, int> currentPair = heap.top();
		heap.pop();

		int currentNode = currentPair.first;
		int currentDistance = currentPair.second;

		visitedNodes[currentNode] = true;
			
		if (currentDistance == distances[currentNode])																				//if the current distance is not the same as the one we have in the distance vector it means that we have 
		{																															//already found a better way
			for (auto neighborPair : m_neighborList[currentNode])																	//visit all neibors
			{
				int neighborNode = neighborPair.m_destinationNode;
				int edgeDistance = neighborPair.m_distance;

				if (visitedNodes[neighborNode] == false)																			//if the node has been visited we already know the minimal distance to it
				{
					if (distances[neighborNode] > currentDistance + edgeDistance)													//test if we can find a smaller distance
					{
						distances[neighborNode] = currentDistance + edgeDistance;													//update the minimal distance if we've found a new one
						heap.push(make_pair(neighborNode, distances[neighborNode]));												//push the node and it's distance in the heap
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

		if (numberOfAparitions[currentNode] == m_nrNodes)																		//if we've encountered the same node (number of nodes - 1) times it means we are in a negative loop
		{
			distances[startNode] = -1;
			break;
		}

		for (auto neighborPair : m_neighborList[currentNode])																		//visit all neibors
		{
			int neighborNode = neighborPair.m_destinationNode;
			int edgeDistance = neighborPair.m_distance;

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




void Graph::buildNeighborList(istream& input)
{
	int node1, node2, distance;

	for (int i = 0; i < m_nrEdges; i++)
	{
		input >> node1 >> node2;

		node1--;
		node2--;

		if (m_weighted == true)
		{
			fin >> distance;
		}
		else
		{
			distance = 0;
		}

		Edge newEdge(node2, distance);

		m_neighborList[node1].push_back( newEdge );

		if (m_oriented == false)
		{
			Edge newEdge(node1, distance);

			m_neighborList[node2].push_back( newEdge );
		}
	}
}

vector<int> Graph::minimalDistances(int startNode)
{
	vector <bool> visited(m_nrNodes, false);
	vector <int> distances(m_nrNodes, -1);

	BFS(visited, distances, startNode);

	return distances;
}

int Graph::numberOfConexComponents()
{
	int numberOfConexComponents = 0;

	vector <bool> visited(m_nrNodes, false);

	for (int i = 0; i < m_nrNodes; i++)
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

	vector<bool> visited(m_nrNodes, false);											//will check whether a node has been visited or not
	vector<int> depth(m_nrNodes, -1);												//will cotain the depth of every node
	vector<int> lowestDepthReacheable(m_nrNodes, -1);								//will contain the lowest depth a node can reach through its descendants					

	BCDFS(bcc, nodeStack, visited, depth, lowestDepthReacheable, 0, -1, 0);

	return bcc;
}

vector< vector <int> > Graph::StronglyConnectedComponents()							//initializing all data structures needed for the Tarjan's DFS Algorithm
{
	vector< vector<int> > scc;														//this will contain all Strongly Connected Components

	stack<int> nodeStack;															//will store the connected ancestors
																					
	vector<bool> stackMember(m_nrNodes, false);										//will check whether a node is in stack
	vector<int> discoveryOrder(m_nrNodes, -1);										//contains the order in which the nodes are dicovered
	vector<int> lowestDepthReacheable(m_nrNodes, -1);								//the lowest ancestor that can be reached

	int currentTime = 0;															//a timer used for discoveryOrder and lowestDepthReacheable

	for (int i = 0; i < m_nrNodes; i++)
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

	vector<int> discoveryOrder(m_nrNodes, -1);
	vector<int> lowestDepthReacheable(m_nrNodes, -1);

	stack<int> nodeStack;

	int currentTime = 0;

	for (int i = 0; i < m_nrNodes; i++)
	{
		if (discoveryOrder[i] == -1)
		{
			TDFS_criticalConnections(solution, nodeStack, discoveryOrder, lowestDepthReacheable, i, -1, currentTime);
		}
	}

	return solution;
}

vector<int> Graph::minimalDistanceBetweenTwoNodes(int startNode, int finishNode)
{
	vector<int> normalWay(m_nrNodes, -1);										//will contain the values from the bfs starting from the starting node
	vector<int> reverseWay(m_nrNodes, -1);										//will contain the values from the bfs starting from the finishing node
	vector<int> frequency(m_nrNodes, 0);										//will contain the frequency of the nodes, if a node is on all of the minimal ways between the starting node and the finishing node,	
	vector<int> result;															//then his distance will be the same from those nodes			

	normalWay = minimalDistances(startNode);									//getting the minimal distances in the normal way
	reverseWay = minimalDistances(finishNode);									//getting the minimal distances in the reverse way

	int minimWay = normalWay[finishNode];										//the minimal distance between the starting node and the finishing node

	for (int i = 0; i < m_nrNodes; i++)
	{
		if (normalWay[i] + reverseWay[i] == minimWay)
		{
			frequency[normalWay[i]]++;
		}
	}

	for (int i = 0; i < m_nrNodes; i++)
	{
		if (normalWay[i] + reverseWay[i] == minimWay && frequency[normalWay[i]] == 1)
		{
			result.push_back(i);
		}
	}

	return result;
}

bool Graph::HavelHakimi(istream& input)
{
	vector<int> degrees;
	int totalDegree = 0;

	for (int i = 0; i < m_nrNodes; i++)
	{
		int degree;
		fin >> degree;

		if (degree < 0 || degree > m_nrNodes - 1)
		{
			return false;
		}

		degrees.push_back(degree);
		totalDegree += degree;
	}

	sort(degrees.begin(), degrees.end(), greater<int>());

	if (totalDegree % 2 == 1 || m_nrNodes == 1)
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
	vector <bool> visited(m_nrNodes, false);
	vector<int> solution;

	stack<int> result;

	for (int i = 0; i < m_nrNodes; i++)
	{
		if (visited[i] == false)
		{
			STDFS(result, visited, i);
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
	priority_queue < pair<int, int>, vector< pair<int, int> >, decltype(cmp) > heap(cmp);

	vector <bool> visited(m_nrNodes, false);
	vector <int> distances(m_nrNodes, 2e9);

	distances[startNode] = 0;

	heap.push(make_pair(startNode, 0));

	Dijkstra(heap, visited, distances);

	return distances;
}

vector<int> Graph::minimalNegativeWeightedDistances(int startNode)
{
	queue<int> nodeOrder;

	vector <bool> inQueue(m_nrNodes, false);
	vector <int> distances(m_nrNodes, 2e9);
	vector <int> numberOfAparitions(m_nrNodes, 0);

	distances[startNode] = 0;																										//initialize the distance from the starting node to himself
	nodeOrder.push(startNode);																										//push it in the queue
	inQueue[startNode] = true;																										//and check it

	BellmanFord(nodeOrder, inQueue, distances, numberOfAparitions, startNode);

	return distances;
}




int main()
{
	int nrNodes, nrEdges, startNode = 0;
	vector <int> distances;

	fin >> nrNodes >> nrEdges;

	Graph graph(nrNodes, nrEdges, true, true);

	graph.buildNeighborList(fin);

	distances = graph.minimalNegativeWeightedDistances(startNode);

	if (distances[startNode] == 0)
	{
		for (int i = 0; i < nrNodes; i++)
		{
			if (i != startNode)
			{
				fout << distances[i] << ' ';
			}
		}
	}
	else
	{
		fout << "Ciclu negativ!";
	}
	
	fin.close();
	fout.close();

	return 0;
}