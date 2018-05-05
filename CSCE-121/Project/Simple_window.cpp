/*
Simple_window.cpp
Minimally revised for C++11 features of GCC 4.6.3 or later
Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
Window(xy,w,h,title),
	quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
	initial_button(Point(x_max()-140,0), 70, 20, "Confirm", cb_initial),
	initial{Point{x_max()-200,0}, 50, 20, "Player Initial: "},
	button_quit(false),
	button_initial(false)
{
	attach(initial_button);
	attach(quit_button);
	attach(initial);
}

bool Simple_window::wait_for_button()
{	
	bool returnValue;
	show();
	while ((!button_initial) && (!button_quit)) {Fl::wait(); Fl::redraw();}
	if (button_initial == true) { Simple_window::wait_for_initial(); return returnValue = true;}
	else if (button_quit == true) { Simple_window::wait_for_quit(); return returnValue = false;}
}
//------------------------------------------------------------------------------

bool Simple_window::wait_for_quit()
	// modified event loop:
	// handle all events (as per default), quit when button_pushed becomes true
	// this allows graphics without control inversion
{
	button_quit = false;
	hide();
	return button_quit;
}

//------------------------------------------------------------------------------

bool Simple_window::wait_for_initial()
{
	button_initial = false;
	hide();
	return button_initial;
}

//------------------------------------------------------------------------------

void Simple_window::cb_initial(Address, Address pw)
	// call Simple_window::next() for the window located at pw
{  
	reference_to<Simple_window>(pw).name();    
}

//------------------------------------------------------------------------------

void Simple_window::cb_quit(Address, Address pw)
{
	reference_to<Simple_window>(pw).quit();
}

//------------------------------------------------------------------------------

void Simple_window::name()
{
	button_initial = true;
	string name = initial.get_string();
	ofstream outFile;
	outFile.open("initial.txt");
	outFile << string(name);
	outFile.close(); 
	hide();
}

//------------------------------------------------------------------------------

void Simple_window::quit()
{
	button_quit = true;
	hide();
}	

//------------------------------------------------------------------------------
