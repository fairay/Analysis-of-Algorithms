import unittest
import main


class GeneralTest(unittest.TestCase):
    @unittest.skip("Skip GeneralTest")
    def setUp(self):
        self.function = None

    def test_empty(self):
        self.assertEqual(self.function("", ""), 0)
        self.assertEqual(self.function("a", ""), 1)
        self.assertEqual(self.function("", "b"), 1)

    def test_match(self):
        self.assertEqual(self.function("abc", "abc"), 0)
        self.assertEqual(self.function("a", "a"), 0)

    def test_simple(self):
        self.assertEqual(self.function("q", "w"), 1)
        self.assertEqual(self.function("aq", "aw"), 1)
        self.assertEqual(self.function("a", "aw"), 1)
        self.assertEqual(self.function("aw", "a"), 1)


class LevTest(GeneralTest):
    def test_lev(self):
        self.assertEqual(self.function("stolb", "telo"), 3)
        self.assertEqual(self.function("kult_tela", "tela_kult"), 6)
        self.assertEqual(self.function("развлечение", "увлечение"), 3)


class DemLevMatrixTest(GeneralTest):
    def setUp(self):
        self.function = main.dem_lev_matrix

    def dem_lev_test(self):
        self.assertEqual(self.function("aba", "aab"), 1)
        self.assertEqual(self.function("ab", "ba"), 1)
        self.assertEqual(self.function("abb", "bab"), 1)


class LevMatrixTest(LevTest):
    def setUp(self):
        self.function = main.lev_matrix


class LevRecursionTest(LevTest):
    def setUp(self):
        self.function = main.lev_recursion


class LevMatRecTest(LevTest):
    def setUp(self):
        self.function = main.lev_matrix_recursion


def module_tests():
    # tests = unittest.TestLoader().loadTestsFromTestCase(LevMatrixTest)
    # unittest.TextTestRunner().run(tests)
    unittest.main()


if __name__ == "__main__":
    module_tests()
