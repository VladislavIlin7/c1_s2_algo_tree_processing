clear_data:
	del *.exe

build_main:
	gcc -o main.exe main.c func.c
build_tests:
	gcc -o tests.exe tests.c func.c

main:
	main.exe

test:
	tests.exe

run_main: build_main main clear_data

run_test: build_tests test clear_data