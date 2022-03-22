#include<iostream>
using namespace std;

class Matrix {
public:
	Matrix() 
	{
		ptr = nullptr;
		col = 0;
		row = 0;
	}
	Matrix(const int col1, const int row1) 
	{
		col = col1;
		row = row1;
		if (ptr != nullptr) {
			for (int i = 0; i < row; i++)
				delete[] ptr[i];
			delete[] ptr;
		}
		ptr = new int* [row];
		for (int i = 0; i < row; i++)
			*(ptr+i) = new int [col];
		for(int i = 0 ; i < row; i++)
			for (int j = 0; j < col; j++) {
				ptr[i][j] = rand() % 6;
			}
	}
	Matrix(const int col1, const int row1, int value) 
	{
		col = col1;
		row = row1;
		if (ptr != nullptr) {
			for (int i = 0; i < row; i++)
				delete[] ptr[i];
			delete[] ptr;
		}
		ptr = new int* [row];
		for (int i = 0; i < row; i++)
			*(ptr + i) = new int[col];
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				ptr[i][j] = value;
			}
	}
	Matrix(Matrix& right) 
		:ptr(ptr = nullptr) 
	{
		col = right.col;
		row = right.row;
		if (ptr != nullptr) {
			for (int i = 0; i < row; i++)
				delete[] ptr[i];
			delete[] ptr;
		}
		ptr = new int* [row];
		for (int i = 0; i < row; i++)
			*(ptr + i) = new int[col];
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				ptr[i][j] = right.ptr[i][j];
			}
	}
	~Matrix() {
		if (ptr != nullptr) {
			for (int i = 0; i < row; i++)
				delete[] ptr[i];
			delete[] ptr;
		}
	}
	void print() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << ptr[i][j] << " ";
			}
			cout << endl;
		}
	}

	void mutiplication(Matrix& a, Matrix& b){
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				for (int k = 0; k < b.row; k++) {
					ptr[i][j] += a.ptr[i][k] * b.ptr[k][j];
				}
	}

	Matrix& operator=(Matrix& right) {
		col = right.col;
		row = right.row;
		if (ptr != nullptr) {
			for (int i = 0; i < row; i++)
				delete[] ptr[i];
			delete[] ptr;
		}
		ptr = new int* [row];
		for (int i = 0; i < row; i++)
			*(ptr + i) = new int[col];
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				ptr[i][j] = right.ptr[i][j];
			}
		return *this;
	}
private:
	int** ptr;
	int col;
	int row;

	
};

int main() {
	int a, b, c, d;
	//cin >> a >> b >> c >> d;
	a = 3, b = 2, c = 2, d = 4;
	srand(12423);
	Matrix a1(b, a);
	a1.print();
	Matrix b1(d, c);
	b1.print();
	Matrix c1(d,a,0);
	c1.mutiplication(a1,b1);
	c1.print();

}
