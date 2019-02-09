/*
WORKING AT LAST!

[1] TITLE
CroutsCholesky.h

[2] DEPENDENCIES
None

[3] DESCRIPTION
This class will compute for the polynomial
solution of the given polynomial expression
with variable size.

However forward and backward substitution
is replaced with inverse matrix multiplication

[4] ARGUMENTS

a) Polynomial Expression in the Form

For a square matrix size 3
0 1 0 K 
1 0 1 K 
0 1 0 K 

[5] LIMITATIONS
can only evaluate polynomial equations
no transcendentals

~ could not check for input errors yet
*/

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Direct
{
public:
	Direct(string);
	void Initialize();
	void Crouts();
	double* Ret_Sol();
	int Ret_Size();
private:
	void Tokenize();
	void LU();
	void Copy(double**,double**);
	void Del(double**);
	void InverseL();
	void InverseU();
	void Multiply(double**,double*,double*);

	string Polynomial;
	int size;
	bool IsValid;

	double **A;
	double **L;
	double **U;

	double **L0;
	double **U0;

	double *K;
	double *R;
	double *X;
};

Direct::Direct(string InPoly)
{
	Polynomial = InPoly;
	Tokenize();

	if(IsValid)
		Crouts();
}

void Direct::Initialize()
{
	A = new double *[size];
	L = new double *[size];
	U = new double *[size];
	L0 = new double *[size];
	U0 = new double *[size];

	R = new double [size];
	X = new double [size];
	K = new double [size];

	for(int row=0;row<size;row++)
	{
		X[row] = 0;
		R[row] = 0;
	}

	for (int row =0; row < size; row++)
	{
		A[row] = new double[size];
		L[row] = new double[size];
		U[row] = new double[size];
		L0[row] = new double[size*2];
		U0[row] = new double[size*2];
	}
}

void Direct::Crouts()
{
	LU();
	Copy(L,L0);
	Copy(U,U0);
	InverseL();
	InverseU();
	Multiply(L0,K,R);
	Multiply(U0,R,X);

	Del(L0);
	Del(U0);
}

// Tokenize inputed string 
void Direct::Tokenize()
{
	string temp;
	vector<string> PolyStr;
	size = 0;
	IsValid = true;

	stringstream split(Polynomial);
	while(split.good())
	{
		getline(split,temp,'|');
		PolyStr.push_back(temp);
	}
	size = PolyStr.size();
	Initialize();

	for (int i = 0; i < size; i++)
	{
		int j=0;
		stringstream splitElem(PolyStr[i]);
		while(splitElem.good())
		{
			getline(splitElem,temp,' ');
			if (istringstream(temp).bad())
			{
				IsValid = false;
				break;
				break;
				break;
			}
			else
			{
				if (j==size)
					istringstream(temp)>>K[i];
				else
					istringstream(temp)>>A[i][j];
			}
			j++;
		}

	}

}

// Decomposes Matrix A to L and U
void Direct::LU()
{
	int i=0,j=0,k=0;
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(j<i)
				L[j][i]=0;
			else
			{
				L[j][i]=A[j][i];
				for(k=0;k<i;k++)
				{
					L[j][i]=L[j][i]-L[j][k]*U[k][i];
				}
			}			
		}
		for(j=0;j<size;j++)
		{
			if(j<i)
				U[i][j]=0;
			else if(j==i)
				U[i][j]=1;
			else
			{
				U[i][j]=A[i][j]/L[i][i];
				for(k=0;k<i;k++)
				{
					U[i][j]=U[i][j]-((L[i][k]*U[k][j])/L[i][i]);	
				}
			}
		}
	}		
}

// Will copy arr Sc(source) to de(destination)
void Direct::Copy(double** Sc, double** De)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			De[i][j] = Sc[i][j];
	}
}

// Deallocate Unneeded Memory
void Direct::Del(double** Arr)
{
	for (int row =0; row < size; row++)
	{
		delete Arr[row];
	}
	delete[] Arr;
}

// Get the Inverse of the L Matrix
void Direct::InverseL()
{
	int i, j, k =0; 
	double	d =0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 2 * size; j++)
		{
			if (j == (i + size))
			{
				L0[i][j] = 1;
			}
			else if (j >= size)
			{
				L0[i][j] = 0;
			}
		}
	}

	//Reduce the diagonal to 1
	for (i = 0; i < size; i++)
	{
		d=L0[i][i];
		for (j = 0; j < size * 2; j++)
		{
			L0[i][j] = L0[i][j] / d;
		}
	}


	//Create Diagonal
	for(i=1;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if (i != j )
			{
				if(L0[i][j] !=0)
				{
					d = L0[i][j];
					for(k=0; k<2*size;k++)
					{
						L0[i][k] = L0[i][k] - d*L0[j][k];
					}
				}
			}
		}
	}
}

// Get the Inverse of the U Matrix
void Direct::InverseU()
{
	int i, j, k =0; 
	double	d =0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 2 * size; j++)
		{
			if (j == (i + size))
			{
				U0[i][j] = 1;
			}
			else if (j >= size)
			{
				U0[i][j] = 0;
			}
		}
	}

	//Create Diagonal
	for(i=1;i>=0;i--)
	{
		for(j=size-1;j>0;j--)
		{
			if (i != j )
			{
				if(U0[i][j] !=0)
				{
					d = U0[i][j];
					for(k=0; k<2*size;k++)
					{
						U0[i][k] = U0[i][k] - d*U0[j][k];
					}
				}
			}
		}
	}
}

//The product of Arr and Mr will be stored in Pr
void Direct::Multiply(double** Arr, double * Mr, double *Pr)
{
	int i,j =0;

	for(i=0; i<size; ++i)
	for(j=0; j<size; ++j)
	 Pr[i]+=Arr[i][j+3]*Mr[j];
}

double* Direct::Ret_Sol()
{
	return X;
}

int Direct::Ret_Size()
{
	return size;
}