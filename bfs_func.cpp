#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <cmath>
#include "bfs.h"
using namespace std;

graph::graph(const string &ver_info, const string &ver_amount)
{
	int i, j=0, k=1, first_dig=0, neib_counter, curr_v=0, curr_neib, digs=0, n=0;
	digs = int(ver_amount.length());
	while (ver_amount[j] >= '0' && ver_amount[j] <= '9')
	{
		n += (int)pow(10.00,digs-1) * (ver_amount[j] - '0');
		digs--;
		j++;
	}
	verts_num=n;
	verts=new vertex [verts_num];
	for (i=0; i < int(ver_info.length()); i++)
	{
		if (ver_info[i] == '{')
		{
			neib_counter=1; //starts from 1 because neib[0] conain how many ints are in neib.
			j=i+1;
			while (ver_info[j] != '}')
			{
 				if (ver_info[j] >= '0' && ver_info[j] <= '9')
				{
					while (ver_info[j] >= '0' && ver_info[j] <= '9')
						j++;
					neib_counter++;
				}
				else
					j++;
			}
			verts[curr_v].neib=new int [neib_counter];
			verts[curr_v].neib[0]=neib_counter-1;//neib_counter-1 because neib[0] conain how many ints are in neib.
			j=i+1;
			curr_neib=0;
			while (ver_info[j] != '}')
			{
				if (ver_info[j] >= '0' && ver_info[j] <= '9')
				{
					while (ver_info[j] >= '0' && ver_info[j] <= '9')
					{
						digs++;
						j++;
					}
					j=j-digs;
					while (ver_info[j] >= '0' && ver_info[j] <= '9')
					{
						curr_neib += (int)pow(10.00,digs-1) * (ver_info[j] - '0');
						digs--;
						j++;
					}
					verts[curr_v].neib[k]=curr_neib;
					curr_neib=0;
					k++;
				}
				else
					j++;
			}
			curr_v++;
			k=1;
			i=j;
			digs=0;
		}
	}
}
bfs_graph::bfs_graph(const graph &G,const int &v_indx)
{
	int i, j=0, k=0, n=G.get_verts_num(), counter=0, curr_v=v_indx-1;
	vertex * V = G.get_verts();
	std::queue<int> Q;
	parents=new int[n];
	colors=new int[n];
	dist=new int[n];
	for(i=0;i<n;i++)
	{
		parents[i]=-1; //means null
		colors[i]=0;
		dist[i]=-1; //means infinity
	}
	parents[curr_v]=-1;
	colors[curr_v]=0;
	dist[curr_v]=0;
	Q.push(curr_v);
	while (!(Q.empty()))
	{
		curr_v = Q.front();
		Q.pop();
		for (i=1 ; i<=V[curr_v].neib[0] ; i++)
		{
			j = V[curr_v].neib[i] - 1; // j is the referenced index e.g if vertex 1 has neib {3,2} then we work on j=3,2
			if (colors[j] == 0)
			{
				colors[j] = 1;
				dist[j] = dist[curr_v] + 1;
				parents[j] = curr_v + 1;
				Q.push(j);
			}
		}
		colors[curr_v]=3;
	}
}
int * bfs_graph::shortest_paths(const graph &G,const int &v_indx) const
{
	int i, *P, n, j, curr_neib, neibs_count;
	n=G.get_verts_num(); 
	vertex * V=G.get_verts();
	P=new int [n];
	for (i=0 ; i < n ; i++)
	{
		P[i]=0;
	}
	P[v_indx]=1; //as described in the Homework page - for v2 and v3 in the example
	for (i=0 ; i < n ; i++)
	{
		if (dist[i] != -1)
		{
			neibs_count=V[i].neib[0];
			for (j=1 ; j <= neibs_count ; j++)
			{
				curr_neib=V[i].neib[j]-1;
				{
					if (dist[i] + 1 == dist[curr_neib])
						P[curr_neib]++;
				}
			}
		}
	}
	for (i=0 ; i < n ; i++) //fixing P for routes we didn't check
	{
		if (P[i] > 1)
		{
			neibs_count=V[i].neib[0];
			for (j=1 ; j <= neibs_count ; j++)
			{
				curr_neib=V[i].neib[j]-1;
				{
					if (dist[i] + 1 == dist[curr_neib])
						P[curr_neib] += P[i] - 1;
				}
			}
		}
	}
	cout << "\nThe output for V" << v_indx + 1 << " is:" << endl; //print
	cout << "(";
	for (i=0 ; i <  n ; i++)
	{
		cout << P[i];
		if (i < n-1)
			cout << ", ";
	}
	cout << ")" << endl;
	return P;
}
void graph::demonstrate()
{
	int select;
	cout << "\nPlease, enter the source node for BFS: ";
	cin >> select;
	if (select > verts_num || select < 1)
	{
		cout << "Invalid input.";
		return;
	}
	bfs_graph TBFS(*this,select);
	TBFS.shortest_paths(*this,select-1);
}
graph::~graph()
{
	int i;
	for ( i=0 ; i < verts_num ; i++ )
		delete verts[i].neib;
	delete verts;
}
bfs_graph::~bfs_graph()
{
	delete colors;
	delete parents;
	delete dist;
}
