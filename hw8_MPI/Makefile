CXX		= mpic++
CXXFLAGS 	= -cxx=clang++ -std=c++11 -Wall
CXXFLAGS2 	= -fopenmp -std=c++11 -Wall

Vector.o: Vector.cpp Vector.hpp
	$(CXX) $(CXXFLAGS2) -c Vector.cpp -o Vector.o

COO.o: COO.cpp COO.hpp
	$(CXX) $(CXXFLAGS2) -c COO.cpp -o COO.o

CSR.o: CSR.cpp CSR.hpp
	$(CXX) $(CXXFLAGS2) -c CSR.cpp -o CSR.o

Matrix.o: Matrix.cpp Matrix.hpp
	$(CXX) $(CXXFLAGS) -c Matrix.cpp -o Matrix.o

bon: Vector.o Matrix.o
	$(CXX) -lpthread -std=c++11 -Wall -O3 Vector.o Matrix.o bonnie_and_clyde.cpp -o bon

rt2n_driver: Vector.o Matrix.o rt2n_driver.cpp
	$(CXX) -lpthread -std=c++11 -Wall -O3 Vector.o Matrix.o rt2n_driver.cpp -o rt2n_driver

tmv.o: tmv.cpp Vector.hpp
	$(CXX) $(CXXFLAGS) -c tmv.cpp -o tmv.o

tmv_driver: Vector.o Matrix.o tmv.o tmv_driver.cpp
	$(CXX) -lpthread -std=c++11 -Wall -O3 Vector.o Matrix.o tmv.o tmv_driver.cpp -o tmv_driver

pt2n_driver: Vector.o pt2n_driver.cpp
	$(CXX) $(CXXFLAGS2) Vector.o pt2n_driver.cpp -o pt2n_driver

coo_driver: Vector.o COO.o coo_driver.cpp
	$(CXX) $(CXXFLAGS2) Vector.o COO.o coo_driver.cpp -o coo_driver

csr_driver: Vector.o CSR.o csr_driver.cpp
	$(CXX) $(CXXFLAGS2) Vector.o CSR.o csr_driver.cpp -o csr_driver

hello: hello.o
	$(CXX) $(CXXFLAGS) hello.cpp -o hello.o

pingpong: pingpong.cpp
	$(CXX) $(CXXFLAGS) pingpong.cpp -o pingpong

ring: ring.cpp
	$(CXX) $(CXXFLAGS) ring.cpp -o ring

mpi2norm_driver: mpi2norm_driver.cpp Vector.o
	$(CXX) $(CXXFLAGS) mpi2norm_driver.cpp Vector.o -o mpi2norm_driver

mpi2norm_timer: mpi2norm_timer.cpp Vector.o
	$(CXX) $(CXXFLAGS) mpi2norm_timer.cpp Vector.o -o mpi2norm_timer


clean:
	/bin/rm -f bench bench.o Matrix.o Vector.o sparsebench sparsebench.o fail fail.o a.out bonnie_and_clyde bon bonnie_and_clyde.o pt2n_driver rt2n_driver hello.o ring.o ring

test: ;
	tar -czf ps8.tgz Makefile ring.cpp Vector.hpp Vector.cpp mpi2norm_driver.cpp mpi2norm_timer.cpp
	rm -rf _testdir
	mkdir _testdir
	cp ps8.tgz ./_testdir
	cp test_ps8.py ./_testdir
	cd ./_testdir &&	\
	tar -xzf ps8.tgz && \
	python test_ps8.py
