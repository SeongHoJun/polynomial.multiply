#include <stdio.h>
#define MAX(a,b)((a)>(b)?(a):(b))
#define MAX_DEGREE 101
typedef struct
{
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

polynomial poly_add(polynomial A, polynomial B)
{
	polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);

	while (Apos <= A.degree && Bpos <= B.degree)
	{
		if (degree_a > degree_b)
		{
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b)
		{
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--;
			degree_b--;
		}
		else
		{
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

polynomial poly_multiply(polynomial A, polynomial B)
{
	polynomial C = { 0,{0} };
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;

	C.degree = A.degree + B.degree;

	for (int i = 0; i <= A.degree; i++)
	{
		for (int j = 0; j <= B.degree; j++)
		{
			polynomial T = { 0,{0} };
			T.degree = (A.degree - i) + (B.degree - j);
			T.coef[0] = A.coef[i] * B.coef[j];
			C = poly_add(C, T);
		}
	}
	return C;
}
void print_poly(polynomial p)
{
	for (int i = p.degree; i > 0; i--)
	{
		if (!p.coef[p.degree - i])continue;
		printf("%3.1lfx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1lf\n", p.coef[p.degree]);
}

int main()
{
	polynomial a = { 3,{4,3,2,1} };
	polynomial b = { 2,{3,2,8} };
	polynomial c;

	print_poly(a);
	print_poly(b);
	c = poly_multiply(a, b);
	//c = poly_add(a, b);
	printf("---------------------------------------------\n");
	print_poly(c);

	return 0;
}