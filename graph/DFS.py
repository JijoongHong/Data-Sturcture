def dfs(graph, start, visited = set()):
    if start not in visited:
        visited.add(start) # 방문 목록에 추가
        print(start,end='') # vertex 출력
        nbr = graph[start] - visited # 그래프에서 vertex삭제
        for v in nbr: # 삭제된 그래프로 dfs 재귀호출
            dfs(graph, v, visited)

graph = {"A": {"B", "C"},
         "B": {"A", "D"},
         "C": {"A", "D", "E"},
         "D": {"B", "C", "F"},
         "E": {"C", "G", "H"},
         "F": {"D"},
         "G": {"E", "H"},
         "H": {"E", "G"}
         }

dfs(graph, "A")
# >>> ABDFCEHG