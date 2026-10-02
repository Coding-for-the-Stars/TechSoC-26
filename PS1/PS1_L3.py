import time
import subprocess

R = int(input("Number of rows: "))
C = int(input("Number of columns: "))
G = int(input("Number of generations: "))

Lo = []  # original list

for i in range(R):
    Le = []  # one element of Lo
    for j in range(C):
        e = (input("Enter either . or # for cell (" + str(i) + "," + str(j) + ") : ")).strip()
        while e != "." and e != "#":
            e = (input("Enter either . or # for cell (" + str(i) + "," + str(j) + ") : ")).strip()
        Le.append(e)
     
    Lo.append(Le)
    


   

def builder(L):
   Lx = actual_copy(L)
   # top and bottom
   Lx.insert(0,L[-1])
   Lx.append(L[0])
   # left and right
   for i in range(R):
       Lx[i+1].append(L[i][0])
       Lx[i+1].insert(0,L[i][-1])
   # corners
   Lx[0].append(L[R-1][0])
   Lx[-1].append(L[0][0])
   Lx[0].insert(0,L[R-1][C-1])
   Lx[-1].insert(0,L[0][C-1])
   return Lx

def popper(L):
    Ly = actual_copy(L)
    Ly.pop(0)
    Ly.pop()
    for i in range(R):
        Ly[i].pop(0)
        Ly[i].pop()
    return Ly

def actual_copy(L):
    Lc = [] # deep copy
    
    for i in L:
        Lr = [] # one row
        for j in i:
            Lr.append(j)
        Lc.append(Lr)    
    return Lc

Lt = actual_copy(Lo) # temporary list to modify

Lo = builder(Lo)

Lt = builder(Lt)


alive = 0
for k in range(G+1):
    
    
    
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
                
                
              
                    if c_alive < 2:
                        Lt[i+1][j+1] = "."
                    elif c_alive > 3:
                        Lt[i+1][j+1] = "."
            else:
                
                    if c_alive == 3:
                        Lt[i+1][j+1] = "#"

    subprocess.run('cls',shell = True)
    print("Generation: ",k,end = '           ')
    print("Population: ",alive)
    for i in popper(Lo):
        for j in i:
            print(j,end = " ")
        print()
    time.sleep(2)   
    subprocess.run('cls',shell = True)
   
    Lt = popper(Lt)
    Lo = actual_copy(Lt)    

       
    
    if k == G-1:
        final = alive 
    Lt = builder(Lt) 
    Lo = builder(Lo)







print("Simulation complete.")
