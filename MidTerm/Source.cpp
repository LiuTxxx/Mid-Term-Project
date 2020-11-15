#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <thread>
using namespace std;

struct Matrix
{
	/**
		参数释义：
		param row 矩阵行数
		param column 矩阵列数
		param data 用vector储存矩阵元素
	*/
	long long row;
	long long column;
	vector<float> data;
};


void RandomFill(vector<float>& numbers, long long size) {
	// 预分配size的缓冲区，这样性能相对更好一点
	numbers.resize(size);
	for (long long i = 0; i < size; ++i) {
		numbers[i] = static_cast<float>(rand() % 20);
	}
}


void Print(const vector<float>& numbers, int  rows, int cols) {
	for (long long row = 0; row != rows; ++row) {
		for (long long col = 0; col != cols; ++col) {
			// 取出每一列的数字
			cout << numbers[row * cols + col] << ' ';
		}
		// 没输出一行之后换一行
		cout << '\n';
	}
}


void Matrix_Product(int isTimeTest)
{
	char order = 'Y';
	//接受指令Y后继续执行
	while (order == 'Y')
	{
		Matrix A, B, C;
		//输入A，B，将A*B保存至C
		cout << "\nInput the size of Matrix A: (row column)\n";
		cin >> A.row >> A.column;
		cout << "Input the size of Matrix B: (row column)\n";
		cin >> B.row >> B.column;
		A.data.resize(A.column * A.row);
		B.data.resize(B.column * B.row);
		if (A.column == B.row)
		{
			C.row = A.row;
			C.column = B.column;
			C.data.resize(C.column * C.row);
			cout << "\nWhich one do you like?\n   A: Random generation\n   B: Input yourself\n";
			char ch;
			cin >> ch;
			if (ch == 'B')
			{
				//输入A，B
				cout << "\nInput Matrix A:\n";
				for (long long i = 0; i < A.row * A.column; i++)
				{
					cin >> A.data[i];
				}
				cout << "Input Matrix B:\n";
				for (long long i = 0; i < B.row * B.column; i++)
				{
					cin >> B.data[i];
				}
			}
			else
			{
				//随机生成A，B并打印
				RandomFill(A.data, A.column * A.row);
				RandomFill(B.data, B.column * B.row);
				if (!isTimeTest)
				{
					cout << "\nMatrix A: \n";
					Print(A.data, A.row, A.column);
					cout << "Matrix B: \n";
					Print(B.data, B.row, B.column);
				}
			}
			/*
				param row_A 遍历A的行
				param col_B 遍历B的列
				param prod 需相乘的数字遍历
			*/
			auto start = std::chrono::steady_clock::now();
			for (long long row_A = 0; row_A < A.row; row_A++)
			{
				for (long long col_B = 0; col_B < B.column; col_B++)
				{
					C.data[row_A * B.column + col_B] = 0;
					for (long long prod = 0; prod < A.column; prod++)
					{
						C.data[row_A * B.column + col_B] += A.data[row_A * A.column + prod] * B.data[prod * B.column + col_B];
					}
				}
			}
			auto end = std::chrono::steady_clock::now();

			if (!isTimeTest)
			{
				cout << "\nThe product of A and B:\n";
				Print(C.data, C.row, C.column);
			}
			else
			{
				cout
					<< "\nMatrix product of this size took "
					<< chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms ≈ "
					<< chrono::duration_cast<chrono::seconds>(end - start).count() << "s.\n";
				break;
			}
			cout << "\nDo you want to continue matrix product? (Y/N)\n";
			cin >> order;
		}
		else
			cout << "\nWrong size, please try again!\n";
	}
}


