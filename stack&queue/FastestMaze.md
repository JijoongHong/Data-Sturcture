# 2. 미로 탐색

 ![image](https://user-images.githubusercontent.com/63644587/116434226-351ad600-a885-11eb-9b7d-88325ffc05ae.png)


## 1. 미로의 저장

- 미로는 다음과 같은 요소를 가진 구조체로 정의된다.
  - x좌표(int x)
  - y좌표(int y)
  - 막혀있는 부분(unsigned short map:4)
  - 진행해야하는 방향(unsigned short dir:4)
  - 미로 경로에 해당하는지 유무(unsigned short star:1)

- 미로의 막혀있는 부분과 진행해야 하는 방향은 비트로 구성하여 0~15의 조합을 만들어 표현하였다. 

- ||<p>상</p><p>(1)</p>||
  | :-: | :-: | :-: |
  |<p>하</p><p>(8)</p>|(x, y)|<p>우</p><p>(4)</p>|
  ||<p>하</p><p>(2)</p>||

- 미로의 전체 좌표는 위와 같은 구조체를 가진 2차원 배열 new\_maze[12][9]로 구성된다.



## 2. 진로방향 설정 및 이동

- 진로설정을 위하여 현재위치, 임시현재위치, 이전위치를 표시하는 구조체를 선언한다. 이는 임시변수로서 원본 좌표정보를 변경하지 않는 역할을 겸한다.  
- find\_way(new\_maze, curr\_pos, prev\_pos)를 통해 다음에 가야할 방향을 찾는다.
  - 현재좌표의 막혀있는 곳, 이전좌표에서 이동한 방향을 더한 후 1111(15)와 XOR 연산 수행 시 다음 진행 방향을 알 수 있다.
  - 아래 사진은 과제로 주어진 미로의 상단이다. 만약 [0,1]에서 [0,2]로 이동한다고 가정했을 때, 오른쪽으로 한칸 진행하는 것을 알 수 있다.


  - ![image](https://user-images.githubusercontent.com/63644587/116432555-a22d6c00-a883-11eb-87ef-66f6e5e72593.png)


  - 이 때 curr\_pose의 map은 위와 아래가 막혀있으므로 3이다. 
  - 그리고 prev\_pose인 [0,0]의 이동방향(dir)을 오른쪽(4)의 반대뱡향인 8로 바꿔준다. 이러한 연산은 한 방향으로 진행할 때 마다 prev\_pose의 dir에 미리 저장해 둔다. (예, 우(4)로 1칸 이동했다면 좌(8)을 저장하여 막혀있는 것처럼 인식하도록 함)
  - 8과 3을 더한 11과 15의 XOR연산 시 다음 진행방향은 오른쪽인 4가 나온다. 이를 curr\_pose의 dir 변수에 저장한다.


  - ||하(8)|우(4)|하(2)|상(1)|
    | :- | :- | :- | :- | :- |
    |막혀있는 곳|1|0|1|1|
    |15|1|1 |1|1|
    |연산결과|0|1|0|0|


  - 즉 이전에 왔던 길을 막음으로써 갈림길이 없는 일반적인 경로에 대해 한가지 진행방향만을 갖도록 만든다.
  - 위와 같은 방식을 목표지점에 도달할 때 까지 반복한다.


- 만약 갈림길인 경우 두 경우로 분할하여 스택에 저장한다.
  - 이 때 두 방향으로 갈리게 되는데, 과제의 미로는 좌상단에서 우하단으로 이동하는 미로이므로 오른쪽과 하단을 우선순위로 정하여, pop할 시 위 방향으로 우선적으로 가도록 했다. 
  - 이는 경로가 2개이므로 무한루프가 도는 것을 방지해줄 수 있다.  


## 3. 갈림길의 저장

- 갈림길은 동적스택을 활용한다.
- 과제의 요구사항에서 스택 이용횟수와 입출입 자료의 내용을 표시해야하므로 전역변수 count를 선언하고, pop과 push가 실행될 때 마다 count를 증가시키고 해당 자료를 출력한다. 

- 갈림길 저장용 유동스택(s)
  - 2개 이상의 진로가 가능한 경우 이를 저장한다.
  - 이를 하나씩 pop하여 이동하고, 만약 진로가 불가능하다면 스택에서 다음 요소를 pop하여 원래 위치로 돌아와 다른 경로로 이동한다. 

- 찾은 경로의 옳은 갈림길 저장 스택(route)
  - 위의 스택은 자료가 지속적으로 소실된다. 그러므로 옳은 갈림길만을 저장하는 스택을 하나 더 운용해야 한다. 
  - 갈림길이 나올 때 마다 유동스택과 마찬가지로 모든 갈림길 정보를 저장한다. 그리고 갈림길의 한 방향에서 실패 시 유동스택에서 다른 갈림길 정보를 pop하게 되는데, 그 때마다 route에 동일한 좌표가 있는지 is\_exist(Stack \*route, maze curr\_pose)를 통해 검사한다. 

  - 아래 정보는 실제 실행과정에서 route 스택의  운용과정을 보여준다. 
  - <img width="170" alt="스크린샷 2021-04-29 오전 12 43 20" src="https://user-images.githubusercontent.com/63644587/116432876-ec165200-a883-11eb-9182-b91967412667.png">


  - 흰색은 운이 좋게도 옳은 갈림길을 선택하여 지속적으로 진로가 가능한 경우이다. 
  - 노란색의 경우 한 방향이 불가능하여 바로 이전 갈림길을 삭제하고, 원래 위치로 돌아간 경우를 표현한다. 
  - 문제가 되는 것은 [8,3]의 초록색 부분이다. [8,3]에서 2(하)방향으로 이동한 후 한동안 정상적인 경로를 따라가는 것 처럼 보인다. 그러나 파란색의 경우 잘못된 갈림길에 진입한 후 지속적으로 또다른 갈림길을 마주치는 경우이다. 그러므로 파란색 값들은 필요가 없는 값이므로 전부 삭제해야한다. 

  - 이 경우를 미로에 표현하면 다음과 같다.

  - ![image](https://user-images.githubusercontent.com/63644587/116432597-ac4f6a80-a883-11eb-8726-a321d4e5babc.png)


  - 그러므로 is\_exist함수는 앞서 말한 스택운용의 노란색 부분을 삭제하는 경우와, 갈림길을 잘못 선택한 후 헤메는 경로인 파란색을 모두 삭제하는 경우로 나누어서 운용한다.

  - 위의 과정을 마치면 한 경로에 대해 옳은 갈림길 정보가 모두 저장된다. 하나의 경로를 찾게 되면 경로의 개수인 routes 변수에 1을 더하고, route스택에 목표지점의 좌표정보를 넣는다. 이는 2개 이상의 경로를 찾을 수 있는 경우가 있으므로 다른 경로와의 구분자 역할을 동시에 수행한다. 


## 4. 2개이상의 경로 탐색

- 하나의 경로를 모두 찾았다면 유동스택 s의 가장 아래쪽에 있는 경로를 현재위치로 삼아 위와 동일한 과정을 수행한다.
- 만약 스택 가장 아래쪽의 경로가 또다른 경로를 찾지 못한다면 종료한다.
- 왜냐하면 이미 가능한 경로를 모두 찾았다면 유동스택 s에 남아있는 위치정보는 성공할 수 없는 위치에 있는 것들만이 남아있는 것이고, 돌아갈 이전 정보가 없기 때문이다.


## 5. 최단거리 찾기

- 가능한 모든 경로의 갈림길이 route에 저장되었다면, 각 경로의 좌표에 이를 표현해주는 한편 최단길이를 계산해야 한다. 
- 이 때 find\_path(Stack \*route, maze new\_maze[12][9], int routes)를 통하여 [12][9]의 2차원 배열로 이루어진 미로의 좌표정보들을 경로 개수만큼 생성한다.
- 이는 [routes][12][9]로 이루어진 3차원 배열을 동적할당하여 생성한다.
- 각 좌표정보들은 갈림길을 제외하고는 동일하게 사용하므로 main에서 입력해준 좌표정보들을 옮긴다. 
- 이후 route스택에서 옳은 갈림길 정보를 pop하여 방향정보를 각 경로에 맞게 설정해준다. 
- 위 과정을 마치면 가능한 경로만큼 새로운 좌표정보가 생성이 된다. 위 좌표정보들을 find\_length(maze\*\*\* revised\_maze, int routes)를 통해 위의 로직과 동일하게 한칸씩 이동하며 해당 좌표가 이동경로임을 표시해준다. 이는 구조체의 star 변수를 1로 바꾸어 주는 방식으로 이루어진다. 이와 동시에 한칸씩 이동할 때 마다 length 변수를 더해주어 경로를 구할 수 있도록 한다. 
- 모든 가능한 경로에 대해 위 과정을 마치면 length의 크기를 비교하고, 크기가 더 작은 경로를 출력한다. 

## 6. 미로의 출력

- 미로는 한 칸에 가로 4칸씩, 세로 2칸씩 저장한다. 가로에는 ‘\_’를 4개 사용하고, 세로에는 ‘|’를 두개 사용하여 정사각형의 형태를 가지도록 하였다. 
- 이는 이동경로를 표현해야하기 때문에 여유를 두어서 미로를 구성한 것이다. 
- 그러므로 한 행을 출력하기 위해서는 두번의 출력작업이 필요하다. 
- 이 때 첫째 줄은 세로줄만 출력하고 둘째 줄에는 세로와 가로줄 모두 출력한다.

- 출력할 정보는 막힌 벽의 정보인 maze구조체의 map 변수를 활용하여 결정하였다. 
- 이 때 한칸의 정보는 다른 한칸과 중첩되게 된다. 그러므로 표현할 정보는 해당 칸의 좌측과 하단의 정보만을 표시한다. 그러므로 미로의 맨 윗쪽 벽과 우측 마지막 벽은 따로 출력하였다. 

- 만약 출력 시 해당 좌표가 미로의 이동경로에 해당한다면 ‘\*’을 추가하여 출력하고, 해당하지 않는다면 일반적인 벽을 구성한다.
- 출력결과

- ![image](https://user-images.githubusercontent.com/63644587/116432643-b7a29600-a883-11eb-8900-cfd21124a887.png)


