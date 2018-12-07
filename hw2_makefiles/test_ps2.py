from __future__ import print_function
import os, sys

def unpacktar(fname):
    print("Unpacking %s into _testdir..." % fname, end="")
    if (not os.path.isfile(fname)):
        print("%s not found" % fname)
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()

    os.system("rm -rf _testdir")
    os.system("mkdir _testdir")
    os.system("cp %s ./_testdir" % fname)
    os.chdir("_testdir")
    os.system("tar -xzf %s" % fname)

    print("done\n")

    print("Checking for Makefile... ", end="")
    if (not os.path.isfile("Makefile")):
        print("not found")
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("found\n")

def runWithArguments(executable, arguments):
    print("\n----------")
    print("Running '%s %s'\n" % (executable, arguments))
    print("your program output is\n")
    val = os.system("./%s %s" % (executable, arguments))
    print("----------\n")

def runWithInput(executable,inputString):
    print('\n----------')
    print("Running '%s'\n" % executable)
    print("For input\n\n%s\n" % inputString)
    print("your program output is\n")
    val = os.system("echo '%s' | ./%s" % (inputString,executable))
    print('----------\n')

def test3p1():
    print("\n*********************")
    print("*** TESTING Exercise 3.1 ***")
    print("*********************\n")

    print("Running 'make seq'... ")
    if (os.system("make seq") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    runWithArguments("seq", "")
    runWithArguments("seq", "4")
    runWithArguments("seq", "4 -o seq_test_output.txt")
    runWithArguments("seq", "4 -o")

def test3p2():
    print("\n*********************")
    print("*** TESTING Exercise 3.2 ***")
    print("*********************\n")

    print("Running 'make amath583.o'... ")
    if (os.system("make amath583.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    print("Creating driver that tests readVector(std::cin)... ",end="")
    codestring = \
"""#include <iostream>
#include <vector>
#include "amath583.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
  double sum;
  vector<double> v = readVector(cin);

  sum = 0.0;
  for (unsigned i = 0;
        i < v.size(); i++)
    sum += v[i];

  cout << sum << endl;

  return 0;

}"""
    if (os.system("echo '%s' > amath583_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    print("\nCompiling driver and linking with amath583.o... ",end="")
    if (os.system("c++ -c amath583_driver.cpp -o amath583_driver.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    if (os.system("c++ amath583_driver.o amath583.o -o amath583_test") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")
    inputString = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    runWithInput("amath583_test",inputString)

    inputString = \
"""INCORRECT HEADER
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    runWithInput("amath583_test",inputString)

    inputString = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
INCORRECT TRAILER"""
    runWithInput("amath583_test",inputString)

    print('Creating driver that tests readVector("test_vector.txt") and test_vector.txt... ',end="")
    codestring = \
"""#include <iostream>
#include <vector>
#include "amath583.hpp"

using std::cout;
using std::endl;
using std::vector;

int main()
{
  double sum;
  vector<double> v = readVector("test_vector.txt");

  sum = 0.0;
  for (unsigned i = 0;
        i < v.size(); i++)
    sum += v[i];

  cout << sum << endl;

  return 0;

}"""
    if (os.system("echo '%s' > amath583_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()

    vectorString = \
"""AMATH 583 VECTOR
6
0.4
-1.3
2.141
3.14159
4.0
5
THIS IS THE END"""
    if (os.system("echo '%s' > test_vector.txt" % vectorString) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    print("\nCompiling driver and linking with amath583.o... ",end="")
    if (os.system("c++ -c amath583_driver.cpp -o amath583_driver.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    if (os.system("c++ amath583_driver.o amath583.o -o amath583_test") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    runWithArguments("amath583_test","")

def test3p3():
    print("\n*********************")
    print("*** TESTING Exercise 3.3 ***")
    print("*********************\n")

    print("Running 'make genRandomVector'... ")
    if (os.system("make genRandomVector") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    runWithArguments("genRandomVector","5")
    runWithArguments("genRandomVector","")

def test3p4():
    print("\n*********************")
    print("*** TESTING Exercise 3.4 ***")
    print("*********************\n")

    print("Running 'make amath583.o'... ")
    if (os.system("make amath583.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    print("")

    print("Creating driver that tests twoNorm([1.0,2.0,3.0])... ",end="")
    codestring = \
"""#include <iostream>
#include <vector>
#include "amath583.hpp"

using std::cout;
using std::endl;
using std::vector;

int main()
{
  double sum;
  vector<double> v(3);
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;

  cout << twoNorm(v) << endl;

  return 0;

}"""
    if (os.system("echo '%s' > amath583_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    print("\nCompiling driver and linking with amath583.o... ",end="")
    if (os.system("c++ -c amath583_driver.cpp -o amath583_driver.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    if (os.system("c++ amath583_driver.o amath583.o -o amath583_test") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    runWithArguments("amath583_test","")

    print("Running 'make vectorNorm'... ")
    if (os.system("make vectorNorm") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    runWithArguments("vectorNorm","10")
    runWithArguments("vectorNorm","1000")
    runWithArguments("vectorNorm","100000")


def test3p5():
    print("\n*********************")
    print("*** TESTING Exercise 3.5 ***")
    print("*********************\n")

    print("Running 'make amath583.o'... ")
    if (os.system("make amath583.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    print("Creating driver that tests writeVector(std::cout)... ",end="")
    codestring = \
"""#include <iostream>
#include <vector>
#include "amath583.hpp"

using std::cout;
using std::endl;
using std::vector;

int main()
{
  double sum;
  vector<double> v(3);
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;

  writeVector(v,cout);

  return 0;

}"""
    if (os.system("echo '%s' > amath583_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    print("\nCompiling driver and linking with amath583.o... ",end="")
    if (os.system("c++ -c amath583_driver.cpp -o amath583_driver.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    if (os.system("c++ amath583_driver.o amath583.o -o amath583_test") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    runWithArguments("amath583_test","")

    print('Creating driver that tests writeVector("test_output.txt")... ',end="")
    codestring = \
"""#include <iostream>
#include <vector>
#include "amath583.hpp"

using std::vector;

int main()
{
  double sum;
  vector<double> v(3);
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;

  writeVector(v,"test_output.txt");

  return 0;

}"""
    if (os.system("echo '%s' > amath583_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    print("\nCompiling driver and linking with amath583.o... ",end="")
    if (os.system("c++ -c amath583_driver.cpp -o amath583_driver.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    if (os.system("c++ amath583_driver.o amath583.o -o amath583_test") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    runWithArguments("amath583_test","")

def test3p6():
    print("\n*********************")
    print("*** TESTING Exercise 3.6 ***")
    print("*********************\n")

    print("Running 'make amath583.o'... ")
    if (os.system("make amath583.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    print("Creating driver that tests dot583([1.0,2.0],[3.0,4.0])... ",end="")
    codestring = \
"""#include <iostream>
#include <vector>
#include "amath583.hpp"

using std::cout;
using std::endl;
using std::vector;

int main()
{
  double sum;
  vector<double> v1(2);
  v1[0] = 1.0;
  v1[1] = 2.0;
  vector<double> v2(2);
  v2[0] = 3.0;
  v2[1] = 4.0;

  cout << dot583(v1,v2) << endl;

  return 0;

}"""
    if (os.system("echo '%s' > amath583_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    print("\nCompiling driver and linking with amath583.o... ",end="")
    if (os.system("c++ -c amath583_driver.cpp -o amath583_driver.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    if (os.system("c++ amath583_driver.o amath583.o -o amath583_test") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    runWithArguments("amath583_test","")

    print("Creating driver that tests dot583([1.0,2.0],[3.0])... ",end="")
    codestring = \
"""#include <iostream>
#include <vector>
#include "amath583.hpp"

using std::cout;
using std::endl;
using std::vector;

int main()
{
  double sum;
  vector<double> v1(2);
  v1[0] = 1.0;
  v1[1] = 2.0;
  vector<double> v2(1);
  v2[0] = 3.0;

  cout << dot583(v1,v2) << endl;

  return 0;

}"""
    if (os.system("echo '%s' > amath583_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    print("\nCompiling driver and linking with amath583.o... ",end="")
    if (os.system("c++ -c amath583_driver.cpp -o amath583_driver.o") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    if (os.system("c++ amath583_driver.o amath583.o -o amath583_test") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    runWithArguments("amath583_test","")

    print("Running 'make dot583'... ")
    if (os.system("make dot583") != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

    runWithArguments("dot583","4")
    runWithArguments("dot583","")


def test3p7():

    print("\n************************")
    print("*** TESTING Exercise 3.7 ***")
    print("************************\n")

    print("Checking for ex2.txt... ", end="")
    if (not os.path.isfile("ex2.txt")):
        print("not found")
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("found\n")

    print("Reading ex2.txt...\n")
    os.system("cat ex2.txt")

    print('----------\n')

###############################################################################
if __name__ == "__main__":

    script = \
"""Select Test to Run

0) All
1) Exercise 3.1
2) Exercise 3.2
3) Exercise 3.3
4) Exercise 3.4
5) Exercise 3.5
6) Exercise 3.7 (Written)
7) Exercise 3.6 (583 Only)

... (q to quit):
"""

    unpacktar("ps2.tgz")
    response = raw_input(script)
    while (response != "q"):
        if (response == "1" or response == "0"):
            test3p1()
        if (response == "2" or response == "0"):
            test3p2()
        if (response == "3" or response == "0"):
            test3p3()
        if (response == "4" or response == "0"):
            test3p4()
        if (response == "5" or response == "0"):
            test3p5()
        if (response == "6" or response == "0"):
            test3p7()
        if (response == "7" or response == "0"):
            test3p6()
        response = raw_input(script)
