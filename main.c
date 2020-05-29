#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

void suma_maxima_triunghi();

void subsir_crescator_maximal();

void suma_maxima_dreptunghi();

void subsir_crescator_maximal2();

void afis(int *, int *, int);

void sapt_13();

void sapt_14();

void subsir_comun_maximal();

#define MAX_LEN 100

void afis_solutii(int lmax[MAX_LEN+1][MAX_LEN+1], const char *s, const char *t, unsigned int i, unsigned int j);

void plata_suma();

int main() {
    sapt_13();
    sapt_14();
    return 0;
}

void sapt_14() {
    subsir_comun_maximal();
    plata_suma();
}

void plata_suma() {
    FILE *f = fopen("monede.in", "r");
    int p, n, *v, *nrmin, *pred;
    fscanf(f, "%d %d", &p, &n);
    v = malloc(n*sizeof(int));
    nrmin = malloc((p+1)*sizeof(int));
    pred = malloc((p+1)*sizeof(int));
    for (int i = 0; i < n; ++i) {
        fscanf(f, "%d", &v[i]);
    }
    for (int i = 0; i <= p; ++i) {
        nrmin[i] = p+1;
        pred[i] = -1;
    }
    fclose(f);
    nrmin[0] = 0;
    for (int i = 1; i <= p; ++i) {
        for (int j = 0; j < n; ++j) {
            if(i-v[j] >=0 && i-v[j] < p && nrmin[i-v[j]]+1 < nrmin[i]) {
                nrmin[i] = nrmin[i-v[j]]+1;
                pred[i] = v[j];
            }
        }
    }
    for (int i = 0; i <= p; ++i) {
        printf("%d ", nrmin[i]);
    }
    printf("\n");
    for (int i = 0; i <= p; ++i) {
        printf("%d ", pred[i]);
    }
    printf("\n%d", pred[p]);
    for (int i = p-pred[p]; pred[i] !=-1; i = i-pred[i]) {
        printf(" %d", pred[i]);
    }
    printf("\n");


    free(pred);
    free(nrmin);
    free(v);
}


void subsir_comun_maximal() {
    char s[MAX_LEN], t[MAX_LEN];
    unsigned int  n, m;
    int lmax[MAX_LEN + 1][MAX_LEN + 1];
    FILE *f = fopen("scm.in", "r");
//    fscanf(f, "%s %s", s, t);
    fgets(s, MAX_LEN, f);
    fgets(t, MAX_LEN, f);
    n = strlen(s);
    m = strlen(t);
    if(s[n-1] == '\n') {
        s[n-1] = '\0';
        n--;
    }
    if(t[m-1] == '\n') {
        t[m-1] = '\0';
        m--;
    }
    for (unsigned int i = 0; i <= n; ++i) {
        lmax[i][0] = 0;
    }
    for (unsigned int i = 0; i <= m; ++i) {
        lmax[0][i] = 0;
    }
    for (unsigned int i = 1; i <= n; ++i) {
        for (unsigned int j = 1; j <= m; ++j) {
            if (s[i-1] == t[j-1]) {
                lmax[i][j] = lmax[i-1][j-1] + 1;
            } else {
                lmax[i][j] = fmax(lmax[i][j-1], lmax[i-1][j]);
            }
        }
    }
    printf("      ");
    for (unsigned int i = 0; i < m; ++i) {
        printf("%3c", t[i]);
    }
    printf("\n");
    for (unsigned int i = 0; i <= n; ++i) {
        if(i>0)
            printf("%3c", s[i-1]);
        else
            printf("   ");
        for (unsigned int j = 0; j <= m; ++j) {
            printf("%3d", lmax[i][j]);
        }
        printf("\n");
    }
    fclose(f);
    afis_solutii(lmax, s, t, n, m);
    printf("\n");
}

void afis_solutii(int lmax[MAX_LEN+1][MAX_LEN+1], const char *s, const char *t, unsigned int i, unsigned int j) {
    if(i==0 || j==0)
        return;
    if(s[i-1] == t[j-1]) {
        afis_solutii(lmax, s, t, i-1, j-1);
        printf("%c", s[i - 1]);
    } else {
        if(lmax[i-1][j] > lmax[i][j-1])
            afis_solutii(lmax, s, t, i-1, j);
        else
            afis_solutii(lmax, s, t, i, j-1);
    }
}

void sapt_13() {
    suma_maxima_triunghi();
    suma_maxima_dreptunghi();
    subsir_crescator_maximal2();
    subsir_crescator_maximal();
}

void subsir_crescator_maximal2() {
    FILE *f = fopen("subsir_crescator.in", "r");
    int n, *t, *lmax, *pred;
    fscanf(f, "%d", &n);
    t = malloc(n * sizeof(int));
    lmax = malloc(n * sizeof(int));
    pred = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        fscanf(f, "%d", &t[i]);
        lmax[i] = 1;
        pred[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d ", t[i]);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if(t[i] >= t[j] && 1 + lmax[j] > lmax[i]) {
                lmax[i] = 1 + lmax[j];
                pred[i] = j;
            }
        }
    }
    int max_i = -1, max_val = INT_MIN;
    for (int i = 0; i < n; ++i) {
        printf("%d ", lmax[i]);
        if(lmax[i] > max_val) {
            max_val = lmax[i];
            max_i = i;
        }
    }
    printf("\n%d %d\n", max_val, max_i);
    for (int i = 0; i < n; ++i) {
        printf("%d ", pred[i]);
    }
    printf("\n");
