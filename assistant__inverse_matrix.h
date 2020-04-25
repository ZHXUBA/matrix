#ifndef ASSISTANT__INVERSE_MATRIX
#define ASSISTANT__INVERSE_MATRIX

#include <vector>

using std::vector;


namespace _matrix {

	void transToREMatrix(vector<vector<double>>&);
	void transToLMMatrix(vector<vector<double>>&/*???????§ß???*/);
	vector<vector<double>> toInverseMatrix(vector<vector<double>> m/*?????*/);
	int exchangeRowK0(vector<vector<double>>&, int, int);
	void exchangeRow(vector<vector<double>>&, int, int);
	void rowDoubling(vector<vector<double>>& m, int handleR, double multiple, int r0);

	typedef vector<double> row_type;
	typedef vector<vector<double>> m_type;

	void transToREMatrix(vector<vector<double>>& m)
	{
		const int r = m.size();
		const int c = r > 0 ? m[0].size() : 0;
		int handleR = 1;
		//exchangeRowK0(m, handleR, 0);
		for (int i = 0; i < c; ++i)
		{
			exchangeRowK0(m, handleR, i + 1);
			if (m[handleR - 1][i] != 0)
			{
				double multi = 1;
				for (int j = handleR/*ha_R-1+1*/; j < r; ++j)
				{
					multi = -m[j][i];
					for (int index = 0; index < c; ++index)
					{
						m[j][index] *= m[handleR - 1][i];
					}
					rowDoubling(m, j + 1, multi, handleR);
				}
				++handleR;
			}
			if (handleR == r + 1)
				break;
		}
	}

	void transToLMMatrix(vector<vector<double>>& m)
	{
		//transToREMatrix(m);
		const int r = m.size();
		const int c = r > 0 ? m[0].size() : 0;
		for (int i = r - 1; i >= 0; --i)
		{
			int j;
			for (j = 0; j < c; ++j)
			{
				if (m[i][j] != 0)
					break;
			}
			if (j != c)
			{
				double multi = 1;
				for (int k = i - 1; k >= 0; --k)
				{
					multi = -m[k][j];
					for (int index = 0; index < c; ++index)
					{
						m[k][index] *= m[i][j];
					}
					rowDoubling(m, k + 1, multi, i + 1);
				}
			}
		}
		double index = -1;
		double ele = 1;
		for (int i = 0; i < r; ++i)
		{
			index = -1;
			for (int j = 0; j < c; ++j)
			{
				if (m[i][j] != 0 && index == -1)
				{
					index = j;
					ele = m[i][index];
					m[i][j] = 1;
				}
				else if (index != -1)
					m[i][j] = m[i][i] == 0 ? 0 : m[i][j] / ele;
			}
		}
	}

	void exchangeRow(vector<vector<double>>& m, int r1, int r2)
	{
		//TO:Exchange the r1_th and r2_th row.
		const int r = m.size();
		const int c = r > 0 ? m[0].size() : 0;
		double helper = 0.0;
		for (int j = 0; j < c; ++j)
		{
			helper = m.at(r1 - 1).at(j);
			m.at(r1 - 1).at(j) = m.at(r2 - 1).at(j);
			m.at(r2 - 1).at(j) = helper;
		}
	}

	void rowDoubling(vector<vector<double>>& m, int handleR, double multiple, int r0)
	{
		const int c = m.size() > 0 ? m[0].size() : 0;
		for (int j = 0; j < c; ++j)
		{
			m.at(handleR - 1).at(j) += multiple * m.at(r0 - 1).at(j);
		}
	}

	//vector<vector<double>> createDanMatirc(int n)
	//{
	//	int c = 0, r = 0;
	//	c = r = n;
	//	vector<vector<double>> matrix;
	//	vector<double> row;
	//	for (; c >= 1; c--)
	//		row.push_back(0);
	//	for (; r >= 1; r--)
	//		matrix.push_back(row);
	//	for (int i = 0; i < n; ++i)
	//	{
	//		matrix.at(i).at(i) = 1;
	//	}
	//	return matrix;
	//}

	vector<vector<double>> toInverseMatrix(vector<vector<double>> m)
	{

		const int r = m.size();
		m_type FM;
		for (int i = 0; i < r; ++i)
		{
			row_type row;
			for (int j = 0; j < 2 * r; ++j)
			{
				if (j < r)
					row.push_back(m[i][j]);
				else
					row.push_back(i == (j - r) ? 1 : 0);
			}
			FM.push_back(row);
		}
		//printMatrix_vector(FM);
		//process FM to [E, A_Inversed].
		transToREMatrix(FM); transToREMatrix(FM);
		//printMatrix_vector(FM);
		transToLMMatrix(FM);
		//printMatrix_vector(FM);
		m_type InvM;
		for (int i = 0; i < r; ++i)
		{
			row_type row;
			for (int j = 0; j < r; ++j)
			{
				row.push_back(FM[i][j + r]);
			}
			InvM.push_back(row);
		}
		//printMatrix_vector(InvM);
		return InvM;
	}

	int exchangeRowK0(vector<vector<double>>& m, int handleR, int handleC)
	{
		//TO:Exchange tow rows to kill zero
		//RETURN:The row number exchanged with the handleR_th row,namely handledR.
		//Include the special situation,all elements is 0:dou't exchange.
		if (m[handleR - 1][handleC - 1] != 0)
			return handleR;
		const int r = m.size();
		const int c = r > 0 ? m[0].size() : 0;
		int i;//the index,from handleR-1 to r-1.
		for (i = handleR - 1; i < r; ++i)
		{
			if (m.at(i).at(handleC - 1) != 0)
			{
				exchangeRow(m, i + 1, handleR);
				break;
			}
		}
		return i + 1;
	}

} // the end of namespace _matrix



#endif // !ASSISTANT__INVERSE_MATRIX

