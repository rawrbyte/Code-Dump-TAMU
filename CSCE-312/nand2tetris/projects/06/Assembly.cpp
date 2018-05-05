// Raymond Zhu / 923008555 / Nand2Tetris / Project 06 Assembler / CPP / CSCE 312 /
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
#include <map>
#include <iomanip>
#include <algorithm>
#include <cstdint>
using namespace std;

ofstream outFile;
ifstream inFile;

// parses binary value for destination
string parseD(int binary){
	switch (binary){
	case 0:
		return "000";
		break;
	case 1:
		return "001";
		break;
	case 2:
		return "010";
		break;
	case 3:
		return "011";
		break;
	case 4:
		return "100";
		break;
	case 5:
		return "101";
		break;
	case 6:
		return "110";
		break;
	case 7:
		return "111";
		break;
	default:
		return "000";
		break;
	}
}
// parses binary value for composition
string parseC(int binary){
	switch (binary){
	case 0:
		return "0101010";
		break;
	case 1:
		return "0111111";
		break;
	case 2:
		return "0111010";
		break;
	case 3:
		return "0001100";
		break;
	case 4:
		return "0110000";
		break;
	case 5:
		return "0001101";
		break;
	case 6:
		return "0110001";
		break;
	case 7:
		return "0001111";
		break;
	case 8:
		return "0110011";
		break;
	case 9:
		return "0011111";
		break;
	case 10:
		return "0110111";
		break;
	case 11:
		return "0001110";
		break;
	case 12:
		return "0110010";
		break;
	case 13:
		return "0000010";
		break;
	case 14:
		return "0010011";
		break;
	case 15:
		return "0000111";
		break;
	case 16:
		return "0000000";
		break;
	case 17:
		return "0010101";
		break;
	case 18:
		return "1110000";
		break;
	case 19:
		return "1110001";
		break;
	case 20:
		return "1110011";
		break;
	case 21:
		return "1110111";
		break;
	case 22:
		return "1110010";
		break;
	case 23:
		return "1000010";
		break;
	case 24:
		return "1010011";
		break;
	case 25:
		return "1000111";
		break;
	case 26:
		return "1000000";
		break;
	case 27:
		return "1010101";
		break;
	default:
		return "0000000";
		break;
	}
}
// parses binary value for jump
string parseJ(int binary){
	switch (binary){
	case 0:
		return "000";
		break;
	case 1:
		return "001";
		break;
	case 2:
		return "010";
		break;
	case 3:
		return "011";
		break;
	case 4:
		return "100";
		break;
	case 5:
		return "101";
		break;
	case 6:
		return "110";
		break;
	case 7:
		return "111";
		break;
	default:
		return "000";
		break;
	}

}
// parses integer value for later binary conversion for pre-set symbols
int parseS(int binary, vector<int> locate){
	switch (binary){
	case 0:
		return 0;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 1;
		break;
	case 3:
		return 2;
		break;
	case 4:
		return 3;
		break;
	case 5:
		return 4;
		break;
	case 6:
		return 0;
		break;
	case 7:
		return 1;
		break;
	case 8:
		return 2;
		break;
	case 9:
		return 3;
		break;
	case 10:
		return 4;
		break;
	case 11:
		return 5;
		break;
	case 12:
		return 6;
		break;
	case 13:
		return 7;
		break;
	case 14:
		return 8;
		break;
	case 15:
		return 9;
		break;
	case 16:
		return 10;
		break;
	case 17:
		return 11;
		break;
	case 18:
		return 12;
		break;
	case 19:
		return 13;
		break;
	case 20:
		return 14;
		break;
	case 21:
		return 15;
		break;
	case 22:
		return 16384;
		break;
	case 23:
		return 24576;
		break;
	default:
		return locate[binary - 24];
		break;
	}
}
// searches for case number
int parseValue(vector<string> parseV, string parser){
	int x = -1;
	for (int i = 0; i<parseV.size(); i++)
	{
		if (parser == parseV[i]) { x = i; }
	}
	return x;
}
// removes all white space and comments from the asm file
void cleanfile(string filename){
	filename = filename + ".asm";
	inFile.open(filename);
	outFile.open("newfile.asm");
	string line = "";
	if (inFile.is_open()){
		while (inFile.good()) {
			getline(inFile, line);

			line.erase(remove_if(line.begin(), line.end(), [](char x){return isspace(x); }), line.end());
			if (line.empty())
				continue;

			while (line.find("/*") != string::npos) {
				size_t Beg = line.find("/*");
				line.erase(Beg, (line.find("*/", Beg) - Beg) + 2);
			}
			while (line.find("//") != std::string::npos) {
				size_t Beg = line.find("//");
				line.erase(Beg, line.find("/n", Beg) - Beg);
			}

			outFile << line << endl;
		}
	}

	cout << "File    Cleaned" << endl;

	outFile.close();
	inFile.close();
}
// checks to see if a string is a number
bool is_number(const std::string& s){
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int main(){
	vector<string> vD = { "null", "M", "D", "MD", "A", "AM", "AD", "AMD" };
	vector<string> vC = { "0", "1", "-1", "D", "A", "!D", "!A", "-D", "-A", "D+1", "A+1", "D-1", "A-1", "D+A", "D-A", "A-D", "D&A",
		"D|A", "M", "!M", "-M", "M+1", "M-1", "D+M", "D-M", "M-D", "D&M", "D|M" };
	vector<string> vJ = { "null", "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP" };
	vector<string> vS = { "0", "SP", "LCL", "ARG", "THIS", "THAT", "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7",
		"R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "SCREEN", "KBD" };
	vector<int> locate;
	vector<string> variable;
	string filename = "";
	cout << "Input asm file: ";
	cin >> filename;
	cleanfile(filename);

	inFile.open("newfile.asm");
	outFile.open(filename + ".hack");

	string input = "";
	string input1 = "";
	string dest = "";
	string comp = "";
	string jump = "";
	int checker = 0;
	int counter = 0;
	int counter1 = 0;

	// first pass of asm file. checks for symbols.
	if (inFile.is_open()){
		while (inFile.good()){
			getline(inFile, input);
			if (input == "")
				continue;
			counter1++;
			if (input.at(0) == '('){
				string push = "";
				for (int i = 1; i < input.length(); i++){
					if (input.at(i) != ')') { push = push + input.at(i); }
					if (input.at(i) == ')') { break; }
				}

				int j = 0;
				for (int i = 0; i < vS.size(); i++){
					if (push == vS[i]) { j++; }
				}
				if (j == 0){ vS.push_back(push); counter1--; locate.push_back(counter1); }
			}
		}
	}

	inFile.close();
	inFile.open("newfile.asm");

	// second pass of asm file. checks for variables.
	if (inFile.is_open()){
		while (inFile.good()){
			getline(inFile, input);
			if (input == "")
				continue;
			if (input.at(0) == '@'){
				string push = "";
				for (int i = 1; i < input.length(); i++){
					push = push + input.at(i);
				}
				if (is_number(push)){
					continue;
				}
				int j = 0, h = 0;
				for (int i = 0; i < vS.size(); i++){
					if (push == vS[i]) { j++; }
				}
				for (int i = 0; i < variable.size(); i++){
					if (push == variable[i]) { h++; }
				}
				if ((j == 0) && (h == 0)){ variable.push_back(push); }
			}
		}
	}

	inFile.close();
	inFile.open("newfile.asm");

	// hack language conversion process
	if (inFile.is_open()){
		while (inFile.good()){
			// ignores empty lines
			getline(inFile, input);
			if (input == "")
				continue;
			// reset variables
			dest = "";
			comp = "";
			jump = "";
			input1 = "";
			checker = 0;
			if (input.at(0) == '@'){
				// recreates the line without @
				for (int i = 1; i < input.length(); i++){
					input1 = input1 + input.at(i);
				}
				// checks if line is pre-set/declared symbol
				int y = parseValue(vS, input1);
				if (y != -1){
					string binary = bitset<16>(parseS(y, locate)).to_string();
					outFile << binary << "\n";
					counter++;
				}
				else{
					// checks if line is a variable
					int z = parseValue(variable, input1);
					int pos = 0;
					if (z != -1){
						for (int i = 0; i < variable.size(); i++){
							if (input1 == variable[i])
								pos = i;
						}
						string binary = bitset<16>((16 + pos)).to_string();
						outFile << binary << "\n";
						counter++;
					}
					else{
						// if line is just a number. go here. 
						if (input.length() == 2){
							input1 = input.at(1);
						}
						// converts string to integer
						int x = stoi(input1);
						string binary = bitset<16>(x).to_string();
						outFile << binary << "\n";
						counter++;
					}
				}
			}
			else{
				// ignores symbols and variables
				if (input.at(0) == '('){
					continue;
				}
				// checks if a destination exists
				for (int i = 0; i < input.length(); i++){
					if (input.at(i) == '=') { checker++; }
				}
				// creates destination string
				if (checker == 1){
					for (int i = 0; i < input.length(); i++){
						if (input.at(i) != '=') { dest = dest + input.at(i); }
						if (input.at(i) == '=') { break; }
					}
				}
				// creates composition string. starts after destination length + 1 (to skip '=' sign)
				if (checker == 1){
					for (int i = dest.length() + 1; i < input.length(); i++){
						if (input.at(i) != ';') { comp = comp + input.at(i); }
						if (input.at(i) == ';') { break; }
					}
				}
				// creates compostion string. technically starts at zero. since dest should == ""
				if (checker == 0){
					for (int i = dest.length(); i < input.length(); i++){
						if (input.at(i) != ';') { comp = comp + input.at(i); }
						if (input.at(i) == ';') { break; }
					}
				}
				// creates jump string. starts after destination and composition length + 2 (to skip '=' & ';' sign)
				if (checker == 1){
					if (dest.length() + comp.length() + 1 == input.length()) { jump = "null"; }
					else{
						for (int i = dest.length() + comp.length() + 2; i < input.length(); i++){
							jump = jump + input.at(i);
						}
					}
				}
				// creates jump string. technically starts at composition length. since dest should == ""
				if (checker == 0){
					if (dest.length() + comp.length() + 1 == input.length()) { jump = "null"; }
					else{
						for (int i = dest.length() + comp.length() + 1; i < input.length(); i++){
							jump = jump + input.at(i);
						}
					}
				}
				// sets dest equal to null if no equal sign exists in command
				if (checker == 0){
					dest = "null";
				}
				// combination steps
				int iD = 0, iC = 0, iJ = 0;
				// grabs case number for dest, comp, jump
				iD = parseValue(vD, dest);
				iC = parseValue(vC, comp);
				iJ = parseValue(vJ, jump);
				// collects binary values and concatenates strings
				outFile << "111" + parseC(iC) + parseD(iD) + parseJ(iJ) << "\n";
				counter++;
			}
		}
	}

	cout << "Done!" << endl;
	inFile.close();
	outFile.close();

	return 0;
}
