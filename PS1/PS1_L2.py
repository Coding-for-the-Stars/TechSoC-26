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






def simulation_one(Lo,R,C):

   
    Lo = builder(Lo)
    Lt = actual_copy(Lo)
    
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
           
                
            
                if c_alive < 2:
                        Lt[i+1][j+1] = "."
                elif c_alive > 3:
                        Lt[i+1][j+1] = "."
            else:
            
                if c_alive == 3:
                        Lt[i+1][j+1] = "#"   
    
   
    Lt = popper(Lt)
    Lo = actual_copy(Lt)
    return Lo

def CoM(Lo,R,C):
    sum_pos_x = 0
    sum_pos_y = 0
    alive = 0
    max_c = 0
    max_r = 0
    min_c = C
    min_r = R
    for i in range(R):
        for j in range(C):
            if Lo[i][j] == "#":
                sum_pos_x += i
                sum_pos_y += j
               
                
                if j < min_c:
                    min_c = j
                if j > max_c:
                    max_c = j   
                if i < min_r:
                    min_r = i     
                if i > max_r:
                    max_r = i      
    alive = population(Lo,R,C)
    if alive != 0:            
        x,y = sum_pos_x/alive,sum_pos_y/alive
        print("Center of mass: ",(x,y))
        print("Bounding Box: ",max_r-min_r+1," x ",max_c-min_c+1," (Rows ",min_r,"-",max_r,"  Cols ",min_c,"-",max_c,")")  
    else:
        print("Center of mass: N/A")
        print("Bounding Box: 0 x 0")        
    print('Live Cells: ',alive) 

def classify(Lo,K,R,C):
            count = 0
            Lm = [actual_copy(Lo)] 
            Lo = simulation_one(Lo,R,C)
          
            for k in range(9):
                if Lo == Lempo:
                    print("Classification: Extinct")
                    print("Extinction step: ",k+1)
                    count += 1
                elif Lo == Lm[-1]:
                    print("Classsification: Still Life")
                    print("Stable at step: ",k)
                    print("Period: 1")
                    count += 1
                elif Lo in Lm:
                    print("Classification: Oscillator") 
                    x = Lm.index(Lo)
                    print("Period: ",len(Lm)-x)
                    print("First repeat Step: ",len(Lm),"(matches Step ",x,")")
                    count += 1  
                
               
                
                Lm.append(actual_copy(Lo))
                Lo = simulation_one(Lo,R,C)
                if count == 1: break
            if count == 0:    
                  print("Classification: Active")
                  print("Reason: No repeat or extinction detected within K = ",K," steps")
            return Lo
def population(Lo,R,C):
    alive = 0
    for i in range(R):
        for j in range(C):
            if Lo[i][j] == "#":
                alive += 1   
    return alive           
    




def grid(Lo):
    for i in Lo:
        for j in i:
            print(j, end = " ")
        print()    

command = input("Command:" \
"toroidal  " \
"classify  " \
"metrics  " \
" ").strip().lower()

R = int(input("Number of rows: "))
C = int(input("Number of columns: "))


Lo = []  # original list
Lempo = [] # list of all dead

for i in range(R):
    Le = []  # one element of Lo
    Lempe = [] # one element of dead(empty) list
    
    for j in range(C):
        e = (input("Enter either . or # for cell (" + str(i) + "," + str(j) + ") : ")).strip()
        while e != "." and e != "#":
            e = (input("Enter either . or # for cell (" + str(i) + "," + str(j) + ") : ")).strip()
        Le.append(e)
        Lempe.append('.')
    Lo.append(Le)
    Lempo.append(Lempe)   

ini = population(Lo,R,C)
if command == 'classify':
    Lo = classify(Lo,10,R,C)
    print("Population: ",population(Lo,R,C))
elif command == 'metrics':
    G = int(input("Number of generations: "))
    for i in range(G):
        Lo = simulation_one(Lo,R,C)
    CoM(Lo,R,C)
elif command == 'toroidal':  
    G = int(input("Number of generations: "))
    print("Initial population: ",ini)  
    for k in range(G):
        max = 0
        geni = population(Lo,R,C)
        
        if max < geni:
            max = geni
        Lo = simulation_one(Lo,R,C)
    fin = population(Lo,R,C)

    print("Final population: ",fin)
    
    print("Peak population: ",max)
    grid(Lo) 
