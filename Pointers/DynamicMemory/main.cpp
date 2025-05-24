﻿#include<iostream>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

void FillRand(int arr[], const int n);
void FillRand(double arr[], const int n);
void FillRand(int** arr, const int rows, const int cols);
void FillRand(double** arr, const int rows, const int cols);

template<typename T>void Print(T arr[], const int n);
template<typename T>void Print(T** arr, const int rows, const int cols);

template<typename T>T* push_back(T arr[], int& n, const T value);
template<typename T>T* push_front(T arr[], int& n, const T value);
template<typename T>T* insert(T arr[], int& n, const T value, int index);

template<typename T>T* pop_back(T arr[], int& n);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);

template<typename T>void push_col_back(T** arr, const int rows, int& cols);
template<typename T>void pop_col_back(T** arr, const int rows, int& cols);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

#define DATA_TYPE double

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	double* arr = new double[n];

	FillRand(arr, n);
	Print(arr, n);
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << *(arr + i) << "\t";
	}
	cout << endl;
	/*
	----------------------------------
	+, -, ++, --;
	----------------------------------
	*/

	double value;
	cout << "Введите добавляемое значение: "; cin >> value;

	arr = push_back(arr, n, value);

	//7) Значение добавлено, проверяем результат:
	Print(arr, n);


	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_back(arr, n), n);
	Print(arr = pop_back(arr, n), n);
	Print(arr, n);
	Print(arr, n);
	Print(arr, n);
	Print(arr, n);
	Print(arr, n);
	Print(arr, n);
	Print(arr, n);
	Print(arr, n);

	delete[] arr;
	//Memory leak  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	typedef double DataType;	//сущестующему типу данных дает второе имя

	//1) Создаем массив указателей:
	DataType** arr = new DataType * [rows];

	//2) Выделяем память под строки двумерного динамического массива:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new DataType[cols];
	}

	/*cout << "Память выделена, для добавления столбца";
	system("PAUSE");

	push_col_back(arr, rows, cols);

	cout << "Столбец добавлен" << endl;*/

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	//int   - 'int';
	//int*  - Указатель на 'int';
	//int** - Указатель на указатель на 'int';

	arr = push_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	pop_col_back(arr, rows, cols);
	Print(arr, rows, cols);

	//1) Сначала удаляем строки:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) Удаляем массив указателей:
	delete[] arr;
#endif // DYNAMIC_MEMORY_2


}

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
		//Index operator, Subscript operator;
	}
}
void FillRand(double arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 10000;
		arr[i] /= 100;
		//Index operator, Subscript operator;
	}
}

void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}
void FillRand(double** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = double(rand() % 10000) / 100;
		}
	}
}

template<typename T>void Print(T arr[], const int n)
{
	cout << arr << ":\n";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
template<typename T>void Print(T** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
	cout << delimiter << endl;
	cout << endl;
}

template<typename T>T* push_back(T arr[], int& n, const T value)
{

	//1) Создаем буферный массив нужного размера:
	T* buffer = new T[n + 1];

	//2) Копируем все содержимое исходного массива в буферный:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}

	//3) Удаляем исходный массив:
	delete[] arr;

	//4) Подменяем адрес в указателе 'arr' адресом нового массива:
	arr = buffer;

	//5) Только после всего этого в конце массива появляется элемент, 
	//	 в который можно сохранить добавляемое значение:
	arr[n] = value;

	//6) После того как в массив добавился элемент, 
	//	 количество его элементов увеличивается на 1:
	n++;

	return arr;
}

template<typename T>T* push_front(T arr[], int& n, const T value)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[0] = value;
	n++;
	return buffer;
}
template<typename T>T* insert(T arr[], int& n, const T value, int index)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < index; i++)
		buffer[i] = arr[i];
	for (int i = index; i < n; i++)
		buffer[i + 1] = arr[i];
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

template<typename T>T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	//1) Создаем буферный массив указателей нужного размера:
	T** buffer = new T * [rows + 1];

	//2) Копируем адреса строк в буферный массив указателей:
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}

	//3) Удаляем исходный массив указателей:
	delete[] arr;

	//4) Создаем добавляемую строку, и записываем ее адрес в массив указателей:
	buffer[rows] = new T[cols]{};

	//5) При добавлении в массив строки, количество его строк увеличивается на 1:
	rows++;

	//6) Возвращаем новый массив на место вывоза:
	return buffer;
}
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	T** buffer = new T * [--rows];
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[] arr[rows];	//Удаление строки
	delete[] arr;		//Удаление массива указателей
	return buffer;
}
template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols + 1]{};
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}
template<typename T>void pop_col_back(T** arr, const int rows, int& cols)
{
	cols--;
	for (int i = 0; i < rows; i++)
	{
		T* buffer = new T[cols];
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
}