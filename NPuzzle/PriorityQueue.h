#pragma once
#include"NPuzzle.h"

class Priority_Queue
{
private:
	int ListSize, HeapSize;

public:
	vector<N_Puzzle> List;
	map<string, int> Hash;
	// Default Constructor.
	Priority_Queue() {
		List.clear();
		List.resize(1e5);
		ListSize = List.size();
		HeapSize = -1;
	}

	// Check if the Heap empty or Not.
	bool isEmpty() {
		return HeapSize < 0;
	}

	// Return List Size.
	int GetListSize() {
		return HeapSize;
	}

	// Return Minimum in Heap.
	N_Puzzle Heap_Minimum() {
		return List[0];
	}

	// Return Minimum in Heap and Remove it form the Heap.
	N_Puzzle Heap_Extract_Min() {

		N_Puzzle Min = List[0];
		Hash.erase(List[0].HashValue);
		if (HeapSize != 0) {
			List[0] = List[HeapSize];
			Hash[List[HeapSize].HashValue] = 0;
		}
		HeapSize--;
		Min_Heapify(0);
		return Min;

	}

	// Insert new Key in the Heap.
	void Heap_Insert(N_Puzzle& Key) {
		HeapSize++;
		Decrease_Key(HeapSize, Key);
	}

	// Remove puzzle from OpenList.
	void Remove(N_Puzzle& Key, int i) {
		Hash.erase(Key.HashValue);
		List[i] = List[HeapSize];
		Hash[List[HeapSize].HashValue] = i;
		HeapSize--;
		Min_Heapify(i);
	}

private:
	// Return index of Parent.
	int Parent(int i) {
		return floor((i / 2));
	}

	// Return index of Left.
	int Left(int i) {
		return i * 2;
	}

	// Return index of Right.
	int Right(int i) {
		return (i * 2) + 1;
	}

	// Let Heap in Min_Heapify Properety.
	void Min_Heapify(int i) {
		int L = Left(i);
		int R = Right(i);
		int Smallest = i;
		if ((L <= HeapSize) && (List[L] < List[i]))
			Smallest = L;
		if ((R <= HeapSize) && (List[R] < List[Smallest]))
			Smallest = R;

		if (Smallest != i) {
			swap(List[i], List[Smallest]);
			Hash[List[i].HashValue] = i;
			Hash[List[Smallest].HashValue] = Smallest;
			Min_Heapify(Smallest);
		}
	}

	// Used in Insert Function to Let Heap in Min_Heapify Properety.
	void Decrease_Key(int i, N_Puzzle& Key) {
		List[i] = Key;
		Hash.emplace(Key.HashValue, i);
		while ((i > 0) && (List[Parent(i)] > List[i]))
		{
			swap(List[i], List[Parent(i)]);
			Hash[List[i].HashValue] = i;
			Hash[List[Parent(i)].HashValue] = Parent(i);
			i = Parent(i);
		}
	}

};