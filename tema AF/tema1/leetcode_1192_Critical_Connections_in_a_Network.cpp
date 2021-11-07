class Solution {
public:					
    vector< vector<int> > solution;		
    vector< vector<int> > neighborList;	

    vector<int> discoveryOrder;				
	vector<int> lowestDepthReacheable;	

    stack<int> nodeStack;
    
    int currentTime = 0;
    
    
    void TDFS_criticalConnections(int currentNode, int parentNode)
    {
        discoveryOrder[currentNode] = currentTime;									
        lowestDepthReacheable[currentNode] = currentTime;
        nodeStack.push(currentNode);
        currentTime++;																

        for (auto neighbor : neighborList[currentNode])							
        {
            if (discoveryOrder[neighbor] == -1)																	
            {
                TDFS(neighbor, currentNode);	

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
    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) 
    {								
        discoveryOrder.assign(n, -1);				
	    lowestDepthReacheable.assign(n, -1);
        
        for (int i = 0; i < n; i++) 
        {
            vector <int> emptyVector;
            neighborList.push_back(emptyVector);
        }
        
        for (auto c : connections) 
        {
            int node1 = c[0];
            int node2 = c[1];

            
            neighborList[node1].push_back(node2);
            neighborList[node2].push_back(node1);
        }
        
        for (int i = 0; i < n; i++)
        {
            if (discoveryOrder[i] == -1)										
            {
                TDFS(i, -1);	
            }
        }

        return solution;
    }
    
    
};