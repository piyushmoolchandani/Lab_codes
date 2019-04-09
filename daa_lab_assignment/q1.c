#include<stdio.h>
#include<stdlib.h>

typedef struct student_data{
    char roll_number[9];
    int arts_marks;
    int science_marks;
}student_data;

void print_list(student_data * list, int n)
{
    for (int i=0; i<n; ++i) 
        printf("%s\t%d\t%d\n", list[i].roll_number, list[i].arts_marks, list[i].science_marks);
}

void print_list_by_index_for_testing(student_data *L, int *J, int n )
{
        for (int i=0; i<n; ++i) 
            printf("%s\t%d\t%d\n", L[J[i]].roll_number, L[J[i]].arts_marks, L[J[i]].science_marks);
}

int compare_arts_marks(student_data *L, int i, int j)
{
    if (L[i].arts_marks > L[j].arts_marks) 
        return 1;
    if (L[i].arts_marks < L[j].arts_marks) 
        return -1;
    return 0;
}

int compare_science_marks(student_data *L, int i, int j)
{
    if (L[i].science_marks > L[j].science_marks)
         return 1;
    if (L[i].science_marks < L[j].science_marks) 
        return -1;
    return 0;
}

int compare_arts(student_data *L, int i, int x )
{
   if (L[i].arts_marks > x) return 1;
   if (L[i].arts_marks < x) return -1;
   return 0;
}

int compare_science(student_data *L, int i, int x )
{
   if (L[i].science_marks > x) return 1;
   if (L[i].science_marks < x) return -1;
   return 0;
}

int *sort(student_data *L, int n, int (*cmp)(student_data *, int, int))
{
    int *J, i, j, k;
    J = (int *)malloc(n * sizeof(int));
    if (J) 
    {
        for (i=0; i<n; ++i) J[i] = i;
        for (j=n-2; j>=0; --j) 
        {
            for (i=0; i<=j; ++i) 
            {
                if (cmp(L,J[i],J[i+1]) < 0)
                {
                    k = J[i];
                    J[i] = J[i+1]; 
                    J[i+1] = k;
                }
            }
        }
   }
   return J;
}

int binary_search(student_data *L, int *J, int n, int x, int (*cmp)(student_data *,int,int) )
{
    int l, u, m;
    l = 0; u = n-1;
    while (l != u) 
    {
        m = (l + u) / 2;
        if (cmp(L,J[m],x) > 0) 
            l = m+1; 
        else 
            u = m;
    }
    return l;
}

void part_1(student_data *L, int *J, int n, int a, int b, int (*cmp)(student_data *,int,int) )
{
    int start, end, i;

    printf("List of students:\n");

    if (cmp(L,J[0],a) < 0) return;
    if (cmp(L,J[n-1],b) > 0) return;

    start = binary_search(L,J,n,b,cmp);
    while ((start > 0) && (cmp(L,J[start],b) == 0)) --start;

    end = binary_search(L,J,n,a,cmp);
    while ((end < n-1) && (cmp(L,J[end],a) == 0)) ++end;

    if (cmp(L,J[start],b) > 0) ++start;
    if (cmp(L,J[end],a) < 0) --end;

    for (i=start; i<=end; ++i) {
        printf("%s\t%d\t%d\n", L[J[i]].roll_number, L[J[i]].arts_marks, L[J[i]].science_marks);
    }
}

void part_2 ( student_data *L, int *JA, int *JS, int n )
{
    int i, rank, *RA, *RS, nBA, nBS, nSC;

    RA = (int *)malloc(n * sizeof(int));
    RS = (int *)malloc(n * sizeof(int));
    if (RA && RS) {
        rank = 0;
        for (i=0; i<n; ++i) {
            if ((i == 0) || (L[JA[i]].arts_marks != L[JA[i-1]].arts_marks)) rank = i + 1;
            RA[JA[i]] = rank;
        }

        nBA = nBS = nSC = rank = 0;
        for (i=0; i<n; ++i) {
            if ((i == 0) || (L[JS[i]].science_marks != L[JS[i-1]].science_marks)) rank = i + 1;
            RS[JS[i]] = rank;
        }

        for (i=0; i<n; ++i) {
            printf("%s\t%d\t%d\tArts rank = %4d\tScience rank = %4d\t",
                    L[i].roll_number, L[i].arts_marks, L[i].science_marks, RA[i], RS[i]);
            if (RA[i] < RS[i]) { printf("Decision: Goes for BA\n"); ++nBA; }
            else if (RA[i] > RS[i]) { printf("Decision: Goes for BS\n"); ++nBS; }
            else { printf("Decision: Given choice\n"); ++nSC; }
        }
    }

    printf("\n");
    printf("Number of BA = %d\n", nBA);
    printf("Number of BS = %d\n", nBS);
    printf("Number of SC = %d\n", nSC);
    free(RA); free(RS);
}

int main ()
{
    int n;
    scanf("%d", &n);
    student_data *L = (student_data *)malloc(n * sizeof(student_data));
    int *JA, *JS;
    int a, b;

    for (int i = 0; i < n; i++)
    {
        scanf("%s", L[i].roll_number);
        scanf("%d", &L[i].arts_marks);
        scanf("%d", &L[i].science_marks);
    }

    JA = sort(L,n,compare_arts_marks); if (JA == NULL) return 0;
    JS = sort(L,n,compare_science_marks); if (JS == NULL) return 0;

    printf("\nPart 1:\n");

    printf("\nQuery 1 with a = 53, b = 65 and subject as arts: \n");
    a = 53; b = 65;
    part_1(L,JA,n,a,b,compare_arts);
    
    printf("\nQuery 2 with a = 13, b = 14 and subject as arts: \n");
    a = 13; b = 14;
    part_1(L,JA,n,a,b,compare_arts);

    
    printf("\nQuery 3 with a = 69, b = 74 and subject as science: \n");
    a = 69; b = 74;
    part_1(L,JS,n,a,b,compare_science);

    printf("\nQuery 3 with a = 69, b = 74 and subject as science: \n");
    a = 26; b = 41;
    part_1(L,JS,n,a,b,compare_science);

    printf("\nPart 2: \n");
    part_2(L,JA,JS,n);
    free(L); free(JA); free(JS);
    return 0;
}