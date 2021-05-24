import random
import time
class Node:
    def __init__(self, word, meaning):
        self.word = word
        self.meaning = meaning
        self.left = None
        self.right = None


class BinaryTree:
    def __init__(self):
        self.head = None

    def search(self, word, level):
        if self.head.word is None:
            return None, 0
        else:
            return self.__search_node(self.head, word, level)

    def __search_node(self, cur, word, level):
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
        return None

    def insert(self, word, meaning):
        if self.head is None:
            self.head = Node(word, meaning)

        else:
            self.__insert_node(self.head, word, meaning)

    def __insert_node(self, cur, word, meaning):
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

    def count_node(self, node):
        if node is None:
            return 0
        else:
            return 1 + self.count_node(node.left) + self.count_node(node.right)

    def cal_height(self, node):
        if node is None:
            return 0
        else:
            return 1 + max(self.cal_height(node.left), self.cal_height(node.right))

    def rotateLL(self, node):
        new = node.left
        node.left = new.right
        new.right = node
        return new

    def rotateRR(self, node):
        new = node.right
        node.right = new.left
        new.left = node
        return new

    def rotateRL(self, node):
        new = node.right
        node.right = self.rotateLL(new)
        return self.rotateRR(node)

    def rotateLR(self, node):
        new = node.left
        node.left = self.rotateRR(new)
        return self.rotateLL(node)

    def cal_height_diff(self, node):
        if node is None:
            return 0
        else:
            return self.cal_height(node.left) - self.cal_height(node.right)

    def rebalance(self, node):

        height_diff = self.cal_height_diff(node)

        if height_diff > 1:
            if self.cal_height_diff(node.left) > 0:
                node = self.rotateLL(node)
            else:
                node = self.rotateLR(node)
        elif height_diff < -1:
            if self.cal_height_diff(node.right) < 0:
                node = self.rotateRR(node)
            else:
                node = self.rotateRL(node)

        return node

    def insert_avl(self, word, meaning):
        if self.head is None:
            self.head = Node(word, meaning)
        else:
            self.head = self.__insert_node_avl(self.head, word, meaning)

        return self.head

    def __insert_node_avl(self, cur, word, meaning):
        if cur.word >= word:
            if cur.left is not None:
                cur.left = self.__insert_node_avl(cur.left, word, meaning)
            else:
                cur.left = Node(word, meaning)
            return self.rebalance(cur)

        else:
            if cur.right is not None:
                cur.right = self.__insert_node_avl(cur.right, word, meaning)
            else:
                cur.right = Node(word, meaning)

            return self.rebalance(cur)



def main():

    a = BinaryTree()
    data = open("./r.TXT")
    print("사전 파일을 읽는 중입니다.")
    s1 = time.time()
    while True:
        line = data.readline()
        if not line:
            break
        word, meaning = line.split(" : ") # 단어와 뜻 분리
        a.insert(word, meaning)
    s2 = time.time()
    count = a.count_node(a.head)

    print("사전 파일을 모두 읽었습니다. {0}개의 단어가 있습니다. 소요시간: {1}".format(count, s2-s1))
    print("A트리의 전체 높이는 {0}입니다.".format(a.cal_height(a.head)))

    data = open("./randdict_utf8.TXT")
    lines = data.readlines()
    random_words = [lines[random.randint(0, count-1)].split(" : ")[0] for i in range(10)]

    print("\n랜덤하게 선택된 단어 10개 : ", random_words)
    s1 = time.time()
    for word in random_words:
        meaning = a.search(word, 0)
        print(word, meaning[0][:-1], "(레벨%d)" % meaning[1])
    s2 = time.time()
    print("10개 단어 탐색 소요 시간 :", s2-s1)


    b = BinaryTree()
    data = open("./r.TXT")
    print("\n\n사전 파일을 읽는 중입니다.")
    s1 = time.time()
    while True:
        line = data.readline()
        if not line:
            break
        word, meaning = line.split(" : ") # 단어와 뜻 분리
        b.head = b.insert_avl(word, meaning)
    s2 = time.time()
    data.close()

    print("사전 파일을 모두 읽었습니다. {0}개의 단어가 있습니다. 소요시간: {1}".format(b.count_node(b.head), s2-s1))
    print("B트리의 전체 높이는 {0}입니다.".format(b.cal_height(b.head)))
    print("\n랜덤하게 선택된 단어 10개 : ", random_words)
    s1 = time.time()
    for word in random_words:
        meaning = b.search(word, 0)
        print(word, meaning[0][:-1], "(레벨%d)" % meaning[1])
    s2 = time.time()
    print("10개 단어 탐색 소요 시간 :", s2 - s1)


if __name__ == "__main__":
    main()