import random
import time
import psutil


def print_matrix(m):
    print("\nМатрица поиска расстояния:")
    for row in m:
        print(row)


def lev_matrix(s1, s2, is_print=False):
    print("Tested matrix")
    matr = [[0] * (len(s1)+1) for i in range(len(s2)+1)]

    for j in range(len(s1)+1):
        matr[0][j] = j
    for i in range(len(s2)+1):
        matr[i][0] = i

    for i in range(1, len(s2)+1):
        for j in range(1, len(s1)+1):
            add = 0 if s1[j-1] == s2[i-1] else 1
            matr[i][j] = min(matr[i-1][j]+1, matr[i][j-1]+1, matr[i-1][j-1]+add)

    if is_print:
        print("Расстояние:", matr[i][j])
        print_matrix(matr)
    return matr[i][j]


def _lev_rec(s1, s2, len1, len2):
    if len1 == 0: return len2
    elif len2 == 0: return len1
    else:
        return min(_lev_rec(s1, s2, len1, len2-1) + 1,
                   _lev_rec(s1, s2, len1-1, len2) + 1,
                   _lev_rec(s1, s2, len1-1, len2-1) + (0 if s1[len1-1] == s2[len2-1] else 1))
def lev_recursion(s1, s2, is_print=False):
    res = _lev_rec(s1, s2, len(s1), len(s2))
    if is_print:
        print("Расстояние:", res)
    return res


def _lev_mr(matr, i, j, s1, s2):
    if i+1 < len(matr) and j+1 < len(matr[0]):
        add = 0 if s1[j] == s2[i] else 1
        if matr[i+1][j+1] > matr[i][j] + add:
            matr[i+1][j+1] = matr[i][j] + add
            _lev_mr(matr, i+1, j+1, s1, s2)
    if j+1 < len(matr[0]) and (matr[i][j+1] > matr[i][j] + 1):
        matr[i][j+1] = matr[i][j] + 1
        _lev_mr(matr, i, j+1, s1, s2)
    if i+1 < len(matr) and (matr[i+1][j] > matr[i][j] + 1):
        matr[i+1][j] = matr[i][j] + 1
        _lev_mr(matr, i+1, j, s1, s2)
def lev_matrix_recursion(s1, s2, is_print=False):
    max_len = max(len(s1), len(s2)) + 1
    matr = [[max_len] * (len(s1) + 1) for i in range(len(s2) + 1)]
    matr[0][0] = 0
    _lev_mr(matr, 0, 0, s1, s2)

    if is_print:
        print("Расстояние:", matr[-1][-1])
        print_matrix(matr)
    return matr[-1][-1]


def dem_lev_matrix(s1, s2, is_print=False):
    if len(s1) == 0: return len(s2)
    elif len(s2) == 0: return len(s1)
    matr = [[0] * (len(s1) + 1) for i in range(len(s2) + 1)]
    for j in range(len(s1)+1):
        matr[0][j] = j
    for i in range(len(s2)+1):
        matr[i][0] = i

    for i in range(1, len(s2) + 1):
        addM = 0 if s1[0] == s2[i-1] else 1
        matr[i][1] = min(matr[i-1][1] + 1, matr[i][0] + 1,
                         matr[i-1][0] + addM)
    for j in range(2, len(s1) + 1):
        addM = 0 if s1[j-1] == s2[0] else 1
        matr[1][j] = min(matr[0][j] + 1, matr[1][j-1] + 1,
                         matr[0][j-1] + addM)

    for i in range(2, len(s2)+1):
        for j in range(2, len(s1)+1):
            addM = 0 if s1[j-1] == s2[i-1] else 1
            addT = 1 if (s1[j-2] == s2[i-1] and s1[j-1] == s2[i-2]) else 2
            matr[i][j] = min(matr[i-1][j]+1, matr[i][j-1]+1,
                             matr[i-1][j-1]+addM, matr[i-2][j-2]+addT)

    if is_print:
        print("Расстояние:", matr[i][j])
        print_matrix(matr)
    return matr[i][j]


def random_str(length):
    a = []
    for i in range(length):
        a.append(random.choice("qwerty"))
    return "".join(a)



def test_input(func):
    s1 = input("Введите сторку №1: ")
    s2 = input("Введите сторку №2: ")
    func(s1, s2, True)


def test_time(func):
    length = int(input("Введите длину строки: "))
    s1 = random_str(length)
    s2 = random_str(length)
    print("Строка 1:", s1)
    print("Строка 2:", s2)

    begin_t = time.process_time()
    count = 0
    while time.process_time() - begin_t < 1.0:
        func(s1, s2)
        count += 1

    t = time.process_time() - begin_t
    print("Выполнено {:} операций за {:} секунд".format(count, t))
    print("Время: {:7.4} секунд".format(t / count))


def test_memory(func, length):
    s1 = random_str(length)
    s2 = random_str(length)
    print("Строка 1:", s1)
    print("Строка 2:", s2)

    p = psutil.Process()
    mem1 = p.memory_info().peak_wset
    func(s1, s2)
    mem2 = p.memory_info().peak_wset

    print("Затраченая память - {:} байт".format(mem2-mem1))


def main():
    f_arr = [lev_matrix, lev_recursion, lev_matrix_recursion, dem_lev_matrix]

    print("Программа для поиска редакционных расстояний\n")
    print(
        "Выберете алгоритм:\n"
        "1) Расстояние Левенштейна (матрично)\n"
        "2) Расстояние Левенштейна (рекурсивно)\n"
        "3) Расстояние Левенштейна (рекурсивно с заполнением матрицы)\n"
        "4) Расстояние Дамерау-Левенштейна (матрично)")
    alg_n = int(input())
    if alg_n < 1 or alg_n > len(f_arr):
        print("Ошибка: Неизвестный алгоритм")
        return
    f = f_arr[alg_n-1]

    print(
        "\nВыберете действие:\n"
        "1) Найти расстояние для введённых строк\n"
        "2) Замер времени работы\n"
        "3) Замер используемой памяти\n")
    act_n = int(input())

    if act_n == 1:
        test_input(f)
    elif act_n == 2:
        test_time(f)
    elif act_n == 3:
        length = int(input("Введите длину строки: "))
        test_memory(f, length)
    else:
        print("Ошибка: Неизвестное действие")


if __name__ == "__main__":
    main()
