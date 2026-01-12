from audioop import add
import itertools
import copy
from queue import PriorityQueue, Queue
from collections import deque
import time
import sys
import os
# import stopit


sys.setrecursionlimit(100000)

miceMoves = [(1, 0), (0, -1), (-1, 0), (0, 1)]
mouseCanGoPlaces = ['.', 'E', '@', 'p']
catCantGoPlaces = ['E', 'p', '@', '#']


# class for the mice on the field
class Mouse:
    index = 0
    x = 0
    y = 0

    def __init__(self, index, x, y):
        self.index = index
        self.x = x
        self.y = y

    def __repr__(self):
        return "s" + str(self.index) + " " + str(self.x) + " " + str(self.y)

    def possibleMove(self, matrix):
        """
        check if the new position of the mouse is available
        :param matrix: out matrix
        :return: returns if the move is possible
        """
        if matrix[self.x][self.y][0] == 's' or matrix[self.x][self.y][0] == '#':
            return False
        return True

    def closestExitHeuristic2(self):
        """
        the first admissible heuristic
        :return: returns the distance to the closest exit so we can use it in the second heuristic
        """
        closest = abs(self.x - Graph.outs[0][0]) + abs(self.y - Graph.outs[0][1])

        for i in range(1, len(Graph.outs)):
            if abs(self.x - Graph.outs[i][0]) + abs(self.y - Graph.outs[i][1]) < closest:
                closest = abs(self.x - Graph.outs[i][0]) + abs(self.y - Graph.outs[i][1])

        return closest

    # returns the distance to the closest exit so we can use it in the third heuristic
    def closestExitHeuristic3(self):
        """
        the second admissible heuristic
        :return:
        """
        closest = abs(self.x - Graph.outs[0][0]) + abs(self.y - Graph.outs[0][1])
        closestIndex = 0

        for i in range(1, len(Graph.outs)):
            if abs(self.x - Graph.outs[i][0]) + abs(self.y - Graph.outs[i][1]) < closest:
                closest = abs(self.x - Graph.outs[i][0]) + abs(self.y - Graph.outs[i][1])
                closestIndex = i

        # from the closest exit we calculate how many walls are there on the shortest path
        signX = 0
        if self.x != Graph.outs[closestIndex][0]:
            signX = -1 * (self.x - Graph.outs[closestIndex][0]) / abs(self.x - Graph.outs[closestIndex][0])

        signY = 0
        if self.y != Graph.outs[closestIndex][1]:
            signY = -1 * (self.y - Graph.outs[closestIndex][1]) / abs(self.y - Graph.outs[closestIndex][1])

        # the number of cluster of walls
        nrWalls = 0
        previous = '.'

        if signX:
            for i in range(self.x + 1, Graph.outs[closestIndex][0] + 1, int(signX)):
                if previous != '#' and Graph.matrix[i][self.y] == '#':
                    nrWalls += 1
                previous = Graph.matrix[i][self.y]

        if signY:
            for j in range(self.y + 1, Graph.outs[closestIndex][1], int(signY)):
                if previous != '#' and Graph.matrix[Graph.outs[closestIndex][0]][j] == '#':
                    nrWalls += 1
                previous = Graph.matrix[Graph.outs[closestIndex][0]][j]

        return closest + nrWalls * 2


# class for the cats on the field
class Cat:
    index = 0
    x = 0
    y = 0

    def __init__(self, index, x, y):
        self.index = index
        self.x = x
        self.y = y

    def __repr__(self):
        return "p" + str(self.index) + " " + str(self.x) + " " + str(self.y)

    # determining the closest mouse to this cat
    def closestMouse(self, mice):
        """
        function that determines the closest mouse to our cat
        :param mice: the vector of mice
        :return: the new position of the cat and the closest mouse
        """
        closest = max(Graph.nrLines, Graph.nrColumns)
        indexMouse = -1

        # iterate through each mouse to mathematically determine which one is the closest
        for idx, mouse in enumerate(mice):
            if Graph.matrix[mouse.x][mouse.y] != '@':
                currentMouse = max(abs(self.x - mouse.x), abs(self.y - mouse.y))

                if closest > currentMouse:
                    closest = currentMouse
                    indexMouse = idx

        if indexMouse == -1:
            return (0, 0), None

        # find in which direction the cat needs to go to get the mouse
        closestMouse = mice[indexMouse]

        diffX = self.x - closestMouse.x
        diffY = self.y - closestMouse.y

        positionX = 0
        positionY = 0

        # the fastest way will be to try and go in a diagonal so the cat does 1 instead of 2 moves (kind of)
        if diffX < 0:
            positionX = 1
        elif diffX > 0:
            positionX = -1

        if diffY < 0:
            positionY = 1
        elif diffY > 0:
            positionY = -1

        if Graph.matrix[self.x + positionX][self.y + positionY][0] in catCantGoPlaces:
            positionX = 0
            positionY = 0

        return (positionX, positionY), mice[indexMouse]


