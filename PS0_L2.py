def sorted_display(L):
    temp_L = []
    for i in range(len(L)):
        flag = 0
        if i == 0:
            temp_L.append(L[i])
            flag = 1
        else:
            for j in range(len(temp_L)):
                if temp_L[j] > L[i]:
                    temp_L.insert(j, L[i])
                    flag = 1
                    break
        if flag == 0:
            temp_L.append(L[i])
    return temp_L


def kth_heavy(L):
    k = int(input("Enter k: "))
    print((sorted_display(L))[-k])


def search(L):
    w = int(input("search weight: "))
    if w in L:
        print("container ", L.index(w) + 1, "has weight ", w)
    else:
        print("no such container")


def graph(L):
    for item in L:
        print(item, ": ", end="")
        for i in range(int(item / 5)):
            if i < (int(item / 5) - 1):
                print("*", end="")
            else:
                print("*")


def cargo():
    L = []
    n = int(input("specify number of containers: "))
    for i in range(n):
        x = int(input("Enter weight of container: "))
        L.append(x)
    info(L)


def info(L):
    sum = 0
    for i in L:
        sum += i
    avg = sum / len(L)

    for k in L:
        if k == L[0]:
            max, min = k, k
        else:
            if k > max:
                max = k
            if k < min:
                min = k

    print("Total Shipment Weight: ", sum)
    print("Average container Weight: ", avg)
    print("Heaviest container: ", max)
    print("Lightest container: ", min)

    if sum < 200:
        cls = 'Light'
    else:
        cls = 'Heavy'
    print("classification: ", cls)

    g = input("1 for graph: ")
    if g == "1":
        graph(L)
    s = input("1 for sort: ") 
    if s == "1":
        print(sorted_display(L))
    v = input("1 for kth heavy: ")
    if v == "1":
        kth_heavy(L)
    f = input("1 for search: ")
    if f == "1":
        search(L)
        
    c = input("save? (yes/no): ")
    if c == "yes":
        file = input("Enter file name: ")
        obj = open(file, 'w')
        lines = ["Heaviest container " + str(max) + "\n", "Lightest container " + str(min) + "\n"]
        obj.writelines(lines)
        obj.close()


def fileopen():
    M = []
    filename = input('filename: ')
    obj = open(filename, 'r')
    P = int(obj.readline().strip())
    print("Loaded ", P, "containers from ", filename)
    print("weights: ", end="")
    for i in range(P):
        M.append(int((obj.readline()).strip()))
    for j in M:
        print(j, end=' ')
    print("\n")
    info(M)
    obj.close()



running = True
while running:
    a = input("1 for opening, 2 for adding: ")
    if a == '1':
        fileopen()
    else:
        cargo()
    r = input('1 to stop running: ')
    if r == '1':
        running = False
    