void Multiple_Thread(Matrix* A, Matrix* B, Matrix* C, int i, int size)
{
	long long sizeA = A->row / (size - 1);
	long long sizeB = B->column / (size - 1);
	long long startA = i * sizeA;
	long long startB = i * sizeB;
	long long endA = min((i + 1) * sizeA, A->row);
	long long endB = min((i + 1) * sizeB, B->column);
	for (int rowA = startA; rowA < endA; rowA++)
	{
		for (int colB = startB; colB < endB; colB++)
		{
			C->data[rowA * B->column + colB] = 0;
			for (int prod = 0; prod < A->column; prod++)
			{
				C->data[rowA * B->column + colB] += A->data[rowA * A->column + prod] * B->data[prod * B->column + colB];
			}
		}
	}
}


void Optimized_Product(int isTimeTest)
{
	char order = 'Y';
	//接受指令Y后继续执行
	while (order == 'Y')
	{
		Matrix A, B, C;
		//输入A，B，将A*B保存至C
		cout << "\nInput the size of Matrix A: (row column)\n";
		cin >> A.row >> A.column;
		cout << "Input the size of Matrix B: (row column)\n";
		cin >> B.row >> B.column;
		A.data.resize(A.column * A.row);
		B.data.resize(B.column * B.row);
		if (A.column == B.row)
		{
			C.row = A.row;
			C.column = B.column;
			C.data.resize(C.column * C.row);
			cout << "\nWhich one do you like?\n   A: Random generation\n   B: Input yourself\n";
			char ch;
			cin >> ch;
			if (ch == 'B')
			{
				//输入A，B
				cout << "\nInput Matrix A:\n";
				for (long long i = 0; i < A.row * A.column; i++)
				{
					cin >> A.data[i];
				}
				cout << "Input Matrix B:\n";
				for (long long i = 0; i < B.row * B.column; i++)
				{
					cin >> B.data[i];
				}
			}
			else
			{
				//随机生成A，B并打印
				RandomFill(A.data, A.column * A.row);
				RandomFill(B.data, B.column * B.row);
				if (!isTimeTest)
				{
					cout << "\nMatrix A: \n";
					Print(A.data, A.row, A.column);
					cout << "Matrix B: \n";
					Print(B.data, B.row, B.column);
				}
			}

			/*
			* param thrNum 计划使用线程数
			* param CON 电脑当前可用线程数
			* param thrs 储存当前使用的线程
			*/
			long thrNum = max(min(A.row / 100, B.column / 100), (long long)2);
			const long CON = thread::hardware_concurrency();
			thrNum = min(CON == 0 ? 4 : CON, thrNum);
			thread* thrs = new thread[thrNum + 2];

			auto start = std::chrono::steady_clock::now();
			for (long i = 0; i < thrNum; i++)
			{
				thrs[i] = thread(Multiple_Thread, &A, &B, &C, i, thrNum);
			}
			for (long i = 0; i < thrNum; i++)
			{
				thrs[i].join();
			}
			auto end = std::chrono::steady_clock::now();


			if (!isTimeTest)
			{
				cout << "\nThe product of A and B:\n";
				Print(C.data, C.row, C.column);
			}
			else
			{
				cout
					<< "\nMatrix product of this size took "
					<< chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms ≈ "
					<< chrono::duration_cast<chrono::seconds>(end - start).count() << "s.\n";
				break;
			}
			cout << "\nDo you want to continue matrix product? (Y/N)\n";
			cin >> ch;
		}
		else
			cout << "\nWrong size, please try again!\n";
	}
}


void TestTime()
{
	char order = 'Y';
	//接受指令Y后继续执行
	while (order == 'Y')
	{
		cout << "\nWhich version do you want to test?\n   A: Basic version\n   B: Optimized version\n";
		char ch;
		cin >> ch;
		if (ch == 'A')
			Matrix_Product(1);
		else
			Optimized_Product(1);
		cout << "\nDo you want to continue time test? (Y/N)\n";
		cin >> order;
	}
}


int main()
{
	while (true)
	{
		//询问执行 矩阵乘法普通版 或 优化版 或 测试耗时
		cout << "Choose what you want:\n   A: Matrix product\n   B: Test time\n   C: End\n";
		char ch; // 用户选择
		cin >> ch;
		if (ch == 'A')
			Matrix_Product(0);
		else if (ch == 'B')
			TestTime();
		else break;
	}
}