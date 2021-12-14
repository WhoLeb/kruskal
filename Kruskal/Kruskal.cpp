#include <iostream>
#include <fstream>
#include <string>
#include "dynamic_array.h"
#include "queue.h"
#include "Stack.h"


class edge
{
public:

	int start_num = -1, end_num = -1;

	std::string start_node = "", end_node = "";
	//char start_node, end_node;
	int length;

	inline bool operator> (const edge& other) { return this->length >  other.length; }
	inline bool operator>=(const edge& other) { return this->length >= other.length; }
	inline bool operator< (const edge& other) { return this->length <  other.length; }
	inline bool operator<=(const edge& other) { return this->length <= other.length; }
};

class Disjoint_set
{
public:
	int rank[50];
	int p[50];

	void make_set(int x)
	{
		p[x] = x;
		rank[x] = 0;
	}

	int find(int x)
	{
		return (x == p[x] ? x : p[x] = find(p[x]));
	}

	void unite(int x, int y)
	{
		if ((x = find(x)) == (y = find(y)))
			return;

		if (rank[x] < rank[y])
			p[x] = y;
		else 
		{
			p[y] = x;
			if (rank[x] == rank[y])
				++rank[x];
		}
	}
};

void read_file(WhoLeb::dynamic_array<edge>* edges);

void BFS(WhoLeb::dynamic_array<edge> edges);
void DFS(WhoLeb::dynamic_array<edge> edges);

std::string edgs[50];

int main() 
{
	WhoLeb::dynamic_array<edge> edges;
	std::fstream out_file;
	out_file.open("outputfile.txt", std::ios::out);

	read_file(&edges);
	std::cout << "BFS: ";
	BFS(edges);
	std::cout << "DFS: ";
	DFS(edges);

	edges.sort();

	Disjoint_set set;
	
	for (int i = 0; i < 50; i++)
		set.make_set(i);
	int counter = 0;
	int res_len = 0;
	while (counter < edges.size())
	{
		if (set.find(edges[counter].start_num) != set.find(edges[counter].end_num))
		{
			std::cout << edges[counter].start_node << ' ' << edges[counter].end_node << std::endl;
			out_file << edges[counter].start_node << ' ' << edges[counter].end_node << std::endl;

			set.unite(edges[counter].start_num, edges[counter].end_num);
			res_len += edges[counter].length;
		}
		counter++;
	}
	std::cout << res_len << std::endl;
	out_file << res_len << std::endl;
}

void read_file(WhoLeb::dynamic_array<edge>* edges)
{

#if 0
	std::fstream in_file;
	char buffer[10];
	in_file.open("inputfile.txt");
	std::string input_line;
	if (in_file.is_open())
	{
		while (in_file.getline(buffer, 10))
		{
			buffer[sizeof(buffer) / sizeof(char) - 1] = '\0';
			edge edg;
			char a, b;
			int len;
			a = buffer[0];
			b = buffer[2];
			char sub[5] = { 0 };
			for (int i = 0; i < 4 && buffer[i + 4] != '\0'; i++)
				sub[i] = buffer[i + 4];
			sub[4] = '\0';
			len = atoi(sub);
			edg.start_node = a;
			edg.end_node = b;
			edg.length = len;

			edges->push(edg);
		}
		in_file.close();
	}
	else
		std::cout << "failed to open one of the files";
#else
	std::fstream in_file;
	in_file.open("inputfile.txt");
	std::string in_line;
	if (in_file.is_open())
	{
		while (std::getline(in_file, in_line))
		{
			edge edg;
			
			std::string a, b;
			a = in_line.substr(0, in_line.find_first_of(" "));
			in_line.erase(0, in_line.find_first_of(" ")+1);
			b = in_line.substr(0, in_line.find_first_of(" ") );
			in_line.erase(0, in_line.find_first_of(" ")+1);
			int len = std::stoi(in_line);
			
			for (int i = 0; i < 50 && edgs[i] != ""; i++)
			{
				if (a == edgs[i])
				{
					edg.start_num = i;
				}
				if (b == edgs[i])
				{
					edg.end_num = i;
				}
			}
			if (edgs[0] == "")
			{
				edgs[0] = a;
				edg.start_num = 0;
				edgs[1] = b;
				edg.end_num = 1;
			}
			else
			{
				if (edg.start_num == -1)
					for (int i = 0; i < 50; i++)
					{
						if (edgs[i] == "")
						{
							edgs[i] = a;
							edg.start_num = i;
							break;
						}
					}
				if (edg.end_num == -1)
					for (int i = 0; i < 50; i++)
					{
						if (edgs[i] == "")
						{
							edgs[i] = b;
							edg.end_num = i;
							break;
						}
					}
			}
			edg.start_node = a;
			edg.end_node = b;
			edg.length = len;
			edges->push(edg);
		}
	}
	else
		std::cout << "Failed to open input file";
#endif
}

void BFS(WhoLeb::dynamic_array<edge> edges)
{
	bool used[50] = { false };
	WhoLeb::queue<std::string> q;
	
	q.push(edges[0].start_node);
	used[0] = true;

	while (!q.is_empty())
	{
		std::string current = q.front();
		q.pop();

		std::cout << current << " ";

		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].start_node == current && !used[edges[i].end_num])
			{
				q.push(edges[i].end_node);
				used[edges[i].end_num] = true;
			}
			if (edges[i].end_node == current && !used[edges[i].start_num])
			{
				q.push(edges[i].start_node);
				used[edges[i].start_num] = true;
			}
		}
	}
	std::cout << std::endl;
}

void DFS(WhoLeb::dynamic_array<edge> edges)
{
	bool used[50] = { false };
	WhoLeb::stack<std::string> s;
	s.push(edges[0].start_node);

	while (!s.empty())
	{
		std::string current = s.top();
		s.pop();
		
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].start_node == current && !used[edges[i].start_num])
			{
				std::cout << current << " ";
				used[edges[i].start_num] = true;
				break;
			}
			if (edges[i].end_node == current && !used[edges[i].end_num])
			{
				std::cout << current << " ";
				used[edges[i].end_num] = true;
				break;
			}
			
		}

		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].start_node == current && !used[edges[i].end_num])
			{
				s.push(edges[i].end_node);
			}
			if (edges[i].end_node == current && !used[edges[i].start_num])
			{
				s.push(edges[i].start_node);
			}
		}
	}
	std::cout << std::endl;
}


