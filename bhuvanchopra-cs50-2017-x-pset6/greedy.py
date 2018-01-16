done=False
while not done:
    h= input("Please enter a float:")
    if float(h)>=0:
        
        try:
            done=(isinstance(float(h),float))
        
        except:
            print("Please enter as specified")
    else:
        print("Please enter positive values only.")
h=float(h)        
t1=int(round(h,2)/0.25)
t2=int(round(h-t1*0.25,2)/0.1)
t3=int(round(h-t1*0.25-t2*0.1,2)/0.05)
t4=int(round(h-t1*0.25-t2*0.1-t3*0.05,2)/0.01)
print(t1+t2+t3+t4)
