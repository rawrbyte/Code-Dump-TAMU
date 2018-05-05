//Raymond Zhu
//CSCE 121-501
//Due: February 25, 2015 
//hw3pr3_zhu.cpp

#include "std_lib_facilities_4a.h"
using namespace std;

bool http_check(string URL)
{
	bool return_value = false;
	string http = "" ;
	for (int i = 0; i < 4; i++)
	{
		http += URL.at(i);
	}
	
	if (http == "http")
		return_value = true;
	else 
		throw 1;

		
	return return_value;
	
}

bool pdf_check(string URL)
{
	bool return_value = false;
	string pdf = "" ;
	int y = URL.length()-1, 	l_pdf = y-3;

	for (int z = y; z > l_pdf; z--)
	{
		pdf += URL.at(z);
	
	}
	if (pdf == ("fdp") || pdf == ("FDP"))
		return_value = true;
	else 
		throw 1;

	
	return return_value;
	
}

void pdf_grab(string URL)
{
	
	string command = string("wget -O webfile.pdf ") + URL;
	system(command.c_str());
	system( "gv webfile.pdf" );
	
}

int main()
{
	
	try{
		
		string URL;
		bool http, pdf;
		cout << "Enter a URL for a PDF file: " << endl;
		cout << "URL = "; cin >> URL;
		if (URL.length() < 4)
			throw 3;
		http = http_check(URL);
		pdf = pdf_check(URL);
		
		if ((http && pdf) == true)
			pdf_grab(URL);
	
		return 0;
	}
	catch (int){
		cerr << "error: invalid URL input\n";
		keep_window_open();
	}
	catch (exception& e){
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch(...){
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2; 
	}
	
}