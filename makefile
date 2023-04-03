all: clean compile run

test: clean compile_tests run_tests

compile:
	g++ -g main.cpp -o main

compile_tests:
	g++ -g unit_tests/tests.cpp -o tests

run:
	./main f unit_tests/test_file.tex

run_tests:
	./tests

debug: compile
	gdb --args main f unit_tests/test_file.tex

clean:
	$(RM) a.out
