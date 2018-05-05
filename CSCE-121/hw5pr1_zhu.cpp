//Raymond Zhu
//CSCE 121 501
//Due: March 26th 2015
//hw5pr1_zhu.cpp

#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"

int main()
try {
  if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ",
		  	   H112);
  Simple_window win1(Point(0,0),500,200, "initials");
  
  
  Line Zhorizontal(Point(275,175),Point(375,175));  // make a horizontal line
  Line Zdiagonal(Point(275,175),Point(375,25)); // make a diagonal line
  Line Zhorizontal1(Point(275,25),Point(375,25)); // second horizontal
  
  Line Rvertical(Point(105,25),Point(105,175));
  Line Rhorizontal_rec(Point(105,25),Point(225,25));
  Line Rvertical1(Point(225,25),Point(225,100));
  Line Rdiagonal(Point(105,138),Point(225,100));
  Line Rdiagonal1(Point(165,119),Point(225,175));
  
  
  win1.attach(Rvertical);
  win1.attach(Rvertical1);
  win1.attach(Rdiagonal);
  win1.attach(Rdiagonal1);
  win1.attach(Rhorizontal_rec);
  
  win1.attach(Zdiagonal);
  win1.attach(Zhorizontal);
  win1.attach(Zhorizontal1);
  
  Rvertical1.set_style(Line_style(Line_style::solid, 5));
  Rhorizontal_rec.set_style(Line_style(Line_style::solid, 5));
  Rdiagonal.set_style(Line_style(Line_style::solid, 5));
  Rdiagonal1.set_style(Line_style(Line_style::solid, 5));
  Rvertical.set_style(Line_style(Line_style::solid, 5));
  
  Zdiagonal.set_style(Line_style(Line_style::solid, 5));
  Zhorizontal.set_style(Line_style(Line_style::solid, 5));
  Zhorizontal1.set_style(Line_style(Line_style::solid, 5));
  
  Zhorizontal.set_color(Color::white);
  Zhorizontal1.set_color(Color::white);
  Zdiagonal.set_color(Color::white);
  
  win1.wait_for_button();
  return 0;
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
