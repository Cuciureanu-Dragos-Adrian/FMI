from queue import PriorityQueue

line = input().strip().split(" ")

startTime = int(line[0])
stopTime = int(line[1])


class Prog:
    def __init__(self, start, finish):
        self.start = start
        self.finish = finish

    def __gt__(self, prog):
        if self.start > prog.start:
            return True
        elif self.start < prog.start:
            return False
        else:
            return self.finish < prog.finish

    def __eq__(self, prog):
        if self.start == prog.start and self.finish == prog.finish:
            return True
        else:
            return False

pq = PriorityQueue()
