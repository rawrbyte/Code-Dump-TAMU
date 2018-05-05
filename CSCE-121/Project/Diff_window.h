
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef Diff_window_GUARD
#define Diff_window_GUARD 1

#include "GUI.h"    // for Diff_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Diff_window : Graph_lib::Window {
	Diff_window(Point xy, int w, int h, const string& title );
	bool wait_for_diff();
private:
	Button diff_button;     // the "next" button
	In_box Difficulty;
	bool button_pushed;     // implementation detail

	static void cb_diff(Address, Address);
	void diff();            // action to be done when diff_button is pressed
};

//------------------------------------------------------------------------------

#endif // Diff_window_GUARD

