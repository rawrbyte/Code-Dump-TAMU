/*
flip_window3.cpp
Minimally revised for C++11 features of GCC 4.6.3 or later
Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "flip_window3.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

flip_window3::flip_window3(Point xy, int w, int h, const string& title) :
Window(xy,w,h,title),
	quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
	p2_3_button(Point(x_max()-400,239), 200, 21, "--_____________________", cb_p2_3),
	p3_button(Point(x_max()-400,261), 200, 21, "--_____________________", cb_p3),
	button_quit(false),
	button_p2_3(false),
	button_p3(false)
{
	attach(quit_button);
	attach(p2_3_button);
	attach(p3_button);
}

//------------------------------------------------------------------------------

bool flip_window3::wait_for_button()
{
	bool returnValue;
	show();
	while((!button_p2_3)&&(!button_p3)&&(!button_quit)) 
	{Fl::wait(); Fl::redraw();}
	if(button_p2_3 == true) {flip_window3::wait_for_p2_3(); return returnValue = true;}
	else if(button_p3 == true) {flip_window3::wait_for_p3(); return returnValue = true;}
	else if(button_quit == true) {flip_window3::wait_for_quit(); return returnValue = false;}
}
//------------------------------------------------------------------------------

bool flip_window3::wait_for_quit()
{
	button_quit = false;
	hide();
	return button_quit;
}

bool flip_window3::wait_for_p2_3()
{
	button_p2_3 = false;
	hide();
	return button_p2_3;
}
//------------------------------------------------------------------------------
bool flip_window3::wait_for_p3()
{
	button_p3 = false;
	hide();
	return button_p3;
}

//------------------------------------------------------------------------------
void flip_window3::cb_quit(Address, Address pw)
	// call flip_window3::quit() for the window located at pw
{  
	reference_to<flip_window3>(pw).quit();    
}

//------------------------------------------------------------------------------

void flip_window3::quit()
{
	button_quit = true;
	hide();
}
//------------------------------------------------------------------------------
void flip_window3::cb_p2_3(Address, Address pw)
	// call flip_window3::quit() for the window located at pw
{  
	reference_to<flip_window3>(pw).p2_3();    
}

//------------------------------------------------------------------------------

void flip_window3::p2_3()
{
	button_p2_3 = true;
	int flip = 2;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}
//------------------------------------------------------------------------------
void flip_window3::cb_p3(Address, Address pw)
	// call flip_window3::quit() for the window located at pw
{  
	reference_to<flip_window3>(pw).p3();    
}

//------------------------------------------------------------------------------

void flip_window3::p3()
{
	button_p3 = true;
	int flip = 3;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}

//------------------------------------------------------------------------------