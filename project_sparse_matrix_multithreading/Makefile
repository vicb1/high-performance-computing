CXX		= c++
CXXFLAGS 	= -Ofast -march=native -DNDEBUG -std=c++11 -Wc++11-extensions -Wall -O3

matvec: matvec.cpp COO.o Vector.o Matrix.o
	$(CXX) $(CXXFLAGS) matvec.cpp -o matvec

bench: bench.o Matrix.o
	$(CXX) $(CXXFLAGS) bench.o Matrix.o -o bench

sparsebench: sparsebench.o COO.o Vector.o Matrix.o
	$(CXX) $(CXXFLAGS) sparsebench.o COO.o -o sparsebench

bench.o: bench.cpp Matrix.hpp
	$(CXX) $(CXXFLAGS) -c bench.cpp -o bench.o

sparsebench.o: sparsebench.cpp COO.hpp
	$(CXX) $(CXXFLAGS) -c sparsebench.cpp -o sparsebench.o

COO.o: COO.cpp COO.hpp
	$(CXX) $(CXXFLAGS) -c COO.cpp -o COO.o

Matrix.o: Matrix.cpp Matrix.hpp
	$(CXX) $(CXXFLAGS) -c Matrix.cpp -o Matrix.o

Vector.o: Vector.cpp Vector.hpp
	$(CXX) $(CXXFLAGS) -c Vector.cpp -o Vector.o

AOSCOO.o: AOSCOO.hpp
	$(CXX) $(CXXFLAGS) -c AOSCOO.hpp -o COO.o

AOSTest: AOSTest.cpp AOSCOO.o
	$(CXX) $(CXXFLAGS) AOSTest.cpp -o AOSTest

aosmatvec: aosmatvec.cpp AOSCOO.o Vector.o Matrix.o
	$(CXX) $(CXXFLAGS) aosmatvec.cpp -o aosmatvec

CSCMatrix.o: CSCMatrix.hpp
	$(CXX) $(CXXFLAGS) -c CSCMatrix.hpp -o CSCMatrix.o

CSCTest: CSCTest.cpp CSCMatrix.o
	$(CXX) $(CXXFLAGS) CSCTest.cpp -o CSCTest

cscmatvec: cscmatvec.cpp CSCMatrix.o Vector.o Matrix.o
	$(CXX) $(CXXFLAGS) cscmatvec.cpp -o cscmatvec

clean:
	/bin/rm -f bench bench.o Matrix.o Vector.o sparsebench sparsebench.o fail fail.o a.out matvec matvec.o
