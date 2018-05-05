
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef flip_window2_GUARD
#define flip_window2_GUARD 1

#include "GUI.h"    // for flip_window2 only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct flip_window2 : Graph_lib::Window {
	flip_window2(Point xy, int w, int h, const string& title );

	bool wait_for_button(); // simple event loop

	// implementation detail
	bool wait_for_p2();
	bool wait_for_quit();
	//

private:
	Button quit_button;     // the "next" button
	Button p2_button;
	bool button_p2; 
	bool button_quit;

	static void cb_quit(Address, Address); // callback for next_button
	static void cb_p2(Address,Address);

	void quit();            // action to be done when next_button is pressed
	void p2();

};

//------------------------------------------------------------------------------

#endif // flip_window2_GUARD