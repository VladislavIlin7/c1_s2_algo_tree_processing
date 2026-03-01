clear_data:
	del *.exe

build_files:
	gcc -o main main.c tree.c
	gcc -o tests tests.c tree.c

run:
	./main.exe

test:
	./tests.exe

main: build_files run clear_data

test_all: build_files test clear_data
