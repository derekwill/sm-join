//Smjoin.cpp 

#include "Smjoin.h"
#include "templ_sort.h"
#include "Display.h"
#include "Lexer.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

void Smjoin::set_tables() {
	repeat_1 = false;
	repeat_2 = false;
	Display display_1(sort_by, table_1);
	display_1.sort();
	repeat_1 = display_1.prepare_print();
	table_1_vec = display_1.get_tables();
	table_1_vec_s = display_1.get_sort_by_tables();
	table_1_vec_d = display_1.get_sorted_tables();
	column_1 = display_1.get_sort_by();
	column_tot_1 = display_1.get_column_tot();
	header_1 = display_1.get_first_line();
	width_1 = display_1.get_biggest_width();

	Display display_2(sort_by, table_2);
	display_2.sort();
	repeat_2 = display_2.prepare_print();
	table_2_vec = display_2.get_tables();
	table_2_vec_s = display_2.get_sort_by_tables();
	table_2_vec_d = display_2.get_sorted_tables();
	column_tot_2 = display_2.get_column_tot();
	header_2 = display_2.get_first_line();
	width_2 = display_2.get_biggest_width();
}

void Smjoin::set_up_header(ofstream& myfile) {
	Lexer lex_1, lex_2;
	Token tok;
	int i = 0;
	lex_1.set_input(header_1);
	lex_2.set_input(header_2);

	while(lex_1.has_more_token()){
		tok = lex_1.next_token();
		if(i != column_1) {
			if(tok.type != DEL){
				myfile<<tok.value;
			} else {
				myfile<<"("<<tok.value<<")"<< setw(width_1);
			}
		} else {
			lex_1.next_token();
		}
		i++;
	}

	while(lex_2.has_more_token()){
		tok =  lex_2.next_token();
		if(tok.type != DEL){
			myfile<<tok.value;
		} else {
			myfile<<"("<<tok.value<<")"<< setw(width_1);
		}
	}
	myfile<<"\n";
}

/*
 *	Sort-merge join
 */

bool Smjoin::smjoin(){
	stringstream ss;
	int m;
	ofstream myfile;

	myfile.open(file_name.c_str());

	if(myfile.is_open()&&(!repeat_1)&&(!repeat_2)){
		int i = 0, j = 0;

		set_up_header(myfile); 

		while( i<table_1_vec_s.size() && j<table_2_vec_s.size()){
			if (table_1_vec_s[i] < table_2_vec_s[j]){
				i++;
			} else if (table_1_vec_s[i] > table_2_vec_s[j]) {
				j++;
			}else{
				for(int k = 0; k<column_tot_1;k++){
					ss << table_1_vec_d[i];
					ss >> m;
					if(k != column_1)
						myfile<<left<< setw(width_1)<<table_1_vec[m][k]<< " ";
					ss.clear();
				}
				for(int l = 0; l < column_tot_2; l++){
					ss << table_2_vec_d[j];
					ss >> m;
					myfile<<left<< setw(width_1)<<table_2_vec[m][l]<< " ";
					ss.clear();
				}	  
				myfile<<"\n";
				j++;
			}
		}
	}
	myfile.close();
	return repeat_1 || repeat_2; 
}
