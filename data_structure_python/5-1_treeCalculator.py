MAX_SIZE = 100


class Queue:
    def __init__(self):
        self.front = 0
        self.rear = 0
        self.items = [None] * MAX_SIZE
        self.flag = False

    def is_empty(self):
        return self.flag is False and self.front == self.rear

    def is_full(self):
        return self.flag is True and self.front == (self.rear + 1) % MAX_SIZE

    def clear(self):
        self.front = self.rear

    def enqueue(self, item):
        if not self.is_full():
            self.items[self.rear] = item
            self.rear = (self.rear + 1) % MAX_SIZE
            self.flag = True
        else:
            print("큐가 찼음")

    def dequeue(self):
        if not self.is_empty():
            temp = self.items[self.front]
            self.front = (self.front + 1) % MAX_SIZE
            self.flag = False
            return temp
        else:
            print("큐가 비었음")

    def peek(self):
        if not self.is_empty():
            return self.items[(self.front + 1) % MAX_SIZE]


class Node:
    def __init__(self, item, left=None, right=None):
        self.item = item
        self.left = left
        self.right = right


class Tree:
    def __init__(self):
        self.root = None

    def init_tree(self, exp):
        stack = []
        for i in range(len(exp)):
            if exp[i].isdigit() is True:
                stack.append(Node(int(exp[i])))
            else:
                temp = Node(exp[i])
                temp.right = stack.pop()
                temp.left = stack.pop()
                stack.append(temp)
        self.root = stack.pop()

    def preorder(self, root):
        if root is not None:
            print(root.item, end="")
            self.preorder(root.left)
            self.preorder(root.right)

    def inorder(self, root):
        if root is not None:
            self.inorder(root.left)
            print(root.item, end="")
            self.inorder(root.right)

    def postorder(self, root):
        if root is not None:
            self.postorder(root.left)
            self.postorder(root.right)
            print(root.item, end="")

    def level(self, root):
        q = Queue()
        q.enqueue(root)
        while not q.is_empty():
            n = q.dequeue()
            if n is not None:
                print(n.item, end="")
                q.enqueue(n.left)
                q.enqueue(n.right)

    def evaluate(self, root):
        if root is None:
            return 0
        if root.left is None and root.right is None:
            return root.item
        else:
            op1 = self.evaluate(root.left)
            op2 = self.evaluate(root.right)

            if root.item == '+':
                return op1 + op2
            elif root.item == '-':
                return op1 - op2
            elif root.item == '*':
                return op1 * op2
            elif root.item == '/':
                return op1 / op2


def get_priority(ch):
    if ch == '*' or ch == '/':
        return 0
    elif ch == '+' or ch == '-':
        return 1
    else:
        return 2


# 8/4-5+2*3-1*5


def postfix(exp):
    stack = []
    result = []
    for i in range(len(exp)):
        if exp[i].isdigit() is True:
            result.append(exp[i])
        else:
            while len(stack) != 0 and (get_priority(stack[-1]) <= get_priority(exp[i])):
                result.append(stack.pop())
            stack.append(exp[i])

    while len(stack) != 0:
        result.append(stack.pop())
    return result


'''
def postfix(exp):
    stack = []
    result = []
    for i in range(len(exp)):
        if exp[i].isdigit() is True:
            result.append(Node(exp[i]))
        else:
            if len(stack) != 0 and get_priority(stack[-1].item) < get_priority(exp[i]):
                temp = Node(exp[i])
                temp.right = stack.pop()
                temp.left = stack.pop()
                stack.append(temp)

            else:
                stack.append(Node(exp[i]))

    while len(stack) != 0:
        result.append(stack.pop())

    return result
'''


def main():
    print("수식을 입력하세요 : ", end="")
    exp = "".join(list(postfix(input())))
    tree = Tree()
    tree.init_tree(exp)

    print("전위순회 : ", end="")
    tree.preorder(tree.root)
    print("\n중위순회 : ", end="")
    tree.inorder(tree.root)
    print("\n후위순회 : ", end="")
    tree.postorder(tree.root)
    print("\n레벨순회 : ", end="")
    tree.level(tree.root)
    print("\n계산결과 : ", end="")
    result = tree.evaluate(tree.root)
    print(result)


if __name__ == "__main__":
    main()
