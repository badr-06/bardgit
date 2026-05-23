
def Nod(l, r):

    if l == 0 or r == 0:
        return 0

    if l == r:
        return l
    else:
        return 1


l = int(input())
r = int(input())
print(Nod(l, r))