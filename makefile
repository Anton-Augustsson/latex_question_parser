all: clean compile run

compile:
	g++ -g main.cpp

run:
	./a.out f test.tex

clean:
	$(RM) a.out
