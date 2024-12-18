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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <matrix.h>

/* Multi threads functions */
void multi_threads(matrix_t *m1, matrix_t *m2) 
{
	clock_t c_before;
	clock_t c_after;
	time_t t_before;
	time_t t_after;
	matrix_t *m3;

	c_before = clock();
	t_before = time(NULL);
	args_t args = {
      .m1= m1,
      .m2= m2,
      .answer= m3
  };
	product_matrix_thread(args);
	t_after = time(NULL);
	c_after = clock();

	if (PRINT) {
		printf("\nProduct :\n");
		print_matrix(m3);
	}

	printf("\nClock_t -> %5.3f ticks (%f seconds)\n",
			 (float) (c_after - c_before),
			 (double) (c_after - c_before) / CLOCKS_PER_SEC);
	printf("Time_t  -> %5.3f seconds\n", difftime(t_after, t_before));

	free_matrix(m3->matrix);
	free(m3);
}

matrix_t *product_matrix_thread(args_t *args) 
{	
	unsigned int i;
	unsigned int j;
	
	if (m1->columns != m2->rows) {
		printf("Dimensions Error\n");
		return NULL;
	}

	result = init_matrix(m1->rows, m2->columns, 0);

	stepSize = m1.columns / NB_THREADS;
	pthread_t threads[NB_THREADS];
	for(int i = 0; i < NB_THREADS; ++i) {
		args_t args {
		.index = i,
		.m1 = m1,
		.m2 = m2,
		.answer = result
		};
		
		pthread_create(
			threads[i],	
			NULL,	
			product_matrix_thread,	
			(void *)args
		);
	}

	pthread_join();

	return result;
}

/* Mono thread functions */
void mono_thread(matrix_t *m1, matrix_t *m2) 
{
	matrix_t *m3;
	clock_t c_before;
	clock_t c_after;
	time_t t_before;
	time_t t_after;

	c_before = clock();
	t_before = time(NULL);
	m3 = product_matrix(m1, m2);
	t_after = time(NULL);
	c_after = clock();

	if (PRINT) {
		printf("\nProduct :\n");
		print_matrix(m3);
	}

	printf("\nClock_t -> %5.3f ticks (%f seconds)\n",
			 (float) (c_after - c_before),
			 (double) (c_after - c_before) / CLOCKS_PER_SEC);
	printf("Time_t  -> %5.3f seconds\n", difftime(t_after, t_before));

	free_matrix(m3->matrix);
	free(m3);
}

matrix_t *product_matrix(matrix_t *m1, matrix_t *m2) 
{
	unsigned int i;
	unsigned int j;
	matrix_t *result;

	if (m1->columns != m2->rows) {
		printf("Dimensions Error\n");
		return NULL;
	}

	result = init_matrix(m1->rows, m2->columns, 0);

	for (i = 0; i < result->columns; ++i) {
		for (j = 0; j < result->rows; ++j) {
			result->matrix[j][i] = product_case(j, i, m1, m2);
		}
	}

	return result;
}

double product_case(int r, int c, matrix_t *m1, matrix_t *m2) 
{
	unsigned int i;
	double tmp;
	
	tmp = 0;

	for (i = 0; i < m1->columns; ++i) {
		tmp += m1->matrix[r][i] * m2->matrix[i][c];
	}

	return tmp;
}


/* Utils matrix functions */

void print_matrix(matrix_t *m) 
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < m->rows; ++i) {
		for (j = 0; j < m->columns; ++j) {
			printf("%04.2f ", m->matrix[i][j]);
		}
		printf("\n");
	}
}

matrix_t *init_matrix(unsigned int rows, unsigned int columns, int fill) 
{
	matrix_t *m;
	
	m = malloc(sizeof(matrix_t));
	m->rows = rows;
	m->columns = columns;
	m->matrix = alloc_matrix(rows, columns);

	if (fill) {
		fill_matrix(m);
	}

	return m;
}

void fill_matrix(matrix_t *m) 
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < m->rows; ++i) {
		for (j = 0; j < m->columns; ++j) {
			m->matrix[i][j] = (double) (rand() % 15) + 10;
		}
	}
}

double **alloc_matrix(unsigned int rows, unsigned int columns) 
{
	double **matrix;
	unsigned int row;

	matrix = (double **) calloc(rows, sizeof(double *));
	if (!matrix) {
		return NULL;
	}

	matrix[0] = (double *) calloc(rows * columns, sizeof(double));
	if (!matrix[0]) {
		free(matrix);
		return NULL;
	}

	for (row = 1; row < rows; ++row) {
		matrix[row] = matrix[row - 1] + columns;
	}

	return matrix;
}

void free_matrix(double **matrix) 
{
	free(matrix[0]);
	free(matrix);
}
