/*
Simple_window.cpp
Minimally revised for C++11 features of GCC 4.6.3 or later
Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Diff_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

Diff_window::Diff_window(Point xy, int w, int h, const string& title) :
Window(xy,w,h,title),
	diff_button(Point(x_max()-70,0), 70, 20, "Next", cb_diff),
	Difficulty{Point{x_max()-120,0}, 50, 20, "Select your difficulty (2-9): "},
	button_pushed(false)
{
	attach(diff_button);
	attach(Difficulty);
}

//------------------------------------------------------------------------------

bool Diff_window::wait_for_diff()
	// modified event loop:
	// handle all events (as per default), quit when button_pushed becomes true
	// this allows graphics without control inversion
{
	show();
	button_pushed = false;
#if 1
	// Simpler handler
	while (!button_pushed) Fl::wait();
	Fl::redraw();
#else
	// To handle the case where the user presses the X button in the window frame
	// to kill the application, change the condition to 0 to enable this branch.
	Fl::run();
#endif
	return button_pushed;
}

//------------------------------------------------------------------------------

void Diff_window::cb_diff(Address, Address pw)
	// call Simple_window::next() for the window located at pw
{  
	reference_to<Diff_window>(pw).diff();    
}

//------------------------------------------------------------------------------
void Diff_window::diff()
{
	button_pushed = true;
	int dif = Difficulty.get_int();
	ofstream outFile;
	outFile.open("difficulty.txt");
	outFile << int(dif);
	outFile.close(); 
	hide();
}