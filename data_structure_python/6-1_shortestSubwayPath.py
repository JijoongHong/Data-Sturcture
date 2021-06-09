INF = 9999


class Graph:
    def __init__(self, len):
        self.matrix = [[INF for i in range(len)] for j in range(len)] # 정방형 인접행렬 생성
        self.num = len # 정점 개수
        self.visited = [False]*self.num # 방문여부 리스트

    def insert_edge(self, row, col, distance):
        self.matrix[row][row] = 0 # 자신까지의 거리 0
        self.matrix[row][col] = distance # 역1->역2까지의 거리
        self.matrix[col][row] = distance # 역2->역1까지의 거리

    def dfs(self, start, station_num):
        self.visited[start] = True # 시작 정점을 방문한 것으로 표시
        print(station_num[start] + " | ", end="")
        for w in range(self.num): # 모든 정점에 대해
            if self.matrix[start][w] != 0 and self.visited[w] is False: # 방문하지 않은 인접 정점을 찾고
                self.dfs(w, station_num) # 재귀적으로 호출

    def choose_vertex(self, dist, found):  # 최소 거리 vertex 찾는 함수
        # 초기값 설정
        min = INF
        min_idx = -1

        for i in range(len(dist)):  # 모든 정점 중에서
            if dist[i] < min and found[i] == False:  # 방문하지 않은 최소 dist 내의 정점
                min = dist[i] # min값 갱신
                min_idx = i # 최소 거리 정점의 인덱스 최신화

        return min_idx  # 최소 거리 정점의 인덱스 반환

    def shotest_path(self, start, end):
        dist = self.matrix[start] # dist 배열 생성 및 초기화
        path = [start] * self.num  # path 배열 생성 및 초기화
        found = [False] * self.num  # found 배열 생성 및 초기화
        found[start] = True  # 시작 정점을 이미 찾은 것으로 표시

        for i in range(self.num):
            shortest = self.choose_vertex(dist, found)  # 최단 거리 정점 탐색
            found[shortest] = True  # 최단 거리 정점를 찾은 것으로 표시

            for vertex in range(self.num):  # 모든 정점에 대해
                if not found[vertex]:  # 아직 찾아지지 않았으면
                    if dist[shortest] + self.matrix[shortest][vertex] < dist[vertex]:  # 갱신조건 검사
                        dist[vertex] = dist[shortest] + self.matrix[shortest][vertex]  # dist 갱신
                        path[vertex] = shortest  # 이전 정점 갱신

        return path, dist[end]  # 찾아진 최단 경로 반환


