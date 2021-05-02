class Node :
    def __init__(self, word, meaning, next = None):
        self.word = word
        self.meaning = meaning
        self.next = next

class Dictionary:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def getNode(self, pos):
        if pos < 0 :
            return None

        node = self.head

        while pos > 0 and node is not None:
            node = node.next
            pos -= 1

        return node

    def insert(self, pos, word, meaning):
        before = self.getNode(pos-1) #이전 노드의 위치 확인
        if before is None:
            self.head = Node(word, meaning, self.head) # 맨앞에 추가, 새로 추가한 노드가 현재 맨 앞 노드의 위치를 가리키도록 하는 한편
            # 헤드가 새로 추가한 노드를 가리키도록 한다

            if pos == self.size: # 맨 처음에 추가한 경우 tail 지정
                self.tail = self.head

        else :
            node = Node(word, meaning, before.next) # 새로 추가한 노드가 다음 노드의 위치를 가리키도록 한다
            before.next = node # 이전 노드의위치를 새로 추가한 노드를 가리키도록 한다

            if pos == self.size: # 맨 마지막에 추가한 경우 tail 지정
                self.tail = node

        self.size += 1


    def insert_new(self, pos, idx, word, meaning): # 완성된 전체 사전 추가 함수
        before = idx.getNode(pos-1) # 이전 노드의 위치 확인
        if before is None:
            idx.head = Node(word, meaning, idx.head) # 맨앞에 추가, 새로 추가한 노드가 현재 맨 앞 노드의 위치를 가리키도록 하는 한편
            # 헤드가 새로 추가한 노드를 가리키도록 한다

            if pos == idx.size: # 맨 처음 추가한경우 tail 지정
                idx.tail = idx.head

        else :
            node = Node(word, meaning, before.next) # 새로 추가한 노드가 다음 노드의 위치를 가리키도록 한다
            before.next = node # 이전 노드의위치를 새로 추가한 노드를 가리키도록 한다
            print(before.word, node.word)
            if pos == idx.size: # 맨 마지막에 추가한 경우 tail지정
                idx.tail = node
        idx.size += 1
        self.size += 1


    def whereToInsert(self, word):
        node = self.head
        pos = 0
        #print(node)
        print(self.size)
        for i in range(self.size):

            #print(node.word)
            if word.lower() < node.word: # 중간에 끼워놓을 곳 찾았을 때
                print(word.lower() < node.word)
                print(word.lower(), node.word)
                return pos # 추가해야할 노드 위치 반환

            node = node.next
            pos += 1

        return pos # 맨 마지막에 추가해야할 때 마지막 노드 위치 반환


    def concat(self, list): # 분할된 연결리스트 병합
        if self.head is None: # 앞 리스트가 비었으면 이후 리스트를 가리키도록 함
            self.head = list.head
        elif list.head is None: # 뒤 리스트가 비었으면 넘어감
            pass
        else:
            self.tail.next = list.head # 정상적인 경우 앞 리스트의 마지막 노드가 이후 리스트의 첫번째를 가키리도록 함


    def search(self, target):
        node = self.head
        for i in range(self.size): # 선형으로 탐색
            if node.word == target: # 타겟을 찾은 경우
                print(node.word, node.meaning)
                return node.meaning # 단어의 의미 반환
            node = node.next

        return None # 찾는 단어가 없는 경우


    def display(self):
        node = self.head
        for i in range(self.size): #처음부터 끝까지 순회하며 단어 출력
            print(node.word, end="->")
            node = node.next
        print()



def main():

    # --------------------- 사전 초기화 ----------------------#

    index = {}

    for i in range(26): # a ~ z 로 시작하는 단어를 담는 사전 클래스 26개 선언
        temp = Dictionary()
        index[i] = temp

    #print(index)
    data = open("/Users/jijoonghong/Downloads/randdict_utf8.TXT")
    i = 1
    while True:

        line = data.readline()
        if not line: break
        word, meaning = line.split(" : ")

        idx = ord(word[0].lower()) - 97 # 단어의 첫글자의 아스키코드를 연산하여 a~z를 0~25로 변환

        print(i, word, meaning)
        pos = index[idx].whereToInsert(word) # 해당 단어가 들어갈 위치 확인
        index[idx].insert(pos, word, meaning) # 해당 위치에 삽입
        i+=1

    data.close()

    #--------------------- 사전 초기화 완료 --------------------#

    #----------------- 분할된 리스트 하나로 연결 ------------------#
    print("1")

    size = 0
    for i in range(25):
        index[i].concat(index[i+1]) # 앞의 tail과 뒤의 head 연결
        print(index[i].tail.word, index[i].tail.next.word)
        size += index[i].size # 전체 사이즈 최신화
    size += index[25].size

    print("2")
    dict = Dictionary() # 전체 사전 클래스 생성
    dict.head = index[0].head # a 사전의 head를 head로 지정
    dict.head = index[25].tail # z 사전의 tail을 tail로 지정
    dict.size = size # 전체 사이즈 지정
    print("3")

    index[17].display()

    #------------------------ 연결 완료 ------------------------#

    #---------------------- 탐색 및 추가 ------------------------#

    while True:
        print("검색할 단어를 입력하세요. 종료하려면 -1입력")
        target = input()
        if target == "-1":
            break

        idx = ord(target[0].lower()) - 97 # 찾고자 하는 단어의 시작 글자 찾기
        print(idx)
        result = index[idx].search(target) # 시작 글자에서부터 찾기
        print(result)

        if result is None: # 단어가 없으면 추가
            print("찾을 수 없는 단어입니다. 뜻을 추가하세요(추가하지 않으려면 공백)")
            new_meaning = input()
            if new_meaning != "":
                #idx = ord(target[0].lower()) - 97
                pos = index[idx].whereToInsert(target) # 들어갈 위치 확인
                print(target, idx, pos)
                dict.insert_new(pos, index[idx], target, new_meaning) # 전체 사전에 대해서 추가
                print(target, new_meaning, "이(가) 추가되었습니다. (총 %d개 단어)"%dict.size)
                index[idx].display()

        else: # 찾는 단어가 있으면 뜻 출력
            print(result)



if __name__ == "__main__":
    main()

