R = int(input("Number of rows: "))
C = int(input("Number of columns: "))
G = int(input("Number of generations: "))

Lo = []  # the original 2D array of cells


for i in range(R):
    Le = []  # one row of cells in the array
    for j in range(C):
        e = (input("Enter either . or # for cell (" + str(i) + "," + str(j) + ") : ")).strip()
        while e != "." and e != "#":
            e = (input("Enter either . or # for cell (" + str(i) + "," + str(j) + ") : ")).strip()
        Le.append(e)
    Lo.append(Le)

   

def builder(L): # surrounding the array with dead cells as per rules of the game at this stage
    Lb = []   # using this to add row of dead cells at top and bottom
    for i in range(R):
        L[i].insert(0,'.')
        L[i].append('.')
    for i in range(C+2):
        Lb.append(".")
    L.insert(0,Lb)
    L.append(Lb)

def popper(L): # removing the bounding dead cells
    L.pop(0)
    L.pop()
    for i in range(R):
        L[i].pop(0)
        L[i].pop()

def actual_copy(L):
    Lc = [] # using this to create a deep copy of L (avoiding in-built function here)
    
    for i in L:
        Lr = [] # using this to create copy of each row one-by-one
        for j in i:
            Lr.append(j)
        Lc.append(Lr)    
    return Lc

Lt = actual_copy(Lo) # a list that will actually be modified first(so that Lo stays same so that update is simultaneous )
builder(Lo)
builder(Lt)

max = 0

for k in range(G+1):
    
    alive = 0
    for i in range(R):
        for j in range(C):
            c_dead,c_alive = 0,0
            for m in [i,i+1,i+2]:
                for n in [j,j+1,j+2]:
                    if (m,n) != (i+1,j+1):
                        if Lo[m][n] == ".":
                            c_dead += 1
                        else:
                            c_alive += 1
            if Lo[i+1][j+1] == "#":
                alive += 1
                if k != G:
                    if c_alive < 2:
                        Lt[i+1][j+1] = "."
                    elif c_alive > 3:
                        Lt[i+1][j+1] = "."
            else:
                if k != G:
                    if c_alive == 3:
                        Lt[i+1][j+1] = "#"
        

    if k == 0:
        max = alive
        print("Initial Population: ",alive)

    if alive > max:
        max = alive

    if k == G:
        print("Final Population: ",alive)
    
    Lo = actual_copy(Lt)

print("Peak Population: ",max)
popper(Lo)
popper(Lt)
    
print("Final Grid: ")
for i in Lo:
    for j in i:
        print(j,end = " ")
    print()
