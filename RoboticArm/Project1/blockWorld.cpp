//Block World (Project 1)
//By Kade Walter
//CS 438
//Due Date: 1/18/2018 at 12:30 pm
//This program simulates a robotic arm following commands moving blocks

#include "blockWorld.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

//structs
struct command
{
	string action;
	int block1;
	string dest;
	int block2;
};

command newCommand(string action, int block1, string dest, int block2)
{
	command temp;
	temp.action = action;
	temp.block1 = block1;
	temp.dest = dest;
	temp.block2 = block2;
	return temp;
}

//prototypes
void moveOnto(command cmd);
void moveOver(command cmd);
void pileOnto(command cmd);
void pileOver(command cmd);

//file
const string blockIn = "blockIn.txt";

//globals
vector<vector<int>>blockList;

int main()
{
	string anything;
	cout << "Press enter to continue..." << endl;
	cin >> anything;
	//variables
	vector<command> commands;
	int blockAmount;

	//fill list
	ifstream in(blockIn);
	//get amount of blocks
	in >> blockAmount;
	//get commands from in file
	string line;
	int block1, block2;
	string action, dest;
	string exit = "quit";
	getline(in, line);
	while (!in.eof())
	{
		getline(in, line);
		stringstream ss(line);
		ss >> action;
		if (action != exit)
		{
			ss >> block1;
			ss >> dest;
			ss >> block2;
			command temp = newCommand(action, block1, dest, block2);
			commands.push_back(temp);
		}
		else
			break;
	}

	//making the block list
	blockList.resize(blockAmount);
	for (int x = 0; x < blockAmount; x++)
	{
		blockList[x].push_back(x);
	}

	//choosing which action to make
	for (int i = 0; i < commands.size(); i++)
	{
		if (commands[i].action == "move")
		{
			if (commands[i].dest == "onto")
				moveOnto(commands[i]);
			else
			{
				moveOver(commands[i]);
			}
		}
		else
		{
			if (commands[i].dest == "onto")
			{
				pileOnto(commands[i]);
			}
			else
			{
				pileOver(commands[i]);
			}
		}
	}


	//output
	ofstream out("blockOut.txt");
	for (int i = 0; i < blockList.size(); i++)
	{
		out << i << ": ";
		for (int j = 0; j < blockList[i].size(); j++)
		{
			out << blockList[i][j] << " ";
		}
		out << endl;
	}

	cout << "Program has been executed." << endl;

	return 0;
}


//In the following functions, A is used to represent the row that block1 is in and B is used to represent the row that block2 is in
//A always corresponds to the first block in the command and B always corresponds to the second block in the command
void moveOnto(command cmd)
{
	//variables
	int block1 = cmd.block1;
	int block2 = cmd.block2;
	int A = NULL;
	int B = NULL;
	int listSize;

	//find the row that block1 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block1)
				A = i;
		}
		if (A != NULL)
			break;
	}
	//find the row that block2 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block2)
				B = i;
		}
		if (B != NULL)
			break;
	}
	//if they are already on the same pile
	if (A == B)
		return;
	//loop to remove blocks on top of block1
	for (int i = blockList[A].size() - 1; i >= 0; i--)
	{
		if (blockList[A][i] != block1)
		{
			int temp = blockList[A][i];
			blockList[temp].push_back(temp);
			blockList[A].pop_back();
		}
		else
			break;
	}
	//loop to remove blocks on top of block2
	for (int i = blockList[B].size() - 1; i >= 0; i--)
	{
		if (blockList[B][i] != block2)
		{
			int temp = blockList[B][i];
			blockList[temp].push_back(temp);
			blockList[B].pop_back();
		}
		else
			break;
	}
	//move block1 on to block2
	listSize = blockList[A].size() - 1;
	int temp = blockList[A][listSize];
	blockList[B].push_back(temp);
	blockList[A].pop_back();
}

void moveOver(command cmd) 
{
	//variables
	int block1 = cmd.block1;
	int block2 = cmd.block2;
	int A = NULL;
	int B = NULL;
	int listSize;

	//find the row that block1 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block1)
				A = i;
		}
		if (A != NULL)
			break;
	}
	//find the row that block2 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block2)
				B = i;
		}
		if (B != NULL)
			break;
	}
	//if they are already on the same pile
	if (A == B)
		return;
	//loop to remove blocks on top of block1
	for (int i = blockList[A].size() - 1; i >= 0; i--)
	{
		if (blockList[A][i] != block1)
		{
			int temp = blockList[A][i];
			blockList[temp].push_back(temp);
			blockList[A].pop_back();
		}
		else
			break;
	}
	//move block1 on to block2
	listSize = blockList[A].size() - 1;
	int temp = blockList[A][listSize];
	blockList[B].push_back(temp);
	blockList[A].pop_back();
}

void pileOnto(command cmd)
{
	//variables
	int block1 = cmd.block1;
	int block2 = cmd.block2;
	int A = NULL;
	int B = NULL;
	int listSize;

	//find the row that block1 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block1)
				A = i;
		}
		if (A != NULL)
			break;
	}
	//find the row that block2 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block2)
				B = i;
		}
		if (B != NULL)
			break;
	}
	//if they are already on the same pile
	if (A == B)
		return;
	//loop to remove blocks on top of block2
	for (int i = blockList[B].size() - 1; i >= 0; i--)
	{
		if (blockList[B][i] != block2)
		{
			int temp = blockList[B][i];
			blockList[temp].push_back(temp);
			blockList[B].pop_back();
		}
		else
			break;
	}
	//load all blocks on top of A into a temp int array
	vector<int> arr;
	for (int i = blockList[A].size() - 1; i >= 0; i--)
	{
		if (blockList[A][i] != block1)
		{
			int temp = blockList[A][i];
			arr.push_back(temp);
			blockList[A].pop_back();
		}
		else
		{
			int temp = blockList[A][i];
			arr.push_back(temp);
			blockList[A].pop_back();
			break;
		}
	}
	//move block1 stack on to block2
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		int temp = arr[i];
		blockList[B].push_back(temp);
		arr.pop_back();

	}
}

void pileOver(command cmd)
{
	//variables
	int block1 = cmd.block1;
	int block2 = cmd.block2;
	int A = NULL;
	int B = NULL;
	int listSize;

	//find the row that block1 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block1)
				A = i;
		}
		if (A != NULL)
			break;
	}
	//find the row that block2 is in
	for (int i = 0; i < blockList.size(); i++)
	{
		for (int j = 0; j < blockList[i].size(); j++)
		{
			if (blockList[i][j] == NULL)
				break;
			if (blockList[i][j] == block2)
				B = i;
		}
		if (B != NULL)
			break;
	}
	//if they are already on the same pile
	if (A == B)
		return;
	//load all blocks on top of A into a temp int array
	vector<int> arr;
	for (int i = blockList[A].size() - 1; i >= 0; i--)
	{
		if (blockList[A][i] != block1)
		{
			int temp = blockList[A][i];
			arr.push_back(temp);
			blockList[A].pop_back();
		}
		else
		{
			int temp = blockList[A][i];
			arr.push_back(temp);
			blockList[A].pop_back();
			break;
		}
	}
	//move block1 stack on to block2
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		int temp = arr[i];
		blockList[B].push_back(temp);
		arr.pop_back();

	}
}

blockWorld::blockWorld()
{
}

blockWorld::~blockWorld()
{
}
