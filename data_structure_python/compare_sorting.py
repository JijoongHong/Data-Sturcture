import random
import string
import time
import copy

# -------------------- Stack -------------------- #

class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        try:
            return self.items.pop()
        except IndexError:
            print("Stack is empty")

    def peek(self):
        try:
            return self.items[-1]
        except IndexError:
            print("Stack is empty")

    def top(self):
        return len(self.items)

    def isEmpty(self):
        return self.items.__len__() == 0


# -------------------- Selection sort -------------------- #

def selection_sort(arr):
    for i in range(len(arr) - 1):
        min = i
        for j in range(i + 1, len(arr)):
            if arr[j][1] < arr[min][1]:
                min = j
        arr[i], arr[min] = arr[min], arr[i] #기준값과 기준값보다 작은 것 중 최솟값 swap

    return arr


# -------------------- Heap sort -------------------- #

def adjust(arr, root_idx, max_idx):
    while 2 * root_idx + 1 <= max_idx:  # 자식 노드가 마지막 인덱스 보다 작을 때 까지
        child_idx = 2 * root_idx + 1  # 자식 노드 설정

        if child_idx < max_idx and arr[child_idx][1] < arr[child_idx + 1][1]:  # 자식노드끼리 비교해서 둘 중 큰거를 부모노드와 비교
            child_idx += 1 # 형제가 더 큼

        if arr[root_idx][1] >= arr[child_idx][1]:  # 부모와 자식 노드 비교
            # 부모가 더 큼, while 탈출
            break

        arr[root_idx], arr[child_idx] = arr[child_idx], arr[root_idx]  # 자식이 더 크면 부모와 자식을 바꿈
        root_idx = child_idx  # 부모가 아래로 내려와 힙이 깨졌으므로 자식 노드와 비교해줘야함, 자식 노드를 루트로 설정

    return arr