# information about a node from the crossing tree
class NodeCrossing:
    def __init__(self, nrOrd, activeMice, cats, outMice=[], hiddenMice=[], eatenMice=[], blockedAnimal=[],
                 nrMiceThatGotOut=0, parent=None, cost=0, h=0):
        # information about the current node active mice, cats, mice that got out, hidden mice, mice that got eaten,
        # blocked animal and number of mice that got out until this node

        self.nrOrd = nrOrd
        self.activeMice = activeMice
        self.cats = cats
        self.outMice = outMice
        self.hiddenMice = hiddenMice
        self.eatenMice = eatenMice
        self.blockedAnimal = blockedAnimal
        self.nrMiceThatGotOut = nrMiceThatGotOut

        # parent in the crossing tree
        self.parent = parent

        # the cost for making the move until here, this will be the g at the A*s
        self.cost = cost

        # this is for a*s
        self.h = h
        self.f = self.cost + self.h

    def __gt__(self, node):
        if self.f > node.f:
            return True
        elif self.f < node.f:
            return False
        else:
            return self.cost > node.cost

    def __eq__(self, node):
        if self.f == node.f and self.cost == node.cost:
            return True
        else:
            return False

    def determiningWay(self, nrMaxNodes, nrTotalNodes):
        """
        wrapper function for outputNode, which determines the nodes and the time
        :param nrMaxNodes: max number of nodes in memory
        :param nrTotalNodes: the total number of nodes in memory
        :return:
        """
        # get the start time and the putput file
        global startTime, g

        stopTime = time.time()
        duration = round(1000*(stopTime - startTime))

        stack = deque()
        node = self
        stack.append(node)

        totalCost = node.cost

        while node.parent is not None:
            stack.append(node.parent)
            node = node.parent
            # totalCost += node.cost

        g.write(f"Timpul de gasire pentru solutie: {duration} milisecunde.\n")
        g.write(f"Lungimea drumului: {len(stack)}\n")
        g.write(f"Costul total: {totalCost}\n")
        g.write(f"Numarul de noduri calculate: {nrTotalNodes}\n")
        g.write(f"Numarul maxim de noduri din meorie: {nrMaxNodes}\n\n\n")

        while len(stack):
            currentNode = stack.pop()
            currentNode.outputNode()

    def outputNode(self):
        """
        function that writes all the information about a node
        :return:
        """
        # get the output file
        global g

        matrix = copy.deepcopy(Graph.matrix)

        for mouse in self.activeMice:
            if matrix[mouse.x][mouse.y] == '@':
                matrix[mouse.x][mouse.y] = 'S' + str(mouse.index)
            else:
                matrix[mouse.x][mouse.y] = 's' + str(mouse.index)

        for cat in self.cats:
            matrix[cat.x][cat.y] = 'p' + str(cat.index)

        g.write(f"Nodul cu indexul {self.nrOrd}:\n\n")

        if len(self.outMice):
            g.write("Soareci care au iesit:\n")

            for idx in self.outMice:
                g.write(f"Soarecele s{idx} a iesit de pe harta.\n")

            g.write("\n")

        if len(self.hiddenMice):
            g.write("Soareci care s-au ascuns:\n")

            for idx in self.hiddenMice:
                g.write(f"Soarecele s{idx} s-a ascuns.\n")

            g.write("\n")

        if len(self.eatenMice):
            g.write("Soareci care au fost mancati:\n")

            for idxCat, idxMouse in self.eatenMice:
                g.write(f"Pisica p{idxCat} a mancat soarecele s{idxMouse}.\n")

            g.write("\n")

        if len(self.blockedAnimal):
            g.write("Animale blocate:\n")

            for animal in self.blockedAnimal:
                if animal[0] == 's':
                    g.write(f"Soarecele {animal} nu s-a miscat.\n")
                else:
                    g.write(f"Pisica {animal} nu s-a miscat.\n")

            g.write("\n")

        for line in matrix:
            for elem in line:
                g.write("{:<4}".format(elem))
            g.write("\n")

        g.write("\n\n\n")


