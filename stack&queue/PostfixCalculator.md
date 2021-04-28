**2021자료구조**

**과제2 – 계산기, 미로탐색, 큐 운영**



![](Aspose.Words.528f683e-cd7d-4f59-998b-9843abeea2d5.001.jpeg)




**중앙대학교**

**자료구조 05분반**

**20173745 정도현**

**20176963 홍지중**

**1. 후위연산 활용 계산기**

\1. 후위식 변환

- int operator(char op) : 연산자에 우선순위를 주는 함수
- ‘^’ 의 우선순위 7, ‘%\*’ 의 우선순위 5, ‘+-’ 의 우선순위 3, ‘(‘ 의 우선순위 1을 주고, 아무것도 없을 경우는 -1를 반환하게 만들었다.

- int whoPrecede(char op1, char op2): 어떤 연산자의 우선순위가 더 높은지 판별하는 함수
- 후위식을 만들 때, 문자열 공간을 하나 만든담에 모두 0이 되도록 초기화를 시킨다.
- 그리고 input으로 들어온 식을 순차탐색한다.
- 숫자일 경우
- input[index]를 result[rindex]에 넣어준다.
- 그리고 만약 input[index+1]이 숫자일 경우는 계속 result[rindex]에 넣어주지만 그 뒤에 연산자가 나올경우 ‘ ‘를 넣어주면서, 2자리수 3자리수를 대비했다.
- 연산자 혹은 괄호일 경우
- 만약 postfix라는 스택이 비어있지 않고, 스택 맨위에 있는 연산자가 input[index]보다 우선순위가 높거나, 같다면, while문을 돌면서 우선순위가 낮은 것이 나올때까지 pop하면서 pop한 값은 result[rindex]에 저장한다. 저장하면서 뒤에는 ‘ ‘를 넣어준다.
- 조건에 맞게 다 스택에서 뺸 뒤에는 input[index] 값을 push 해준다.(stack이 비었을때, 혹은 우선순위가 낮은 연산자가 나왔을 경우)
- ‘(’가 나왔을 경우, 스택에 push 한다.
- ‘)’ 가 나왔을 경우, 스택에는 무조건 ‘(’ 가 존재해야한다. 아니면 오류이다. 따라서 while(1)을 돌면서 pop한다. 그리고 pop한 데이터는 result에 붙여준다. 그리고 ‘(‘ 가 나올 경우, while 문에서 break 한다.
- 식이 다 끝날을 경우, stack이 비지 않았다면, result에 pop으로 붙여준다.
- 그리고 result값은 input에 strcpy로 복사한 뒤, result는 free 해준다.
- 출력값
  ![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh6.googleusercontent.com/3saLv29peqBPW\_YUXzzUVf2bOBVCIKLMO0A3cPaBQ9kfuaXjvIgH9o-Gmcqtao5oXB6vDhAM5dh3BcOj1f9fX9l7BLqVL614WigU0SBcGnPtwDkP8dZpckBzetTQhaHY0\_UX3\_bb)

\2. 후위식 계산

- 후위식 계산 전에, strtok로 후위식 변환으로 변경된 문자열을 잘라서 char\* result[100]이라는 배열에 저장하였다.
- 위의 경우는 [“2”, “3”, “4”, “\*”, “2”, “^”, “+, “12”, “-”]로 저장된다.
- 그 뒤에 이 배열을 순차탐색을 한다.
  - ` `**if**(atoi(result[i])>0 && strcmp(result[i],"0")) atoi함수는 result가 문자면 0을 반환하고, 숫자면 숫자에 맞게 반환한다. 따라서 result에 0을 제외한 모든 숫자가 있을 경우, stack에 push하도록 했다.
  - **else** **if** (!strcmp(result[i],"0")) 이 경우는 result가 숫자 0 일 경우이다. 마찬가지로 stack에 push 하도록 했다.
  - **else** result[i]가 연산자 혹은 괄호일 때이다.
  - 스택은 후입선출이기 때문에, 먼저 뺸것이 연산자를 기준으로 뒤로 가야한다. 
  - 두개를 pop 시킨다음 그에 대한 연산 결과를 다시 push 한다. 그리고 순차탐색을 하면서, 연산자가 나올 경우, 동일한 매커니즘으로 진행한다.
  - 순차탐색이 완료될 경우, 모든 연산이 끝났음을 의미하므로, stack에는 하나의 숫자만 있을 것이고, 이를 pop 시키면 결과가 나온다.
- 출력값

`	`![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh4.googleusercontent.com/3VOtsF0lwas7kAik4AMyQ90QHnR1x9f3HUHfW7u\_DA98a0Boi7nc6fLL2cC\_odXM3NN10XU-DbYOLpCJasaYOTwCHGByxGL9\_cl8SVbVerrQ6UPpBTt8OKqsD94wS4un9VSRCEY-)




\3. 오류 판별

- 오류 판별의 경우는 main에서 후위연산과 후위연산 계산 함수에 들어가기전에 먼저 진행한다.
- 오류 종류는 1. 처음에 연산자가 나올경우, 2. 연산자가 연속으로 나올 경우, 3. 괄호가 안 닫혀있는 경우, 4. 닫는 괄호만  있는 경우
- 역시 식을 순차탐색하면서, switch 문을 활용해서 경우를 나눴다.
- **case** '+': **case** '-': **case** '\*': **case** '%': **case** '^': //부호라면
  - 처음에 있다면 그 위치를 반환했다. (오류종류 1번)
  - 또한 지금 위치 바로 전에 부호가 존재한다면, 지금 위치를 반환하게 한다. (오류종류 2번)
- **case** '(': 
  - 스택에 push한다. 
- **case** ')': 
  - 스택에 push는 ‘(’만 하기 때문에, ‘)’ 이 나올 경우, pop을 시키면, ‘(’ 이 나와야한다. 또한 문제의 조건에서 중첩괄호를 쓰지 않기 때문에, 이 명제는 성립한다. 만약에 pop을 할 경우에 stack에 ‘(’이 없다면, 이 위치를 반환하게 했다.(오류종류 4번) 
- 순차탐색이 끝난 휘에, 스택이 비지 않았다면, ‘(’ 만 남았다는 의미이다. (오류 종류 3번) 순차탐색 인덱스 - 1의 위치를 반환한다.
- 오류가 없다면 MAX\_NUM +1을 반환하게 했다.

\4. Main함수

- 오류가 있을 경우, location이라는 변수로 오류 위치를 받고, for문으로 location 전까지 “ “를 찍고, 마지막에 ("^이위치에 오류존재\n")를 출력했다.

![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh5.googleusercontent.com/6X3jb6hUoGHsXdDT6npsUMTPQ7YjkvPVkyyYPCH70ZTC278THJ5ngasVpNyMpM0jjjEUcjRM1HPNTII3MLX37kclF\_DVuGJkPodMjZRxM734qugPe7ZzElPEu40o3zbLTtIIO78K)   ![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh5.googleusercontent.com/VEBDWasY\_yiRUAJCk1yV3ZznwkbNMMrWHQpeu5rHpBTq6Rdtl7aafbIaTr\_I5pMFAGzQGm6-12wtI2RWF46Q78Gg7c1ayd2s7X8H-hlZdACvgnGOIUNtds2xut0kpeeufoMmp2Qc)

![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh5.googleusercontent.com/02r7w6uxB0QGjiIgKUUh3Fa5jHJNbxhMavQXTxIlay2OfuguDeOju12iHIQupDdoK1-AoS9bEEcI0padcYkZczCdaZkmiNRpkxGJHtHwjQZYgfjkuEijMGNvVmUaBPVFJCUAMDHX)            ![](https://lh6.googleusercontent.com/7\_lnQOHCHzyCpYOd1T55CNEZqMdgzmfms02oFX8RXiT8ij08wRmdrjAMNs9t7I7Dpahzs2-RA\_nQf5Y0UX1jSQ3YDdQlroel\_IERX4mx-OGY7Foole3UJKz16Z3szmIFb9Jb2z5s)

**2. 미로 탐색**

\1. 미로의 저장

- 미로는 다음과 같은 요소를 가진 구조체로 정의된다.
- x좌표(int x)
- y좌표(int y)
- 막혀있는 부분(unsigned short map:4)
- 진행해야하는 방향(unsigned short dir:4)
- 미로 경로에 해당하는지 유무(unsigned short star:1)

- 미로의 막혀있는 부분과 진행해야 하는 방향은 비트로 구성하여 0~15의 조합을 만들어 표현하였다. 

||<p>상</p><p>(1)</p>||
| :-: | :-: | :-: |
|<p>하</p><p>(8)</p>|(x, y)|<p>우</p><p>(4)</p>|
||<p>하</p><p>(2)</p>||

- 미로의 전체 좌표는 위와 같은 구조체를 가진 2차원 배열 new\_maze[12][9]로 구성된다.



\2. 진로방향 설정 및 이동

- 진로설정을 위하여 현재위치, 임시현재위치, 이전위치를 표시하는 구조체를 선언한다. 이는 임시변수로서 원본 좌표정보를 변경하지 않는 역할을 겸한다.  
- find\_way(new\_maze, curr\_pos, prev\_pos)를 통해 다음에 가야할 방향을 찾는다.
- 현재좌표의 막혀있는 곳, 이전좌표에서 이동한 방향을 더한 후 1111(15)와 XOR 연산 수행 시 다음 진행 방향을 알 수 있다.
- 아래 사진은 과제로 주어진 미로의 상단이다. 만약 [0,1]에서 [0,2]로 이동한다고 가정했을 때, 오른쪽으로 한칸 진행하는 것을 알 수 있다.

  ![](https://lh5.googleusercontent.com/E4\_tg17qn6HIt6dgVfBdMK3ETybEiG6B21PxXH-NfuwtvZfvaMfMTvxNinXkAHcMPiM6bzRmRkcKALJIcz8da3Et\_qm6wlsiPvy\_uFQ0CTDfZh-xNTFsxoC04Riek6A012O9pI8r)

- 이 때 curr\_pose의 map은 위와 아래가 막혀있으므로 3이다. 
- 그리고 prev\_pose인 [0,0]의 이동방향(dir)을 오른쪽(4)의 반대뱡향인 8로 바꿔준다. 이러한 연산은 한 방향으로 진행할 때 마다 prev\_pose의 dir에 미리 저장해 둔다. (예, 우(4)로 1칸 이동했다면 좌(8)을 저장하여 막혀있는 것처럼 인식하도록 함)
- 8과 3을 더한 11과 15의 XOR연산 시 다음 진행방향은 오른쪽인 4가 나온다. 이를 curr\_pose의 dir 변수에 저장한다.


||하(8)|우(4)|하(2)|상(1)|
| :- | :- | :- | :- | :- |
|막혀있는 곳|1|0|1|1|
|15|1|1 |1|1|
|연산결과|0|1|0|0|








- 즉 이전에 왔던 길을 막음으로써 갈림길이 없는 일반적인 경로에 대해 한가지 진행방향만을 갖도록 만든다.
- 위와 같은 방식을 목표지점에 도달할 때 까지 반복한다.


- 만약 갈림길인 경우 두 경우로 분할하여 스택에 저장한다.
- 이 때 두 방향으로 갈리게 되는데, 과제의 미로는 좌상단에서 우하단으로 이동하는 미로이므로 오른쪽과 하단을 우선순위로 정하여, pop할 시 위 방향으로 우선적으로 가도록 했다. 
- 이는 경로가 2개이므로 무한루프가 도는 것을 방지해줄 수 있다.  


\3. 갈림길의 저장

- 갈림길은 동적스택을 활용한다.
- 과제의 요구사항에서 스택 이용횟수와 입출입 자료의 내용을 표시해야하므로 전역변수 count를 선언하고, pop과 push가 실행될 때 마다 count를 증가시키고 해당 자료를 출력한다. 

- 갈림길 저장용 유동스택(s)
- 2개 이상의 진로가 가능한 경우 이를 저장한다.
- 이를 하나씩 pop하여 이동하고, 만약 진로가 불가능하다면 스택에서 다음 요소를 pop하여 원래 위치로 돌아와 다른 경로로 이동한다. 

- 찾은 경로의 옳은 갈림길 저장 스택(route)
- 위의 스택은 자료가 지속적으로 소실된다. 그러므로 옳은 갈림길만을 저장하는 스택을 하나 더 운용해야 한다. 
- 갈림길이 나올 때 마다 유동스택과 마찬가지로 모든 갈림길 정보를 저장한다. 그리고 갈림길의 한 방향에서 실패 시 유동스택에서 다른 갈림길 정보를 pop하게 되는데, 그 때마다 route에 동일한 좌표가 있는지 is\_exist(Stack \*route, maze curr\_pose)를 통해 검사한다. 

- 아래 정보는 실제 실행과정에서 route 스택의  운용과정을 보여준다. 

**(8, 6, 11, 4)**

**~~(8, 6, 13, 2)~~**

**(6, 7, 13, 2)**

**(8, 3, 11, 4)**

**(10, 5, 11, 4)**

**~~(10, 5, 14, 1)~~**

**(9, 3, 11, 4)**

**(9, 0, 14, 1)**

**~~(9, 0, 13, 2)~~**

**~~(9, 3, 13, 2)~~**

**~~(8, 3, 13, 2)~~**

**(5, 3, 13, 2)**

**(4, 3, 13, 2)**

**(5, 0, 13, 2)**

**(2, 2, 7, 8)**

**~~(2, 2, 13, 2)~~**

**(0, 0, 13, 2)**

- 흰색은 운이 좋게도 옳은 갈림길을 선택하여 지속적으로 진로가 가능한 경우이다. 
- 노란색의 경우 한 방향이 불가능하여 바로 이전 갈림길을 삭제하고, 원래 위치로 돌아간 경우를 표현한다. 
- 문제가 되는 것은 [8,3]의 초록색 부분이다. [8,3]에서 2(하)방향으로 이동한 후 한동안 정상적인 경로를 따라가는 것 처럼 보인다. 그러나 파란색의 경우 잘못된 갈림길에 진입한 후 지속적으로 또다른 갈림길을 마주치는 경우이다. 그러므로 파란색 값들은 필요가 없는 값이므로 전부 삭제해야한다. 

- 이 경우를 미로에 표현하면 다음과 같다.

![](https://lh5.googleusercontent.com/GIG5hmjGoQEueVdHqAs3MYgq2pOrqMtBwyHL4MTZTad2fa4m5JOFkAiS7R2v6-N95qqax3uNtpvZwBWJaYwwh2MDW7q-SNdewgjaxNfWPUbthWNOD7W1JB6NPo59jbdFD\_Vzyfta)

- 그러므로 is\_exist함수는 앞서 말한 스택운용의 노란색 부분을 삭제하는 경우와, 갈림길을 잘못 선택한 후 헤메는 경로인 파란색을 모두 삭제하는 경우로 나누어서 운용한다.

- 위의 과정을 마치면 한 경로에 대해 옳은 갈림길 정보가 모두 저장된다. 하나의 경로를 찾게 되면 경로의 개수인 routes 변수에 1을 더하고, route스택에 목표지점의 좌표정보를 넣는다. 이는 2개 이상의 경로를 찾을 수 있는 경우가 있으므로 다른 경로와의 구분자 역할을 동시에 수행한다. 


\4. 2개이상의 경로 탐색

- 하나의 경로를 모두 찾았다면 유동스택 s의 가장 아래쪽에 있는 경로를 현재위치로 삼아 위와 동일한 과정을 수행한다.
- 만약 스택 가장 아래쪽의 경로가 또다른 경로를 찾지 못한다면 종료한다.
- 왜냐하면 이미 가능한 경로를 모두 찾았다면 유동스택 s에 남아있는 위치정보는 성공할 수 없는 위치에 있는 것들만이 남아있는 것이고, 돌아갈 이전 정보가 없기 때문이다.


\5. 최단거리 찾기

- 가능한 모든 경로의 갈림길이 route에 저장되었다면, 각 경로의 좌표에 이를 표현해주는 한편 최단길이를 계산해야 한다. 
- 이 때 find\_path(Stack \*route, maze new\_maze[12][9], int routes)를 통하여 [12][9]의 2차원 배열로 이루어진 미로의 좌표정보들을 경로 개수만큼 생성한다.
- 이는 [routes][12][9]로 이루어진 3차원 배열을 동적할당하여 생성한다.
- 각 좌표정보들은 갈림길을 제외하고는 동일하게 사용하므로 main에서 입력해준 좌표정보들을 옮긴다. 
- 이후 route스택에서 옳은 갈림길 정보를 pop하여 방향정보를 각 경로에 맞게 설정해준다. 
- 위 과정을 마치면 가능한 경로만큼 새로운 좌표정보가 생성이 된다. 위 좌표정보들을 find\_length(maze\*\*\* revised\_maze, int routes)를 통해 위의 로직과 동일하게 한칸씩 이동하며 해당 좌표가 이동경로임을 표시해준다. 이는 구조체의 star 변수를 1로 바꾸어 주는 방식으로 이루어진다. 이와 동시에 한칸씩 이동할 때 마다 length 변수를 더해주어 경로를 구할 수 있도록 한다. 
- 모든 가능한 경로에 대해 위 과정을 마치면 length의 크기를 비교하고, 크기가 더 작은 경로를 출력한다. 

\6. 미로의 출력

- 미로는 한 칸에 가로 4칸씩, 세로 2칸씩 저장한다. 가로에는 ‘\_’를 4개 사용하고, 세로에는 ‘|’를 두개 사용하여 정사각형의 형태를 가지도록 하였다. 
- 이는 이동경로를 표현해야하기 때문에 여유를 두어서 미로를 구성한 것이다. 
- 그러므로 한 행을 출력하기 위해서는 두번의 출력작업이 필요하다. 
- 이 때 첫째 줄은 세로줄만 출력하고 둘째 줄에는 세로와 가로줄 모두 출력한다.

- 출력할 정보는 막힌 벽의 정보인 maze구조체의 map 변수를 활용하여 결정하였다. 
- 이 때 한칸의 정보는 다른 한칸과 중첩되게 된다. 그러므로 표현할 정보는 해당 칸의 좌측과 하단의 정보만을 표시한다. 그러므로 미로의 맨 윗쪽 벽과 우측 마지막 벽은 따로 출력하였다. 

- 만약 출력 시 해당 좌표가 미로의 이동경로에 해당한다면 ‘\*’을 추가하여 출력하고, 해당하지 않는다면 일반적인 벽을 구성한다.
- 출력결과

![](https://lh3.googleusercontent.com/-M8OhirSzYfxgf2V\_TjBIXSIP1HfZi3rFSVGpNH\_XRifzYUC4TjTHPJCbMpivm5eQ3fF4JfB6zGJw98wH-YiMuJ0NU-17K-W6ucolFt-v49rEP1BHDUVdtEOjH0dEaXansaMgPUf)

**3. 큐 운영하기**

\1. 에러표시 

- 입력큐를는 20 글자를 갖고, 초과하면 ERROR 표시를 갖기 위해 MAX\_NUM을 21로 만들고, queue 함수에서 20이 넘어갈 경우, ERROR를 표시하게 만들었다.
- 출력결과

![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh5.googleusercontent.com/BxlXF4ccv2L0H8tg1FzWcqj-LcEoXs4pUf\_S4BjR1jNz-y7hYHiHrIlJvhi-IpW49cEm7x0kIv2om1IupK\_aSvYzNH\_QVwhS8fz8vvV1fAJ1wVL8ZXotzi-UmJ9ReuWrTxhdCkSQ)

\2. System start

- start system이 출력되고, do while 문을 통해서 전체 반복문이 돌아간다. 반복문 내에서는 시간을 재기 시작한다. 그 뒤에 0 혹은 다른 숫자를 입력하면, 시간 재는 것을 멈춘다. time이라는 변수에 잰 시간을 대입한다.
- 처음에 oldtime = 0 으로 설정해준다음에, 시간을 잰 뒤, oldtime + 잰 시간(time)을 더한 다음 그만큼 enqueue를 시켰다.
- 그리고 newtime = oldtime + 잰 시간(time)으로 변경시킨다.

\3. 0을 입력한 경우 (if num == 0)

- oldtime부터 newtime까지 enqueue 한 상태를 출력한다.
- A-Z까지 돌기위해서 인덱스의 % 26을 해주었다. 또한 + 65를 통해 아스키코드 값을 나타냈다.
- 출력결과

![텍스트, 영수증이(가) 표시된 사진

자동 생성된 설명](https://lh3.googleusercontent.com/4utDjW2qG37iUAzXKJyprcx8xk-sspxU9NfRPbbsCzwuLboQdfiSp\_4H-P0x\_j2E604jp0pp0w7kgucOO6aLhdE0gMM6lrV1BBi34atGYeJzwpeMDHrXIGNjeQJGYZUlEvJ1qts8)

\3. 0이 아닌 숫자를 입력한 경우 (else)

- oldtime부터 newtime까지 enqueue 한 상태를 출력한다.
- oldindex = queue.front로 초기화시켜준다. 
- dqIndex(dequeue를 할 인덱스) = oldindex로 저장한뒤에, oldindex + num 까지 포문을 돌면서 dequeue를 한다. 
- queue가 비었다면, FAIL 메세지와 함께 for문을 break 한다.

![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh3.googleusercontent.com/21cwttj0T0Qcj2qO8NW3c1i34XEx7osMm0ZdYtLqu3C-t7kyHV2SO0ipxtm1QlZNEJQrAMK4AMh4S4ryrilLj0l15FHFbQ3q3YetWcrN9MJjbUuy6GzL9AWo7WJc4vaBX-cCXsQa)

- printf("DEQUEUE() = %c, F=%d R=%d\n", queue.queueArray[(queue.front+1)%21], (queue.front+1)%21, queue.rear);
- dequeue를 할때는 front 다음값이 dequeue되기 때문에, 출력할 때는 queue.front +1를 해주었다. 또한 A-Z가 순환하면서 queueArray에 저장되기 때문에, 인덱스를 아스키코드르 바꾸지 않고, queueArray의 값을 바로 char로 뽑았다.
- dequeue한 값은 result 라는 배열에 저장하면서, 마지막 다음값에 ‘\0’을 넣어서 string으로 출력했다. 그리고 result[0]에 ‘\0’을 넣고, result의 index = 0으로 초기화를 진행했다.
- 출력결과

![텍스트이(가) 표시된 사진

자동 생성된 설명](https://lh5.googleusercontent.com/8Hg5WosJMYYyE-S0Y5xfVoG4LzLXXRtLILqg4rcTnDDdnX-UFaXF3xb0xu-j4T9zhcALb-B\_BJ\_FNcTg\_8YmeTE2ze-h\_4RgPdQ7SO4t\_YCJ5EHot3-YSHXw0HaOIgusyXxLvt8B)

\4. 상태표시 (큐에 어떤 값이 남아있는지 확인)

- isEmpty가 성립한다면 없다는 것을 나타냈다.
- 그렇지 않을 경우, newI = queue.front + 1로 초기화 해주었다.
- 원형큐이기 때문에, newI%21를 통해서 인덱스가 순환하게 만들었다.
- **while**(isalpha(queue.queueArray[newI%21])) 을 통해 queueArray가 알파벳이면 출력하게 만들었다.
- 하지만 큐의 enqueue, dequeue 모두 인덱스가 변경되고, isFull의 경우, front 와 rear가 같은 위치일 경우, true를 반환하기 때문에, 사실 queueArray에 모두 알파벳이 들어 있는 경우가 한바퀴를 다돌면서부터 생긴다.
- 따라서 무한루프를 방지하기 위해,  queue.queueArray[queue.rear+1] = '!'; 를 통해서, 출력하면 안되는 인덱스에 알파벳이 아닌 값을 집어넣어서 break를 시켜주었다. 















