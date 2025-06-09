colors = [0] * n
def dfs(x: int) -> bool:
    colors[x] = 1  # x visiting
    for y in g[x]:
        if colors[y] == 1 or colors[y] == 0 and dfs(y):
            return True
    colors[x] = 2
    return False