#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "HS_window.h"
#include "flip_window9.h"
#include "flip_window8.h"
#include "flip_window7.h"
#include "flip_window6.h"
#include "flip_window5.h"
#include "flip_window4.h"
#include "flip_window3.h"
#include "flip_window2.h"
#include "Diff_window.h"
#include "Graph.h"
#include "find_solution.h"


int calc_score(int, int, int);
class high_score  // creates a class that collects a string and two int values
{
public:
	void setRank(int scoreRank){ rank = scoreRank;} // sets rank value at a position in vector
	void setPlayer(string scorePlayer){ player = scorePlayer;} // sets player value at a position in vector
	void setScore(int scorePoints){ points = scorePoints;} // sets score value at a position in vector
	int getRank(int rankValue){return rank;} // gets rank value at a position in vector
	string getPlayer(string playerValue){return player;} // gets player value at a position in vector
	int getPoints(int pointValue){return points;} // gets score value at a position in vector
private:		
	int rank;
	string player;
	int points;
};
void display_score(vector<high_score>); // declaring function ahead of time to avoid linking error
vector<int> ngame(int diff){			//ngame  = new game, makes a randomized vector of ints which will represent the pancakes
	int i;
	Vector<int>temptemppos;
	for (i=0;i<diff;++i){
		temptemppos.push_back(i);
	}
	Vector<int>temppos;
	while(!temptemppos.empty()){
		int pos = rand() % temptemppos.size();
		temppos.push_back(temptemppos[pos]);
		temptemppos.erase(temptemppos.begin()+pos);
	}	
	return temppos;
}
void write_checker(vector<int> temppos)
{
	ofstream outFile;
	outFile.open("checker.txt");
	for(int n=0; n<temppos.size(); n++){
		outFile << temppos[n] << " ";
	}
	outFile.close();
}
int read_flip(int flip)
{
	ifstream inFile;
	inFile.open("flip.txt");
	inFile>>flip;
	inFile.close();
	return flip;
}
void write_count(int flips)
{
	ofstream outFile;
	outFile.open("count.txt");
	outFile << int(flips);
	outFile.close();
}
void read_checker(vector<int> pos)
{
	vector <int> rec;
	int p=0;

	ifstream inFile;
	inFile.open("checker.txt");
	while ( inFile >> p) 
		rec.push_back(p);
	inFile.close();

	int u=0;
	for(int e=0; e<pos.size(); e++)
		if(rec[e] == pos[e]){
			u++;
		}
		if(u != rec.size()){
			ofstream outFile;
			outFile.open("count.txt");
			outFile << -1;
			outFile.close();
		}
}
int read_count(int count)
{
		ifstream inFile;
		inFile.open("count.txt");
		inFile >> count;
		inFile.close();
		return count;
}

int ys(int x, int j){
	int i;
	vector<int>y2s(2); for (i=0; i<2; ++i){y2s[i]=(228+(i*22));}
	vector<int>y3s(3); for (i=0; i<3; ++i){y3s[i]=(217+(i*22));}
	vector<int>y4s(4); for (i=0; i<4; ++i){y4s[i]=(206+(i*22));}
	vector<int>y5s(5); for (i=0; i<5; ++i){y5s[i]=(195+(i*22));}
	vector<int>y6s(6); for (i=0; i<6; ++i){y6s[i]=(184+(i*22));}
	vector<int>y7s(7); for (i=0; i<7; ++i){y7s[i]=(173+(i*22));}
	vector<int>y8s(8); for (i=0; i<8; ++i){y8s[i]=(162+(i*22));}
	vector<int>y9s(9); for (i=0; i<9; ++i){y9s[i]=(151+(i*22));}
	if (x==9){return y9s[j];}
	else if (x==8){return y8s[j];}
	else if (x==7){return y7s[j];}
	else if (x==6){return y6s[j];}
	else if (x==5){return y5s[j];}
	else if (x==4){return y4s[j];}
	else if (x==3){return y3s[j];}
	else if (x==2){return y2s[j];}
}

