#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "bfs.h"

using namespace std;

int main()
{
	char y_or_n;
	ifstream fil;
	std::string filename;
	std::string vertex_amount;
	std::string vertex_info;
	cout << "Please enter the name of your text file, to read the graph from: ";
	getline(cin,filename,'\n');
	fil.open(filename);
	if (fil==NULL)
	{
		cout << filename << "does not exist. Please try again." << endl;
		return 0;
	}
	getline(fil,vertex_amount,'\n');
	getline(fil,vertex_info,'\n');
	fil.close();
	graph G(vertex_info,vertex_amount);
	G.demonstrate();
	while (1)
	{
		cout << "\nWould you like to try again? y-yes n-no: ";
		cin >> y_or_n;
		if (y_or_n=='y')
		{
			cout << "------------------------------------------------------------------------" << endl;
			G.demonstrate();
		}
		else
		{
			cout << "\nThank you, goodbye.\n\n\n" << endl;
			return 0;
		}
	}
	return 0;
}