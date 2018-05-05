//Raymond Zhu
//CSCE 121 501
//Due: March 26th 2015
//hw5pr2_zhu.cpp

#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"

int main()
try {
  if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ",
		  	   H112);
  Simple_window win1(Point(0,0),600,600, "Aggie");
  Color aggie_maroon(fl_rgb_color(80,0,0));
  

  Rectangle flag(Point(60,50), 500, 500);
  
  Closed_polyline A;
  A.add(Point(165,240));
  A.add(Point(225,240));
  A.add(Point(225,265));
  A.add(Point(220,265));
  A.add(Point(250,365));
  A.add(Point(260,365));
  A.add(Point(260,390));
  A.add(Point(215,390));
  A.add(Point(215,365));
  A.add(Point(218,365));
  A.add(Point(215,355));
  A.add(Point(185,355));
  A.add(Point(182,365));
  A.add(Point(185,365));
  A.add(Point(185,390));
  A.add(Point(140,390));
  A.add(Point(140,365));
  A.add(Point(150,365));
  A.add(Point(180,265));
  A.add(Point(175,265));
  A.add(Point(175,240));
  
  Closed_polyline T;
  T.add(Point(175,150));
  T.add(Point(425,150));
  T.add(Point(425,225));
  T.add(Point(375,225));
  T.add(Point(375,200));
  T.add(Point(325,200));
  T.add(Point(325,400));
  T.add(Point(350,400));
  T.add(Point(350,450));
  T.add(Point(250,450));
  T.add(Point(250,400));
  T.add(Point(275,400));
  T.add(Point(275,200));
  T.add(Point(225,200));
  T.add(Point(225,225));
  T.add(Point(175,225));
  T.add(Point(175,150));
  
  Closed_polyline M;
  M.add(Point(370,240));
  M.add(Point(405,305));
  M.add(Point(435,240));
  M.add(Point(470,240));
  M.add(Point(470,265));
  M.add(Point(465,265));
  M.add(Point(465,365));
  M.add(Point(470,365));
  M.add(Point(470,390));
  M.add(Point(435,390));
  M.add(Point(435,365));
  M.add(Point(440,365));
  M.add(Point(440,300));
  M.add(Point(405,375));
  M.add(Point(370,300));
  M.add(Point(370,365));
  M.add(Point(375,365));
  M.add(Point(375,390));
  M.add(Point(340,390));
  M.add(Point(340,365));
  M.add(Point(345,365));
  M.add(Point(345,265));
  M.add(Point(340,265));
  M.add(Point(340,240));
  M.add(Point(375,240));
  
  Polygon tri;
  tri.add(Point(190,325));
  tri.add(Point(200,295));
  tri.add(Point(210,325));
  

  
  
  win1.attach(flag);
  win1.attach(A);
  win1.attach(T);
  win1.attach(M);
  win1.attach(tri);
  
  flag.set_fill_color(aggie_maroon);
  flag.set_color(Color::invisible);
  
  A.set_fill_color(Color::white);
  A.set_color(Color::invisible);
  
  T.set_fill_color(Color::white);
  T.set_color(Color::invisible);

  M.set_fill_color(Color::white);
  M.set_color(Color::invisible);
  
  tri.set_fill_color(aggie_maroon);
  tri.set_color(Color::invisible);
 
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
