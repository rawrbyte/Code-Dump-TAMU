/*
HS_window.cpp
Minimally revised for C++11 features of GCC 4.6.3 or later
Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "HS_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

HS_window::HS_window(Point xy, int w, int h, const string& title) :
Window(xy,w,h,title),
	exit_button(Point(x_max()-70,0), 70, 20, "Exit", cb_exit),
	play_button(Point(x_max()-140,0), 70, 20, "Play", cb_play),
	button_play(false),
	button_exit(false)
{
	attach(exit_button);
	attach(play_button);
}

//------------------------------------------------------------------------------

bool HS_window::wait_for_button()
{	
	bool returnValue;
	show();
	while ((!button_play) && (!button_exit)) {Fl::wait(); Fl::redraw();}
	if (button_play == true) { HS_window::wait_for_play(); return returnValue = true;}
	else if (button_exit == true) { HS_window::wait_for_exit(); return returnValue = false;}
}

//------------------------------------------------------------------------------

bool HS_window::wait_for_exit()
	// modified event loop:
	// handle all events (as per default), exit when button_pushed becomes true
	// this allows graphics without control inversion
{
	button_exit = false;
	hide();
	return button_exit;
}

//------------------------------------------------------------------------------

bool HS_window::wait_for_play()
{
	button_play = false;
	hide();
	return button_play;
}

//------------------------------------------------------------------------------

void HS_window::cb_exit(Address, Address pw)
{
	reference_to<HS_window>(pw).exit();
}

//------------------------------------------------------------------------------

void HS_window::cb_play(Address,Address pw)
{
	reference_to<HS_window>(pw).play();
}

//------------------------------------------------------------------------------

void HS_window::exit()
{
	button_exit = true;
	hide();
}	

//------------------------------------------------------------------------------

void HS_window::play()
{
	button_play = true;
	hide();
}