# problem graph
class Graph:
    nrOrd = 0
    nrMiceNeedOut = 0
    matrix = []
    cats = []
    mice = []
    outs = []
    nrLines = None
    nrColumns = None

    def __init__(self):
        # get the input file (f)
        global f

        # self.__class__ current class
        # read number of mouse that need to get out
        self.__class__.nrMiceNeedOut = int(f.readline())

        # and the matrix
        file = f.readlines()
        self.__class__.matrix = []
        self.__class__.nrLines = len(file)

        for line in file:
            line = line.strip().split()

            # test if the lines have a different dimension from one another
            if self.__class__.nrColumns is None:
                self.__class__.nrColumns = len(line)
            elif self.__class__.nrColumns != len(line):
                print("wrong input1")
                break

            self.__class__.matrix.append(line)

        self.__class__.cats = []
        self.__class__.mice = []

        # iterate through each element of the matrix to find the cats and mice
        for i in range(self.__class__.nrLines):
            for j in range(self.__class__.nrColumns):
                if self.__class__.matrix[i][j][0] == 'p':
                    cat = Cat(int(self.__class__.matrix[i][j][1:]), i, j)
                    self.__class__.cats.append(cat)
                    self.__class__.matrix[i][j] = '.'

                elif self.__class__.matrix[i][j][0] == 's':
                    mouse = Mouse(int(self.__class__.matrix[i][j][1:]), i, j)
                    self.__class__.mice.append(mouse)
                    self.__class__.matrix[i][j] = '.'

                elif self.__class__.matrix[i][j][0] == 'E':
                    self.__class__.outs.append((i, j))

        if len(self.__class__.outs) == 0:
            print("wrong input2")

        self.__class__.cats = sorted(self.__class__.cats, key=lambda x: x.index, reverse=False)
        self.__class__.mice = sorted(self.__class__.mice, key=lambda x: x.index, reverse=False)

    def testFinishCondition(self, currentNode):
        """
        check if the current node is in a finale state
        :param currentNode: the current node for which we test
        :return: a boolean if it is finished
        """
        return currentNode.nrMiceThatGotOut >= self.__class__.nrMiceNeedOut

    def matrixOutput(self):
        """
        just a test function
        :return:
        """
        g.write(f"{self.__class__.nrMiceNeedOut}\n")
        for line in self.__class__.matrix:
            for elem in line:
                g.write("{:<4}".format(elem))
            g.write("\n")

        g.write("\n")

        for mouse in self.__class__.mice:
            g.write(f"{mouse}\n")

        for cat in self.__class__.cats:
            g.write(f"{cat}\n")

        g.write("\n")

    def allCombinationsMice(self, node):
        """
        function
        :param node: the current node for which we determine the combination
        :return: all the combinations for the mice we currently have
        """
        allMicePositions = [(mouse.x, mouse.y) for mouse in node.activeMice]
        combinations = []

        for mouse in node.activeMice:
            places = []

            for coordination in miceMoves:
                newX = mouse.x + coordination[0]
                newY = mouse.y + coordination[1]

                # check if the new coordination is inside
                if 0 <= newY <= Graph.nrColumns - 1 and 0 <= newX <= Graph.nrLines - 1:
                    # check so that the mouse doesn't go in an illegal place
                    # we will verify again later to see if the new place is ok
                    if ((Graph.matrix[newX][newY][0] in mouseCanGoPlaces) or
                            ((newX, newY) in allMicePositions[:mouse.index])) and \
                            ((newX, newY) not in allMicePositions[mouse.index + 1:]):
                        places.append(coordination)

            if len(places) == 0:
                places.append((0, 0))

            combinations.append(places)

        return combinations

    def generateSuccessors(self, currentNode, heuristicType=0):
        """
        the function that generates our successors
        for heuristics:
        0 - no heuristic
        1 - trivial heuristic
        2 - admissible heuristic 1
        3 - admissible heuristic 2
        4 - impossible heuristic
        :param currentNode: the current node
        :param heuristicType: the type of heuristic we use
        :return:
        """
        # next nodes generating from this current node
        successors = []

        # and we do cartesian product on that set
        cartesianProduct = itertools.product(*self.allCombinationsMice(currentNode))

        for combination in cartesianProduct:
            # declare the child node parameters
            # set the initial cost to the number of active mice
            cost = len(currentNode.activeMice)

            # set the new active mice
            newActiveMice = []

            # the new mice coordinates
            newActiveMicePositions = []

            # set the new cats
            newCats = []

            # the variable in which we will increment the number of mice that got out
            newNrMiceThatGotOut = currentNode.nrMiceThatGotOut

            # mice that got eaten and have to be removed
            miceToBeRemoved = []

            # index of the mouse that got out
            outMice = []

            # index of the hidden mice
            hiddenMice = []

            # index of the cat and index of the mouse
            eatenMice = []

            # the animals that couldn't move
            blockedAnimal = []

            for idx, mouse in enumerate(currentNode.activeMice):
                newX = mouse.x + combination[idx][0]
                newY = mouse.y + combination[idx][1]

                if Graph.matrix[newX][newY] == 'E':
                    newNrMiceThatGotOut += 1
                    cost = 1
                    outMice.append(mouse.index)
                    continue
                elif (newX, newY) in newActiveMicePositions:
                    (newX, newY) = (mouse.x, mouse.y)

                if Graph.matrix[newX][newY] == '@':
                    hiddenMice.append(mouse.index)

                if (newX, newY) == (mouse.x, mouse.y):
                    blockedAnimal.append('s' + str(mouse.index))

                newMouse = Mouse(mouse.index, newX, newY)
                newActiveMice.append(newMouse)
                newActiveMicePositions.append((newX, newY))

            for cat in currentNode.cats:
                packet = cat.closestMouse(newActiveMice)

                newX = cat.x + packet[0][0]
                newY = cat.y + packet[0][1]

                mouse = packet[1]

                if mouse is not None and (newX, newY) == (mouse.x, mouse.y):
                    cost = len(currentNode.cats) * len(newActiveMice)
                    miceToBeRemoved.append(mouse)
                    eatenMice.append((cat.index, mouse.index))

                if (newX, newY) == (cat.x, cat.y):
                    blockedAnimal.append('p' + str(cat.index))

                newCat = Cat(cat.index, newX, newY)
                newCats.append(newCat)

            newMice = [mouse for mouse in newActiveMice if mouse not in miceToBeRemoved]

            # test if the current node can make it into a final state
            if newNrMiceThatGotOut + len(newMice) >= Graph.nrMiceNeedOut:

                if heuristicType == 0:
                    newNode = NodeCrossing(Graph.nrOrd, newMice, newCats, outMice, hiddenMice, eatenMice, blockedAnimal,
                                           newNrMiceThatGotOut, currentNode, currentNode.cost + cost)
                    Graph.nrOrd += 1
                    successors.append(newNode)

                elif heuristicType == 1:
                    h = len(newMice)
                    newNode = NodeCrossing(Graph.nrOrd, newMice, newCats, outMice, hiddenMice, eatenMice, blockedAnimal,
                                           newNrMiceThatGotOut, currentNode, currentNode.cost + cost, h)
                    Graph.nrOrd += 1
                    successors.append(newNode)

                elif heuristicType == 2:
                    h = 0

                    for mouse in newMice:
                        h += mouse.closestExitHeuristic2()

                    newNode = NodeCrossing(Graph.nrOrd, newMice, newCats, outMice, hiddenMice, eatenMice, blockedAnimal,
                                           newNrMiceThatGotOut, currentNode, currentNode.cost + cost, h)
                    Graph.nrOrd += 1
                    successors.append(newNode)

                elif heuristicType == 3:
                    h = 0

                    for mouse in newMice:
                        h += mouse.closestExitHeuristic3()

                    newNode = NodeCrossing(Graph.nrOrd, newMice, newCats, outMice, hiddenMice, eatenMice, blockedAnimal,
                                           newNrMiceThatGotOut, currentNode, currentNode.cost + cost, h)
                    Graph.nrOrd += 1
                    successors.append(newNode)

                else:
                    h = (Graph.nrLines * Graph.nrColumns) ** 2

                    newNode = NodeCrossing(Graph.nrOrd, newMice, newCats, outMice, hiddenMice, eatenMice, blockedAnimal,
                                           newNrMiceThatGotOut, currentNode, currentNode.cost + cost, h)
                    Graph.nrOrd += 1
                    successors.append(newNode)

        return successors


