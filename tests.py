from os import system
from time import perf_counter
import operator
from random import randint

BASE_COMMAND = "cmake-build-debug\\integer.exe "
TEST_FILE = "test.txt"
METHOD_NUMBER = {
    "Output": 0,
    "Karatsuba": 1,
    "Tom-Cook": 2,
    "Modular": 3,
    "Schonhage-Shtrassen": 4,
    "Float": 5,
    "Division": 6,
    "Fermat": 7,
    "Rabin-Miller": 8,
    "Solovay_Shtrassen": 8,
    "Agrawal": 10,
    "Sum": 11,
    "Subtract": 12,
    "Product": 13
}
TESTS_FOR_CATEGORY = 10
MAX_DIGITS = 1000
SHORT_NUMBER = 200

last_test_executed = None
final_output = ""
testing_start_time = perf_counter()


class Test:
    """
    Base class for all tests

    By default, it tests the output of the app
    """
    status = "not checked yet"
    my_result = None
    execution_time = None
    name = "Output test"

    def __init__(self, *, method: int = 0, integer1: int, **kwargs):
        self.method_number = method
        self.integer1 = integer1
        if "integer2" in kwargs.keys():
            self.integer2 = kwargs["integer2"]
        else:
            self.integer2 = None

    def execute(self):
        """
        Runs the app with the test's arguments
        """
        command = f"{BASE_COMMAND} {self.method_number} {self.integer1}"
        if self.integer2 is not None:
            command += f" {self.integer2}"
        command += f" > {TEST_FILE}"

        start_time = perf_counter()
        system(command)
        self.execution_time = perf_counter() - start_time
        global last_test_executed
        last_test_executed = self

    def self_execute(self):
        """
        Counts the right answer for the test
        """
        self.my_result = f"{self.integer1}"
        if self.integer2 is not None:
            self.my_result += f" {self.integer2}"

    def check(self):
        """
        Concludes the result of the test
        """
        if self.my_result is None:
            self.self_execute()

        if last_test_executed != self:
            raise Exception("This test's execution output has been expired")

        with open(TEST_FILE, 'r') as fin:
            its_result = fin.read()

        output = ""
        if self.my_result == its_result:
            self.status = "SUCCESS"
        else:
            self.status = "FAIL"
        output += self.status
        if self.integer2 is not None:
            integer_length = max([len(str(self.integer1)), len(str(self.integer2)), len(str(self.my_result)), len(str(its_result))])
            output += f" {self.name} executed in {self.execution_time} s\n\tIntegers:\n\t\t{self.integer1:>{integer_length}}\n\t\t{self.integer2:>{integer_length}}\n\tExpected output:\n\t\t{self.my_result:>{integer_length}}\n\tResult:\n\t\t{its_result:>{integer_length}}"
        else:
            integer_length = max([len(str(self.integer1)), len(str(self.my_result)), len(str(its_result))])
            output += f" {self.name} executed in {self.execution_time} s\n\tInteger:\n\t\t{self.integer1:>{integer_length}}\n\tExpected output:\n\t\t{self.my_result:>{integer_length}}\n\tResult:\n\t\t{its_result:>{integer_length}}"

        return output


class ArithmeticTest(Test):
    """
    Base class for arithmetic tests
    """
    name = "Arithmetic test"
    operation = None
    method_number = None

    def __init__(self, integer1: int, integer2: int):
        Test.__init__(self, method=self.method_number, integer1=integer1, integer2=integer2)

    def self_execute(self):
        self.my_result = f"{self.operation(self.integer1, self.integer2)}"


class SumTest(ArithmeticTest):
    name = "Sum test"
    operation = operator.add
    method_number = METHOD_NUMBER["Sum"]


def custom_subtract(obj, a: int, b: int):
    """
    If a < b, then returns 0

    Else, does usual subtraction
    """
    if a < b:
        return 0
    return a - b


class SubtractTest(ArithmeticTest):
    name = "Subtract test"
    operation = custom_subtract
    method_number = METHOD_NUMBER["Subtract"]


class ProductTest(ArithmeticTest):
    name = "Product test"
    operation = operator.mul
    method_number = METHOD_NUMBER["Product"]


class KaratsubaTest(ProductTest):
    name = "Karatsuba multiplication test"
    method_number = METHOD_NUMBER["Karatsuba"]


def update_output():
    """
    Adds the last test's result to the final output
    """
    global final_output

    final_output += f"\n\n{last_test_executed.check()}"


def summarise(tests: list[Test]):
    """
    Outputs a file with the tests' results
    """
    global final_output

    tests_time = sum([test.execution_time for test in tests])
    successful_tests = sum([1 for test in tests if test.status == "SUCCESS"])
    all_tests = len(tests)
    if successful_tests == all_tests:
        status = "SUCCESS"
    else:
        status = "FAIL"
    final_output = f"{status} {successful_tests}/{all_tests} in {perf_counter() - testing_start_time} s ({tests_time} s in the tested app)" + final_output

    with open(TEST_FILE, 'w', encoding="UTF-8") as fout:
        fout.write(final_output)


def get_random_integer(length=None) -> int:
    """
    Generates random integer

    The length of the integer can be specified
    """
    if length is None:
        length = randint(1, MAX_DIGITS)

    result = ""

    for _ in range(length):
        result += str(randint(0, 9))

    return int(result)


def main():
    test_types = [Test, SumTest, SubtractTest, ProductTest, KaratsubaTest]
    fast_test_types = [Test, SumTest, SubtractTest]

    all_tests = []

    for category in test_types:
        for i in range(TESTS_FOR_CATEGORY):
            if category in fast_test_types:
                all_tests.append(category(integer1=get_random_integer(MAX_DIGITS), integer2=get_random_integer(MAX_DIGITS)))
            else:
                all_tests.append(category(integer1=get_random_integer(SHORT_NUMBER), integer2=get_random_integer(SHORT_NUMBER)))


    for i, test in enumerate(all_tests, 1):
        print(f"{i:>2}. {test.name:>70}")
        test.execute()
        update_output()

    summarise(all_tests)


if __name__ == "__main__":
    main()