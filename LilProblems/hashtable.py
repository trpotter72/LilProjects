#! usr/bin/env python3

class Hashtable:


    def __init__(self, fn = None, b = 10):
        self.buckets = b
        self.table = []
        if fn == None:
            self.hash = self.defaultHash
        else:
            self.hash = fn
        for i in range(b):
            self.table.append([])

    def defaultHash(self, x):
        return(x % self.buckets)

    def insert(self, x):
        pos = self.hash(x)
        if not x in self.table[pos]:
            self.table[pos].append(x)
            return True
        return False

    def remove(self, x):
        pos = self.hash(x)
        if x in self.table[pos]:
            self.table[pos].remove(x)
            return True
        return False

    def find(self, x):
        pos = self.hash(x)
        if x in self.table[pos]:
            #return the value in the list, not the value given for search
            i = self.table[pos].index(x)
            return self.table[pos][i]
        return None
