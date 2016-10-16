#include"PriorityQueue.h"


class Tree {
private:
	deque<N_Puzzle> Queue, Stack;
	Priority_Queue OpenList;	// The set of tentative nodes to be evaluated, initially containing the start node.
	map<string, N_Puzzle> ClosedList;  	// The set of nodes already evaluated.
	multimap<string, pair<N_Puzzle, N_Puzzle>>Came_From;	// The map of navigated nodes.
	vector<N_Puzzle> total_path;     //path from start state to goal state.
	clock_t start, stop, Time;   //To Calculate Time.
public:

	//Check if Puzzle Solvable or Not.
	void CheckSolvability(N_Puzzle& Intial_State , char choice) {
		start = clock();
		if (Intial_State.isSolvable() == false) {
			stop = clock();
			cout << "\nIt's Unsolvable!!!!!" << endl;
			printf("Time : %.2f sec.\n", float((stop - start) / CLOCKS_PER_SEC));
		}
		else
			A_Star(Intial_State, choice);

	}

	//Solve The Puzzle.
	void A_Star(N_Puzzle& Intial_State, char choice) {

		OpenList.Heap_Insert(Intial_State);

		while (!OpenList.isEmpty())
		{
			N_Puzzle Current = OpenList.Heap_Extract_Min();

			if (Current.isGoal()) {
				cout << "\n\t\t     (Using A* Algorithm.)\nSolvable..!" << endl;
				cout << "Number Of Steps : " << Current.gVal << endl;
				stop = clock();
				printf("Time : %.2f sec.\n", (float)((float)(stop - start) / CLOCKS_PER_SEC));
				//Display_Path(reconstruct_path(Came_From, Current));
				break;
			}

			ClosedList.emplace(Current.HashValue, Current);

			//Generate all possible states of the puzzle.
			for (int i = 0; i < 4; ++i)
			{
				N_Puzzle successor = Current;
				if (Current.isValid((N_Puzzle::direction)i))
				{
					successor.move((N_Puzzle::direction)i);
					successor.gVal = Current.gVal + abs(Current.gVal - successor.gVal);	// length of this path.
					if(choice == 'h') successor.hVal = successor.HammingDistance();
					else successor.hVal = successor.ManhattanDistance();
					successor.fVal = successor.gVal + successor.hVal;

					//successor isn't in openList or closedList.
					if (ClosedList.find(successor.HashValue) == ClosedList.end() && OpenList.Hash.find(successor.HashValue) == OpenList.Hash.end()) {
						OpenList.Heap_Insert(successor); //Add it to OpenList.
						// This path is the best until now. Record it!
						//Came_From.emplace(successor.HashValue, make_pair(successor, Current));
					}

					//successor is in Open.
					if (OpenList.Hash.find(successor.HashValue) != OpenList.Hash.end()) {
						map<string, int>::iterator itOpen = OpenList.Hash.find(successor.HashValue);
						if (OpenList.List[itOpen->second].fVal > successor.fVal) {
							OpenList.Remove(OpenList.List[itOpen->second], itOpen->second); //Removed it from OpenList.
							OpenList.Heap_Insert(successor); //Add successor with low F(n) to OpenList.
						}
					}

					//successor is in Closed.
					if (ClosedList.find(successor.HashValue) != ClosedList.end()) {
						map<string, N_Puzzle>::iterator itClosed = ClosedList.find(successor.HashValue);
						if (itClosed->second.fVal > successor.fVal) {
							ClosedList.erase(itClosed); //Remove it from ClosedList.
							OpenList.Heap_Insert(successor); //Add it to OpenList.
						}
					}
				}
			}
		}
	}

	//Return Path From Initial Staet To Goal State.
	vector<N_Puzzle> reconstruct_path(multimap<string, pair<N_Puzzle, N_Puzzle>> Came_From, N_Puzzle& current) {
		total_path.push_back(current);
		while (Came_From.find(current.HashValue) != Came_From.end()) {
			current = Came_From.find(current.HashValue)->second.second;
			total_path.push_back(current);
		}
		return total_path;
	}

	//Display el Path.
	void Display_Path(vector<N_Puzzle> Path) {
		for (int i = Path.size() - 1; i >= 0; --i) {
			Path[i].print();
			cout << endl << endl;
		}
	}


	//BFS Algorithm.
	void Breadth_First_Search(N_Puzzle Intial_State) {
		map<string, N_Puzzle> TempForSearch;
		int Steps = 0;
		Queue.push_back(Intial_State);
		TempForSearch.emplace(Intial_State.HashValue, Intial_State);
		while (!Queue.empty())
		{
			Steps++;
			N_Puzzle Parent = Queue.front();
			Queue.pop_front();
			TempForSearch.erase(TempForSearch.find(Parent.HashValue));
			ClosedList.emplace(Parent.HashValue, Parent);

			if (Parent.isGoal()) {
				cout << "\n\t\t     (Using Breadth_First_Search)\nSolvable..!" << endl;
				cout << "Number Of Steps : " << Steps << endl;
				stop = clock();
				printf("Time : %.2f sec.\n", (float)((float)(stop - start) / CLOCKS_PER_SEC));
				Display_Path(reconstruct_path(Came_From, Parent));
				break;
			}
			for (int i = 0; i < 4; ++i) {
				N_Puzzle Child = Parent;
				if (Parent.isValid((N_Puzzle::direction)i)) {
					Child.move((N_Puzzle::direction)i);
					if (ClosedList.find(Child.HashValue) == ClosedList.end() && TempForSearch.find(Child.HashValue) == TempForSearch.end()) {
						Queue.push_back(Child);
						TempForSearch.emplace(Child.HashValue, Child);
						Came_From.emplace(Child.HashValue, make_pair(Child, Parent));
					}
				}
			}
		}
	}

};