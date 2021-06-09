import random
import time

class Node:
    def __init__(self, word, meaning):
        self.word = word # 단어
        self.meaning = meaning # 뜻
        self.left = None # 좌측 링크
        self.right = None # 우측 링크


class BinarySearchTree:
    def __init__(self): # 생성자
        self.root = None # 루트노드

    def search(self, word, level): # 단어 탐색을 위해 루트 노드인지 확인
        if self.root is None:
            return None, 0
        else:
            return self.__search_node(self.root, word, level)

    def __search_node(self, cur, word, level): # 노드 탐색
        if cur is None:
            return None, 0
        if cur.word == word:
            return cur.meaning, level
        else:
            if cur.word >= word:
                level += 1
                return self.__search_node(cur.left, word, level)
            else:
                level += 1
                return self.__search_node(cur.right, word, level)
        return None,0

    def insert(self, word, meaning): # 노드 삽입을 위해 루트 노드인지 확인
        if self.root is None:
            self.root = Node(word, meaning)

        else:
            self.__insert_node(self.root, word, meaning)

    def __insert_node(self, cur, word, meaning): # 노드 삽입
        if cur.word >= word:
            if cur.left is not None:
                self.__insert_node(cur.left, word, meaning)
            else:
                cur.left = Node(word, meaning)
        else:
            if cur.right is not None:
                self.__insert_node(cur.right, word, meaning)
            else:
                cur.right = Node(word, meaning)

    def count_node(self, node): # 노드 개수 계산
        if node is None:
            return 0
        else:
            return 1 + self.count_node(node.left) + self.count_node(node.right)

    def cal_height(self, node): # 트리 높이 계산
        if node is None:
            return 0
        else:
            return 1 + max(self.cal_height(node.left), self.cal_height(node.right))


def init_btree(b, lines): # 중앙값 추출하여 트리 삽입
    if len(lines) == 0: # 재귀 탈출 조건
        return

    pivot = (len(lines)//2) # 중앙값 인덱스
    word, meaning = lines[pivot].split(" : ") # 단어와 뜻 분리
    b.insert(word, meaning) # 트리에 추가
    init_btree(b, lines[:pivot]) # 좌측 재귀 호출
    init_btree(b, lines[pivot+1:]) # 우측 재귀 호출


def main():
    # A트리 생성
    a = BinarySearchTree()
    data = open("./randdict_utf8.TXT")
    print("사전 파일을 읽는 중입니다.")
    s1 = time.time()
    while True: # 한줄씩 읽어와 트리에 추가
        line = data.readline()
        if not line:
            break
        word, meaning = line.split(" : ") # 단어와 뜻 분리
        a.insert(word, meaning)
    s2 = time.time()
    count = a.count_node(a.root) # 노드의 개수

    print("사전 파일을 모두 읽었습니다. {0}개의 단어가 있습니다. 소요시간: {1}".format(count, s2-s1))
    print("A트리의 전체 높이는 {0}입니다.".format(a.cal_height(a.root)))

    # 랜덤 단어 10개 추출 및 탐색
    data = open("./randdict_utf8.TXT")
    lines = data.readlines()
    random_words = [lines[random.randint(0, count-1)].split(" : ")[0] for _ in range(10)]

    print("\n랜덤하게 선택된 단어 10개 : ", random_words)
    s1 = time.time()
    for word in random_words:
        meaning = a.search(word, 0)
        print(word, meaning[0][:-1], "(레벨%d)" % meaning[1])
    s2 = time.time()
    print("10개 단어 탐색 소요 시간 :", s2-s1)

    # B트리 생성
    b = BinarySearchTree()
    data = open("./randdict_utf8.TXT")
    print("\n\n사전 파일을 읽는 중입니다.")
    s1 = time.time()
    lines = sorted(data.readlines())
    init_btree(b, lines)
    s2 = time.time()
    data.close()

    # 추출된 랜덤 단어 10개 탐색
    print("사전 파일을 모두 읽었습니다. {0}개의 단어가 있습니다. 소요시간: {1}".format(b.count_node(b.root), s2-s1))
    print("B트리의 전체 높이는 {0}입니다.".format(b.cal_height(b.root)))
    print("\n랜덤하게 선택된 단어 10개 : ", random_words)
    s1 = time.time()
    for word in random_words:
        meaning = b.search(word, 0)
        print(word, meaning[0][:-1], "(레벨%d)" % meaning[1])
    s2 = time.time()
    print("10개 단어 탐색 소요 시간 :", s2 - s1)


if __name__ == "__main__":
    main()
