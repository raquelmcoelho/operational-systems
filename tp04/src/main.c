/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * Unix System Programming
 * Chapter "Threads"
 *
 * 2016 Alain Lebret (alain.lebret@ensicaen.fr)
 */

#include <stdio.h>
#include <stdlib.h>
#include <matrix.h>

int main(void) 
{
	matrix_t *m1;
	matrix_t *m2;

	m1 = init_matrix(SIZE, SIZE, 1);
	m2 = init_matrix(SIZE, SIZE, 1);

	if (PRINT) {
		printf("Matrix m1\n");
		print_matrix(m1);
		printf("\nMatrix m2\n");
		print_matrix(m2);
	}

	printf("\n======== Mono   Thread ========\n");
	mono_thread(m1, m2);

	printf("\n======== Multi Threads ========\n\n");
	multi_threads(m1, m2);

	free_matrix(m1->matrix);
	free_matrix(m2->matrix);

	free(m1);
	free(m2);

	exit(EXIT_SUCCESS);
}
