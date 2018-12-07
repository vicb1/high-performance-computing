from __future__ import print_function
import os, sys

def checkForFile(fname):
    print("Checking for %s... " % fname, end="")
    if (not os.path.isfile(fname)):
        print("%s not found" % fname)
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("found\n")


def promptUser():
    if (raw_input("Type q to quit, any other key to continue... ") is 'q'):
        sys.exit()

def sendInput(inputstring):
    print('\n----------')
    print("For input\n\n%s\n" % inputstring)
    print("your program output is\n")
    val = os.system("echo '%s' | ./a.out" % inputstring)
    print('----------\n')

def test_N():
    print("\n*********************")
    print("*** TESTING N.cpp ***")
    print("*********************\n")

    checkForFile('N.cpp')
    print("Compiling and running N.cpp... ")
    if (os.system("c++ N.cpp") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()

    sendInput('10')
    promptUser()

    sendInput('-2')

def test_vsum():
    print("\n************************")
    print("*** TESTING vsum.cpp ***")
    print("************************\n")

    checkForFile('vsum.cpp')
    print("Compiling and running vsum.cpp... ")
    if (os.system("c++ vsum.cpp") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()

    inputstring = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    sendInput(inputstring)
    promptUser()

    inputstring = \
"""INCORRECT HEADER
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    sendInput(inputstring)
    promptUser()

    inputstring = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
INCORRECT TRAILER"""
    sendInput(inputstring)

def test_vector():
    print("\n***************************")
    print("*** TESTING vector.cpp ***")
    print("***************************\n")

    checkForFile('vector.cpp')

    print("Creating vector_driver.cpp... ")
    codestring = \
"""#include <iostream>
#include <vector>

std::vector<double> readVector();

int main()
{
  double sum;
  std::vector<double> double_vector = readVector();

  sum = 0.0;
  for (std::vector<double>::iterator vals = double_vector.begin();
        vals != double_vector.end(); vals++)
    sum += *vals;

  std::cout << sum << std::endl;

  return 0;

}"""
    if (os.system("echo '%s' > vector_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()

    print("\nCompiling and running vector_driver.cpp and vector.cpp...",)
    if (os.system("c++ vector_driver.cpp vector.cpp") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()

    inputstring = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    sendInput(inputstring)
    promptUser()

    inputstring = \
"""INCORRECT HEADER
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    sendInput(inputstring)
    promptUser()

    inputstring = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
INCORRECT TRAILER"""
    sendInput(inputstring)


def test_vsum2():

    print("\n*************************")
    print("*** TESTING vsum2.cpp ***")
    print("*************************\n")

    checkForFile('vsum2.cpp')
    checkForFile('vector.cpp')

    print("Compiling and running vsum2.cpp and vector.cpp... ")
    if (os.system("c++ vsum2.cpp vector.cpp") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()

    inputstring = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    sendInput(inputstring)

def test_written():

    print("\n************************")
    print("*** TESTING ex1.txt ***")
    print("************************\n")

    checkForFile('ex1.txt')

    print("Reading ex1.txt...\n")
    os.system("cat ex1.txt")

if __name__ == "__main__":
    # 483/583 Tests
    test_N()
    promptUser()
    test_vsum()
    promptUser()

    # 583 Tests
    if (sys.argv[1] == 'True'):
        test_vector()
        promptUser()
        test_vsum2()
        promptUser()

    test_written()
    print("")
