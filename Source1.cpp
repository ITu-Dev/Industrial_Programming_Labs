#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;




int main()
{
	setlocale(LC_ALL, "RUSSION");
	srand(time(NULL));
	int matHeight1, matWidth1, matHeight2, matWidth2, initVariant, updMatSize = 2;
	system("chcp 1251");
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Ввод размеров матрицы пользователем////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	cout << "Введите размеры первой матрицы\n";
	int** originalMat1 = createMatWithInputs(matHeight1, matWidth1);

	cout << "Введите размеры второй матрицы\n";
	int** originalMat2 = createMatWithInputs(matHeight2, matWidth2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выбор способа заполнения и заполнение матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	do
	{
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> initVariant;
	} while (initVariant < 1 || initVariant > 2);
	switch (initVariant)
	{
	case 1:
		initMat(originalMat1, matHeight1, matWidth1);
		cout << "\nМатрица 1\n\n";
		printMat(originalMat1, matHeight1, matWidth1);

		initMat(originalMat2, matHeight2, matWidth2);
		cout << "\nМатрица 2\n\n";
		printMat(originalMat2, matHeight2, matWidth2);

		break;
	case 2:
		initMatRandom(originalMat1, matHeight1, matWidth1);
		cout << "\nМатрица 1\n\n";
		printMat(originalMat1, matHeight1, matWidth2);

		initMatRandom(originalMat2, matHeight2, matWidth2);
		cout << "\nМатрица 2\n\n";
		printMat(originalMat2, matHeight2, matWidth2);
		break;
	}

	///////////////////////////////////////////////////////////////////////////////
	/////////////////Приведение матриц к требуемому размеру////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	while (updMatSize < matHeight1 || updMatSize < matHeight2 || updMatSize < matWidth1 || updMatSize < matWidth2)
		updMatSize *= 2;

	int** updMat1 = updatedMat(originalMat1, matHeight1, matWidth1, updMatSize);
	int** updMat2 = updatedMat(originalMat2, matHeight2, matWidth2, updMatSize);

	cout << "Приведенные матрицы\n";

	cout << "\nМатрица 1\n\n";
	printMat(updMat1, updMatSize, updMatSize);

	cout << "\nМатрица 2\n\n";
	printMat(updMat2, updMatSize, updMatSize);

	///////////////////////////////////////////////////////////////////////////////
	///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** subMat1_1 = getSubmat(updMat1, updMatSize, 0, 0);
	int** subMat2_1 = getSubmat(updMat1, updMatSize, 0, updMatSize / 2);
	int** subMat3_1 = getSubmat(updMat1, updMatSize, updMatSize / 2, 0);
	int** subMat4_1 = getSubmat(updMat1, updMatSize, updMatSize / 2, updMatSize / 2);
	int** subMat1_2 = getSubmat(updMat2, updMatSize, 0, 0);
	int** subMat2_2 = getSubmat(updMat2, updMatSize, 0, updMatSize / 2);
	int** subMat3_2 = getSubmat(updMat2, updMatSize, updMatSize / 2, 0);
	int** subMat4_2 = getSubmat(updMat2, updMatSize, updMatSize / 2, updMatSize / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Создание промежуточных матриц//////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** intermediateMat1 = createMat(updMatSize / 2);
	int** intermediateMat2 = createMat(updMatSize / 2);
	int** intermediateMat3 = createMat(updMatSize / 2);
	int** intermediateMat4 = createMat(updMatSize / 2);
	int** intermediateMat5 = createMat(updMatSize / 2);
	int** intermediateMat6 = createMat(updMatSize / 2);
	int** intermediateMat7 = createMat(updMatSize / 2);


	///////////////////////////////////////////////////////////////////////////////
	////////////////////Вычисление значений промежуточных матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < updMatSize / 2; i++)
	{
		for (int j = 0; j < updMatSize / 2; j++)
		{
			intermediateMat1[i][j] = 0;
			intermediateMat2[i][j] = 0;
			intermediateMat3[i][j] = 0;
			intermediateMat4[i][j] = 0;
			intermediateMat5[i][j] = 0;
			intermediateMat6[i][j] = 0;
			intermediateMat7[i][j] = 0;
			for (int z = 0; z < updMatSize / 2; z++)
			{
				intermediateMat1[i][j] += (subMat1_1[i][z] + subMat4_1[i][z]) * (subMat1_2[z][j] + subMat4_2[z][j]);
				intermediateMat2[i][j] += (subMat3_1[i][z] + subMat4_1[i][z]) * subMat1_2[z][j];
				intermediateMat3[i][j] += (subMat1_1[i][z] * (subMat2_2[z][j] - subMat4_2[z][j]);
				intermediateMat4[i][j] += (subMat4_1[i][z] * (subMat3_2[z][j] - subMat1_2[z][j]);
				intermediateMat5[i][j] += (subMat1_1[i][z] + subMat2_1[i][z]) * subMat4_2[z][j];
				intermediateMat6[i][j] += (subMat3_1[i][z] - subMat1_1[i][z]) * (subMat1_2[z][j] + subMat2_2[z][j]);
				intermediateMat7[i][j] += (subMat2_1[i][z] - subMat4_1[i][z]) * (subMat3_2[z][j] + subMat4_2[z][j]);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////Создание вспомогательных матриц/////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** supportingMat1 = createMat(updMatSize / 2);
	int** supportingMat2 = createMat(updMatSize / 2);
	int** supportingMat3 = createMat(updMatSize / 2);
	int** supportingMat4 = createMat(updMatSize / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////Подсчет значений вспомогательных матриц из промежуточных///////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < updMatSize / 2; i++)
	{
		for (int j = 0; j < updMatSize / 2; j++)
		{
			supportingMat1[i][j] = intermediateMat1[i][j] + intermediateMat4[i][j] - intermediateMat5[i][j] + intermediateMat7[i][j];
			supportingMat2[i][j] = intermediateMat3[i][j] + intermediateMat5[i][j];
			supportingMat3[i][j] = intermediateMat2[i][j] + intermediateMat4[i][j];
			supportingMat4[i][j] = intermediateMat1[i][j] - intermediateMat2[i][j] + intermediateMat3[i][j] + intermediateMat6[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Создание результирующей матрицы/////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** resaultMat = createMat(updMatSize);


	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < updMatSize / 2; i++)
	{
		for (int j = 0; j < updMatSize / 2; j++)
		{
			resaultMat[i][j] = supportingMat1[i][j];
			resaultMat[i][j + updMatSize / 2] = supportingMat2[i][j];
			resaultMat[i + updMatSize / 2][j] = supportingMat3[i][j];
			resaultMat[i + updMatSize / 2][j + updMatSize / 2] = supportingMat4[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int x = 0, f = 100, s = 100;
	for (int i = 0; i < updMatSize; i++)
	{
		x = 0;
		for (int j = 0; j < updMatSize; j++)
		{
			if (resaultMat[i][j] != 0)
			{
				x++;
				f = 100;
				s = 100;
			}
		}
		if (x == 0 && i < f)
		{
			f = i;
		}
		if (x == 0 && i < s)
		{
			s = i;
		}
	}

	int** alignResaultMat = new int*[f];
	for (int i = 0; i < f; i++)
	{
		alignResaultMat[i] = new int[s];
		for (int j = 0; j < s; j++)
			alignResaultMat[i][j] = resaultMat[i][j];
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Вывод результирующей матрицы////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	cout << "\nРезультирующая матрица\n\n";
	printMat(alignResaultMat, f, s);


	system("pause");

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////Очистка динамической памяти///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	deleteMat(matrix1, matHeight1);
	deleteMat(originalMat2, matHeight2);
	deleteMat(updMat1, updMatSize);
	deleteMat(updMat2, updMatSize);
	deleteMat(resaultMat, updMatSize);
	deleteMat(alignResaultMat, f);
	deleteMat(subMat1_1, updMatSize / 2);
	deleteMat(subMat2_1, updMatSize / 2);
	deleteMat(subMat3_1, updMatSize / 2);
	deleteMat(subMat4_1, updMatSize / 2);
	deleteMat(subMat1_2, updMatSize / 2);
	deleteMat(subMat2_2, updMatSize / 2);
	deleteMat(subMat3_2, updMatSize / 2);
	deleteMat(subMat4_2, updMatSize / 2);
	deleteMat(supportingMat1, updMatSize / 2);
	deleteMat(supportingMat2, updMatSize / 2);
	deleteMat(supportingMat3, updMatSize / 2);
	deleteMat(supportingMat4, updMatSize / 2);
	deleteMat(intermediateMat1, updMatSize / 2);
	deleteMat(intermediateMat2, updMatSize / 2);
	deleteMat(intermediateMat3, updMatSize / 2);
	deleteMat(intermediateMat4, updMatSize / 2);
	deleteMat(intermediateMat5, updMatSize / 2);
	deleteMat(intermediateMat6, updMatSize / 2);
	deleteMat(intermediateMat7, updMatSize / 2);


	delete[] matrix1, originalMat2, updMat1, updMat2, resaultMat, alignResaultMat;
	delete[] subMat1_1, subMat2_1, subMat3_1, subMat4_1, subMat1_2, subMat2_2, subMat3_2, subMat4_2, supportingMat1, supportingMat2, supportingMat3, supportingMat4;
	delete[] intermediateMat1, intermediateMat2, intermediateMat3, intermediateMat4, intermediateMat5, intermediateMat6, intermediateMat7;


	return 0;
}

int** createMatWithInputs(int &n, int &m) {
	do
	{
		cin >> n >> m;
	} while (n <= 0 && m <= 0);

	int** mat = createMat(n, m);
	return mat;
}


int** createMat(int n, int m) {
	int** mat = new int*[n];
	for (int i = 0; i < a; i++)
	{
		mat[i] = new int[m];
	}
	return mat;
}


int** createMat(int l) {
	int** mat = new int*[l];
	for (int i = 0; i < l; i++)
	{
		mat[i] = new int[l];
	}
	return mat;
}

void initMat(int** mat, int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> mat[i][j];
}

void initMatRandom(int** mat, int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat[i][j] = rand() % 10;
}

void printMat(int** mat, int n, int m) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

int** updatedMat(int** mat, int n, int m, int l) {

	int** newMat = createMat(l);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			newMat[i][j] = mat[i][j];

	}
	return newMat;
}

int** getSubmat(int** mat, int l, int k_i, int k_j) {
	int** submat = new int*[l / 2];
	for (int i = 0; i < l / 2; i++)
	{
		submat[i] = new int[l / 2];
		for (int j = 0; j < l / 2; j++)
			submat[i][j] = mat[i + k_i][j + k_j];
	}

	return submat;
}

void deleteMat(int** mat, int n) {
	for (int i = 0; i < n; i++)
		delete[] mat[i];
}