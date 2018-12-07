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
    val = os.system("mpirun -np 4 ./%s %s" % (executable, arguments))
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

    make('ring')

    runWithArguments("ring", "")

def test3p2():
    print("\n****************************")
    print("*** TESTING Exercise 3.2 ***")
    print("****************************\n")

    make('mpi2norm_driver')
    runWithArguments("mpi2norm_driver", "100")

def test3p3():
    print("\n****************************")
    print("*** TESTING Exercise 3.3 ***")
    print("****************************\n")

    make('mpi2norm_timer')
    runWithArguments('mpi2norm_timer', '100')

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

    unpacktar("ps8.tgz")
    response = raw_input(script)
    while (response != "q"):
        if (response == "1" or response == "0"):
            test3p1()
        if (response == "2" or response == "0"):
            test3p2()
        if (response == "3" or response == "0"):
            test3p3()
        response = raw_input(script)
