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

def make(target):

    print("Running 'make %s'" % target)
    if (os.system('make %s' % target) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")


def compile(fname,flags="",cflags= '-std=c++11 -Wall'):

    compileString = 'c++ ' + cflags + ' ' + flags + ' -c ' + fname + ' -o ' + fname[0:fname.find('cpp')-1] + '.o'
    print("Running '%s'" % compileString)
    if (os.system(compileString) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

def link(objNames, executable):

    linkString = 'c++ '
    for name in objNames:
        linkString += name + ' '
    linkString += '-o ' + executable

    print("Running '%s'" % linkString)
    if (os.system(linkString) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

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
    print("\n****************************")
    print("*** TESTING Exercise 3.1 ***")
    print("****************************\n")

    make('Vector.o')

    codestring = \
"""#include <iostream>
#include "Vector.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting Vector x = [1, 2]^T" << endl;
  Vector x(4);
  x(0) = 1.0;
  x(1) = 2.0;

  cout << endl << "Calling partitionedTwoNorm(x,1): ";
  cout << partitionedTwoNorm(x,1) << endl;

  return 0;

}"""
    print("Creating driver that tests partitionedTwoNorm... ",end="")
    if (os.system("echo '%s' > partitionedTwoNorm_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('partitionedTwoNorm_driver.cpp')
    link(['-pthread','Vector.o','partitionedTwoNorm_driver.o'], 'partitionedTwoNorm_driver')
    runWithArguments("partitionedTwoNorm_driver", "")

    make('pt2n_driver')
    runWithArguments('pt2n_driver', '100 4')

def test3p2():
    print("\n****************************")
    print("*** TESTING Exercise 3.2 ***")
    print("****************************\n")

    make('Vector.o')

    codestring = \
"""#include <iostream>
#include "Vector.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting Vector x = [1, 2]^T" << endl;
  Vector x(4);
  x(0) = 1.0;
  x(1) = 2.0;

  cout << endl << "Calling recursiveTwoNorm(x,1): ";
  cout << recursiveTwoNorm(x,1) << endl;

  return 0;

}"""
    print("Creating driver that tests recursiveTwoNorm... ",end="")
    if (os.system("echo '%s' > recursiveTwoNorm_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('recursiveTwoNorm_driver.cpp')
    link(['-pthread','Vector.o','recursiveTwoNorm_driver.o'], 'recursiveTwoNorm_driver')
    runWithArguments("recursiveTwoNorm_driver", "")

    make('rt2n_driver')
    runWithArguments('rt2n_driver', '100 4')

def test3p3():
    print("\n****************************")
    print("*** TESTING Exercise 3.3 ***")
    print("****************************\n")

    make('Vector.o')
    make('tmv.o')
    make('Matrix.o')

    codestring = \
"""#include <iostream>
#include "Vector.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting Matrix A(0,0) = 1, A(0,1) = 2, A(1,0) = 3, A(1,1) = 4" << endl;
  Matrix A(2,2);
  A(0,0) = 1.0;
  A(0,1) = 2.0;
  A(1,0) = 3.0;
  A(1,1) = 4.0;

  cout << endl << "Setting Vector x(0) = 1, x(0) = 2" << endl;
  Vector x(2);
  x(0) = 1;
  x(1) = 2;

  cout << endl << "Calling task_matvec(A,x,y,1): " << endl;
  Vector y(2);
  zeroize(y);
  task_matvec(A,x,y,1);

  for (int i=0; i < y.numRows(); i++)
  {
    cout << y(i) << endl;
  }
  return 0;

}"""
    print("Creating driver that tests task_matvec... ",end="")
    if (os.system("echo '%s' > task_matvec_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('task_matvec_driver.cpp')
    link(['-pthread','Vector.o','tmv.o','task_matvec_driver.o'], 'task_matvec_driver')
    runWithArguments("task_matvec_driver", "")

    make('tmv_driver')
    runWithArguments('tmv_driver', '100 4')

def test3p4():

    print("\n************************")
    print("*** TESTING Exercise 3.4 ***")
    print("************************\n")

    print("Reading ex5.txt...\n")
    if (not os.path.isfile("ex5.txt")):
        print("not found")
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    os.system("cat ex5.txt")

    print('----------\n')

###############################################################################
if __name__ == "__main__":

    script = \
"""Select Test to Run

0) All
1) Exercise 3.1
2) Exercise 3.2
3) Exercise 3.4 (Written)
4) Exercise 3.3 (583 Only)

... (q to quit):
"""

    unpacktar("ps5.tgz")
    response = raw_input(script)
    while (response != "q"):
        if (response == "1" or response == "0"):
            test3p1()
        if (response == "2" or response == "0"):
            test3p2()
        if (response == "3" or response == "0"):
            test3p4()
        if (response == "4" or response == "0"):
            test3p3()
        response = raw_input(script)
