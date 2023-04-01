all: clean compile_tests run_tests clean compile run

compile:
	g++ -g main.cpp -o main

compile_tests:
	g++ -g unit_tests/tests.cpp -o tests

run:
	./main f unit_tests/test_file.tex

run_tests:
	./tests

clean:
	$(RM) a.out
