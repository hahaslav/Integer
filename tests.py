from os import system
from time import perf_counter
import operator
from random import randint, choice
from sympy import isprime

BASE_COMMAND = "cmake-build-debug\\integer.exe "
TEST_FILE = "test.txt"
METHOD_NUMBER = {
    "Output": 0,
    "Karatsuba": 1,
    "Tom-Cook": 2,
    "Modular": 3,
    "Schonhage-Strassen": 4,
    "Newton": 5,
    "Division": 6,
    "Fermat": 7,
    "Rabin-Miller": 8,
    "Solovay-Strassen": 9,
    "Agrawal": 10,
    "Sum": 11,
    "Subtract": 12,
    "Product": 13,
    "Division/": 14,
    "Remainder": 15,
    "Repeated addition": 16
}
RANDOM_TO_LENGTH = 5

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

    def success_criteria(self, another_result):
        return self.my_result == another_result

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
        if self.success_criteria(its_result):
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


class InverseTest(Test):
    """
    Class for Newton's inverse method
    """
    name = "Inverse test"
    method_number = METHOD_NUMBER["Newton"]

    def __init__(self, integer1: int):
        Test.__init__(self, method=self.method_number, integer1=integer1)

    def self_execute(self):
        self.my_result = f"{1 / self.integer1}"

    def success_criteria(self, another_result):
        return float(self.my_result) == float(another_result)


class PrimalityTest(Test):
    """
    Base class for primality check tests
    """
    name = "Primality test"
    method_number = None

    def __init__(self, integer1: int):
        Test.__init__(self, method=self.method_number, integer1=integer1)

    def self_execute(self):
        if isprime(self.integer1) == True:
            self.my_result = "IS_PRIME"
        else:
            self.my_result = "NOT_PRIME"


class SumTest(ArithmeticTest):
    name = "Sum test"
    operation = operator.add
    method_number = METHOD_NUMBER["Sum"]


class SubtractTest(ArithmeticTest):
    name = "Subtract test"
    operation = operator.sub
    method_number = METHOD_NUMBER["Subtract"]


class ProductTest(ArithmeticTest):
    name = "Product test"
    operation = operator.mul
    method_number = METHOD_NUMBER["Product"]


class KaratsubaTest(ProductTest):
    name = "Karatsuba multiplication test"
    method_number = METHOD_NUMBER["Karatsuba"]


class TomCookTest(ProductTest):
    name = "Tom-Cook multiplication test"
    method_number = METHOD_NUMBER["Tom-Cook"]


class RepeatedAdditionTest(ProductTest):
    name = "Repeated addition multiplication test"
    method_number = METHOD_NUMBER["Repeated addition"]


def custom_div(obj: any, a: int, b: int):
    if (a < 0) ^ (b < 0):
        sign = -1
    else:
        sign = 1

    a = abs(a)
    b = abs(b)

    return a // b * sign


class DivisionTest(ArithmeticTest):
    name = "Division test"
    operation = custom_div
    method_number = METHOD_NUMBER["Division/"]


class LargeDivisionTest(DivisionTest):
    name = "Large division test"


def custom_mod(obj: any, a: int, b: int):
    a = abs(a)
    b = abs(b)

    return a % b


class RemainderTest(ArithmeticTest):
    name = "Remainder test"
    operation = custom_mod
    method_number = METHOD_NUMBER["Remainder"]


class LargeRemainderTest(RemainderTest):
    name = "Large remainder test"
    operation = custom_mod
    method_number = METHOD_NUMBER["Remainder"]


class FermatTest(PrimalityTest):
    name = "Fermat test"
    method_number = METHOD_NUMBER["Fermat"]


class RabinMillerTest(PrimalityTest):
    name = "Rabin-Miller test"
    method_number = METHOD_NUMBER["Rabin-Miller"]


class SolovayStrassenTest(PrimalityTest):
    name = "Solovay-Strassen test"
    method_number = METHOD_NUMBER["Solovay-Strassen"]


TESTS_FOR_CATEGORY = {
    Test: 40,
    SumTest: 40,
    SubtractTest: 40,
    ProductTest: 10,
    KaratsubaTest: 10,
    TomCookTest: 10,
    RepeatedAdditionTest: 15,
    InverseTest: 20,
    DivisionTest: 40,
    RemainderTest: 40,
    LargeDivisionTest: 25,
    LargeRemainderTest: 25,
    FermatTest: 85,
    RabinMillerTest: 85,
    SolovayStrassenTest: 85
}
NUMBER1_LENGTH = {
    "max": 1000,
    Test: 1000,
    SumTest: 1000,
    SubtractTest: 1000,
    ProductTest: 200,
    KaratsubaTest: 200,
    TomCookTest: 200,
    RepeatedAdditionTest: 1000,
    InverseTest: 4,
    DivisionTest: 1000,
    RemainderTest: 1000,
    LargeDivisionTest: 200,
    LargeRemainderTest: 200,
    FermatTest: 4,
    RabinMillerTest: 4,
    SolovayStrassenTest: 4
}
NUMBER2_LENGTH = {
    "max": 1000,
    Test: 1000,
    SumTest: 1000,
    SubtractTest: 1000,
    ProductTest: 200,
    KaratsubaTest: 200,
    TomCookTest: 200,
    RepeatedAdditionTest: 4,
    InverseTest: None,
    DivisionTest: 8,
    RemainderTest: 8,
    LargeDivisionTest: 180,
    LargeRemainderTest: 180,
    FermatTest: None,
    RabinMillerTest: None,
    SolovayStrassenTest: None
}


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


def get_random_integer(*, length=None, positive=False) -> int:
    """
    Generates random integer

    The length of the integer can be specified
    """
    if length is None:
        length = randint(1, NUMBER1_LENGTH["max"])
    elif length > 49:
        length += randint(0, RANDOM_TO_LENGTH * 2) - RANDOM_TO_LENGTH

    if positive is False:
        sign = choice([-1, 1])
    else:
        sign = 1

    result = ""

    for _ in range(length):
        result += str(randint(0, 9))

    return sign * int(result)


def main():
    all_tests = []

    for category in TESTS_FOR_CATEGORY:
        for _ in range(TESTS_FOR_CATEGORY[category]):
            if issubclass(category, InverseTest):
                all_tests.append(category(integer1=get_random_integer(length=NUMBER1_LENGTH[category])))
            elif issubclass(category, PrimalityTest):
                all_tests.append(category(integer1=get_random_integer(length=NUMBER1_LENGTH[category], positive=True)))
            else:
                all_tests.append(category(integer1=get_random_integer(length=NUMBER1_LENGTH[category]), integer2=get_random_integer(length=NUMBER2_LENGTH[category])))

    for i, test in enumerate(all_tests, 1):
        print(f"{i:>3}. {test.name:>70}")
        test.execute()
        update_output()

    summarise(all_tests)


if __name__ == "__main__":
    main()