/*
flip_window2.cpp
Minimally revised for C++11 features of GCC 4.6.3 or later
Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "flip_window2.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

flip_window2::flip_window2(Point xy, int w, int h, const string& title) :
Window(xy,w,h,title),
	quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
	p2_button(Point(x_max()-400,250), 200, 21, "--_____________________", cb_p2),
	button_quit(false),
	button_p2(false)
{
	attach(quit_button);
	attach(p2_button);
}

//------------------------------------------------------------------------------

bool flip_window2::wait_for_button()
{
	bool returnValue;
	show();
	while((!button_p2)&&(!button_quit)) {Fl::wait(); Fl::redraw();}
	if(button_p2 == true) {flip_window2::wait_for_p2(); return returnValue = true;}
	else if(button_quit == true) {flip_window2::wait_for_quit(); return returnValue = false;}
}
//------------------------------------------------------------------------------

bool flip_window2::wait_for_quit()
{
	button_quit = false;
	hide();
	return button_quit;
}
//------------------------------------------------------------------------------
bool flip_window2::wait_for_p2()
{
	button_p2 = false;
	hide();
	return button_p2;
}

//------------------------------------------------------------------------------
void flip_window2::cb_quit(Address, Address pw)
	// call flip_window2::quit() for the window located at pw
{  
	reference_to<flip_window2>(pw).quit();    
}

//------------------------------------------------------------------------------

void flip_window2::quit()
{
	button_quit = true;
	hide();
}
//------------------------------------------------------------------------------
void flip_window2::cb_p2(Address, Address pw)
	// call flip_window2::quit() for the window located at pw
{  
	reference_to<flip_window2>(pw).p2();    
}

//------------------------------------------------------------------------------

void flip_window2::p2()
{
	button_p2 = true;
	int flip = 2;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}

//------------------------------------------------------------------------------