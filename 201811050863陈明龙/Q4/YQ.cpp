#include<iostream>
using namespace std;
int main()
{
	int n, m;//�����к���
	int b, c;
	c = 0;
	cout << "��������,����" << endl;
	cin >> n >> m;
	cout << "������������" << endl;
	cin >> b;
	cout << "�������ͼ���飺" << endl;
	//��̬�����ά���鲢���и�ֵ
	char** a = new char* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new char[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[i][j];
		}
	}
	while (c < b)
	{
		c++;
		int i = 0;
		for (i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (a[i][j] == 'X')
				{
					if (i + 1 < n && a[i + 1][j] == 'O')
					{
						a[i + 1][j] = 'd';
					}
					if (j + 1 < m && a[i][j + 1] == 'O')
					{
						a[i][j + 1] = 'd';
					}
					if (i - 1 >= 0 && a[i - 1][j] == 'O')
					{
					a[i - 1][j] = 'd';
					}
					if (j - 1 >= 0 && a[i][j - 1] == 'O')
					{
						a[i][j - 1] = 'd';
					}
							
						
				}
			}
		}
		for (i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (a[i][j] == 'd')
					a[i][j] = 'X';
			}
		}

	}

	//�����ά����
	cout << "��ά����Ϊ" << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}