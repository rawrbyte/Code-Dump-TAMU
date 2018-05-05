/*
flip_window7.cpp
Minimally revised for C++11 features of GCC 4.6.3 or later
Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "flip_window7.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

flip_window7::flip_window7(Point xy, int w, int h, const string& title) :
Window(xy,w,h,title),
	quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
	p2_3_button(Point(x_max()-400,195), 200, 21, "--_____________________", cb_p2_3),
	p3_4_button(Point(x_max()-400,217), 200, 21, "--_____________________", cb_p3_4),
	p4_5_button(Point(x_max()-400,239), 200, 21, "--_____________________", cb_p4_5),
	p5_6_button(Point(x_max()-400,261), 200, 21, "--_____________________", cb_p5_6),
	p6_7_button(Point(x_max()-400,283), 200, 21, "--_____________________", cb_p6_7),
	p7_button(Point(x_max()-400,305), 200, 21, "--_____________________", cb_p7),
	button_quit(false),
	button_p2_3(false),
	button_p3_4(false),
	button_p4_5(false),
	button_p5_6(false),
	button_p6_7(false),
	button_p7(false)
{
	attach(quit_button);
	attach(p2_3_button);
	attach(p3_4_button);
	attach(p4_5_button);
	attach(p5_6_button);
	attach(p6_7_button);
	attach(p7_button);
}

//------------------------------------------------------------------------------

bool flip_window7::wait_for_button()
{
	bool returnValue;
	show();
	while((!button_p2_3)&&(!button_p3_4)&&(!button_p4_5)&&(!button_p5_6)&&(!button_p6_7)&&(!button_p7)&&
		(!button_quit)) {Fl::wait(); Fl::redraw();}
	if(button_p2_3 == true) {flip_window7::wait_for_p2_3(); return returnValue = true;}
	else if(button_p3_4 == true) {flip_window7::wait_for_p3_4(); return returnValue = true;}
	else if(button_p4_5 == true) {flip_window7::wait_for_p4_5(); return returnValue = true;}
	else if(button_p5_6 == true) {flip_window7::wait_for_p5_6(); return returnValue = true;}
	else if(button_p6_7 == true) {flip_window7::wait_for_p6_7(); return returnValue = true;}
	else if(button_p7 == true) {flip_window7::wait_for_p7(); return returnValue = true;}
	else if(button_quit == true) {flip_window7::wait_for_quit(); return returnValue = false;}
}
//------------------------------------------------------------------------------

bool flip_window7::wait_for_quit()
{
	button_quit = false;
	hide();
	return button_quit;
}

bool flip_window7::wait_for_p2_3()
{
	button_p2_3 = false;
	hide();
	return button_p2_3;
}
//------------------------------------------------------------------------------
bool flip_window7::wait_for_p3_4()
{
	button_p2_3 = false;
	hide();
	return button_p3_4;
}
//------------------------------------------------------------------------------
bool flip_window7::wait_for_p4_5()
{
	button_p4_5 = false;
	hide();
	return button_p4_5;
}
//------------------------------------------------------------------------------
bool flip_window7::wait_for_p5_6()
{
	button_p5_6 = false;
	hide();
	return button_p5_6;
}
//------------------------------------------------------------------------------
bool flip_window7::wait_for_p6_7()
{
	button_p6_7 = false;
	hide();
	return button_p6_7;
}
//------------------------------------------------------------------------------
bool flip_window7::wait_for_p7()
{
	button_p7 = false;
	hide();
	return button_p7;
}

//------------------------------------------------------------------------------
void flip_window7::cb_quit(Address, Address pw)
	// call flip_window7::quit() for the window located at pw
{  
	reference_to<flip_window7>(pw).quit();    
}

//------------------------------------------------------------------------------

void flip_window7::quit()
{
	button_quit = true;
	hide();
}
//------------------------------------------------------------------------------
void flip_window7::cb_p2_3(Address, Address pw)
	// call flip_window7::quit() for the window located at pw
{  
	reference_to<flip_window7>(pw).p2_3();    
}

//------------------------------------------------------------------------------

void flip_window7::p2_3()
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
void flip_window7::cb_p3_4(Address, Address pw)
	// call flip_window7::quit() for the window located at pw
{  
	reference_to<flip_window7>(pw).p3_4();    
}

//------------------------------------------------------------------------------

void flip_window7::p3_4()
{
	button_p3_4 = true;
	int flip = 3;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}
//------------------------------------------------------------------------------
void flip_window7::cb_p4_5(Address, Address pw)
	// call flip_window7::quit() for the window located at pw
{  
	reference_to<flip_window7>(pw).p4_5();    
}

//------------------------------------------------------------------------------

void flip_window7::p4_5()
{
	button_p4_5 = true;
	int flip = 4;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}
//------------------------------------------------------------------------------
void flip_window7::cb_p5_6(Address, Address pw)
	// call flip_window7::quit() for the window located at pw
{  
	reference_to<flip_window7>(pw).p5_6();    
}

//------------------------------------------------------------------------------

void flip_window7::p5_6()
{
	button_p5_6 = true;
	int flip = 5;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}
//------------------------------------------------------------------------------
void flip_window7::cb_p6_7(Address, Address pw)
	// call flip_window7::quit() for the window located at pw
{  
	reference_to<flip_window7>(pw).p6_7();    
}

//------------------------------------------------------------------------------

void flip_window7::p6_7()
{
	button_p6_7 = true;
	int flip = 6;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}
//------------------------------------------------------------------------------
void flip_window7::cb_p7(Address, Address pw)
	// call flip_window7::quit() for the window located at pw
{  
	reference_to<flip_window7>(pw).p7();    
}

//------------------------------------------------------------------------------

void flip_window7::p7()
{
	button_p7 = true;
	int flip = 7;
	ofstream outFile;
	outFile.open("flip.txt");
	outFile << int(flip);
	outFile.close(); 
	hide();
}

//------------------------------------------------------------------------------