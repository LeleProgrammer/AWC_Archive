N=51

n,k=input().strip().split()
n=int(n)
k=int(k)
k=min(k,n-1)
a=input().strip().split()
for i in range(len(a)):
    a[i]=int(a[i])
f=[[[0 for i in range(N)] for j in range(N)] for i in range(N)]
for i in range(n):
    f[i][i][0]=a[i]
for t in range(k+1):
    for len in range(2,n+1):
        for l in range(n-len+1):
            r=l+len-1
            for j in range(l,r):
                for g in range(t+1):
                    f[l][r][t]=max(f[l][r][t],f[l][j][g]+f[j+1][r][t-g])
                    if g!=t:
                        f[l][r][t]=max(f[l][r][t],(f[l][j][g]+f[j+1][r][t-g-1])*2)
ans=0
for i in range(k+1):
    ans=max(ans,f[0][n-1][i]);
print(ans)