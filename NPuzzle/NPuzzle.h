#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <iterator>
#include <utility>
#include <unordered_set>
#include <time.h>
#include <string>

using namespace std;

class N_Puzzle {
private:


public:
	string HashValue;
	int theSize, emptyXCoor, emptyYCoor, hVal, gVal, fVal;
	vector<vector<int>> thePuzzle;

	enum positions { center, edge, corner };
	positions emptyPosition;

	enum direction { up = 0, down = 1, right = 2, left = 3 };


	//Default constuctor.
	N_Puzzle() {
		theSize = 0;
		emptyXCoor = 0;
		emptyYCoor = 0;
		thePuzzle.clear();
		HashValue = "";
	}

	// constructor with one parameter.
	N_Puzzle(vector<vector<int>> puzzle) : theSize(puzzle.size()), gVal(0){
		vector <int> temp;
		for (int i = 0; i < theSize; ++i) {
			for (int j = 0; j < theSize; j++)
			{
				temp.push_back(puzzle[i][j]);
				if (puzzle[i][j] == 0)
					theEmptyPosition(theSize, i, j);
			}
			thePuzzle.push_back(temp);
			temp.clear();
		}
		theEmptyPosition(theSize, emptyXCoor, emptyYCoor);
		hVal = ManhattanDistance();
		fVal = hVal + gVal;
		HashValue = Hash_Function();
	}

	//Copy constructor
	N_Puzzle(const N_Puzzle& aPuzzle) {
		theSize = aPuzzle.theSize;
		emptyXCoor = aPuzzle.emptyXCoor;
		emptyYCoor = aPuzzle.emptyYCoor;
		emptyPosition = aPuzzle.emptyPosition;
		gVal = aPuzzle.gVal;
		hVal = aPuzzle.hVal;
		fVal = aPuzzle.fVal;
		HashValue = aPuzzle.HashValue;

		vector <int> temp;
		for (int i = 0; i < theSize; ++i) {
			for (int j = 0; j < theSize; j++)
			{
				temp.push_back(aPuzzle.thePuzzle[i][j]);
			}
			thePuzzle.push_back(temp);
			temp.clear();
		}
	}

	//Overloading the = operator
	N_Puzzle& operator =(const N_Puzzle& aPuzzle) {
		for (int i = 0; i < theSize; ++i)
			thePuzzle[i].clear();
		thePuzzle.clear();

		theSize = aPuzzle.theSize;
		emptyXCoor = aPuzzle.emptyXCoor;
		emptyYCoor = aPuzzle.emptyYCoor;
		emptyPosition = aPuzzle.emptyPosition;
		gVal = aPuzzle.gVal;
		hVal = aPuzzle.hVal;
		fVal = aPuzzle.fVal;
		HashValue = aPuzzle.HashValue;

		vector <int> temp;
		for (int i = 0; i < theSize; ++i) {
			for (int j = 0; j < theSize; j++)
			{
				temp.push_back(aPuzzle.thePuzzle[i][j]);
			}
			thePuzzle.push_back(temp);
			temp.clear();
		}
		return *(this);
	}

	//Overloading the == operator 
	bool operator ==(const N_Puzzle& Puzzle1) {
		if (HashValue == Puzzle1.HashValue)
			return true;
		else
			return false;
	}

	//Overloading the < operator 
	bool operator <(const N_Puzzle& Puzzle1) {
		return fVal < Puzzle1.fVal;
	}

	//Overloading the > operator 
	bool operator >(const N_Puzzle& Puzzle1) {
		return fVal > Puzzle1.fVal;
	}

	//Determining whether the empty postion is an Edge , Corner or Center.
	void theEmptyPosition(int n, int xIdx, int yIdx) {
		if ((xIdx == 0 || xIdx == n - 1) && (yIdx == 0 || yIdx == n - 1))
			emptyPosition = corner;
		else if ((xIdx != 0 && xIdx != n - 1) && (yIdx != 0 && yIdx != n - 1))
			emptyPosition = center;
		else
			emptyPosition = edge;
		emptyXCoor = xIdx;
		emptyYCoor = yIdx;
	}

