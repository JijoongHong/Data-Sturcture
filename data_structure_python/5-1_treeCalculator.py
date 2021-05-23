MAX_SIZE = 100

class Queue:
    def __init__(self):
        self.front = 0
        self.rear = 0
        self.items = [None] * MAX_SIZE
        self.flag = False

    def isEmpty(self):
        return self.flag == False and self.front == self.rear

    def isFull(self):
        return self.flag == True and self.front == (self.rear + 1) % MAX_SIZE

    def clear(self):
        self.front = self.rear

    def enqueue(self, item):
        if not self.isFull():
            self.items[self.rear] = item
            self.rear = (self.rear + 1) % MAX_SIZE
            self.flag = True
        else:
            print("큐가 찼음")

    def dequeue(self):
        if not self.isEmpty():
            temp = self.items[self.front]
            self.front = (self.front + 1) % MAX_SIZE
            self.flag = False
            return temp
        else:
            print("큐가 비었음")

    def peek(self):
        if not self.isEmpty():
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

    def preorder(self, node):
        if node is not None:
            print(node.item, end="")
            self.preorder(node.left)
            self.preorder(node.right)

    def inorder(self, node):
        if node is not None:
            self.inorder(node.left)
            print(node.item, end="")
            self.inorder(node.right)

    def postorder(self,node):
        if node is not None:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.item, end="")

    def level(self, root):
        q = Queue()
        q.enqueue(root)
        while not q.isEmpty():
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
    if ch == '*' or '/':
        return 0
    elif ch == '+' or '-':
        return 1
    else:
        return 2


def postfix(exp):
    stack = []
    result = []
    for i in range(len(exp)):
        if exp[i].isdigit() is True:
            result.append(exp[i])
        else:
            if len(stack) != 0 and get_priority(stack[-1]) < get_priority(exp[i]):
                while get_priority(stack[-1]) < get_priority(exp[i]):
                    result.append(stack.pop())
            else:
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

    print("전위순회 : ", end = "")
    tree.preorder(tree.root)
    print("\n중위순회 : ", end = "")
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

