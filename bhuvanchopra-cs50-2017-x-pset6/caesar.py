import sys
if len(sys.argv)!=2:
    print("Error.")
    exit(1)
else:
    k=int(sys.argv[1])
    s=input("Plaintext: ")
    L=[]
    st=''
    for i in range(len(s)):
        L.append(ord(s[i]))
    for i in range(len(s)):
        if ((ord(s[i])>64 and ord(s[i])<91) or (ord(s[i])>96 and ord(s[i])<123)):
            if ((ord(s[i])<90 and (ord(s[i])+k%26)>90) or (ord(s[i])<122 and (ord(s[i])+k%26)>122)):
                L[i]=L[i]+(k%26)-26
                st+=chr(L[i])
            else:
                L[i]=L[i]+(k%26)
                st+=chr(L[i])
        else:
            st+=chr(L[i])
    print("ciphertext: {}".format(st))
    