	//Determining whether a move can be done or not.
	bool isValid(direction movement)
	{
		if (emptyPosition == center)
			return true;
		else if (emptyPosition == corner) {
			if (emptyXCoor == 0 && emptyYCoor == 0) {
				if (movement == right || movement == down)
					return true;
			}
			else if (emptyXCoor == 0 && emptyYCoor == theSize - 1){
				if (movement == left || movement == down)
					return true;
			}
			else if (emptyXCoor == theSize - 1 && emptyYCoor == 0){
				if (movement == right || movement == up)
					return true;
			}
			else if (emptyXCoor == theSize - 1 && emptyYCoor == theSize - 1){
				if (movement == left || movement == up)
					return true;
			}
		}
		else {
			if (emptyXCoor == 0){
				if (movement == left || movement == right || movement == down)
					return true;
			}
			else if (emptyYCoor == 0){
				if (movement == right || movement == up || movement == down)
					return true;
			}
			else if (emptyXCoor == theSize - 1){
				if (movement == left || movement == right || movement == up)
					return true;
			}
			else if (emptyYCoor == theSize - 1){
				if (movement == left || movement == up || movement == down)
					return true;
			}
		}
		return false;
	}

	//Make move function
	N_Puzzle& move(direction movement) {
		if (isValid(movement))
		{
			if (movement == up) {
				swap(thePuzzle[emptyXCoor][emptyYCoor], thePuzzle[emptyXCoor - 1][emptyYCoor]);
				--emptyXCoor;
				theEmptyPosition(theSize, emptyXCoor, emptyYCoor);
				++gVal;
				HashValue = Hash_Function();
				return *(this);
			}
			else if (movement == down) {
				swap(thePuzzle[emptyXCoor][emptyYCoor], thePuzzle[emptyXCoor + 1][emptyYCoor]);
				++emptyXCoor;
				theEmptyPosition(theSize, emptyXCoor, emptyYCoor);
				++gVal;
				HashValue = Hash_Function();
				return *(this);
			}
			else if (movement == right) {
				swap(thePuzzle[emptyXCoor][emptyYCoor], thePuzzle[emptyXCoor][emptyYCoor + 1]);
				++emptyYCoor;
				theEmptyPosition(theSize, emptyXCoor, emptyYCoor);
				++gVal;
				HashValue = Hash_Function();
				return *(this);
			}
			else if (movement == left) {
				swap(thePuzzle[emptyXCoor][emptyYCoor], thePuzzle[emptyXCoor][emptyYCoor - 1]);
				--emptyYCoor;
				theEmptyPosition(theSize, emptyXCoor, emptyYCoor);
				++gVal;
				HashValue = Hash_Function();
				return *(this);
			}
		}
		return (*this);
	}

	//Determining whether a state is goal state or not
	bool isGoal()
	{
		for (int i = 0; i < theSize; i++)
		{
			for (int j = 0; j < theSize; j++)
			{
				if (thePuzzle[i][j] != 0 && thePuzzle[i][j] != ((i * theSize) + (j + 1)))
					return false;
			}
		}
		return true;
	}

	//Calculating the Hamming distance (misplaced tiles) for a given state
	int HammingDistance()
	{
		int Hamming = 0;
		for (int i = 0; i < theSize; i++)
		{
			for (int j = 0; j < theSize; j++)
			{
				if (thePuzzle[i][j] != 0 && thePuzzle[i][j] != ((i * theSize) + (j + 1)))
					Hamming++;
				else
					continue;
			}
		}
		return Hamming;
	}

