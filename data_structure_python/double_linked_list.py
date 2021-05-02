import random
import string


class Node:
    def __init__(self, id, name, phone, next=None):
        self.id = id
        self.name = name
        self.phone = phone
        self.next_id = next
        self.next_name = next


class Student:
    def __init__(self):
        self.head_id = None
        self.head_name = None
        self.size = 0


    def getNodeId(self, pos):
        if pos < 0:
            return None

        node = self.head_id

        while pos > 0 and node is not None:
            node = node.next_id
            pos -= 1

        return node


    def getNodeName(self, pos):
        if pos < 0:
            return None

        node = self.head_name

        while pos > 0 and node is not None:
            node = node.next_name
            pos -= 1

        return node


    def insert_id(self, pos, student_id, name, phone):
        before = self.getNodeId(pos - 1)  # 이전 노드의 위치 확인
        if before is None:
            node = Node(student_id, name, phone, self.head_id)  # 맨앞에 추가, 새로 추가한 노드가 현재 맨 앞 노드의 위치를 가리키도록 하는 한편
            self.head_id = node
            # 헤드가 새로 추가한 노드를 가리키도록 한다


        else:
            node = Node(student_id, name, phone, before.next_id)  # 새로 추가한 노드가 다음 노드의 위치를 가리키도록 한다
            before.next_id = node  # 이전 노드의위치를 새로 추가한 노드를 가리키도록 한다

        self.size += 1

        return node


    def insert_name(self, pos, Node):
        before = self.getNodeName(pos - 1)  # 이전 노드의 위치 확인

        if before is None:
            Node.next_name = self.head_name
            self.head_name = Node  # 맨앞에 추가, 새로 추가한 노드가 현재 맨 앞 노드의 위치를 가리키도록 하는 한편
            # 헤드가 새로 추가한 노드를 가리키도록 한다

        else:
            Node.next_name = before.next_name  # 새로 추가한 노드가 다음 노드의 위치를 가리키도록 한다
            before.next_name = Node  # 이전 노드의위치를 새로 추가한 노드를 가리키도록 한다


    def whereToInsertId(self, id):
        node = self.head_id
        pos = 0
        # print(node)
        # print(self.size)
        while node is not None:

            if id < node.id:  # 중간에 끼워놓을 곳 찾았을 때
                return pos  # 추가해야할 노드 위치 반환

            node = node.next_id
            pos += 1

        return pos  # 맨 마지막에 추가해야할 때 마지막 노드 위치 반환

    def whereToInsertName(self, name):
        node = self.head_name
        pos = 0

        while node is not None:
            if name < node.name:  # 중간에 끼워놓을 곳 찾았을 때
                return pos  # 추가해야할 노드 위치 반환

            node = node.next_name
            pos += 1

        return pos  # 맨 마지막에 추가해야할 때 마지막 노드 위치 반환

    def display_id(self):
        node = self.head_id

        for i in range(self.size):  # 처음부터 끝까지 순회하며 단어 출력
            if (i + 1) % 100 == 1:
                print(i + 1, ":", node.id, node.name, node.phone)
            node = node.next_id
            i += 1
        print()

    def display_name(self):
        node = self.head_name
        for i in range(self.size):  # 처음부터 끝까지 순회하며 단어 출력
            if (i + 1) % 100 == 1:
                print(i + 1, ":", node.id, node.name, node.phone)
            node = node.next_name
        print()


def generate_data(student_data):
    print("# ------------Generate a new dataset------------ #")
    student_id_list = random.sample(range(20130000, 20200000), 10000)  # 학번 무작위 생성

    for id in student_id_list:  # 데이터 생성 상태 출력
        if student_id_list.index(id) == 0:
            print("0%")
        elif student_id_list.index(id) == 2499:
            print("25%")
        elif student_id_list.index(id) == 4999:
            print("50%")
        elif student_id_list.index(id) == 7499:
            print("75%")
        elif student_id_list.index(id) == 9999:
            print("100%")

        student_id = str(id)  # 학번 지정
        name = "".join([random.choice(string.ascii_lowercase) for _ in range(10)])  # 이름지정
        phone_number = "010" + "".join([str(random.randint(0, 9)) for _ in range(8)])  # 번호지정

        pos = student_data.whereToInsertId(student_id)  # 학번 기준으로 삽입할 곳 탐색
        new_node = student_data.insert_id(pos, student_id, name, phone_number)  # 삽입 후 추가한 노드 정보 저장
        pos = student_data.whereToInsertName(name)  # 이름 기준으로 삽입할 곳 탐색
        student_data.insert_name(pos, new_node)  # 이미 생성된 노드를 이름순으로 정렬되도 삽입

    print("# ------------Dataset is created and sorted------------ #")


def main():
    student_data = Student()
    generate_data(student_data)

    while True:
        print("(1) 학번순")
        print("(2) 이름순")
        print("메뉴선택(종료:0) :", end=" ")
        mode = input()

        if mode == "1":
            student_data.display_id()  # 학번순 출력
        elif mode == "2":
            student_data.display_name()  # 이름순 출력
        elif mode == "0":
            break  # 종료
        else:
            print("잘못된 입력입니다. 다시 입력하세요")  # 입력이 잘못된 경우 다시 실


if __name__ == "__main__":
    main()
