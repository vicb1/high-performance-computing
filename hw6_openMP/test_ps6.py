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


def compile(fname,flags="",cflags= '-std=c++11 -Wall -fopenmp'):

    compileString = 'c++ ' + cflags + ' ' + flags + ' -c ' + fname + ' -o ' + fname[0:fname.find('cpp')-1] + '.o'
    print("Running '%s'" % compileString)
    if (os.system(compileString) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("")

def link(objNames,executable,lflags='-fopenmp'):

    linkString = 'c++ ' + lflags + ' '
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
  Vector x(2);
  x(0) = 1.0;
  x(1) = 2.0;

  cout << endl << "Calling ompTwoNorm(x): ";
  cout << ompTwoNorm(x) << endl;

  return 0;

}"""
    print("Creating driver that tests ompTwoNorm... ",end="")
    if (os.system("echo '%s' > ompTwoNorm_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('ompTwoNorm_driver.cpp')
    link(['Vector.o','ompTwoNorm_driver.o'], 'ompTwoNorm_driver')
    runWithArguments("ompTwoNorm_driver", "")

    make('pt2n_driver')
    runWithArguments('pt2n_driver', '10000 1000')

def test3p2():
    print("\n****************************")
    print("*** TESTING Exercise 3.2 ***")
    print("****************************\n")

    make('Vector.o')
    make('COO.o')

    codestring = \
"""#include <iostream>
#include "COO.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting Matrix A such that A(0,0) = 1, A(0,1) = 2, A(1,0) = 3, A(1,1) = 0" << endl;

  COOMatrix A(2,2);
  A.push_back(0,0,1.0);
  A.push_back(0,1,2.0);
  A.push_back(1,0,3.0);

  cout << "Setting Vector x = [1, 2]^T" << endl;
  Vector x(2);
  x(0) = 1.0;
  x(1) = 2.0;

  Vector y(2);
  zeroize(y);
  cout << endl << "Calling ompMatvec(A,x,y)" << endl;
  ompMatvec(A,x,y);
  cout << "Result y is" << endl;

  for (unsigned int i=0; i < y.numRows(); i++)
  {
    cout << y(i) << endl;
  }

  return 0;

}"""
    print("Creating driver that tests ompMatvec... ",end="")
    if (os.system("echo '%s' > ompMatvec_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('ompMatvec_driver.cpp')
    link(['Vector.o','COO.o','ompMatvec_driver.o'], 'ompMatvec_driver')
    runWithArguments("ompMatvec_driver", "")

    make('coo_driver')
    runWithArguments('coo_driver', '10000')


def test3p3():
    print("\n****************************")
    print("*** TESTING Exercise 3.3 ***")
    print("****************************\n")

    make('Vector.o')
    make('CSR.o')

    codestring = \
"""#include <iostream>
#include "CSR.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting Matrix A such that A(0,0) = 1, A(0,1) = 2, A(1,0) = 3, A(1,1) = 0" << endl;

  CSRMatrix A(2,2);
  A.openForPushBack();
  A.push_back(0,0,1.0);
  A.push_back(0,1,2.0);
  A.push_back(1,0,3.0);
  A.closeForPushBack();

  cout << "Setting Vector x = [1, 2]^T" << endl;
  Vector x(2);
  x(0) = 1.0;
  x(1) = 2.0;

  Vector y(2);
  zeroize(y);
  cout << endl << "Calling ompMatvec(A,x,y)" << endl;
  ompMatvec(A,x,y);
  cout << "Result y is" << endl;

  for (unsigned int i=0; i < y.numRows(); i++)
  {
    cout << y(i) << endl;
  }

  return 0;

}"""
    print("Creating driver that tests ompMatvec... ",end="")
    if (os.system("echo '%s' > ompMatvec_driver2.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('ompMatvec_driver2.cpp')
    link(['Vector.o','CSR.o','ompMatvec_driver2.o'], 'ompMatvec_driver2')
    runWithArguments("ompMatvec_driver2", "")

    make('csr_driver')
    runWithArguments('csr_driver', '10000')

###############################################################################
if __name__ == "__main__":

    script = \
"""Select Test to Run

0) All
1) Exercise 3.1
2) Exercise 3.2
3) Exercise 3.3 (583 Only)

... (q to quit):
"""

    unpacktar("ps6.tgz")
    response = raw_input(script)
    while (response != "q"):
        if (response == "1" or response == "0"):
            test3p1()
        if (response == "2" or response == "0"):
            test3p2()
        if (response == "3" or response == "0"):
            test3p3()
        response = raw_input(script)