	//Calculating the Manhattan distance (number of steps between every element and its goal destintion) for a given state
	int ManhattanDistance()
	{
		int Manhattan = 0;
		for (int i = 0; i < theSize; i++)
		{
			for (int j = 0; j < theSize; j++)
			{
				if (thePuzzle[i][j] != 0)
				{
					int value = thePuzzle[i][j];
					int targetX = (value - 1) / theSize;
					int targetY = (value - 1) % theSize;
					int xx = i - targetX;
					int yy = j - targetY;
					Manhattan += (abs(xx) + abs(yy));
				}
			}
		}
		return Manhattan;
	}

	//Printing the Puzzle
	void print()
	{
		for (int i = 0; i < theSize; i++)
		{
			for (int j = 0; j < theSize; j++)
			{
				cout << thePuzzle[i][j] << " ";
			}
			cout << endl;
		}
	}


	// sort given Array and Return Number of Inversion.
	int mergeSort(int arr[], int array_size)
	{
		int *temp = (int *)malloc(sizeof(int)*array_size);
		return _mergeSort(arr, temp, 0, array_size - 1);
	}
	int _mergeSort(int arr[], int temp[], int left, int right)
	{
		int mid, inv_count = 0;
		if (right > left)
		{
			/* Divide the array into two parts and call _mergeSortAndCountInv()
			for each of the parts */
			mid = (right + left) / 2;

			/* Inversion count will be sum of inversions in left-part, right-part
			and number of inversions in merging */
			inv_count = _mergeSort(arr, temp, left, mid);
			inv_count += _mergeSort(arr, temp, mid + 1, right);

			/*Merge the two parts*/
			inv_count += merge(arr, temp, left, mid + 1, right);
		}
		return inv_count;
	}
	int merge(int arr[], int temp[], int left, int mid, int right)
	{
		int i, j, k;
		int inv_count = 0;

		i = left; /* i is index for left subarray*/
		j = mid;  /* i is index for right subarray*/
		k = left; /* i is index for resultant merged subarray*/
		while ((i <= mid - 1) && (j <= right))
		{
			if (arr[i] <= arr[j])
			{
				temp[k++] = arr[i++];
			}
			else
			{
				temp[k++] = arr[j++];

				/*this is tricky -- see above explanation/diagram for merge()*/
				inv_count = inv_count + (mid - i);
			}
		}

		/* Copy the remaining elements of left subarray
		(if there are any) to temp*/
		while (i <= mid - 1)
			temp[k++] = arr[i++];

		/* Copy the remaining elements of right subarray
		(if there are any) to temp*/
		while (j <= right)
			temp[k++] = arr[j++];

		/*Copy back the merged elements to original array*/
		for (i = left; i <= right; i++)
			arr[i] = temp[i];

		return inv_count;
	}


	//Check if Puzzle Solvable or Not.
	bool isSolvable() {
		int k = 0;
		int *Temp = new int[theSize*theSize];
		for (int i = 0; i < theSize; ++i) {
			for (int j = 0; j < theSize; ++j) {
				if (thePuzzle[i][j] != 0)
					Temp[k++] = (thePuzzle[i][j]);
			}
		}
		int inversion_count = mergeSort(Temp, k);

		// It's Solvable
		if ((theSize % 2 != 0 && inversion_count % 2 == 0))
			return true;
		else if ((theSize % 2 == 0) && (inversion_count % 2 != 0) && ((theSize - emptyXCoor) % 2 == 0))
			return true;
		else if ((theSize % 2 == 0) && (inversion_count % 2 == 0) && ((theSize - emptyXCoor) % 2 != 0))
			return true;

		// It's NotSolvable
		else
			return false;
	}



	// Give Value (Key) to The Puzzle.
	string Hash_Function() {
		string str = "";
		for (int i = 0; i < theSize; ++i)
		{
			for (int j = 0; j < theSize; ++j)
			{
				str += to_string(thePuzzle[i][j]);
			}
		}
		return str;
	}

};