listL = [1, 2, 5, 21, 21, 23, 51, 512, 12, 2333, 1] #sample list
largest, tempheld = 0,0 #storing in memory the largest and one being evaluated

def myMax (listL): #actual function
    global largest, tempheld   #making variables global. Can also put them inside loop but I prefer global
    if (len(listL)) == 0: #safecase once list is 0, would throw error if it pops nothing
        return
    tempheld = listL[0] #storing next item in list in memory
    if (tempheld > largest): #evaluating if it's larger than what we have
        largest = tempheld #if it is larger, we change our largest to it
    listL.pop(0) #remove the one we just evaluated
    myMax (listL) #recursively move onto next one

myMax(listL) #calls function
print largest #prints largest value
