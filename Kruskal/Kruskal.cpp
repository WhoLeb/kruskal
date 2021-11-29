#include <iostream>
#include <fstream>
#include "dynamic_array.h"


class edge
{
public:

	char start_node, end_node;
	int length;

	inline bool operator> (const edge& other) { return this->length >  other.length; }
	inline bool operator>=(const edge& other) { return this->length >= other.length; }
	inline bool operator< (const edge& other) { return this->length <  other.length; }
	inline bool operator<=(const edge& other) { return this->length <= other.length; }
};

class Disjoint_set
{
public:
	int rank[27];
	int p[27];

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

int main() 
{
	WhoLeb::dynamic_array<edge> edges;
	std::fstream out_file;
	out_file.open("outputfile.txt", std::ios::out);
	
	read_file(&edges);

	edges.sort();

	Disjoint_set set;
	
	for (int i = 0; i < 27; i++)
		set.make_set(i);
	int counter = 0;
	int res_len = 0;
	while (counter < edges.size())
	{
		if (set.find(edges[counter].start_node - 65) != set.find(edges[counter].end_node - 65))
		{
			out_file << edges[counter].start_node << ' ' << edges[counter].end_node << std::endl;

			set.unite(edges[counter].start_node - 65, edges[counter].end_node - 65);
			res_len += edges[counter].length;
		}
		counter++;
	}
	out_file << res_len << std::endl;
	//if (out_file.is_open())
	//	for(int i = 0; i < edges.size(); i++)
	//		out_file << edges[i].start_node << edges[i].end_node << edges[i].length << std::endl;
}

void read_file(WhoLeb::dynamic_array<edge>* edges)
{
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
}