def init_graph(stations):
    graph = Graph(len(stations))

    # 1호선
    graph.insert_edge(stations["노량진"], stations["용산"], 1.8)
    graph.insert_edge(stations["용산"], stations["남영"], 1.5)
    graph.insert_edge(stations["남영"], stations["서울역"], 1.7)
    graph.insert_edge(stations["서울역"], stations["시청"], 1.1)
    graph.insert_edge(stations["시청"], stations["종각"], 1.0)
    graph.insert_edge(stations["종각"], stations["종로3가"], 0.8)
    graph.insert_edge(stations["종로3가"], stations["종로5가"], 0.9)
    graph.insert_edge(stations["종로5가"], stations["동대문"], 0.8)

    # 2호선
    graph.insert_edge(stations["충정로"], stations["시청"], 1.1)
    graph.insert_edge(stations["시청"], stations["을지로입구"], 0.7)
    graph.insert_edge(stations["을지로입구"], stations["을지로3가"], 0.8)
    graph.insert_edge(stations["을지로3가"], stations["을지로4가"], 0.6)
    graph.insert_edge(stations["을지로4가"], stations["동대문역사문화공원"], 1.0)

    # 3호선
    graph.insert_edge(stations["종로3가"], stations["을지로3가"], 0.6)
    graph.insert_edge(stations["을지로3가"], stations["충무로"], 0.7)
    graph.insert_edge(stations["충무로"], stations["동대입구"], 0.9)
    graph.insert_edge(stations["동대입구"], stations["옥수"], 2.3)
    graph.insert_edge(stations["옥수"], stations["압구정"], 2.1)
    graph.insert_edge(stations["압구정"], stations["신사"], 1.5)
    graph.insert_edge(stations["신사"], stations["고속터미널"], 2.1)

    # 4호선
    graph.insert_edge(stations["동대문"], stations["동대문역사문화공원"], 0.7)
    graph.insert_edge(stations["동대문역사문화공원"], stations["충무로"], 1.3)
    graph.insert_edge(stations["충무로"], stations["명동"], 0.7)
    graph.insert_edge(stations["명동"], stations["서울역"], 1.6)
    graph.insert_edge(stations["서울역"], stations["삼각지"], 2.2)
    graph.insert_edge(stations["삼각지"], stations["이촌"], 2.0)
    graph.insert_edge(stations["이촌"], stations["동작"], 2.7)

    # 5호선
    graph.insert_edge(stations["여의도"], stations["마포"], 2.8)
    graph.insert_edge(stations["마포"], stations["충정로"], 2.8)
    graph.insert_edge(stations["충정로"], stations["광화문"], 1.8)
    graph.insert_edge(stations["광화문"], stations["종로3가"], 1.2)
    graph.insert_edge(stations["종로3가"], stations["을지로4가"], 1.0)
    graph.insert_edge(stations["을지로4가"], stations["동대문역사문화공원"], 0.9)

    # 경의중앙선
    graph.insert_edge(stations["용산"], stations["이촌"], 1.9)
    graph.insert_edge(stations["이촌"], stations["서빙고"], 1.7)
    graph.insert_edge(stations["서빙고"], stations["한남"], 1.9)
    graph.insert_edge(stations["한남"], stations["옥수"], 1.6)

    # 9호선
    graph.insert_edge(stations["여의도"], stations["노량진"], 2.0)
    graph.insert_edge(stations["노량진"], stations["흑석"], 2.2)
    graph.insert_edge(stations["흑석"], stations["동작"], 1.4)
    graph.insert_edge(stations["동작"], stations["고속터미널"], 2.5)

    return graph


def main():
    stations_list = ["노량진", "용산", "남영", "서울역", "시청", "종각", "종로3가", "종로5가",
                     "동대문", "충정로", "을지로입구", "을지로3가", "을지로4가", "동대문역사문화공원",
                     "충무로", "동대입구", "옥수", "압구정", "신사", "고속터미널", "명동", "삼각지", "이촌", "동작",
                     "광화문", "마포", "여의도", "흑석", "서빙고", "한남"]

    idx = [i for i in range(len(stations_list))] # 역번호
    stations = dict(zip(stations_list, idx)) # {역이름 : 번호}
    station_num = dict(zip(idx, stations)) # {번호 : 역이름}
    graph = init_graph(stations) # 그래프 생성
    graph.dfs(0, station_num) # dfs

    print("\n출발역을 입력하세요 ", end="")
    start = stations[input()]
    print("도착역을 입력하세요 ", end="")
    end = stations[input()]

    path = graph.shotest_path(start, end) # 최단경로와 최단거리 반환

    # 백트래킹
    result = []
    if end != start:
        print("\n[최단경로 %s->%s] " % (stations_list[start], stations_list[end]), end='')
        result.append(stations_list[end])
        while path[0][end] != start:
            result.append(stations_list[path[0][end]])
            end = path[0][end]
        result.append(stations_list[path[0][end]])

    # 결과 출력
    for i in range(len(result)-1, 0, -1): # 역순 출력
        print("%s->" % result[i], end="")
    print(result[0])
    print("이동거리" + str(round(path[1], 1)))


if __name__ == "__main__":
    main()
