class Node:
    def __init__(self, word, meaning, next=None):
        self.word = word # 영단어
        self.meaning = meaning # 단어뜻
        self.next = next # 다음 노드


class Dictionary:
    def __init__(self):
        self.head = None # 맨 앞 노드를 가리키는 변수
        self.tail = None # 맨 뒤 노드를 가리키는 변수
        self.size = 0 # 사전 단어의 갯수

    def get_node(self, pos): # pos번째 노드의 주소 반환
        if pos < 0:
            return None

        node = self.head

        while pos > 0 and node is not None:
            node = node.next
            pos -= 1

        return node

    def insert(self, pos, word, meaning): # 지정 위치에 삽입
        before = self.get_node(pos - 1)  # 이전 노드의 위치 확인
        if before is None:
            self.head = Node(word, meaning, self.head)  # 맨앞에 추가, 새로 추가한 노드가 현재 맨 앞 노드의 위치를 가리키도록 하는 한편
            # 헤드가 새로 추가한 노드를 가리키도록 한다

            if pos == self.size:  # 맨 처음에 추가한 경우 tail 지정
                self.tail = self.head

        else:
            node = Node(word, meaning, before.next)  # 새로 추가한 노드가 다음 노드의 위치를 가리키도록 한다
            before.next = node  # 이전 노드의위치를 새로 추가한 노드를 가리키도록 한다

            if pos == self.size:  # 맨 마지막에 추가한 경우 tail 지정
                self.tail = node

        self.size += 1

    def insert_new(self, pos, idx, word, meaning):  # 완성된 전체 사전에 삽입
        before = idx.get_node(pos - 1)  # 이전 노드의 위치 확인
        if before is None:
            idx.head = Node(word, meaning, idx.head)  # 맨앞에 추가, 새로 추가한 노드가 현재 맨 앞 노드의 위치를 가리키도록 하는 한편
            # 헤드가 새로 추가한 노드를 가리키도록 한다

            if pos == idx.size:  # 맨 처음 추가한경우 tail 지정
                idx.tail = idx.head

        else:
            node = Node(word, meaning, before.next)  # 새로 추가한 노드가 다음 노드의 위치를 가리키도록 한다
            before.next = node  # 이전 노드의위치를 새로 추가한 노드를 가리키도록 한다
            if pos == idx.size:  # 맨 마지막에 추가한 경우 tail지정
                idx.tail = node
        idx.size += 1
        self.size += 1

    def where_to_insert(self, word): # 삽입위치 지정
        count = 0 # 결과 비교를 위해 연산 횟수 카운트

        node = self.head
        pos = 0
        for i in range(self.size):
            count += 1
            if word.lower() < node.word:  # 중간에 끼워놓을 곳 찾았을 때
                return pos, count  # 추가해야할 노드 위치 반환

            node = node.next
            pos += 1

        return pos, count  # 맨 마지막에 추가해야할 때 마지막 노드 위치 반환

    def concat(self, list):  # 분할된 연결리스트 병합
        if self.head is None:  # 앞 리스트가 비었으면 이후 리스트를 가리키도록 함
            self.head = list.head
        elif list.head is None:  # 뒤 리스트가 비었으면 넘어감
            pass
        else:
            self.tail.next = list.head  # 정상적인 경우 앞 리스트의 마지막 노드가 이후 리스트의 첫번째를 가키리도록 함

    def search(self, target): # 리스트에서 해당 단어 탐색
        count = 0 # 결과 비교를 위해 연산 횟수 카운트
        node = self.head
        for i in range(self.size):  # 선형으로 탐색
            count += 1
            if node.word == target:  # 타겟을 찾은 경우
                return node.meaning, count  # 단어의 의미 반환
            node = node.next

        return None, count  # 찾는 단어가 없는 경우

    def display(self): # 리스트의 단어 출력
        node = self.head
        for i in range(self.size):  # 처음부터 끝까지 순회하며 단어 출력
            print(node.word, end="->")
            node = node.next
        print()


def main():
    # 결과 비교용 변수들
    init_count = 0 # 사전 초기화에 들어간 총 비교연산 횟수
    operation_per_word = [] # 사전 초기화 시 개별 단어별 비교연산 횟수
    search_count = {} # 특정 단어 탐색에 대한 비교연산 횟수 예) {apple : 2012}

    # --------------------- 사전 초기화 ----------------------#
    print("# --------------------- 사전 초기화 ----------------------#\n")
    index = {}

    for i in range(26):  # a ~ z 로 시작하는 단어를 담는 사전 클래스 26개 선언
        temp = Dictionary()
        index[i] = temp

    data = open("./randdict_utf8.TXT")

    while True:
        line = data.readline()
        if not line: break
        word, meaning = line.split(" : ") # 단어와 뜻 분리

        if meaning != '': # 뜻이 빈 경우 넘어감
            idx = ord(word[0].lower()) - 97  # 단어의 첫글자의 아스키코드를 연산하여 a~z를 0~25로 변환
            pos = index[idx].where_to_insert(word)  # 해당 단어가 들어갈 위치 확인
            init_count += pos[1]
            operation_per_word.append(pos[1])
            index[idx].insert(pos[0], word, meaning)  # 해당 위치에 삽입

    data.close()

    # --------------------- 사전 초기화 완료 --------------------#

    # ----------------- 분할된 리스트 하나로 연결 ------------------#

    size = 0
    for i in range(25):
        index[i].concat(index[i + 1])  # 앞의 tail과 뒤의 head 연결
        size += index[i].size  # 전체 사이즈 최신화
    size += index[25].size

    eng_dict = Dictionary()  # 전체 사전 클래스 생성
    eng_dict.head = index[0].head  # a 사전의 head를 head로 지정
    eng_dict.head = index[25].tail  # z 사전의 tail을 tail로 지정
    eng_dict.size = size  # 전체 사이즈 지정

    # ------------------------ 연결 완료 ------------------------#

    # ---------------------- 탐색 및 추가 ------------------------#

    while True:
        print("검색할 단어를 입력하세요. 종료하려면 -1입력")
        target = input()
        if target == "-1":
            break

        idx = ord(target[0].lower()) - 97  # 찾고자 하는 단어의 시작 글자 찾기
        result = index[idx].search(target)  # 시작 글자에서부터 찾기
        search_count[target] = result[1]

        if result[0] is None:  # 단어가 없으면 추가
            print("찾을 수 없는 단어입니다. 뜻을 추가하세요(추가하지 않으려면 공백)")
            new_meaning = input()
            if new_meaning != '':
                pos = index[idx].where_to_insert(target)  # 들어갈 위치 확인
                eng_dict.insert_new(pos[0], index[idx], target, new_meaning)  # 전체 사전에 대해서 추가
                print(target, new_meaning, "이(가) 추가되었습니다. (총 %d개 단어)" % eng_dict.size)

        else:  # 찾는 단어가 있으면 뜻 출력
            print(result[0])

    return init_count, search_count, operation_per_word


