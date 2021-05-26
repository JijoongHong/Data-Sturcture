def find_connected_component(graph):
    visited = set() # 방문한 정점 집합
    color_list = [] # 부분 그래프별 정점 리스트

    for vtx in graph: # 그래프의 모든 정점들에 대해
        if vtx not in visited: # 방문하지 않은 정점이 있으면
            color = dfs_cc(graph,[], vtx, visited) # 새로운 컬러 리스트
            color_list.append(color) # 컬러리스트 추가

    print("그래프 연결성분 개수 = %d"%len(color_list))
    print(color_list)


def dfs_cc(graph, color, vertex, visited):
    if vertex not in visited:
        visited.add(vertex) # 방문 목록에 추가
        color.append(vertex) # 같은 색의 정점 리스트에 추가
        nbr = graph[vertex] - visited # 그래프에서 vertex삭제
        for v in nbr: # 삭제된 그래프로 dfs 재귀호출
            dfs_cc(graph, color, v, visited)

    return color

graph = {"A": set(["B", "C"]),
         "B": set(["A"]),
         "C": set(["A"]),
         "D": set(["E"]),
         "E": set(["D"])
         }

find_connected_component(graph)
# >>> 그래프 연결성분 개수 = 2
# [['A', 'C', 'B'], ['D', 'E']]