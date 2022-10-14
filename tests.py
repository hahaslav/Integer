from os import system
from time import perf_counter

BASE_COMMAND = "cmake-build-debug\\integer.exe "
TEST_FILE = "test.txt"

last_test_executed = None
final_output = ""
testing_start_time = perf_counter()


class Test:
    status = "not checked yet"
    my_result = None
    execution_time = None
    def __init__(self, *, method: int, integer1: int, **kwargs):
        self.method = method
        self.integer1 = integer1
        if "integer2" in kwargs.keys():
            self.integer2 = kwargs["integer2"]
        else:
            self.integer2 = None

    def execute(self):
        command = f"{BASE_COMMAND} {self.method} {self.integer1}"
        if self.integer2 is not None:
            command += f" {self.integer2}"
        command += f" > {TEST_FILE}"

        start_time = perf_counter()
        system(command)
        self.execution_time = perf_counter() - start_time
        global last_test_executed
        last_test_executed = self

    def self_execute(self):
        self.my_result = f"{self.integer1}"
        if self.integer2 is not None:
            self.my_result += f" {self.integer2}"

    def check(self):
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
            output += f" executed in {self.execution_time} s\n\tIntegers:\n\t\t{self.integer1:>{integer_length}}\n\t\t{self.integer2:>{integer_length}}\n\tExpected output:\n\t\t{self.my_result:>{integer_length}}\n\tResult:\n\t\t{its_result:>{integer_length}}"
        else:
            integer_length = max([len(str(self.integer1)), len(str(self.my_result)), len(str(its_result))])
            output += f" executed in {self.execution_time} s\n\tInteger:\n\t\t{self.integer1:>{integer_length}}\n\tExpected output:\n\t\t{self.my_result:>{integer_length}}\n\tResult:\n\t\t{its_result:>{integer_length}}"

        return output


def update_output(test: Test):
    global final_output

    final_output += f"\n\n{test.check()}"


def summarise(tests: list[Test]):
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

if __name__ == "__main__":
    a = Test(method=0, integer1=235897358979834789373478923589735897983478937347897937893789373578932752378623782348683267324732682362346783246732687324673223589735897983478937347897937893789373578932752378623782348683267324732682362346783246732687324673279378937893735789327523786237823486832673247326823623467832467326873246732, integer2=128390384932489032490239832908324843299032890328903248903292478893242323589735897983478937347897937893789373578932752378623782348683267324732682362346783246732687324673258973589798347893734789793789378937357893275237862378234868326732473268236234678324673268732467327234798232348903289832982398232)
    a.execute()
    update_output(a)
    b = Test(method=0, integer1=12345)
    b.execute()
    update_output(b)
    summarise([a, b])