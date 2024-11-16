# /bin/sh
make clean
make
valgrind -s --leak-check=full ./iplot 