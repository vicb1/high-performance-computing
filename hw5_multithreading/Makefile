CXX		= c++
CXXFLAGS 	= -Ofast -march=native -DNDEBUG -std=c++11 -Wc++11-extensions -Wall -O3

Vector.o: Vector.cpp Vector.hpp
	$(CXX) $(CXXFLAGS) -Wall -c Vector.cpp -o Vector.o

Matrix.o: Matrix.cpp Matrix.hpp
	$(CXX) $(CXXFLAGS) -c Matrix.cpp -o Matrix.o

bon: Vector.o Matrix.o
	$(CXX) -lpthread -std=c++11 -Wall -O3 Vector.o Matrix.o bonnie_and_clyde.cpp -o bon

pt2n_driver: Vector.o Matrix.o pt2n_driver.cpp
	$(CXX) -lpthread -std=c++11 -Wall -O3 Vector.o Matrix.o pt2n_driver.cpp -o pt2n_driver

rt2n_driver: Vector.o Matrix.o rt2n_driver.cpp
	$(CXX) -lpthread -std=c++11 -Wall -O3 Vector.o Matrix.o rt2n_driver.cpp -o rt2n_driver

tmv.o: tmv.cpp Vector.hpp
	$(CXX) $(CXXFLAGS) -c tmv.cpp -o tmv.o

tmv_driver: Vector.o Matrix.o tmv.o tmv_driver.cpp
	$(CXX) -lpthread -std=c++11 -Wall -O3 Vector.o Matrix.o tmv.o tmv_driver.cpp -o tmv_driver


clean:
	/bin/rm -f bench bench.o Matrix.o Vector.o sparsebench sparsebench.o fail fail.o a.out bonnie_and_clyde bon bonnie_and_clyde.o pt2n_driver rt2n_driver

test: ;
	tar -czf ps5.tgz ex5.txt Makefile Vector.cpp Vector.hpp Matrix.cpp Matrix.hpp pt2n_driver.cpp bandwidth.png roofline.pdf rt2n_driver.cpp tmv.cpp tmv_driver.cpp
	rm -rf _testdir
	mkdir _testdir
	cp ps5.tgz ./_testdir
	cp test_ps5.py ./_testdir
	cd ./_testdir &&	\
	tar -xzf ps5.tgz && \
	python test_ps5.py
