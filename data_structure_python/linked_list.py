class Node :
    def __init__(self, data, next = None):
        self.data = data
        self.next = next

class LinkedList:
    def __init__(self):
        self.head = None

    def getNode(self, pos):
        if pos < 0 :
            return None

        node = self.head

        while pos > 0 and node != None:
            node = node.next
            pos -= 1

        return node

    def insert(self, pos, element):
        before = self.getNode(pos-1) #이전 노드의 위치 확인
        if before == None:
            self.head = Node(element, self.head) # 맨앞에 추가, 새로 추가한 노드가 현재 맨 앞 노드의 위치를 가리키도록 하는 한편
            # 헤드가 새로 추가한 노드를 가리키도록 한다
        else :
            node = Node(element, before.next) # 새로 추가한 노드가 다음 노드의 위치를 가리키도록 한다
            before.next = node # 이전 노드의위치를 새로 추가한 노드를 가리키도록 한다

    def delete(self, pos):
        before = self.getNode(pos - 1) # 이전 노드의 위치 확인
        if before is None: # 맨 앞을 지우려면
            removed = self.head # 현재 맨 앞 노드를 임시 변수에 옮긴다
            self.head = self.head.next # 헤드가 헤드의 다음을 가리키도록 한다
            # 둘의 순서를 바꾸면 안된다. 헤드를 다음걸로 설정해주고 지워버리면 자료의 손실이 일어나기 때문이다.
        else :#중간이나 마지막 것을 지우려면
            removed = before.next #지정 위치를 임시 변수에 옮긴다
            before.next = before.next.next #이전 노드가 이전노드의 다음다음, 즉 지정 위치의 다음을 가리키도록 한다.

        del removed #확인사살

    def display(self):
        node = self.head
        while node is not None:
            print(node.data, end="->")
            node = node.next
        print()

l = LinkedList()
l.insert(0,10)
l.insert(0,20)
l.insert(1,30)
l.display()