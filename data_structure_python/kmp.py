def strstr(arr, target):
    count = 0
    for i in range(len(arr)):
        for j in range(len(target)):
            if target[j] == arr[i+j]:
                count += 1
                if count == len(target):
                    return i
            else:
                break


def kmp(H, N):
    n = len(H)
    m = len(N)
    # 결과값 리스트
    ret = []
    # pi[i]는 N[~i]의 접두사도 되고 접미사는 되는 문자열의 최대 길이
    pi = get_pattern(N)
    begin = 0
    matched = 0
    while begin <= n - m:
        # 글자가 일치한다면
        if matched < m and H[begin + matched] == N[matched]:
            matched += 1
            # m글자가 모두 일치한다면
            if matched == m:
                ret.append(begin)
        else:
            # matched가 0인 경우 다음 칸에서 시작
            if matched == 0:
                begin += 1
            else:
                begin += matched - pi[matched - 1]
                matched = pi[matched - 1]
    return ret

def get_pattern(target):
    m = len(target)
    pi = [0] * m
    # KMP로 N에서 N을 찾는다 (begin은 1부터)
    begin = 1
    matched = 0
    # 비교할 문자가 N의 끝에 도달할 때까지 부분 일치를 모두 기록
    while begin + matched < m:
        if target[begin + matched] == target[matched]:
            matched += 1
            pi[begin + matched - 1] = matched
            print("1", pi, "begin:", begin, "matched:", matched)
        else:
            if matched == 0:
                begin += 1
                print("2", pi, "begin:", begin, "matched:", matched)
            else:
                begin += matched - pi[matched - 1]
                matched = pi[matched - 1]
                print("3", pi, "begin:", begin, "matched:", matched)

    return pi



def kmp2(a, b):
    max_a = len(arr) - 1
    max_b = len(target) - 1
    a_idx = 0
    b_idx = 0
    result = []

    while a_idx < len(arr):
        if max_b == 1:
            if a[a_idx] == b[b_idx] and a[a_idx+1] == b[b_idx+1]:
                result.append(a_idx)
        elif max_b == 0:
            if a[a_idx] == b[b_idx]:
                result.append(a_idx)
        else:
            if a[a_idx] == b[b_idx] and a[(a_idx + max_b - b_idx - 1)] == b[max_b - 1] and a[(a_idx + max_b)] != b[max_b]:
                a_idx = a_idx + max_b - 1
                continue
            else:
                j = a_idx
                flag = 0
                while j < a_idx + max_b - 1:
                    if a[j+1] == b[b_idx+1]:
                        j+=1
                        b_idx+=1
                        flag = 1
                    else:
                        flag = 0
                        break

                if flag == 1:
                    result.append(a_idx)
                    b_idx = 0

        a_idx += 1

    return result




arr = "asdlkaadbaaabaacacplaa"
target = "cacp"

#print(strstr(arr, target))
#print(kmp(arr,target))
print(kmp2(arr, target))


