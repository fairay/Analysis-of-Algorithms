def dem_lev_matrix(matr, s1, s2):
1    if len(s1) == 0: return len(s2)
2    elif len(s2) == 0: return len(s1)

3    for j in range(len(s1)+1):
4        matr[0][j] = j
5    for i in range(1, len(s2)+1):
6        matr[i][0] = i

7    for i in range(1, len(s2) + 1):
8		 addM = 1 - int(s1[0] == s2[i-1])
9        matr[i][1] = min(matr[i-1][1] + 1, matr[i][0] + 1,
                           matr[i-1][0] + addM)

10    for j in range(2, len(s1) + 1):
11		  addM = 1 - int(s1[j-1] == s2[0])
12        matr[1][j] = min(matr[0][j] + 1, matr[1][j-1] + 1,
                           matr[0][j-1] + addM)

13    for i in range(2, len(s2)+1):
14        for j in range(2, len(s1)+1):
15			  addM = 1 - int(s1[j-1] == s2[i-1])
16			  addT = 2 - int(s1[j-2] == s2[i-1] and s1[j-1] == s2[i-2])
17            matr[i][j] = min(matr[i-1][j]+1, matr[i][j-1]+1,
                               matr[i-1][j-1]+addM, matr[i-2][j-2]+addT)

