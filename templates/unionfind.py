class UnionFind:
    def __init__(self, n: int):
        self.par = [i for i in range(n)]
        self.rank = [1] * n
    
    def find(self, i: int) -> int:
        if self.par[i] == i:
            return i
        return self.find(self.par[i])

    def union(self, i: int, j: int) -> bool:
        p1 = self.find(i)
        p2 = self.find(j)
        if p1 == p2:
            return False
        
        if self.rank[p1] >= self.rank[p2]:
            self.par[p2] = p1
            self.rank[p1] += self.rank[p2]
        else:
            self.par[p1] = p2
            self.rank[p2] += self.rank[p1]
        return True

#use this
class UnionFind:
    def __init__(self, n: int):
        self._fa = list(range(n))
        self._size = [1] * n
        self.cc = n

    def find(self, x: int) -> int:
        if self._fa[x] != x:
            self._fa[x] = self.find(self._fa[x])
        return self._fa[x]

    def is_same(self, x: int, y: int) -> bool:
        return self.find(x) == self.find(y)

    def merge(self, from_: int, to: int) -> bool:
        x, y = self.find(from_), self.find(to)
        if x == y:
            return False
        self._fa[x] = y
        self._size[y] += self._size[x]
        self.cc -= 1
        return True

    def get_size(self, x: int) -> int:
        return self._size[self.find(x)]
    
    def init(self):
        self._fa = list(range(self.cc))
        self._size = [1] * self.cc