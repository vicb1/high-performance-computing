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

    codestring = \
"""#include <iostream>
#include "Matrix.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting 2x2 Matrix A(0,0) = 1, A(0,1) = 2, A(1,0) = 3, A(1,1) = 4" << endl;
  Matrix A(2,2);
  A(0,0) = 1.0;
  A(0,1) = 2.0;
  A(1,0) = 3.0;
  A(1,1) = 4.0;

  cout << "A =" << endl;
  for (int i=0; i < A.numRows(); i++)
  {
    for (int j=0; j < A.numCols(); j++)
    {
      cout << A(i,j) << " ";
    }
    cout << endl;
  }

  cout << endl << "Computing A*A*A" << endl;
  Matrix B(2,2);
  B = A * A * A;

  cout << "A*A =" << endl;
  for (int i=0; i < B.numRows(); i++)
  {
    for (int j=0; j < B.numCols(); j++)
    {
      cout << B(i,j) << " ";
    }
    cout << endl;
  }
  return 0;

}"""
    print("Creating driver that tests Matrix... ",end="")
    if (os.system("echo '%s' > matrix_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('Matrix.cpp')
    compile('matrix_driver.cpp')
    link(['Matrix.o','matrix_driver.o'], 'matrix_driver')
    runWithArguments("matrix_driver", "")

    compile('Matrix.cpp','-DALTMATRIX')
    compile('matrix_driver.cpp','-DALTMATRIX')
    link(['Matrix.o','matrix_driver.o'], 'matrix_driver')
    runWithArguments("matrix_driver", "")


def test3p2():
    print("\n****************************")
    print("*** TESTING Exercise 3.2 ***")
    print("****************************\n")

    codestring = \
"""#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting 2x2 Matrix A(0,0) = 1, A(0,1) = 2, A(1,0) = 3, A(1,1) = 4" << endl;
  Matrix A(2,2);
  A(0,0) = 1.0;
  A(0,1) = 2.0;
  A(1,0) = 3.0;
  A(1,1) = 4.0;

  cout << endl << "Setting 2x1 Vector x(0) = 1, x(0) = 2" << endl;
  Vector x(2);
  x(0) = 1;
  x(1) = 2;

  cout << "x =" << endl;
  for (int i=0; i < x.numRows(); i++)
  {
    cout << x(i) << endl;
  }

  cout << endl << "Computing A*x" << endl;
  Vector y(2);
  y = A*x;

  cout << "A*x =" << endl;
  for (int i=0; i < y.numRows(); i++)
  {
    cout << y(i) << endl;
  }
  return 0;

}"""
    print("Creating driver that tests Vector/amath583... ",end="")
    if (os.system("echo '%s' > vector_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('amath583.cpp')
    compile('Vector.cpp')
    compile('Matrix.cpp')
    compile('vector_driver.cpp')
    link(['amath583.o','Vector.o','Matrix.o','vector_driver.o'],'vector_driver')
    runWithArguments("vector_driver", "")

def test3p3():
    print("\n****************************")
    print("*** TESTING Exercise 3.3 ***")
    print("****************************\n")

    compile('amath583.cpp','-O3')
    compile('Vector.cpp','-O3')
    compile('Matrix.cpp','-O3')
    compile('bench.cpp','-O3')
    link(['amath583.o','Vector.o','Matrix.o','bench.o'],'bench')
    runWithArguments("bench","multMVinner 16")
    runWithArguments("bench","multMVouter 16")
    runWithArguments("bench","multMVstudent 16")

def test3p4():
    print("\n****************************")
    print("*** TESTING Exercise 3.4 ***")
    print("****************************\n")

    compile('Matrix.cpp','-Ofast -march=native -DNDEBUG')
    compile('ps4bex1.cpp','-Ofast -march=native -DNDEBUG')
    link(['Matrix.o','ps4bex1.o'],'ps4bex1')
    runWithArguments("ps4bex1","| tee output.txt")

    f = open('output.txt')
    lines = f.readlines()
    f.close()

    for line in lines[1:]:
        words = line.split()
        print ("For '%s' with %d loop-ops, you reported an achieved flop count of %e" % (words[0],float(words[3]),float(words[8])))

    print('----------\n')


def test3p5():
    print("\n****************************")
    print("*** TESTING Exercise 3.5 ***")
    print("****************************\n")

    compile('Vector.cpp','-Ofast -march=native -DNDEBUG')
    compile('COO.cpp','-Ofast -march=native -DNDEBUG')
    compile('ps4bex2.cpp','-Ofast -march=native -DNDEBUG')
    link(['Vector.o','COO.o','ps4bex2.o'],'ps4bex2')
    runWithArguments("ps4bex2","| tee output.txt")

    f = open('output.txt')
    lines = f.readlines()
    f.close()

    for line in lines[1:]:
        words = line.split()
        print ("For '%s' with %d loop-ops, you reported an achieved flop count of %e" % (words[0],float(words[3]),float(words[8])))

    print('----------\n')

def test3p6():
    print("\n****************************")
    print("*** TESTING Exercise 3.6 ***")
    print("****************************\n")

    codestring = \
"""#include <iostream>
#include "COO.hpp"
#include "Vector.hpp"

using std::cout;
using std::endl;

int main()
{
  cout << "Setting 2x2 Matrix A(0,0) = 1, A(0,1) = 2, A(1,0) = 3, A(1,1) = 4 in COO format" << endl;
  COOMatrix A(2,2);
  A.push_back(0,0,1.0);
  A.push_back(0,1,2.0);
  A.push_back(1,0,3.0);
  A.push_back(1,1,4.0);

  A.streamMatrix(cout);

  cout << endl << "Setting 2x1 Vector x(0) = 1, x(0) = 2" << endl;
  Vector x(2);
  x(0) = 1;
  x(1) = 2;

  cout << endl << "Computing transpose(A)*x" << endl;
  Vector y(2);
  A.trMatvec(x,y);

  cout << "transpose(A)*x =" << endl;
  for (int i=0; i < y.numRows(); i++)
  {
    cout << y(i) << endl;
  }
  return 0;

}"""
    print("Creating driver that tests COO... ",end="")
    if (os.system("echo '%s' > COO_driver.cpp" % codestring) != 0):
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    print("done")

    compile('Vector.cpp')
    compile('amath583.cpp')
    compile('COO.cpp',cflags="-std=c++11")
    compile('COO_driver.cpp')
    link(['Vector.o','amath583.o','COO.o','COO_driver.o'],'COO_driver')
    runWithArguments("COO_driver", "")



def test3p7():

    print("\n************************")
    print("*** TESTING Exercise 3.7 ***")
    print("************************\n")

    print("Reading ps4ex3.txt...\n")
    if (not os.path.isfile("ps4ex3.txt")):
        print("not found")
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    os.system("cat ps4ex3.txt")

    print('----------\n')


def test3p8():

    print("\n************************")
    print("*** TESTING Exercise 3.8 ***")
    print("************************\n")

    print("Reading ex4.txt...\n")
    if (not os.path.isfile("ex4.txt")):
        print("not found")
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    os.system("cat ex4.txt")

    print('----------\n')

def test3p9():

    print("\n************************")
    print("*** TESTING Exercise 3.9 ***")
    print("************************\n")

    print("Reading ps4exec.txt...\n")
    if (not os.path.isfile("ps4exec.txt")):
        print("not found")
        print("\n!!! TEST FAILED !!!\n")
        sys.exit()
    os.system("cat ps4exec.txt")

    print('----------\n')


###############################################################################
if __name__ == "__main__":

    script = \
"""Select Test to Run

0) All
1) Exercise 3.1
2) Exercise 3.2
3) Exercise 3.4
4) Exercise 3.5
5) Exercise 3.6
6) Exercise 3.8 (Written)
7) Exercise 3.3 (583 Only)
8) Exercise 3.7 (583 Only)
9) Exercise 3.9 (Extra Credit)

... (q to quit):
"""

    unpacktar("ps4.tgz")
    response = raw_input(script)
    while (response != "q"):
        if (response == "1" or response == "0"):
            test3p1()
        if (response == "2" or response == "0"):
            test3p2()
        if (response == "3" or response == "0"):
            test3p4()
        if (response == "4" or response == "0"):
            test3p5()
        if (response == "5" or response == "0"):
            test3p6()
        if (response == "6" or response == "0"):
            test3p8()
        if (response == "7" or response == "0"):
            test3p3()
        if (response == "8" or response == "0"):
            test3p7()
        if (response == "9" or response == "0"):
            test3p9()
        response = raw_input(script)
