#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
    double *buf;
    int size;
    int capacity;
} vector;

typedef struct
{
    int m;
    int n;
    vector k;
    vector v;
} matrix;

void mat_init(matrix *m);
void mat_destroy(matrix *m);
void mat_read(matrix *mat, FILE *f);
void mat_print(matrix *mat);
void mat_print_vec(matrix *mat);
void mat_trans_diag(matrix *mat, matrix *ans);
bool mat_check_skew_symmetry(matrix *mat);
bool v_init(vector *v);
void v_destroy(vector *v);
double v_get(vector *v, int i);
void v_set(vector *v, int i, double val);
int v_get_size(vector *v);
bool v_set_size(vector *v, int size);
double v_pop_back(vector *v);
bool v_push_back(vector *v, double val);
void v_swap(vector *v, int i1, int i2);

#endif
