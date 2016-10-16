#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <string>
using namespace std;


class Edge;
class Node;
class Compare;
class Graph;

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
	string n_letter;
	int n_from_start;
	list<Edge *> n_list;
	Node * n_previous;

	Node(string c) : n_letter(c) {}
};

class Compare
{
public:
	bool operator()(Node * n1, Node * n2)
	{
		return (n1->n_from_start < n2->n_from_start);
	}
};

class Graph
{
public:
	Node ** nodes;
	priority_queue<Node *> pq;
	bool neg;
	int n_N;

	Graph(int nN) : n_N(nN)
	{
		nodes = new Node *[nN];
		this->neg = false;
		for (int i = 0; i < nN; i++)
			this->nodes[i] = nullptr;
	}


	void addNode(string c);
	void addNeighbors(string from, string to, int weight);
	void initialize(string start);
	void dijkstra(string start);
	void bellmanFord(string start);
	void displayNodes(string start);
	void showGraph();
	int nNodes();
};

int main()
{
	cout << "Choose file to read:\n"
		<< "\t- generator(1)\n"
		<< "\t- graph of Poland(2)\n"
		<< "Enter 1 or 2: ";
	int wybor;
	string data;
	cin >> wybor;
	if (wybor == 1)
		data = "generated_graph.txt";
	else if (wybor == 2)
		data = "graph_of_poland.txt";
	string start;
	cout << "Enter the root node: ";
	cin >> start;
	cin.get();
	ifstream inFile;
	inFile.open(data, ifstream::in);
	if (!inFile.is_open())
	{
		cout << "File opening failed!" << endl;
		exit(EXIT_FAILURE);
	}
	int n_nodes;
	string nodes;
	inFile >> n_nodes;

	Graph g(n_nodes);

	inFile.get();
	getline(inFile, nodes);
	int pos = 0;
	for (int i = 0; i < nodes.length(); i++)
	{
		string node;
		if (nodes[i] == ' ')
			continue;
		while (nodes[i] != ' ')
		{
			node += nodes[i];
			i++;
		}
		g.addNode(node);
	}
	nodes.clear();
	int n_edges;
	inFile >> n_edges;
	inFile.get();
	for (int i = 0; i < n_edges; i++)
	{
		getline(inFile, nodes);
		string n1;
		string n2;
		string nw;
		int j, k, l;
		for (j = 0; j < nodes.length(); j++)
		{
			if (nodes[j] == ' ')
			{
				j++;
				break;
			}
			n1 += nodes[j];
		}

		for (k = j; k < nodes.length(); k++)
		{
			if (nodes[k] == ' ')
			{
				k++;
				break;
			}
			n2 += nodes[k];
		}

		for (l = k; l < nodes.length(); l++)
		{
			if (nodes[l] == ' ')
			{
				l++;
				break;
			}
			nw += nodes[l];
		}
		g.addNeighbors(n1, n2, stoi(nw));
	}
	g.dijkstra(start);
	g.displayNodes(start);
	inFile.close();
	return 0;
}

void Graph::dijkstra(string start)
{
	this->initialize(start);
	for (int i = 0; (i < n_N) && (this->nodes[i] != nullptr); i++)
	{
		if (this->nodes[i]->n_letter == start)
		{
			this->pq.push(this->nodes[i]);
		}
	}

	while (this->pq.size() != 0)
	{
		Node * u = this->pq.top();	this->pq.pop();
		for (list<Edge *>::iterator it = u->n_list.begin(); it != u->n_list.end(); ++it)
		{
			if ((*it)->n_to->n_from_start > (u->n_from_start + (*it)->n_w))
			{
				(*it)->n_to->n_from_start = (u->n_from_start + (*it)->n_w);
				(*it)->n_to->n_previous = u;
				this->pq.push((*it)->n_to);
			}
		}
	}

}


void Graph::bellmanFord(string start)
{
	this->initialize(start);
	for (int i = 0; i < this->nNodes() - 1; i++)
	{
		for (list<Edge *>::iterator it = this->nodes[i]->n_list.begin(); it != this->nodes[i]->n_list.end(); ++it)
		{
			if ((*it)->n_to->n_from_start >(this->nodes[i]->n_from_start + (*it)->n_w))
			{
				(*it)->n_to->n_from_start = (this->nodes[i]->n_from_start + (*it)->n_w);
				(*it)->n_to->n_previous = this->nodes[i];
			}
		}
	}
}

void Graph::addNode(string c)
{
	int i;
	for (i = 0; (i < n_N) && this->nodes[i] != nullptr; i++)
	{
	}
	this->nodes[i] = new Node(c);
}

void Graph::initialize(string start)
{
	for (int i = 0; (i < n_N) && (this->nodes[i] != nullptr); i++)
	{
		this->nodes[i]->n_from_start = 100000;
		this->nodes[i]->n_previous = nullptr;
		if (this->nodes[i]->n_letter == start)
		{
			this->nodes[i]->n_from_start = 0;
		}
	}
}

void Graph::addNeighbors(string from, string to, int weight)
{
	Node * f = nullptr;
	Node * t = nullptr;
	for (int i = 0; (i < n_N) && (this->nodes[i] != nullptr); i++)
	{


		if (this->nodes[i]->n_letter == from)
			f = this->nodes[i];
		else if (this->nodes[i]->n_letter == to)
			t = this->nodes[i];
	}
	if (f == nullptr || t == nullptr)
	{
		cout << "f\t = nullptr!" << endl;
	}
	f->n_list.push_back(new Edge(t, weight));
}

void Graph::displayNodes(string start)
{
	ofstream outFile;
	outFile.open("results.txt", ofstream::out | ofstream::trunc);
	outFile << "Ways from every node to " << start << " node:" << endl;
	Node * temp;
	for (int i = 0; (i < n_N) && (this->nodes[i] != nullptr); i++)
	{
		if (this->nodes[i]->n_letter == start)
			continue;
		temp = this->nodes[i];
		while (temp->n_letter != start && temp->n_previous != nullptr)
		{
			outFile << temp->n_letter << " -> ";
			temp = temp->n_previous;
		}
		outFile << start;
		outFile << endl;
	}

	outFile << endl;
	outFile << "Summed weight from " << start << " to evry node:" << endl;
	for (int i = 0; (i < n_N) && (this->nodes[i] != nullptr); i++)
	{
		if (this->nodes[i]->n_from_start < 0)
		{
			outFile << "!" << endl;
			break;
		}
	}

	for (int i = 0; (i < n_N) && (this->nodes[i] != nullptr); i++)
	{
		outFile << this->nodes[i]->n_letter << " " << this->nodes[i]->n_from_start << endl;
	}
	outFile.close();
}

void Graph::showGraph()
{
	for (int i = 0; (i < n_N) && (this->nodes[i] != nullptr); i++)
	{
		cout << this->nodes[i]->n_letter << endl;
		for (list<Edge *>::iterator it = this->nodes[i]->n_list.begin(); it != this->nodes[i]->n_list.end(); ++it)
		{
			cout << "\tto " << (*it)->n_to->n_letter << " " << (*it)->n_w << endl;
		}
	}
}

int Graph::nNodes()
{
	int i;
	for (i = 1; (i < n_N) && (this->nodes[i] != nullptr); i++);
	return i;
}
