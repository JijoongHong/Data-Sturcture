# 3. 큐 운영하기

## 1. 에러표시 

- 입력큐를는 20 글자를 갖고, 초과하면 ERROR 표시를 갖기 위해 MAX\_NUM을 21로 만들고, queue 함수에서 20이 넘어갈 경우, ERROR를 표시하게 만들었다.
- 출력결과
-  ![image](https://user-images.githubusercontent.com/63644587/116431467-c9376e00-a882-11eb-97bb-afc568de7cec.png)


## 2. System start

- start system이 출력되고, do while 문을 통해서 전체 반복문이 돌아간다. 반복문 내에서는 시간을 재기 시작한다. 그 뒤에 0 혹은 다른 숫자를 입력하면, 시간 재는 것을 멈춘다. time이라는 변수에 잰 시간을 대입한다.
- 처음에 oldtime = 0 으로 설정해준다음에, 시간을 잰 뒤, oldtime + 잰 시간(time)을 더한 다음 그만큼 enqueue를 시켰다.
- 그리고 newtime = oldtime + 잰 시간(time)으로 변경시킨다.


## 3. 0을 입력한 경우 (if num == 0)

- oldtime부터 newtime까지 enqueue 한 상태를 출력한다.
- A-Z까지 돌기위해서 인덱스의 % 26을 해주었다. 또한 + 65를 통해 아스키코드 값을 나타냈다.
- 출력결과
-  ![image](https://user-images.githubusercontent.com/63644587/116431504-cf2d4f00-a882-11eb-9bee-480a923b94dc.png)


## 4. 0이 아닌 숫자를 입력한 경우 (else)

- oldtime부터 newtime까지 enqueue 한 상태를 출력한다.
- oldindex = queue.front로 초기화시켜준다. 
- dqIndex(dequeue를 할 인덱스) = oldindex로 저장한뒤에, oldindex + num 까지 포문을 돌면서 dequeue를 한다. 
- queue가 비었다면, FAIL 메세지와 함께 for문을 break 한다.

-  ![image](https://user-images.githubusercontent.com/63644587/116431528-d3f20300-a882-11eb-818d-fdd654316cd2.png)

- printf("DEQUEUE() = %c, F=%d R=%d\n", queue.queueArray[(queue.front+1)%21], (queue.front+1)%21, queue.rear);
- dequeue를 할때는 front 다음값이 dequeue되기 때문에, 출력할 때는 queue.front +1를 해주었다. 또한 A-Z가 순환하면서 queueArray에 저장되기 때문에, 인덱스를 아스키코드르 바꾸지 않고, queueArray의 값을 바로 char로 뽑았다.
- dequeue한 값은 result 라는 배열에 저장하면서, 마지막 다음값에 ‘\0’을 넣어서 string으로 출력했다. 그리고 result[0]에 ‘\0’을 넣고, result의 index = 0으로 초기화를 진행했다.
- 출력결과
- ![image](https://user-images.githubusercontent.com/63644587/116431540-d8b6b700-a882-11eb-977f-414a737827b5.png)


## 5. 상태표시 (큐에 어떤 값이 남아있는지 확인)

- isEmpty가 성립한다면 없다는 것을 나타냈다.
- 그렇지 않을 경우, newI = queue.front + 1로 초기화 해주었다.
- 원형큐이기 때문에, newI%21를 통해서 인덱스가 순환하게 만들었다.
- **while**(isalpha(queue.queueArray[newI%21])) 을 통해 queueArray가 알파벳이면 출력하게 만들었다.
- 하지만 큐의 enqueue, dequeue 모두 인덱스가 변경되고, isFull의 경우, front 와 rear가 같은 위치일 경우, true를 반환하기 때문에, 사실 queueArray에 모두 알파벳이 들어 있는 경우가 한바퀴를 다돌면서부터 생긴다.
- 따라서 무한루프를 방지하기 위해,  queue.queueArray[queue.rear+1] = '!'; 를 통해서, 출력하면 안되는 인덱스에 알파벳이 아닌 값을 집어넣어서 break를 시켜주었다. 















