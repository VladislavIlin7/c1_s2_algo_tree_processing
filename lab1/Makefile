clear_data:
	del *.exe

build_files:
	gcc -o main.exe main.c tree.c
	gcc -o tests.exe tests.c tree.c

main:
	main.exe

test:
	tests.exe

run_main: build_files main clear_data

run_test: build_files test clear_data