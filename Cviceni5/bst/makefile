tree: bst.o tree.o
    gcc bst.o tree.o -o tree

bst.o: bst.c
    gcc -c bst.c -Wall -Wextra -pedantic -ansi

tree.o: tree.c
    gcc -c tree.c -Wall -Wextra -pedantic -ansi

clean:
    rm *.o tree -f