# @StopTokenizing.threading_timeoutable(default="valoare returnata de functie cand intra in timeout")
def BFS(gr, nrSol=1):
    """
    BFS algorithm
    :param gr: the graph of the problem
    :param nrSol: the number of solutions we want
    :return:
    """
    g.write("----------------BFS----------------\n\n")

    Graph.nrOrd = 0
    nodeStart = NodeCrossing(Graph.nrOrd, Graph.mice, Graph.cats)
    Graph.nrOrd += 1

    # queue with our nodes form the tree
    q = Queue()
    q.put(nodeStart)

    nrMaxNodes = 1
    nrTotalNodes = 1

    while not q.empty():
        currentNode = q.get()

        if gr.testFinishCondition(currentNode):
            currentNode.determiningWay(nrMaxNodes, nrTotalNodes)
            g.write("\n----------------\n\n")

            nrSol -= 1
            if nrSol == 0:
                return

        successors = gr.generateSuccessors(currentNode)

        for addNode in successors:
            q.put(addNode)
            # addNode.outputNode()

        nrTotalNodes += len(successors)
        nrMaxNodes = max(nrMaxNodes, q.qsize())


def DFS(gr, nrSol=1):
    """
    DFS algorithm
    :param gr: the graph of the problem
    :param nrSol: the number of solutions we want
    :return:
    """
    g.write("----------------DFS----------------\n\n")

    Graph.nrOrd = 0
    nodeStart = NodeCrossing(Graph.nrOrd, Graph.mice, Graph.cats)
    Graph.nrOrd += 1

    # stack with our nodes form the tree
    stack = deque()
    stack.append(nodeStart)

    nrMaxNodes = 1
    nrTotalNodes = 1

    while len(stack) > 0:
        currentNode = stack.pop()

        if gr.testFinishCondition(currentNode):
            currentNode.determiningWay(nrMaxNodes, nrTotalNodes)
            g.write("\n----------------\n\n")

            nrSol -= 1
            if nrSol == 0:
                return

        else:
            successors = gr.generateSuccessors(currentNode)

            for addNode in successors:
                stack.append(addNode)

            nrTotalNodes += len(successors)
            nrMaxNodes = max(nrMaxNodes, len(stack))


