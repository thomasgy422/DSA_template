class SegmentTree:
    def __init__(self, nums):
        self.n = len(nums)
        self.nums = nums
        self.lst = [0] * (4 * self.n)
        self.buildTree(1, 0, self.n - 1)

    def maintain(self, i):
        self.lst[i] = max(self.lst[2 * i], self.lst[2 * i + 1])

    def buildTree(self, s, l, r):
        if l == r:
            self.lst[s] = self.nums[l]
            return
        mid = (l + r) // 2
        self.buildTree(2 * s, l, mid)
        self.buildTree(2 * s + 1, mid + 1, r)
        self.maintain(s)
        return

    def query_and_update(self, s, l, r, t):
        if self.lst[s] < t:
            return -1
        if l == r:
            self.lst[s] = -1
            return l
        mid = (l + r) // 2
        idx = self.query_and_update(2 * s, l, mid, t)
        if idx == -1:
            idx = self.query_and_update(2 * s + 1, mid + 1, r, t)
        self.maintain(s)
        return idx