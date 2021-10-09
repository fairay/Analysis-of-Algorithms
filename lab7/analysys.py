fname = 'data.txt'

if __name__ == "__main__":
    c = [0] * 10
    f = open(fname, 'r')
    for i in f.readlines():
        key, val = map(int, i.split())
        c[key%10] += 1
    f.close()
    print(c)
