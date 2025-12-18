#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_SIZE = 5; // 最大矩阵尺寸
const double EPS = 1e-10; // 判断是否为0的容差

// 函数声明
void printMatrix(double matrix[][MAX_SIZE], int rows, int cols);
void reducedRowEchelonForm(double matrix[][MAX_SIZE], int rows, int cols);
void swapRows(double matrix[][MAX_SIZE], int row1, int row2, int cols);

int main() {
	double matrix[MAX_SIZE][MAX_SIZE];
	int rows, cols;

	// 输入矩阵尺寸
	cout << "请输入矩阵的行数 (1-" << MAX_SIZE << "): ";
	cin >> rows;
	cout << "请输入矩阵的列数 (1-" << MAX_SIZE << "): ";
	cin >> cols;

	// 输入矩阵元素
	cout << "请输入矩阵元素，按行输入:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> matrix[i][j];
		}
	}

	cout << "原始矩阵:" << endl;
	printMatrix(matrix, rows, cols);

	// 计算简化行阶梯形
	reducedRowEchelonForm(matrix, rows, cols);

	cout << "简化行阶梯形矩阵 (RREF):" << endl;
	printMatrix(matrix, rows, cols);

	return 0;
}

// 打印矩阵
void printMatrix(double matrix[][MAX_SIZE], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// 判断是否为0（考虑浮点数误差）
			if (fabs(matrix[i][j]) < EPS) {
				cout << setw(10) << "0.00";
			} else {
				cout << setw(10) << fixed << setprecision(4) << matrix[i][j];
			}
		}
		cout << endl;
	}
}

// 交换两行
void swapRows(double matrix[][MAX_SIZE], int row1, int row2, int cols) {
	for (int j = 0; j < cols; j++) {
		double temp = matrix[row1][j];
		matrix[row1][j] = matrix[row2][j];
		matrix[row2][j] = temp;
	}
}

// 将矩阵化为简化行阶梯形
void reducedRowEchelonForm(double matrix[][MAX_SIZE], int rows, int cols) {
	int lead = 0; // 主元所在的列

	for (int r = 0; r < rows; r++) {
		if (lead >= cols) {
			return;
		}

		int i = r;

		// 找到主元所在的行（当前列中绝对值最大的元素）
		while (fabs(matrix[i][lead]) < EPS) {
			i++;
			if (i == rows) {
				i = r;
				lead++;
				if (lead == cols) {
					return;
				}
			}
		}

		// 交换当前行和主元所在行
		if (i != r) {
			swapRows(matrix, i, r, cols);
		}

		// 主元归一化：将主元所在行除以主元值
		double pivot = matrix[r][lead];
		if (fabs(pivot) > EPS) {
			for (int j = 0; j < cols; j++) {
				matrix[r][j] /= pivot;
			}
		}

		// 消元：将主元所在列的其他元素消为0
		for (int i = 0; i < rows; i++) {
			if (i != r) {
				double factor = matrix[i][lead];
				for (int j = 0; j < cols; j++) {
					matrix[i][j] -= factor * matrix[r][j];
				}
			}
		}

		lead++;
	}
}