def DFIHelper(gr, currentNode, depth, nrSol, nrMaxNodes, nrTotalNodes):
    """
    DFI algorithm
    :param gr: the graph of the problem
    :param currentNode: the current node
    :param depth: the depth we are at
    :param nrSol: the number of solutions we want
    :param nrMaxNodes: the maximum number of nodes that we have in memory at a moment in this function
    :param nrTotalNodes: the total number of nodes that we have in memory in this function
    :return:
    """
    if depth == 1 and gr.testFinishCondition(currentNode):
        currentNode.determiningWay(nrMaxNodes, nrTotalNodes)
        g.write("\n----------------\n")

        nrSol -= 1
        if nrSol == 0:
            return nrSol, nrMaxNodes, nrTotalNodes

    if depth > 1:
        successors = gr.generateSuccessors(currentNode)

        nrMaxNodes += len(successors)
        nrTotalNodes += len(successors)

        for addNode in successors:
            if nrSol != 0:
                nrMaxNodes -= 1
                nrSol, nrMaxNodes, nrTotalNodes = DFIHelper(gr, addNode, depth - 1, nrSol, nrMaxNodes, nrTotalNodes)

    return nrSol, nrMaxNodes, nrTotalNodes


def DFI(gr, nrSol=1):
    """
    DFI algorithm
    :param gr: the graph of the problem
    :param nrSol: the number of solutions we want
    :return:
    """
    g.write("----------------DFI----------------\n\n")

    Graph.nrOrd = 0
    nodeStart = NodeCrossing(Graph.nrOrd, Graph.mice, Graph.cats)
    Graph.nrOrd += 1

    nrMaxNodes = 1
    nrTotalNodes = 1

    for i in range(1, Graph.nrColumns * Graph.nrLines + 1):
        if nrSol == 0:
            return
        else:
            nrSol, nrMaxNodes, nrTotalNodes = DFIHelper(gr, nodeStart, i, nrSol, nrMaxNodes, nrTotalNodes)


