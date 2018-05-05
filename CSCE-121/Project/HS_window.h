
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef HS_window_GUARD
#define HS_window_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct HS_window : Graph_lib::Window {
	HS_window(Point xy, int w, int h, const string& title );

	bool wait_for_button(); // simple event loop
	bool wait_for_exit();
	bool wait_for_play();

private:
	Button exit_button;
	Button play_button;
	bool button_play;     // implementation detail
	bool button_exit;

	static void cb_exit(Address, Address);
	static void cb_play(Address, Address);
	void exit();
	void play();

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD

