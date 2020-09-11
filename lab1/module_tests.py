import unittest
import main


# Общий набор тестов для всех алгоритмов
class GeneralTest(unittest.TestCase):
    # Данный класс являтся абстрактным, поэтому для него тесты пропускаются
    @unittest.skip("Skip GeneralTest")
    def setUp(self):
        self.function = None

    # Проверка пустыми строками
    def test_empty(self):
        self.assertEqual(self.function("", ""), 0)
        self.assertEqual(self.function("a", ""), 1)
        self.assertEqual(self.function("", "b"), 1)

    # Проверка нахождения совпадений
    def test_match(self):
        self.assertEqual(self.function("abc", "abc"), 0)
        self.assertEqual(self.function("a", "a"), 0)
        self.assertEqual(self.function("A", "a"), 1)

    # Прочие общие тесты
    def test_other(self):
        self.assertEqual(self.function("q", "w"), 1)
        self.assertEqual(self.function("aq", "aw"), 1)
        self.assertEqual(self.function("a", "aw"), 1)
        self.assertEqual(self.function("aw", "a"), 1)


# Набор тестов для алгоритмов поиска расстояния Левенштейна
class LevTest(GeneralTest):
    def test_lev(self):
        self.assertEqual(self.function("stolb", "telo"), 3)
        self.assertEqual(self.function("kult_tela", "tela_kult"), 6)
        self.assertEqual(self.function("развлечение", "увлечение"), 3)


# Набор тестов для алгоритма поиска расстояния Дамерау-Левенштейна
class DemLevMatrixTest(GeneralTest):
    def setUp(self):
        self.function = main.dem_lev_matrix

    def dem_lev_test(self):
        self.assertEqual(self.function("aba", "aab"), 1)
        self.assertEqual(self.function("ab", "ba"), 1)
        self.assertEqual(self.function("abb", "bab"), 1)


# Следующие алгоритмы поиска расстояния Левенштейна проходят одинковые тесты
# из класса LevTest
# Алгоритм поиска расстояния Левенштейна, матричный метод
class LevMatrixTest(LevTest):
    def setUp(self):
        self.function = main.lev_matrix


# Алгоритм поиска расстояния Левенштейна, рекурсивный метод
class LevRecursionTest(LevTest):
    def setUp(self):
        self.function = main.lev_recursion


# Алгоритм поиска расстояния Левенштейна,
# рекурсивный метод с заполнением матрицы
class LevMatRecTest(LevTest):
    def setUp(self):
        self.function = main.lev_matrix_recursion


# Точка входа, запуск тестов
if __name__ == "__main__":
    unittest.main()