def AStar(gr, nrSol=1, heuristicType=1):
    """
    A* algorithm
    :param gr: the graph of the problem
    :param nrSol:  the number of solutions we want
    :param heuristicType: the type of heuristic we use
    :return:
    """
    g.write(f"----------------Normal A* Type {heuristicType}----------------\n\n")

    Graph.nrOrd = 0
    nodeStart = NodeCrossing(Graph.nrOrd, Graph.mice, Graph.cats)
    Graph.nrOrd += 1

    nrMaxNodes = 1
    nrTotalNodes = 1

    # priority queue with our nodes
    pq = PriorityQueue()
    pq.put(nodeStart)

    while not pq.empty():
        currentNode = pq.get()

        if gr.testFinishCondition(currentNode):
            currentNode.determiningWay(nrMaxNodes, nrTotalNodes)
            g.write("\n----------------\n\n")

            nrSol -= 1
            if nrSol == 0:
                return

        else:
            successors = gr.generateSuccessors(currentNode, heuristicType)

            for addNode in successors:
                pq.put(addNode)

            nrTotalNodes += len(successors)
            nrMaxNodes = max(nrMaxNodes, pq.qsize())


def AStarOptimized(gr, heuristicType=1):
    """
    A* optimized algorithm
    :param gr: the graph of the problem
    :param heuristicType: the type of heuristic we use
    :return:
    """
    g.write(f"----------------A* Optimized Type {heuristicType}----------------\n\n")

    Graph.nrOrd = 0
    nodeStart = NodeCrossing(Graph.nrOrd, Graph.mice, Graph.cats)
    Graph.nrOrd += 1

    nrMaxNodes = 1
    nrTotalNodes = 1

    # priority queue with our nodes that need to be expanded
    l_open = [nodeStart]

    # l_closed contains already expanded nodes
    l_closed = []

    while len(l_open) > 0:
        currentNode = l_open.pop(0)
        l_closed.append(currentNode)

        if gr.testFinishCondition(currentNode):
            currentNode.determiningWay(nrMaxNodes, nrTotalNodes)
            g.write("\n----------------\n\n")

            return

        else:
            successors = gr.generateSuccessors(currentNode, heuristicType)

            for addNode in successors:
                foundC = False

                for nodC in l_open:
                    if addNode.activeMice == nodC.activeMice and addNode.cats == nodC.cats and \
                            addNode.nrMiceThatGotOut == nodC.nrMiceThatGotOut:
                        foundC = True
                        if addNode.f >= nodC.f:
                            successors.remove(addNode)
                        else:
                            l_open.remove(nodC)
                        break

                if not foundC:
                    for nodC in l_closed:
                        if addNode.activeMice == nodC.activeMice and addNode.cats == nodC.cats and \
                                addNode.nrMiceThatGotOut == nodC.nrMiceThatGotOut:
                            if addNode.f >= nodC.f:
                                successors.remove(addNode)
                            else:
                                l_closed.remove(nodC)
                            break

            for addNode in successors:
                i = 0
                foundPlace = False
                for i in range(len(l_open)):
                    # sort by f, if f are equal reverse sort by g
                    if l_open[i].f > addNode.f or (l_open[i].f == addNode.f and l_open[i].cost <= addNode.cost):
                        foundPlace = True
                        break

                if foundPlace:
                    l_open.insert(i, addNode)
                else:
                    l_open.append(addNode)

            nrTotalNodes += len(successors)
            nrMaxNodes = max(nrMaxNodes, len(l_open) + len(l_closed))


