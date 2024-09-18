VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all 

all: main hello race singleton guard

singleton: singleton.cpp
	g++ -o singleton singleton.cpp
	
guard: guard.cpp
	g++ -o guard guard.cpp

main: main.cpp
	g++ -fprofile-arcs -ftest-coverage -pg -g -o main main.cpp

hello: hello.c
	gcc -g -o hello hello.c
	
race: race.c
	gcc -g -pthread -o race race.c
	
racegrind: race
	valgrind --tool=helgrind ./race > helgrind_report 2>&1
	
valgdb: hello
	valgrind --tool=memcheck --vgdb=yes --vgdb-error=0 ./hello some chosen string
	
cvalgrind: hello
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./hello some chosen string > vallgrind_hello_report 2>&1
	
valgrind: main
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./main -v 5 -e 10 -s 2 > valgrind_memcheck_report.txt 2>&1 
	
callgrind: main
	valgrind --tool=callgrind ./main -v 5 -e 10 -s 2 > valgrind_callgraph_report.txt 2>&1 
	
	
.PHONY: valgrind callgrind all 


clean: 
	rm -f main race hello guard singleton main.gcno *.gcov *.gcda *.out


