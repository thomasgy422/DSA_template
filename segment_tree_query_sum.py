#single point update and range sum query
class SegmentTree:
    def __init__(self, nums):
        n = len(nums)
        self.nums = nums
        self.lst = [0] * (4 * n)
        self.buildTree(1, 0, n - 1)

    def maintain(self, s):
        self.lst[s] = self.lst[2 * s] + self.lst[2 * s + 1]

    def buildTree(self, s, l, r):
        if l == r:
            self.lst[s] = self.nums[l]
            return
        mid = (l + r) // 2
        self.buildTree(2 * s, l, mid)
        self.buildTree(2 * s + 1, mid + 1, r)
        self.maintain(s)
        return

    def update(self, s, l, r, ui, uv):
        if l == r:
            self.lst[s] = uv
            return
        mid = (l + r) // 2
        if ui <= mid:
            self.update(2 * s, l, mid, ui, uv)
        else:
            self.update(2 * s + 1, mid + 1, r, ui, uv)
        self.maintain(s)
        return

    def query_sum(self, s, l, r, tl, tr):
        if l >= tl and r <= tr:
            return self.lst[s]
        if r < tl or l > tr:
            return 0
        mid = (l + r) // 2
        ls = self.query_sum(s * 2, l, mid, tl, tr)
        rs = self.query_sum(s * 2 + 1, mid + 1, r, tl, tr)
        return ls + rs