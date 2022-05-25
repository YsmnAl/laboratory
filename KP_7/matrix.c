#include <stdlib.h>
#include "stdbool.h"
#include <stdio.h>
#include "matrix.h"

const int MIN_CAP = 64;

bool v_init(vector *v)
{
    double *newbuf = malloc(MIN_CAP * sizeof(double));
    if (newbuf != NULL)
    {
        v->buf = newbuf;
        v->size = 0;
        v->capacity = MIN_CAP;
        return true;
    }
    return false;
}

void v_destroy(vector *v)
{
    free(v->buf);
    v->buf = NULL;
    v->size = 0;
    v->capacity = 0;
}

double v_get(vector *v, int i)
{
    return v->buf[i];
}

void v_set(vector *v, int i, double val)
{
    v->buf[i] = val;
}

int v_get_size(vector *v)
{
    return v->size;
}

bool v_set_size(vector *v, int new_size)
{
    if (new_size > v->capacity)
    {
        int new_cap = v->capacity * 3 / 2;
        if (new_cap < new_size)
        {
            new_cap = new_size;
        }
        if (new_cap < MIN_CAP)
        {
            new_cap = MIN_CAP;
        }

        double *new_buf = realloc(v->buf, new_cap * sizeof(double));
        if (new_buf == NULL)
        {
            return false;
        }

        v->buf = new_buf;
        v->capacity = new_cap;
    }
    else if (new_size * 3 / 2 < v->capacity)
    {
        int new_cap = new_size * 3 / 2;
        if (new_cap < MIN_CAP)
        {
            new_cap = MIN_CAP;
        }

        v->buf = realloc(v->buf, new_cap * sizeof(double));
        v->capacity = new_cap;
    }

    for (int i = v->size; i < new_size; i++)
    {
        v_set(v, i, 0);
    }

    v->size = new_size;
    return true;
}

double v_pop_back(vector *v)
{
    double res = v_get(v, v_get_size(v) - 1);
    v_set_size(v, v_get_size(v) - 1);
    return res;
}

bool v_push_back(vector *v, double val)
{
    if (v_set_size(v, v_get_size(v) + 1))
    {
        v_set(v, v_get_size(v) - 1, val);
        return true;
    }
    return false;
}

void v_swap(vector *v, int i1, int i2)
{
    double t = v_get(v, i1);
    v_set(v, i1, v_get(v, i2));
    v_set(v, i2, t);
}

void mat_init(matrix *m)
{
    v_init(&m->k);
    v_init(&m->v);
}

void mat_destroy(matrix *m)
{
    v_init(&m->k);
    v_init(&m->v);
    m->m = 0;
    m->n = 0;
}

void mat_read(matrix *mat, FILE *f)
{
    fscanf(f, "%d%d", &mat->m, &mat->n);
    for (int i = 0; i < mat->m; i++)
    {
        for (int j = 0; j < mat->n; j++)
        {
            int tmp;
            fscanf(f, "%d", &tmp);
            if (tmp != 0)
            {
                v_push_back(&mat->k, i * mat->n + j);
                v_push_back(&mat->v, (double)tmp);
            }
        }
    }
}

void mat_print_vec(matrix *mat)
{
    fprintf(stdout, "(Вектор индексации) LB:  ");
    for (int i = 0; i < v_get_size(&mat->k); i++)
    {
        fprintf(stdout, "%3d ", (int)v_get(&mat->k, i));
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "(Вектор значений) YE:    ");
    for (int i = 0; i < v_get_size(&mat->v); i++)
    {
        fprintf(stdout, "%3d ", (int)v_get(&mat->v, i));
    }
    fprintf(stdout, "\n");
}

void print_zeros(int *prev_i, int *prev_j, int border_i, int border_j, int n)
{
    while (*prev_i != border_i || *prev_j != border_j)
    {
        int x = 0;
        fprintf(stdout, "%3d ", x);
        if (*prev_j == n - 1)
        {
            *prev_j = 0;
            *prev_i += 1;
            fprintf(stdout, "\n");
        }
        else
        {
            *prev_j += 1;
        }
    }
}

void mat_print(matrix *mat)
{
    if (mat->n == 0 || mat->m == 0)
    {
        return;
    }
    int prev_i = 0;
    int prev_j = 0;
    for (int t = 0; t < v_get_size(&mat->k); t++)
    {
        int ind = (int)v_get(&mat->k, t);
        int val = (int)v_get(&mat->v, t);
        int i = ind / mat->n;
        int j = ind % mat->n;
        print_zeros(&prev_i, &prev_j, i, j, mat->n);
        fprintf(stdout, "%3d ", val);
        prev_i = i;
        prev_j = j + 1;
        if (prev_j == mat->n)
        {
            fprintf(stdout, "\n");
            prev_i++;
            prev_j = 0;
        }
    }
    print_zeros(&prev_i, &prev_j, mat->m, 0, mat->n);
}

int v_binarysearch(vector *v, double val)
{
    int l = 0;
    int r = v_get_size(v);
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (val < v_get(v, m))
        {
            r = m;
        }
        else if (val > v_get(v, m))
        {
            l = m;
        }
        else
        {
            return m;
        }
    }
    return (l + r) / 2;
}

int mat_get(matrix *mat, int i, int j)
{
    int ind = v_binarysearch(&mat->k, i * mat->n + j);
    if (v_get(&mat->k, ind) == i * mat->n + j)
    {
        return v_get(&mat->v, ind);
    }
    return 0;
}

void mat_trans_diag(matrix *a, matrix *ans)
{
    ans->m = a->m;
    ans->n = a->n;
    int b[a->n * a->n];
    for (int i = 0; i < a->n * a->n; i++)
    {
        b[i] = 0;
    }
    ans->m = a->m;
    ans->n = a->n;
    int j2 = 0, i2 = 0;
    for (int i = a->n - 1; i >= 0; i--)
    {
        for (int j = a->n - 1; j >= 0; j--)
        {
            int tmp = (int)mat_get(a, i, j);
            int ind = j2 * a->n + i2;
            j2++;
            b[ind] = tmp;
        }
        i2++;
        j2 = 0;
    }
    for (int i = 0; i < a->n * a->n; i++)
    {
        if (b[i] != 0)
        {
            v_push_back(&ans->k, i);
            v_push_back(&ans->v, (double)b[i]);
        }
    }
}

bool mat_check_skew_symmetry(matrix *mat)
{
    for (int t = 0; t < v_get_size(&mat->k); t++)
    {
        int i = (int)v_get(&mat->k, t) / mat->n;
        int j = (int)v_get(&mat->k, t) % mat->n;
        if ((int)v_get(&mat->v, t) != -mat_get(mat, j, i))
        {
            return false;
        }
    }
    return true;
}
