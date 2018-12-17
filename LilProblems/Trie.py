from collections import deque

class TrieNode:

    def __init__(self):
        self.alphabet = dict()
        self.terminal = False
        self.data = 0

    def keyExists(self, char):
        return char in self.alphabet


class Trie:

    def __init__(self):
        self.root = TrieNode()

    def search(self, string):
        temp = self.searchNode(string)
        if  temp != False:
            return temp.data
        else:
            return False

    def insert(self, string, data):
        current = self.root
        for char in string:
            if current.keyExists(char): #Existing node
                current = current.alphabet[char]
            else: #Create a new node
                current.alphabet[char] = TrieNode()
                current = current.alphabet[char]
        if current.terminal:
            return False
        else:
            current.terminal = True
            current.data = data
            return data

    #NOTE: This implementation would create nodes dynamically on the way
    #       to a failed path.  This would increase the size requirement with no
    #       additional speed, but it helps us not have to redefine the method
    #       for an autocomplete feature
    def searchNode(self, string):
        current = self.root
        for char in string:
            if current.keyExists(char):
                current = current.alphabet[char]
            else:
                current.alphabet[char] = TrieNode()
                current = current.alphabet[char]
        return current


    def returnClosestNodes(self, count, string):
        #use BFS until we find enough values
        closest = []
        current = self.searchNode(string)
        bfs = deque()
        bfs.append(current)
        while (len(bfs)!=0 and len(closest) < count):
            current = bfs.popleft()
            if current.terminal:
                closest.append(current)
            for key, node in current.alphabet.items():
                bfs.append(node)
        return closest

    def returnClosest(self, count, string):
        return [x.data for x in self.returnClosestNodes(count, string)]

    def load_dict(self, text_file = "words.txt"):
        file = open(text_file,'r')
        for line in file:
            if(line != "\n"):
                space = line.find(' ')
                word = line[ :space]
                self.insert(word, line)