def heap_sort(arr):
    max_idx = len(arr)-1  # 인덱스가 0부터 시작하기 때문

    # 힙만들기
    for i in reversed(range((max_idx + 1)//2)):  # max_idx//2 은 가장 마지막 부모 노드의 인덱스
        adjust(arr, i, max_idx)

    # 가장 큰 수 빼와서 힙 유지하기
    for i in range(max_idx):
        arr[0], arr[max_idx] = arr[max_idx], arr[0]  # 가장 큰 수와 마지막 요소 위치 변경하여 가장 큰수 pop
        max_idx -= 1  # 가장 큰 수가 빠졌으므로 인덱스 조정
        adjust(arr, 0, max_idx)  # 힙이 깨졌으므로 재구성

    return arr  # 결과 반환


# -------------------- Quick sort -------------------- #

def quick_sort_non_recursive(arr, lo, hi):

    stack = Stack() #스택 선언 및 초기정보 저장
    stack.push(lo)
    stack.push(hi)

    while not stack.isEmpty(): #더이상 분할되지 않을 때 까지

        hi = stack.pop() #리스트와 sub 리스트의 우극단
        lo = stack.pop() #리스트와 sub 리스트의 좌극단

        pivot = partition(arr, lo, hi) #피봇기준으로 분할

        if pivot - 1 > lo: #피봇 좌측 구획 정보 저장
            stack.push(lo)
            stack.push(pivot - 1)

        if pivot + 1 < hi: #피봇 우측 구획 정보 저장
            stack.push(pivot + 1)
            stack.push(hi)


def quick_sort(arr, lo, hi):
    if lo >= hi: #더이상 분할할 수 없을 경우 종료
        return

    pivot = partition(arr, lo, hi) #피봇기준으로 분할
    quick_sort(arr, lo, pivot - 1) #피봇 좌측 구획 정렬
    quick_sort(arr, pivot + 1, hi) #피봇 우측 구획 정렬


def partition(arr, pivot, hi):
    i = pivot + 1
    j = hi
    while True:
        while i < hi and arr[i][1] < arr[pivot][1]:  # 피봇보다 큰거 찾을 때 까지
            i += 1
        while j > pivot and arr[j][1] > arr[pivot][1]:  # 피봇보다 작은거 찾을 때 까지
            j -= 1
        if j <= i:  # 크로스 되면 종료
            break
        arr[i], arr[j] = arr[j], arr[i]  # 큰값과 작은값 위치 변경
        i += 1  # 각자 다음 인덱스로
        j -= 1

    arr[pivot], arr[j] = arr[j], arr[pivot]  # 피봇과 j위치 변경

    return j  # 피봇은 j


# --------------------End of Sorting Area-------------------- #


def generate_data():
    print("# ------------Generate a new dataset------------ #")
    data = []
    student_id_list = random.sample(range(20130000, 20200000), size) # 학번 무작위 생성
    validate_duplication(student_id_list) #중복확인

    for id in student_id_list:
        student_id = str(id) # 학번 지정
        name = "".join([random.choice(string.ascii_lowercase) for _ in range(10)]) # 이름지정
        phone_number = "010" + "".join([str(random.randint(0, 9)) for _ in range(8)]) # 번호지정
        temp = [student_id, name, phone_number] # 한명의 데이터 생성
        data.append(temp) #2차원 리스트에 추가

    return data #결과 반환


def validate_duplication(data):
    if len(set(data)) == size: #set은 요소의 중복이 불가능하므로 중복이 없다면 크기가 size와 동일해야함
        print("\n생성된 학번에 중복이 없습니다.\n")
    else:
        print("\n생성된 학번에 중복이 있습니다.\n")


def validate_order(data):
    for i in range(len(data)-1):
        if data[i] > data[i+1]: #현재와 다음 값 크기 비교
            print("\n이름이 오름차순으로 정렬되지 않았습니다.\n")
            print(i, data[i], data[i+1])
            return #종료

    print("\n이름이 오름차순으로 정렬되었습니다.\n") #for문이 끝까지 돈 경우


if __name__ == "__main__":

    size = 50000 #데이터 사이즈 지정
    data = generate_data() #데이터 생성

    # ------------Built in Sort------------ #
    print("# ------------Built in Sort------------ #")
    builtin_start = time.time() #시작시간
    builtin = sorted(data, key=lambda x: x[1]) #이름이 있는 1열을 기준으로 정렬
    builtin_end = time.time() #종료시간

    sorted_name = list(zip(*builtin))[1] #이름이 있는 1열만 추출
    validate_order(sorted_name) #정렬검증

    for i in range(0,size,1000): #1000개 단위로 출력
        print(i+1, ":", builtin[i])

    print("\n내장함수 소요시간:", builtin_end-builtin_start, "\n")

    # ------------Quick Sort------------ #
    print("# ------------Quick Sort------------ #")
    quick = copy.deepcopy(data) #원본 손상방지를 위해 deep copy
    quick_start = time.time()
    quick_sort(quick,0,len(quick)-1)
    quick_end = time.time()

    sorted_name = list(zip(*quick))[1]
    validate_order(sorted_name)

    for i in range(0,size,1000):
        print(i+1, ":", quick[i])

    print("\n퀵정렬 소요시간:", quick_end-quick_start, "\n")

    # ------------Non-recursive Quick Sort------------ #
    print("# ------------Non-recursive Quick Sort------------ #")
    quick2 = copy.deepcopy(data)
    quick_start2 = time.time()
    quick_sort_non_recursive(quick2,0,len(quick2)-1)
    quick_end2 = time.time()

    sorted_name = list(zip(*quick2))[1]
    validate_order(sorted_name)

    for i in range(0,size,1000):
        print(i+1, ":", quick2[i])

    print("\n비재귀 퀵정렬 소요시간:", quick_end2-quick_start2, "\n")

    # ------------Heap Sort------------ #
    print("# ------------Heap Sort------------ #")
    heap = copy.deepcopy(data)
    heap_start = time.time()
    heap_sort(heap)
    heap_end = time.time()

    sorted_name = list(zip(*heap))[1]
    validate_order(sorted_name)

    for i in range(0,size,1000):
        print(i+1, ":", heap[i])

    print("\n힙정렬 소요시간:", heap_end-heap_start, "\n")

    # ------------Selection Sort------------ #
    print("# ------------Selection Sort------------ #")
    selection = copy.deepcopy(data)
    selection_start = time.time()
    selection_sort(selection)
    selection_end = time.time()

    sorted_name = list(zip(*selection))[1]
    validate_order(sorted_name)

    for i in range(0,size,1000):
        print(i+1, ":", selection[i])

    print("\n선택정렬 소요시간:", selection_end-selection_start)

    # ------------Summary of Sorting------------ #
    print("\n# ------------Summary of Sorting------------ #\n")
    print("내장함수 소요시간:", builtin_end - builtin_start)
    print("퀵정렬 소요시간:", quick_end - quick_start)
    print("비재귀 퀵정렬 소요시간:", quick_end2 - quick_start2)
    print("힙정렬 소요시간:", heap_end - heap_start)
    print("선택정렬 소요시간:", selection_end - selection_start)