def normal_list():
    # 결과 비교용 변수들
    init_count2 = 0 # 사전 초기화에 들어간 총 비교연산 횟수
    operation_per_word2 = [] # 사전 초기화 시 개별 단어별 비교연산 횟수
    search_count2 = {} # 특정 단어 탐색에 대한 비교연산 횟수 예) {apple : 2012}

    # --------------------- 사전 초기화 ----------------------#
    print("# --------------------- 사전 초기화(개선 전) ----------------------#\n")
    data = open("./randdict_utf8.TXT")

    eng_dict2 = Dictionary()

    while True:

        line = data.readline()
        if not line: break
        word, meaning = line.split(" : ") # 단어와 뜻 분리

        if meaning != '': # 뜻이 빈 경우 넘어감
            pos = eng_dict2.where_to_insert(word)  # 해당 단어가 들어갈 위치 확인
            init_count2 += pos[1]
            operation_per_word2.append(pos[1])
            eng_dict2.insert(pos[0], word, meaning)  # 해당 위치에 삽입

    data.close()

    # ---------------------- 탐색 및 추가 ------------------------#
    while True:
        print("검색할 단어를 입력하세요. 종료하려면 -1입력")
        target = input()
        if target == "-1":
            break

        result = eng_dict2.search(target)  # 첫 노드부터 순회하며 탐색
        search_count2[target] = result[1]

        if result[0] is None:  # 단어가 없으면 추가
            print("찾을 수 없는 단어입니다. 뜻을 추가하세요(추가하지 않으려면 공백)")
            new_meaning = input()
            if new_meaning != '':
                pos = eng_dict2.where_to_insert(target)  # 들어갈 위치 확인
                eng_dict2.insert_new(pos[0], eng_dict2, target, new_meaning)  # 전체 사전에 대해서 추가
                print(target, new_meaning, "이(가) 추가되었습니다. (총 %d개 단어)" % eng_dict2.size)

        else:  # 찾는 단어가 있으면 뜻 출력
            print(result[0])

    return init_count2, search_count2, operation_per_word2


def validate_improvement():
    from matplotlib import pyplot as plt
    import numpy as np

    result2 = normal_list() # 개선 전
    result1 = main() # 개선 후

    print("사전 초기화 작업 : 기존 ({0}) | 개선 ({1})".format(format(result2[0], ","), format(result1[0], ",")))
    print("\n단어 검색")
    print("apple  : 기존 ({0}) | 개선({1})".format(result2[1]["apple"], result1[1]["apple"]))
    print("mugger : 기존 ({0}) | 개선({1})".format(result2[1]["mugger"], result1[1]["mugger"]))
    print("zincic : 기존 ({0}) | 개선({1})".format(result2[1]["zincic"], result1[1]["zincic"]))

    normal = result2[2]
    improved = result1[2]

    n_avg = np.mean(normal)  # 평균
    n_med = np.median(normal)  # 중위값
    n_std = np.std(normal)  # 표준편차
    n_max = np.max(normal)  # 최댓값

    i_avg = np.mean(improved)
    i_med = np.median(improved)
    i_std = np.std(improved)
    i_max = np.max(improved)

    print("\n기존  최댓값: {0}, 평균: {1}, 중위값: {2}, 표준편차: {3}".format(n_max, n_avg, n_med, n_std))
    print("개선  최댓값: {0}, 평균: {1}, 중위값: {2}, 표준편차: {3}".format(i_max, i_avg, i_med, i_std))

    fig = plt.figure(figsize=(18,6))
    ax1 = fig.add_subplot(1, 3, 1)
    ax2 = fig.add_subplot(1, 3, 2)
    ax3 = fig.add_subplot(1, 3, 3)

    # 선 그래프
    ax1.plot(normal, label='normal')
    ax1.plot(improved, label='improved')
    ax1.legend(loc='upper left')
    ax1.set_title('Line graph')

    # 바 그래프
    ax2.bar(np.arange(len(normal)), normal, label='normal')
    ax2.bar(np.arange(len(improved)), improved, label='improved')
    ax2.legend(loc='upper left')
    ax2.set_title('Bar graph')

    # 히스토그램
    ax3.hist(normal, alpha=0.8, label=['normal'])
    ax3.hist(improved, alpha=0.8, label=['improved'])
    ax3.legend(loc='upper right')
    ax3.set_title('Histogram')

    plt.show()



if __name__ == "__main__":
    #main()
    validate_improvement() # 비교 test 시 사용 # test 단어는 apple, mugger, zincic로 한정
