hello: hello.cpp
	c++ hello.cpp -o hello

goodbye: goodbye.cpp hello
	c++ goodbye.cpp -o goodbye

test1: hello goodbye
	echo "say hello then goodbye"
	./hello
	./goodbye
	echo "done"

test2: goodbye hello
	echo "say goodbye then hello"
	./goodbye
	./hello
	echo "done"

seq: seq.cpp
	c++ seq.cpp -o seq -std=c++14 -Wall

amath583.o: amath583.cpp
	c++ -c amath583.cpp -o amath583.o -std=c++14 -Wall -Wextra -pedantic

vic.o: vic.cpp
	c++ -c vic.cpp -o vic.o -std=c++14 -Wall -Wextra -pedantic

exe: vic.o amath583.o
	c++ vic.o amath583.o -o vic.exe -std=c++14 -Wall -Wextra -pedantic

genRandomVector.o: genRandomVector.cpp
	c++ -c genRandomVector.cpp -o genRandomVector.o -std=c++14 -Wall -Wextra -pedantic

genRandomVector: genRandomVector.o amath583.o
	c++ genRandomVector.o amath583.o -o genRandomVector -std=c++14 -Wall -Wextra -pedantic

vectorNorm.o: vectorNorm.cpp
	c++ -c vectorNorm.cpp -o vectorNorm.o -std=c++14 -Wall -Wextra -pedantic

vectorNorm: vectorNorm.o amath583.o
	c++ vectorNorm.o amath583.o -o vectorNorm -std=c++14 -Wall -Wextra -pedantic

testWrite.o: testWrite.cpp
	c++ -c testWrite.cpp -o testWrite.o -std=c++14 -Wall -Wextra -pedantic

testWrite: testWrite.o amath583.o
	c++ testWrite.o amath583.o -o testWrite -std=c++14 -Wall -Wextra -pedantic

dot583.o: dot583.cpp
	c++ -c dot583.cpp -o dot583.o -std=c++14 -Wall -Wextra -pedantic

dot583: dot583.o amath583.o
	c++ dot583.o amath583.o -o dot583 -std=c++14 -Wall -Wextra -pedantic

clean:
	rm -f *.o *.exe a.out

tests583: ;
	rm -rf _testdir
	mkdir _testdir
	cp ps2.tgz ./_testdir
	cp test_ps2.py ./_testdir
	cd ./_testdir &&	\
	tar -xzf ps2.tgz && \
	python test_ps2.py
