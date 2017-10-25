#include"stdafx.h"
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

bool raz(int &m , int &n)
{
	string razmer;
	char op; int*t = new int;
	getline(cin, razmer);
	istringstream stream(razmer);
	stream >> *t;
	if (stream >> op && op == ',')
	{
		m =*t;
		delete t;
		if (!(stream >> n))
		{
			cout << "fail!!!";
			return false;
		}
		else return true;
	}
	else 
	{
		return false;
	}
}

bool read(int **matrix , int str , int col )
{
	int k =0;
	for (int i=0; i < str ; i++)
	{
		string row;
		getline(cin, row);
		istringstream stream(row);
		for (int j=0; j < col; j++)
		{
			if (stream >> matrix[i][j]) { k++; }
		}
	}
	if (k == str*col) return true;
	else return false;
}

void print(int **matrix , int str , int col)
{
	for (int i = 0; i < str; i++)
	{
		cout << endl;
		for (int j = 0; j < col; j++)
		{
			cout << matrix[i][j]<< " ";
		}
	}
}

void add(int ** mat1, int ** mat2,int str,int col)
{
	for (int i = 0; i < str; i++)
	{
		cout << endl;
		for (int j = 0; j < col; j++)
		{
			cout << mat1[i][j] + mat2[i][j] << " ";
		}
	}
}

void sub(int ** mat1, int ** mat2, int str, int col)
{
	for (int i = 0; i < str; i++)
	{
		cout << endl;
		for (int j = 0; j < col; j++)
		{
			cout << mat1[i][j] - mat2[i][j] << " ";
		}
	}
}

void mul(int ** mat1, int ** mat2, int str, int col,int col1)
{
	int ** mat3 = new int*[str];
	for (int i = 0; i < str; i++)
	{
		mat3[i] = new int[col];
	}
	for (int i = 0; i < str; i++) {
		cout << endl;
		for (int j = 0; j < col; j++) {
			int res = 0;
			for (int k = 0; k < col1; k++) {
				res += mat1[i][k] * mat2[k][j];
			}

			mat3[i][j] = res;
			cout << mat3[i][j]<<" ";
		}
	}
}

void T(int ** mat3 , int **matrix1 ,int col1 , int str1)
{
	for (int i = 0; i < col1; i++)
	{
		mat3[i] = new int[str1];
	}
	for (int i = 0; i < col1; ++i)
	{
		for (int j = 0; j < str1; ++j)
		{
			mat3[i][j] = matrix1[j][i];
		}
	}
}

void TR(double ** mat3, double **matrix1, int col1, int str1)
{
	for (int i = 0; i < col1; i++)
	{
		mat3[i] = new double[str1];
	}
	for (int i = 0; i < col1; ++i)
	{
		for (int j = 0; j < str1; ++j)
		{
			mat3[i][j] = matrix1[j][i];
		}
	}
}

void min_matrix(int ** mat, int **n_mat, int i,int j, int N)
{
	int k = 0; int  g;
	for (int i1 = 0;  i1<N -1; i1++) 
	{ 		
		if (i1 == i)
		{
			k = 1;
		}
			g = 0;
		for (int j1 = 0; j1< N - 1; j1++) 
		{
			if (j1 == j)
			{
				g = 1;
			}
			n_mat[ i1 ][ j1 ] = mat[ i1 + k ][ j1 + g ];
		}
	}
}

int det(int ** mat, int N)
{
	int i=0;
	int deter=0;
	int M = N - 1;
	int step = 1;

	int ** n_mat;
	n_mat = new int *[N];
	for (int i = 0; i < N; i++)
	{
		n_mat[i] = new int[N];
	}

	if (N < 1)
	{
		for (int i = 0; i < N; i++)
		{
			delete[] n_mat[i];
		}
		cout << "fail";
	}
	if (N == 1)
	{
		deter = mat[0][0];
		
		return(deter);
	}
	if (N == 2)
	{
		deter = mat[0][0] * mat[1][1] - (mat[1][0] * mat[0][1]);
		for (int i = 0; i < N; i++)
		{
			delete[] n_mat[i];
		}
		return(deter);
	}
	if (N>2)
	{
		for (i = 0; i<N; i++) 
		{
			min_matrix(mat, n_mat, i, 0, N);
			deter = deter + step * mat[i][0] * det(n_mat, M);
			step = -step;
		}
	}
	for (int i = 0; i < N; i++)
	{
		delete[] n_mat[i];
	}
	return(deter);
}

