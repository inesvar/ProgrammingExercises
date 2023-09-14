N = int(input())
token = [True] * (N + 1)

# UTILS
def fill(index: int):
    # nothing to do if it's filled
    if token[index]:
        return
    # handle 1 when it's 2
    elif index == 2:
        if not token[1]:
            fill(1)
    # in other cases handle all the predecessors
    else:
        if not token[index - 1]:
            fill(index - 1)
        for i in range(index - 2, 0, -1):
            empty(i)

    token[index] = True
    print(index)   
    

def empty(index: int):
    # nothing to do if it's empty
    if not token[index]:
        return
    # handle 1 when it's 2
    elif index == 2:
        if not token[1]:
            fill(1)
    # in other cases handle all the predecessors
    else:
        if not token[index - 1]:
            fill(index - 1)
        for i in range(index - 2, 0, -1):
            empty(i)

    token[index] = False
    print(index)   
    

for index in range(N, 0, -1):
    empty(index)