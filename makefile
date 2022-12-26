all: compile run

compile:
	g++ -g parser.cpp

run:
	./a.out

clean:
	$(RM) a.out
