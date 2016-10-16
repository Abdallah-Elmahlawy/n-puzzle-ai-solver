#include "AStar.h"
int main()
{
	char choice;
	vector < vector<int> > arr;
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int n;
	cin >> n;

	vector<int> temp;
	for (int i = 0; i < n; i++)
	{
		int var;
		for (int j = 0; j < n; j++)
		{
			cin >> var;
			temp.push_back(var);
		}
		arr.push_back(temp);
		temp.clear();
	}

	N_Puzzle Test(arr);
	Tree testtree;
	//cout << "For A* press 'a' , For BFS press 'b' :" << endl;
	cin >> choice;
	if (choice == 'a')
	{
		//cout << "For Hamming Distance press 'h' , Manhattan Distance press 'm' : " << endl;
		cin >> choice;
		testtree.CheckSolvability(Test, choice);
	}
	else if (choice == 'b')
		testtree.Breadth_First_Search(Test);

	return 0;
}