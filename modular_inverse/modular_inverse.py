def egcd(a, m):
    if a == 0:
        return (m, 0, 1)
    else:
        j, y, x = egcd(m%a, a)
        return (j, x - (m//a)*y, y)

def MyExMod(a,n,m):
    return (a**n)%m

def MyInvMod(a,m):
    j, x, y = egcd(a, m)
    if j != 1:
        raise Exception("Not inverse modular")
    else:
        return x%m

a = int(input("a : "))
n = int(input("n : "))
m = int(input("m : "))

print("a^n mod m : ", MyExMod(a, n, m))
print("a^-1 mod m : ", MyInvMod(a, m))
