import collections

def bfs(graph, start):
    visited = set([start])
    queue = collections.deque([start])
    while queue:
        vertex = queue.popleft()
        print(vertex, end='')
        nbr = graph[vertex] - visited
        for v in nbr:
            visited.add(v)
            queue.append(v)

graph = {"A": {"B", "C"},
         "B": {"A", "D"},
         "C": {"A", "D", "E"},
         "D": {"B", "C", "F"},
         "E": {"C", "G", "H"},
         "F": {"D"},
         "G": {"E", "H"},
         "H": {"E", "G"}
         }

bfs(graph, "A")
# >>> ACBEDHGF