﻿**2021자료구조**

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