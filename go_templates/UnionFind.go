package main

type UnionFind struct {
	parent []int
	rank   []int
	size   int
}

func UF(n int) *UnionFind {
	uf := &UnionFind{
		parent: make([]int, n),
		rank:   make([]int, n),
		size:   n,
	}
	for i := range n {
		uf.parent[i] = i
		uf.rank[i] = 1
	}
	return uf
}

func (uf *UnionFind) Find(i int) int {
	for uf.parent[i] != i {
		uf.parent[i] = uf.parent[uf.parent[i]]
		i = uf.parent[i]
	}
	return i
}

func (uf *UnionFind) Merge(a, b int) bool {
	pa := uf.Find(a)
	pb := uf.Find(b)
	if pa == pb {
		return false
	}
	if uf.rank[pa] > uf.rank[pb] {
		uf.parent[pb] = pa
	} else if uf.rank[pb] > uf.rank[pa] {
		uf.parent[pa] = pb
	} else {
		uf.parent[pb] = pa
		uf.rank[pa]++
	}
	uf.size--
	return true
}

func (uf *UnionFind) Size() int {
	return uf.size
}