def IDAStarHelper(gr, currentNode, limit, nrSol, nrMaxNodes, nrTotalNodes, heuristicType):
    """
    IDA* algorithm
    :param gr: out graph
    :param currentNode: the current node
    :param limit: the limit in algorithm
    :param nrSol: the number of solutions that we want
    :param nrMaxNodes: the maximum number of nodes that we have in memory at a moment in this function
    :param nrTotalNodes: the total number of nodes that we have in memory in this function
    :param heuristicType: the type of heuristic that we use
    :return:
    """
    if currentNode.f > limit:
        return nrSol, currentNode.f, nrMaxNodes, nrTotalNodes

    if gr.testFinishCondition(currentNode) and currentNode.f == limit:
        currentNode.determiningWay(nrMaxNodes, nrTotalNodes)
        g.write("\n----------------\n\n")

        nrSol -= 1
        if nrSol == 0:
            return 0, "stop", nrMaxNodes, nrTotalNodes

    else:
        successors = gr.generateSuccessors(currentNode, heuristicType)

        nrMaxNodes += len(successors)
        nrTotalNodes += len(successors)

        minim = float('inf')
        for addNode in successors:
            nrMaxNodes -= 1

            nrSol, rez, nrMaxNodes, nrTotalNodes = IDAStarHelper(gr, addNode, limit, nrSol, nrMaxNodes,
                                                                 nrTotalNodes, heuristicType)

            if rez == "stop":
                return 0, "stop", nrMaxNodes, nrTotalNodes

            if rez < minim:
                minim = rez

        return nrSol, minim, nrMaxNodes, nrTotalNodes


def IDAStar(gr, nrSol=1, heuristicType=1):
    """
    the wrapper function for IDA*
    :param gr: the graph of the problem
    :param nrSol:  the number of solutions we want
    :param heuristicType: the type of heuristic we use
    :return:
    """
    g.write(f"----------------IDA* Type {heuristicType}----------------\n\n")

    Graph.nrOrd = 0
    nodeStart = NodeCrossing(Graph.nrOrd, Graph.mice, Graph.cats)
    Graph.nrOrd += 1

    nrMaxNodes = 1
    nrTotalNodes = 1

    limit = nodeStart.f

    while True:
        nrSol, rez, nrMaxNodes, nrTotalNodes = IDAStarHelper(gr, nodeStart, limit, nrSol, nrMaxNodes,
                                                             nrTotalNodes, heuristicType)

        if rez == "stop" or rez == float('inf'):
            break

        limit = rez


# get the input folder, output folder and the number of solutions
inputFolder = sys.argv[1]
outputFolder = sys.argv[2]
nSol = int(sys.argv[3])
f = None
g = None


def algorithm():
    """
    function that executes all the algorithms (BFS, DFS, DFI, A*, A* Optimizat, IDA*)
    :return:
    """
    global f, g, inputFolder, outputFolder, nSol, startTime

    inputFiles = os.listdir(inputFolder)

    if not os.path.exists(outputFolder):
        os.mkdir(outputFolder)

    for inputFile in inputFiles:
        f = open(inputFolder + '/' + inputFile, "r")

        outputFile = "output_" + inputFile
        g = open(outputFolder + '/' + outputFile, "w")

        graph = Graph()

        # start the timer
        startTime = time.time()

        BFS(graph, nSol)
        DFS(graph, nSol)
        DFI(graph, nSol)
        AStar(graph, nSol, 1)
        AStar(graph, nSol, 2)
        AStar(graph, nSol, 3)
        AStar(graph, nSol, 4)
        AStarOptimized(graph, 1)
        AStarOptimized(graph, 2)
        AStarOptimized(graph, 3)
        AStarOptimized(graph, 4)
        IDAStar(graph, 1, 1)
        IDAStar(graph, 1, 2)
        IDAStar(graph, 1, 3)
        IDAStar(graph, 1, 4)


algorithm()
