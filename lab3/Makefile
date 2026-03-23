clear_data:
	del *.exe

build_main:
	gcc -o main.exe main.c parser.c tree.c stacks.c
build_tests:
	gcc -o tests.exe tests.c parser.c tree.c stacks.c

main:
	main.exe

test:
	tests.exe

run_main: build_main main clear_data

run_test: build_tests test clear_data