#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <time.h>
#include <vector>
#include <string>
#include <random>
using namespace std;


class Node;

class Edge
{
public:
	Node * n_to;
	int n_w;
	Edge(Node * to, int w) : n_to(to), n_w(w) {}
};


class Node
{
public:
	string name;
	list<Edge *> e_list;
	int n_neighbors;


	Node(string n, int neighbors) : name(n), n_neighbors(neighbors) {}
};


using uint32 = unsigned int;

class Random {
public:
	Random() = default;
	Random(mt19937::result_type seed) : eng(seed) {}
	uint32 DrawNumber(uint32 min, uint32 max)
	{
		return std::uniform_int_distribution<uint32>{min, max}(eng);
	}

private:
	mt19937 eng{ random_device{}() };
}rando; //////////////////


void v_rand(vector<int> &vec, int n, int i, int size);

int main()
{
	vector<Node *> n_vector;
	vector<int> v_vec;
	int n_nodes = 0;
	cout << "Enter the number of nodes to generate: ";
	cin >> n_nodes;
	int num_neighs = 0;
	for (int i = 0; i < n_nodes; i++)
	{
		int num_neigh = rando.DrawNumber(0, n_nodes - 1);
		n_vector.push_back(new Node("n_" + to_string(i), num_neigh));
		num_neighs += num_neigh;
	}		// tworze wierzcholek o nazwie n_i oraz losuje ilosc sasiadow dla niego

	for (int i = 0; i < n_vector.size(); i++)
	{
		v_rand(v_vec, n_vector[i]->n_neighbors, i, n_vector.size());	// losujemy indeksy na tablicy v_vec
		for (int j = 0; j < v_vec.size(); j++)
		{
			n_vector[i]->e_list.push_back(new Edge(n_vector[v_vec[j]], rando.DrawNumber(0, n_nodes * 20)));
		}	// dodajemy sasiadow o indeksach v_vec[j] do wierzcholka n_vector[i]
		v_vec.clear();
	}

	ofstream outFile;
	outFile.open("generated_graph.txt", ofstream::out | ofstream::trunc);
	outFile << n_vector.size() << endl;
	for (int i = 0; i < n_nodes; i++)
	{
		outFile << n_vector[i]->name;
		if (i < n_nodes - 1)
			outFile << " ";
	}
	outFile << " " << endl;
	outFile << num_neighs << endl;

	for (int i = 0; i < n_vector.size(); i++)
	{
		for (list<Edge *>::iterator it = n_vector[i]->e_list.begin(); it != n_vector[i]->e_list.end(); ++it)
		{
			outFile << n_vector[i]->name << " ";
			outFile << (*it)->n_to->name << " ";
			outFile << (*it)->n_w;
			outFile << endl;
		}
	}
	outFile.close();


	ofstream info;
	info.open("info.txt", ofstream::out | ofstream::trunc);
	cout << "Done!" << endl;
	info << "Graph with " << n_nodes << " nodes ";
	info << "and " << num_neighs << " edges." << endl;
	for (int i = 0; i < n_vector.size(); i++)
	{
		info << n_vector[i]->name << " have " << n_vector[i]->n_neighbors << " neighbors" << endl;
	}
	info.close();
	return 0;
}

void v_rand(vector<int> &vec, int n, int i, int size)
{
	vector<int> ex;
	bool flag;
	ex.push_back(i);
	while (ex.size() != n + 1)
	{
		flag = true;
		int num = rando.DrawNumber(0, size - 1);
		for (int j = 0; j < ex.size(); j++)
		{
			if (num == ex[j])
				flag = false;
		}

		if (flag)
		{
			vec.push_back(num);
			ex.push_back(num);
		}
	}
}