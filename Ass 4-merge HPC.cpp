#include<cstdlib>
#include <bits/stdc++.h>
#include<ctime>
#include<omp.h>

using namespace std;

void merge(int *array, int l, int m, int r)
{
	int i,j,k;
	int n1 = m-l +1;
	int n2 = r-m;
	int *L = new int[n1];
	int *R = new int[n2];
	for(i =0; i<n1; i++)
		L[i] = array[l+i];
	
	for(j = 0; j<n2; j++)
		R[j] = array[m+1+j];
		
	i=0;
	j=0;
	k=l;
	
	while(i<n1 && j<n2)
	{
		if(L[i]<= R[j])
		{
			array[k] = L[i];
			i++;
		}
		else 
		{
			array[k] = R[j];
			j++;
		}
		k++;
	}
	
	while(i<n1)
	{
		array[k]=L[i];
		i++;
		k++;
	}
	
	while(j<n2)
	{
		array[k]=R[j];
		j++;
		k++;
	}
	
	delete[] L;
	delete[] R;
}


void parallelMergesort(int *array, int l, int r)
{
	if(l<r)
	{
		int m = l+(r-l)/2;
		
		#pragma omp parallel sections
		{
			#pragma omp section
			parallelMergesort(array, l, m);
			
			#pragma omp section
			parallelMergesort(array, m+1, r);
			
		}
		merge(array,l,m,r);
	}
}

	
	
int main()
{
	int n;
	cout<<"enter the size of array: ";
	cin>>n;
	
	int *array = new int[n];
	srand(time(0));
	
	for(int i = 0; i<n; i++)
	{
		array[i] = rand()%100;
	}
	
	cout<<"original Array: ";
	for(int i = 0; i<n; i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
	
	parallelMergesort(array,0,n-1);
	
	cout<<"sorted array: ";
	for(int i =0; i<n; i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
	
	delete[] array;
	return 0;
}
	