int gameover(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){  //Nine pancake game ends, check flips, return number of flips in game
	read_checker(pos);
	int count = read_count(count);
	return count+1;
}
int game(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score);
void game_2(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//Button action for game9
		int flip = read_flip(flip);
		reverse(temppos.begin(),temppos.begin()+flip);
		write_checker(temppos);
		int j=0;
		for (int i=0;i<temppos.size();++i){if(pos[i] == temppos[i]){++j;}}
		if (j != temppos.size()){
			flips++; 
			score = calc_score(flips, min, diff);
			if (score<0){gameover(temppos,diff,flips,pos,min,score);}
			else{
			write_count(flips);
			game(temppos, diff, flips, pos, min, score);}}
}
int game9Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window9 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game8Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window8 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game7Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window7 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game6Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window6 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game5Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window5 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game4Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window4 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game3Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window3 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game2Rec(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){//make pancakes (use temppos to fill other templeg,tempx, height standardized)
	flip_window2 win20(Point(100,200),600,400,"Filpflaps");
	int i;
	stringstream ss; ss << "Number of Flips Required: " << min << " ---" << " Current Score: " << score << " ---" << " Current Flips: " << flips; Text Current{Point{50,50}, ss.str()};  ss.str(""); win20.attach(Current);
	vector<int>tempx;
	for (i=0;i<temppos.size();++i){tempx.push_back(0);}
	for (i=0;i<temppos.size();++i){tempx[i]=(350-(temppos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<temppos.size();++i){templeg.push_back(0);}
	for (i=0;i<temppos.size();++i){templeg[i]=((temppos[i]*25)+25);} 
	Vector_ref<Rectangle> r1;
	for (i=0; i<temppos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],ys(diff,i)},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		win20.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<temppos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(ys(diff,i)+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		win20.attach(r2[r2.size()-1]);}
	if (win20.wait_for_button() == true) {game_2(temppos, diff, flips, pos, min, score);}
	return gameover(temppos, diff, flips, pos, min, score);}
int game(vector<int> temppos, int diff, int flips, vector<int> pos, int min, int score){	//Nine pancake game starts, makes window
	write_checker(temppos);
	if(diff==9){return game9Rec(temppos, diff, flips, pos, min, score);}
	else if(diff==8){return game8Rec(temppos, diff, flips, pos, min, score);}
	else if(diff==7){return game7Rec(temppos, diff, flips, pos, min, score);}
	else if(diff==6){return game6Rec(temppos, diff, flips, pos, min, score);}
	else if(diff==5){return game5Rec(temppos, diff, flips, pos, min, score);}
	else if(diff==4){return game4Rec(temppos, diff, flips, pos, min, score);}
	else if(diff==3){return game3Rec(temppos, diff, flips, pos, min, score);}
	else if(diff==2){return game2Rec(temppos, diff, flips, pos, min, score);}
}
ifstream inFile;
ofstream outFile;
vector <high_score> top;
high_score *s1 = new high_score;	

void check_file() // checks if scores.txt exists, if not, create the file
{

	int rank{1}, points{0};
	string player = " NONE ";

	inFile.open("scores.txt");
	if( inFile.fail() )
	{
		outFile.open("scores.txt");
		for (int n=0; n<5; n++)
		{
			outFile << rank++ << player << points << " "; // copies values to scores.txt

			s1->setRank(rank-1); // stores values into a vector
			s1->setPlayer(player);
			s1->setScore(points);
			top.push_back(*s1);
		}			
		outFile.close();
	}	
	inFile.close();

}
void printHS(vector <high_score> top) // prints out a vector that holds classes
{
	int rank{1}, points{0};
	string player = " NONE ";

	for (int o=0; o<5; o++)
	{
		cout << top[o].getRank(rank) << top[o].getPlayer(player) << top[o].getPoints(points) << endl;
	}
}
vector <high_score> read_file(vector<high_score> top) // reads scores.txt and copies the values into a vector of classes 
{
	int rank{1}, points{0};
	string player = " NONE ";

	inFile.open("scores.txt");
	string STRING, c;
	char a[256], buffer[256];
	while( inFile.good() )
	{
		getline(inFile, STRING);
	}	
	stringstream person(STRING); 
	while ( person >> a >> c >> buffer)
	{
		s1->setRank(atoi(a)); // atoi to change a char into an int
		s1->setPlayer(" " + c + " ");
		s1->setScore(atoi(buffer));
		top.push_back(*s1); 
	}
	inFile.close();
	return top;
}
vector <high_score> update(vector <high_score> top, int x, string p) // updates vector of high scores, replacing values if new values are greater
{
	int score_temp, points;
	string player_temp, player;
	if (x > top[4].getPoints(points)) { top[4].setPlayer(" " + p + " "); top[4].setScore(x); }

	for (int i=0; i<5; i++)
		for (int z=i+1; z<5; z++)
		{
			if (top[z].getPoints(points) > top[i].getPoints(points))
			{
				score_temp = top[z].getPoints(points); // temp value to hold on to initial value in order to compare values
				player_temp = top[z].getPlayer(player);
				top[z].setScore(top[i].getPoints(points));
				top[z].setPlayer(top[i].getPlayer(player));
				top[i].setScore(score_temp);
				top[i].setPlayer(player_temp);
			}
		}

		return top;		
}
void update_file(vector <high_score> top) // copies the updated vector of classes into scores.txt to permanently store game values
{
	int rank{1}, points{0};
	string player = " NONE ";

	outFile.open("scores.txt"); 
	for (int i =0; i<5; i++)
	{
		outFile << top[i].getRank(rank) <<  top[i].getPlayer(player) << top[i].getPoints(points) << " "; 
	}
	outFile.close();
}

int min_flip (vector<int> pancake) // calculates the minimum number of flips a certain stack of pancakes need to be sorted
{
	vector<int>* m = find_solution(pancake);
	return m->size();
}
int calc_score(int flips, int difficulty, int stack) // calculates the player's score
{
	int score;
	score = ( 100 - (10*(flips-difficulty))) * stack;
	return score;
} 

string read_initial(string temp_player)
{
	inFile.open("initial.txt"); // gets player initials
	inFile >> temp_player;
	inFile.close();
	return temp_player;
}
int read_score(int temp_score)
{
	inFile.open("temp_score.txt"); // gets player score
	inFile >> temp_score;
	inFile.close();
	return temp_score;
}
void write_temp_score(int temp_score)
{
	outFile.open("temp_score.txt");
	outFile << temp_score;
	outFile.close();
}
void reset_count()
{
	outFile.open("count.txt");
	outFile << 0;
	outFile.close();
}
vector<int> read_solution(vector<int> min)
{
	inFile.open("solution.txt");
	int y, i = 0;
	while ( inFile >> y ){
		min[i] = y+1;
		i++;
	}
	inFile.close();
	return min;
}
void write_solution(vector<int> temppos)
{
	outFile.open("solution.txt");
	for (int n=0; n<temppos.size(); n++)
	{	
		outFile << temppos[n] << " ";
	}
	outFile.close();
}
int read_difficulty(int temp)
{
	inFile.open("difficulty.txt");
	inFile >> temp;
	inFile.close();
	return temp;
}
int check_score(int score,  int diff,  int flips, int min)
{
	if (score > (diff*100)) { score = 0; }
	else if (flips < min) { score = 0; }
	else if (score < 0) { score = 0; }
	return score;
}
vector<int> check_random(vector<int> temppos, int diff, int j, vector<int> pos)
{ 
	int i;
	while(j == temppos.size()){
		j=0;
		temppos = ngame(diff);
		for (i=0;i<temppos.size();++i){
			if(pos[i] == temppos[i]){
				++j;
			}
		}
	}
	return temppos;
}
void start_game (vector<high_score> top){
	int x = read_difficulty(x), diff = x, flips=0, j=diff, score = 0; string user;
	vector<int>temppos = ngame(diff);
	Vector<int>pos; //position
	for (int i=0;i<diff;++i){pos.push_back(i);}
	temppos = check_random(temppos, diff, j, pos);
	write_solution(temppos); int n = temppos.size();
	vector<int> min(n); min = read_solution(min);
	if(diff==9||diff==8||diff==7||diff==6||diff==5||diff==4||diff==3||diff==2){flips = game(temppos, diff, flips, pos, (min_flip(min)), score);}
	score = calc_score(flips, min_flip(min), diff);
	score = check_score(score, diff, flips, (min_flip(min)));
	user = read_initial(user);
	write_temp_score(score);
	top = update(top, score, user);
	update_file(top); reset_count();
	display_score(top);
}
void show_diff(vector<high_score> top){
	Diff_window dif(Point(100,200), 600,400, "FlipFlaps" ); int i;
	Vector<int>pos; //position
		for (i=0;i<9;++i){pos.push_back(i);}
	vector<int>tempx;
	for (i=0;i<9;++i){tempx.push_back(0);}
	for (i=0;i<9;++i){tempx[i]=(350-(pos[i]*12.5));}
	vector<int>templeg;
	for (i=0;i<9;++i){templeg.push_back(0);}
	for (i=0;i<9;++i){templeg[i]=((pos[i]*25)+25);} 
	vector<int>y9s(9);
	for (i=0; i<9; ++i){
		y9s[i]=(151+(i*22));}
	Vector_ref<Rectangle> r1;
	for (i=0; i<pos.size(); ++i){
		r1.push_back(new Rectangle {Point{tempx[i],y9s[i]},templeg[i],8});
		r1[r1.size()-1].set_fill_color(fl_rgb_color(238,196,120));
		dif.attach(r1[r1.size()-1]);}
	Vector_ref<Rectangle> r2;
	for (i=0; i<pos.size(); ++i){
		r2.push_back(new Rectangle {Point{tempx[i],(y9s[i]+7)},templeg[i],10});
		r2[r2.size()-1].set_fill_color(fl_rgb_color(178,134,90));
		dif.attach(r2[r2.size()-1]);}
	if (dif.wait_for_diff() == true) {start_game(top);}}

void display_score(vector<high_score> top) // display high score
{
	HS_window High_Sr(Point(100,200), 600,400, "High Scores");
	int rank{1}, points{0}, temp_score{0}; string player = " NONE ", temp_player;
	
	temp_player = read_initial(temp_player);
	temp_score = read_score(temp_score);
	stringstream ss; 
	
	ss << '#' << top[0].getRank(rank) << " " << top[0].getPlayer(player) << " Pts: " << top[0].getPoints(points);
	Text Rank1{Point{50,50}, ss.str()};  ss.str("");
	ss << '#' << top[1].getRank(rank) << " " << top[1].getPlayer(player) << " Pts: " << top[1].getPoints(points);
	Text Rank2{Point{50,70}, ss.str()};  ss.str("");
	ss << '#' << top[2].getRank(rank) << " " << top[2].getPlayer(player) << " Pts: " << top[2].getPoints(points);
	Text Rank3{Point{50,90}, ss.str()};  ss.str("");
	ss << '#' << top[3].getRank(rank) << " " << top[3].getPlayer(player) << " Pts: " << top[3].getPoints(points);
	Text Rank4{Point{50,110}, ss.str()}; ss.str("");
	ss << '#' << top[4].getRank(rank) << " " << top[4].getPlayer(player) << " Pts: " << top[4].getPoints(points);
	Text Rank5{Point{50,130}, ss.str()}; ss.str("");
	ss << "Player: " << temp_player << " ---" << " Pts: " << temp_score;
	Text Player1{Point{300, 50}, ss.str()}; ss.str("");
	
	High_Sr.attach(Rank1); High_Sr.attach(Rank2); High_Sr.attach(Rank3); High_Sr.attach(Rank4); High_Sr.attach(Rank5); High_Sr.attach(Player1);
	
	update_file(top);
	if (High_Sr.wait_for_button() == true) {show_diff(top); } // goes to game menu when player clicks play, otherwise quit
}

void display_flip() // creates a window, and checks score.txt and the vector of classes. displays score when user sends their initials
{
	int rank{1}, points{0};
	string player = " NONE ";

	Simple_window win(Point(100,200),600,400,"FlipFlaps");

	Text FlipFlap{Point{0,200}, "Flip Flaps"};
	FlipFlap.set_font_size(100);
	FlipFlap.set_font(FL_COURIER);
	win.attach(FlipFlap);
	check_file();

	top = read_file(top);
	printHS(top);
	top = update(top, points, player);
	
	outFile.open("temp_score.txt"); // changes score to 0 to replace old value, last played by previous player
	outFile << 0;
	outFile.close();

	if (win.wait_for_button() == true) {display_score(top); } // displays score if player clicks confirm, otherwise quit
}
int main()
	try {
		display_flip();
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