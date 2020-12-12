#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;
#include "helper_functions.h"

	
int main(){
	cout << "\n \n ---------------------------------CMOS Circuit SPICE GeneratorSimulation----------------------------------" << endl;
    cout << "              Youssef Hussien     Akram Aziz " << endl;
    cout << "                Fundamentals of Microelectronics, AUC, copyrights@fall_2020" << endl;
	cout<<"\nPlease Enter the boolean Expression\n";
	string input;
	cin>>input;
	//This function parses the input and cuts the expressions using the seimcolons and on each expression generate its own CMOS circuit by calling other helper functions
	unordered_map <string,string> expressions = semicolon(input);
	vector<string> out_symbols=get_out(expressions);
	vector<string> exp_list = get_exps(expressions);
	string out_symbol="";
	for(int i=0; i<exp_list.size(); i++)
		{if(is_valid(exp_list[i]))
			{
				//unordered_map<string,string>::iterator got = expressions.find (exp_list[i]);
			out_symbol=out_symbols[i];
			cout<<out_symbol;
			generateFunction(exp_list[i],out_symbol);}
			else
			{cout<<"Input is Wrong\n";
			break;}
		}
	
	return 0;
	}
