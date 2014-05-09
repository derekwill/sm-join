//Smjoin.h

#ifndef SMJOIN_H_
#define SMJOIN_H_

#include <string>
#include <vector>
#include <fstream>

class Smjoin {

 public:
  //constructor
 Smjoin(std::string tab_1, std::string tab_2, 
	std::string column_name, std::string file) 
   : table_1(tab_1), table_2(tab_2), sort_by(column_name), file_name(file) 
  { set_tables(); }
   bool smjoin();

 private:
   void set_up_header(std::ofstream&);

  // void out(int, int, std::ofstream);
  void set_tables();
  bool repeat_1, repeat_2; //ugly
  //data field
  std::string table_1, table_2, sort_by, file_name;
  std::vector< std::vector<std::string> > table_1_vec;
  std::vector<std::string> table_1_vec_s;
   std::vector<int> table_1_vec_d;
  std::vector< std::vector<std::string> > table_2_vec;
  std::vector<std::string> table_2_vec_s;
  std::vector<int> table_2_vec_d;
  int column_1, column_tot_1, column_tot_2, width_1, width_2;;
  std::string header_1, header_2;
  
};
#endif
