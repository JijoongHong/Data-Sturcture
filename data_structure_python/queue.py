MAX_SIZE = 10

class Queue:
    def __init__(self):
        self.front = 0
        self.rear = 0
        self.items = [None] * MAX_SIZE

    def isEmpty(self):
        return self.front == self.rear

    def isFull(self):
        return self.front == (self.rear + 1)%MAX_SIZE

    def clear(self):
        self.front = self.rear

    def enqueue(self, item):
        if not self.isFull():
            self.rear = (self.rear + 1) % MAX_SIZE
            self.rear = item
        else :
            print("큐가 찼")

    def dequeue(self):
        if not self.isEmpty():
            self.front = (self.front+1) % MAX_SIZE

            return self.items[self.front]
        else :
            print("큐가 비었음")

    def peek(self):
        if not self.isEmpty():
            return self.items[(self.front + 1) % MAX_SIZE]


class Queue2:
    def __init__(self):
        self.front = 0
        self.rear = 0
        self.items = [None] * MAX_SIZE
        self.flag = False

    def isEmpty(self):
        return self.flag == False and self.front == self.rear

    def isFull(self):
        return self.flag == True and self.front == (self.rear +1)% MAX_SIZE

    def clear(self):
        self.front = self.rear

    def enqueue(self, item):
        if not self.isFull():
            self.rear = item
            self.rear = (self.rear+1) % MAX_SIZE
            self.flag = True
        else :
            print("큐가 찼")

    def dequeue(self):
        if not self.isEmpty():
            temp = self.front
            self.front = (self.front+1) % MAX_SIZE
            self.flag = False
            return self.items[temp]
        else :
            print("큐가 비었음")

    def peek(self):
        if not self.isEmpty():
            return self.items[(self.front + 1) % MAX_SIZE]


class Deque:
    def __init__(self):
        self.front = 0
        self.rear = 0
        self.data = [None] * MAX_SIZE

    def isEmpty(self):
        return self.front == self.rear

    def isFull(self):
        return self.front == (self.rear + 1)%MAX_SIZE

    def clear(self):
        self.front = self.rear

    def add_rear(self, item):
        if not self.isFull():
            self.rear = (self.rear + 1) % MAX_SIZE
            self.rear = item
        else :
            print("큐가 찼")

    def add_front(self, item):
        if not self.isFull():
            self.data[self.front] = item
            self.front = (self.front -1) % MAX_SIZE


    def delete_front(self):
        if not self.isEmpty():
            self.front = (self.front+1) % MAX_SIZE

            return self.items[self.front]
        else :
            print("큐가 비었음")


    def delete_rear(self):
        if not self.isEmpty():
            temp = self.rear
            self.rear = (self.rear -1) % MAX_SIZE

            return self.items[temp]
        else :
            print("큐가 비었음")

    def get_front(self):
        if not self.isEmpty():
            return self.items[(self.front+1) % MAX_SIZE]
        else :
            print("큐가 비었음")


    def get_rear(self):
        if not self.isEmpty():
            return self.items[self.rear]
        else :
            print("큐가 비었음")