void R(double ** matR, int ** matrix1, int str1, int col1)
{
	int **n_mat;
	double ** mat;
	n_mat = new int*[str1];
	mat = new double*[str1];
	for (int i = 0; i < str1; i++)
	{
		matR[i] = new double[col1];
		n_mat[i] = new int[col1];
	}
	int deter = det(matrix1, str1);
	if (deter != 0)
	{
		for (int i = 0; i < str1; i++)
		{
			for (int j = 0; j < col1; j++)
			{
				min_matrix(matrix1, n_mat, i, j, str1);
				double d = det(n_mat, (str1 - 1));
				matR[i][j] = d * pow((-1), (i + j)) * (1.0 / deter);
			}
		}
		TR(mat, matR, str1, col1);
		for (int i = 0; i < col1; ++i)
		{
			cout << endl;
			for (int j = 0; j < str1; ++j)
			{
				cout << matR[i][j] << " ";
			}

		}
	}
	else cout << "fail R , det = 0";

	for (int i= 0 ; i < str1 ; i++)
	{
		delete [] n_mat[i];
	}
	for (int i = 0; i < str1; i++)
	{
		delete[] mat[i];
	}
}

int main()
{
	int str1, col1;
	int str2, col2;
	static int **matrix1;
	static bool mat1=false ,mat2=false;
	static int **matrix2;
	static char op;
	if (raz(str1, col1))
	{
		matrix1 = new int*[str1];
		for (int i = 0; i < str1; i++)
		{
			matrix1[i] = new int[col1];
		}
		if (read(matrix1, str1, col1))
		{
			mat1 = true;
			//cout << "op  " << endl ;
			cin >> op;
			cin.get();
		}
		else cout << "fail input";
	}
	if (op == '+' || op == '-' || op == '*')
	{
		if (raz(str2, col2))
		{
			matrix2 = new int*[str2];
			for (int i = 0; i < str2; i++)
			{
				matrix2[i] = new int[col2];
			}
			if (read(matrix2, str2, col2))
			{
				mat2 = true;
			}
			else
			{
				cout << "fail input";
				return 0;
			}
		}
		switch (op)
		{
		case '+':
			if (str1 == str2 && col1 == col2)
			{
				add(matrix1, matrix2, str1, col1);
			}
			else
			{
				cout << "fail";
				break;
			}
			break;
		case '-':
			if (str1 == str2 && col1 == col2)
			{
				sub(matrix1, matrix2, str1, col1);
			}
			else
			{
				cout << "fail";
				break;
			}
			break;
		case '*':
			if (col1 == str2)
			{
				mul(matrix1, matrix2, str1, col2,col1);
			}
			else
			{
				cout << "fail";
				break;
			}
			break;

		}
	}
	else if (op == 'T')
	{
		int ** mat3;
		 mat3 = new int*[col1];
		 T(mat3, matrix1, col1, str1);
		print(mat3, col1, str1);
		for (int i = 0; i < col1; i++)
		{
			delete[] mat3[i];
		}

	}
	else if (op == 'R')
	{
		double ** matR; 
		matR = new double*[str1];
		R(matR, matrix1, str1, col1);
		for (int i = 0; i < str1; i++)
		{
			delete[] matR[i];
		}
	}
	cin.get();
	if (mat1)
	{
		for (int i = 0; i < str1; i++)
		{
			delete[] matrix1[i];
		}
	}
	if (mat2)
	{
		for (int i = 0; i < str2; i++)
		{
			delete[] matrix2[i];
		}
	}
	return 0;
}
