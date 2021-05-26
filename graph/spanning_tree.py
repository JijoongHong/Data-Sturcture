import collections

def bfs_spanning_tree(graph, start):
    visited = set([start]) # 맨 처음의 경우 방문 노드에 start
    queue = collections.deque([start]) # 덱 생성
    while queue: # 큐가 공백이 아닐 때 까지
        vertex = queue.popleft() # 큐에서 하나의 정점을 꺼냄
        nbr = graph[vertex] - visited # 그래프에서 방문 정점을 삭제함
        for u in nbr: # 갈 수 있는 모든 정점에 대해
            print("(", vertex, ",", u,")", end='') #(v,u) 간선 추가
            visited.add(u) # u방문
            queue.append(u) # u 큐에 삽입



graph = {"A": {"B", "C"},
         "B": {"A", "D"},
         "C": {"A", "D", "E"},
         "D": {"B", "C", "F"},
         "E": {"C", "G", "H"},
         "F": {"D"},
         "G": {"E", "H"},
         "H": {"E", "G"}
         }
bfs_spanning_tree(graph, "A")
# >>> ( A , B )( A , C )( B , D )( C , E )( D , F )( E , H )( E , G )