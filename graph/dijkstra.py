INF = 9999

def choose_vertex(dist, found): # 최소 거리 vertex 찾는 함수
    min = INF
    minpos = -1
    for i in range(len(dist)):  # 모든 정점 중에서
        if dist[i] < min and found[i] == False: # 방문하지 않은 최소 dist 정점
            min = dist[i]
            minpos = i

    return minpos # 최소 dist 정점의 인덱스 반환

def shotest_path(vtx, adj, start):
    vsize = len(vtx) # 정점 수
    dist = list(adj[start]) # dist 배열 생성 및 초기화
    path = [start] * vsize # path 배열 생성 및 초기화
    found = [False] * vsize  # found 배열 생성 및 초기화
    found[start] = True # 시작 정점을 이미 찾은 것으로 표시
    dist[start] # 시작정점의 거리 0

    for i in range(vsize):
        print("step%2d:"%(i+1), dist) # 단계별 거리 출력용
        u = choose_vertex(dist, found) # 최소 정점 거리 정점 u 탐색
        found[u] = True # u를 찾은 것으로 표시

        for w in range(vsize): # 모든 정점에 대해
            if not found[w]: # 아직 찾아지지 않았으면
                if dist[u] + adj[u][w] < dist[w]: # 갱신조건 검사
                    dist[w] = dist[u] + adj[u][w] # dist 갱신
                    path[w] = u # 이전 정점 갱신

    return path # 찾아진 최단 경로 반환


vertex = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
weight = [[0,7,INF, INF, 3, 10, INF],
          [7,0,4,10,2,6,INF],
          [INF,4,0,2,INF,INF,INF],
          [INF,10,2,0,11,9,4],
          [3,2,INF,11,0,13,5],
          [10,6,INF,9,13,0,INF],
          [INF,INF,INF,4,5,INF,0]]

print("shortest Path by dijkstra algorithm")
start = 0 
path = shotest_path(vertex, weight, start)

for end in range(len(vertex)):
    if end != start:
        print("[최단경로 %s->%s] %s"%(vertex[start], vertex[end], vertex[end]), end='')
        while (path[end] != start):
            print(" <- %s"%vertex[path[end]], end='')
            end = path[end]
        print(" <-%s"%vertex[path[end]])

