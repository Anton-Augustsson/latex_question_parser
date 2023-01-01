all: compile run

compile:
	g++ -g main.cpp

run:
	./a.out

clean:
	$(RM) a.out
