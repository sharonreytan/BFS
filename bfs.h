//#ifndef __bfs_h
//#define __bfs_h

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

enum color {WHITE,GRAY,BLACK};

class vertex
{
private:
	int * neib;
public:
	friend class graph;
	friend class bfs_graph;
	int * get_neib() const {return neib;}
	void set_neib(int * new_neib) {neib=new_neib;}
};

class graph
{
private:
	vertex * verts;
	int verts_num;
public:
	graph(const string &ver_info, const string &ver_am);
	int get_verts_num() const {return verts_num;}
	vertex* get_verts() const {return verts;}
	void demonstrate();
	~graph();
};

class bfs_graph
{
private:
	int * parents;
	int * colors;
	int * dist;
public:
	bfs_graph() {parents=NULL,colors=NULL,dist=NULL;}
	bfs_graph(const graph &, const int &);
	int * shortest_paths(const graph &, const int &) const;
	~bfs_graph();
};



//#endif