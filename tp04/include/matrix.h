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
#ifndef MATRIX_H
#define MATRIX_H

#define SIZE 10
#define NB_THREADS 4
#define PRINT 1

typedef struct matrix {
	unsigned int rows;      
	unsigned int columns; 
	double **matrix;       
} matrix_t;

typedef struct args_t {	
	int stepSize;
	const unsigned int index;

	matrix_t *m1;	
	matrix_t *m2;	
	matrix_t *answer;	
} args_t;	

/* Multi thread functions */	
void multi_threads(matrix_t *m1, matrix_t *m2);	
void *product_matrix_thread(args_t *args);

/* Mono thread functions */
void mono_thread(matrix_t *m1, matrix_t *m2);
matrix_t *product_matrix(matrix_t *m1, matrix_t *m2);
double product_case(int r, int c, matrix_t *m1, matrix_t *m2);

/* Utils matrix functions */
void print_matrix(matrix_t *m);
matrix_t *init_matrix(unsigned int rows, unsigned int columns, int fill);
void fill_matrix(matrix_t *m);
double **alloc_matrix(unsigned int rows, unsigned int columns);
void free_matrix(double **matrix);

#endif /* MATRIX_H */
