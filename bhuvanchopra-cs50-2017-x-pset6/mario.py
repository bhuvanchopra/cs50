
done=False
while not done:
    h=input('Height: ')
    if (h).isdigit():
    
        done=True
        for i in range(int(h)):
            for j in range(int(h)+1):
                if (i+j)>=(int(h)-1):
                    print("#",end='')
                else:
                    print(" ",end='')
            print("\n",end='')
    else:
        print('Please enter an integer.')
    