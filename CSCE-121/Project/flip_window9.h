
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef flip_window9_GUARD
#define flip_window9_GUARD 1

#include "GUI.h"    // for flip_window9 only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct flip_window9 : Graph_lib::Window {
	flip_window9(Point xy, int w, int h, const string& title );

	bool wait_for_button(); // simple event loop

	// implementation detail
	bool wait_for_p2_3();
	bool wait_for_p3_4();
	bool wait_for_p4_5();
	bool wait_for_p5_6();
	bool wait_for_p6_7();
	bool wait_for_p7_8();
	bool wait_for_p8_9();
	bool wait_for_p9();
	bool wait_for_quit();
	//

private:
	Button quit_button;     // the "next" button
	Button p2_3_button;
	Button p3_4_button;
	Button p4_5_button;
	Button p5_6_button;
	Button p6_7_button;
	Button p7_8_button;
	Button p8_9_button;
	Button p9_button;
	bool button_p2_3; 
	bool button_p3_4; 
	bool button_p4_5; 
	bool button_p5_6; 
	bool button_p6_7; 
	bool button_p7_8; 
	bool button_p8_9;
	bool button_p9; 
	bool button_quit;

	static void cb_quit(Address, Address); // callback for next_button
	static void cb_p2_3(Address,Address);
	static void cb_p3_4(Address,Address);
	static void cb_p4_5(Address,Address);
	static void cb_p5_6(Address,Address);
	static void cb_p6_7(Address,Address);
	static void cb_p7_8(Address,Address);
	static void cb_p8_9(Address,Address);
	static void cb_p9(Address,Address);

	void quit();            // action to be done when next_button is pressed
	void p2_3();
	void p3_4();
	void p4_5();
	void p5_6();
	void p6_7();
	void p7_8();
	void p8_9();
	void p9();

};

//------------------------------------------------------------------------------

#endif // flip_window9_GUARD