//    printf("%d ", t[max_i]);
    for (int i = max_i; i > -1; i=pred[i]) {
        printf("%d ", t[i]);
    }
    printf("\n");
    afis(t, pred, max_i);
    printf("\n");
    free(pred);
    free(lmax);
    free(t);
    fclose(f);
}

void suma_maxima_dreptunghi() {
    FILE *f = fopen("dreptunghi.in", "r");
    int n, m, **mat;
    fscanf(f, "%d %d", &n, &m);
    mat = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        mat[i] = malloc(m * sizeof(int));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fscanf(f, "%d", &mat[i][j]);
        }
    }
    for (int i = 1; i < n; ++i) {
        mat[i][0] += fmax(mat[i-1][0], mat[i-1][1]);
        mat[i][m-1] += fmax(mat[i-1][m-2], mat[i-1][m-1]);
        for (int j = 1; j < m-1; ++j) {
            mat[i][j] += fmax(fmax(mat[i-1][j-1], mat[i-1][j]), mat[i-1][j+1]);
        }
    }
    int max_val = INT_MIN, max_j = -1;
    for (int i = 0; i < m; ++i) {
        if(mat[n-1][i] > max_val) {
            max_val = mat[n-1][i];
            max_j = i;
        }
    }
    printf("%d\n%d ", max_j, max_val);
    for (int i = n - 2; i >= 0; --i) {
        if(max_j == 0) {
            if(mat[i][max_j] < mat[i][max_j+1])
                max_j++;
        }
        else if(max_j == m - 1) {
            if(mat[i][max_j] < mat[i][max_j-1])
                max_j--;
        }
        else {
            if(mat[i][max_j] < mat[i][max_j+1])
                max_j++;
            else if(mat[i][max_j] < mat[i][max_j-1])
                max_j--;
        }
        printf("%d ", mat[i][max_j]);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%4d", mat[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; ++i) {
        free(mat[i]);
    }
    free(mat);
    fclose(f);
}

void subsir_crescator_maximal() {
    FILE *f = fopen("subsir_crescator.in", "r");
    int n, *v, *pred, *lmax;
    fscanf(f, "%d", &n);
    v = malloc(n*sizeof(int));
    pred = malloc(n*sizeof(int));
    lmax = malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        fscanf(f, "%d", &v[i]);
        pred[i] = -1;
        lmax[i] = 1;
    }
    // greedy
    int i_start = 0, i_best = -1, len = 0, max_len = 0;
    for (int i = 1; i < n; ++i) {
        if(v[i] > v[i-1])
            len++;
        else {
            if(len > max_len) {
                i_best = i_start;
                max_len = len;
            }
            len = 0;
            i_start = i;

        }
    }
    printf("greedy: %d %d\n", i_best, max_len);
    for (int i = i_best; i < i_best + max_len; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("pd: ");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if(v[i] >= v[j] && 1 + lmax[j] > lmax[i]) {
                lmax[i] = 1 + lmax[j];
                pred[i] = j;
            }
        }
    }
    int l_max = INT_MIN, l_i = -1;
    for (int i = 0; i < n; ++i) {
        if(lmax[i] > l_max) {
            l_max = lmax[i];
            l_i = i;
        }
        printf("%d ", lmax[i]);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", pred[i]);
    }
    printf("\n");
//    int prev = 0;
//    for (int i = 0; i < n; ++i) {
//        if(pred[i] > -1) {
//            prev = i;
//            break;
//        }
//    }

    printf("%d\n", l_max);
//    while (pred[l_i] > -1) {
//        printf("%d ", v[l_i]);
//        l_i = pred[l_i];
//    }
    afis(v, pred, l_i);
    printf("\n");
//    for (int i = prev; lmax[i] < l_max; i=pred[i]) {
//        printf("%d ", v[i]);
//    }

    free(v);
    free(pred);
    free(lmax);
    fclose(f);
}

void afis(int *v, int *pred, int max_i) {
    if(max_i != -1) {
        afis(v, pred, pred[max_i]);
        printf("%d ", v[max_i]);
    }
}

void suma_maxima_triunghi() {
    FILE *f = fopen("triunghi.in", "r");
    int n, **mat;
    fscanf(f,"%d", &n);
    mat = malloc(n*sizeof(int*));
    for (int i = 0; i < n; ++i) {
        mat[i] = malloc((i+1)*sizeof(int));
        for (int j = 0; j <= i; ++j) {
            fscanf(f, "%d", &mat[i][j]);
        }
    }
    //greedy
    int max_g = 0;//, max_val_g = mat[0][0];
    printf("greedy: %d ", mat[0][0]);
    for (int i = 1; i < n; ++i) {
        if(mat[i][max_g] < mat[i][max_g+1]) {
            max_g++;
        }
        printf("%d ", mat[i][max_g]);
    }
    printf("\n");
    // pd
    for (int i = 1; i < n; ++i) {
        mat[i][0] += mat[i-1][0];
        for (int j = 1; j < i; ++j) {
            mat[i][j] += fmax(mat[i-1][j-1], mat[i-1][j]);
        }
        mat[i][i] += mat[i-1][i-1];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            printf("%4d", mat[i][j]);
        }
        printf("\n");
    }
    int max_val = INT_MIN, max_i = -1;
    for (int i = n-1; i >= 0; --i) {
        if(mat[n-1][i] > max_val) {
            max_val = mat[n-1][i];
            max_i = i;
        }
    }
    printf("pd: %d ", max_val);
    for (int i = n-2; i >= 0; --i) {
        if(max_i > 0 && mat[i][max_i] < mat[i][max_i-1]) {
            max_i--;
        }
        printf("%d ", mat[i][max_i]);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        free(mat[i]);
    }
    free(mat);
    fclose(f);
}
