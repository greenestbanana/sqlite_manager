
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include "sqlite/sqlite3.h"
#include "SqliteConnection.hpp"

int dogEnumerator(void* list, int argc, char **argv, char **azColName) {
  std::vector<std::string>* dogList = (std::vector<std::string>*) list;
  std::string curString = "";
  for(int i = 0; i < argc; i++) {
    if(std::strcmp(azColName[i], "name") == 0) {
      curString.append(argv[i]);
    } else if(std::strcmp(azColName[i], "breed") == 0) {
      curString.append(" the ");
      curString.append(argv[i]);
    }
  }
  dogList->push_back(curString);
  return 0;
}

int PrintRow(void *callback_arg, int column_count, char **column_data, char **column_names) {
  int *row_count = (int*)callback_arg;

  if(*row_count == 1) {
    for(int i = 0; i < column_count; i++) {
      std::cout << column_names[i];
      if(i == (column_count - 1)) {
        std::cout << std::endl;
      } else {
        std::cout << " | ";
      }
    }
  }
  
  std::cout << *row_count << ": ";
  
  *row_count += 1;
  
  for(int i = 0; i < column_count; i++) {
    std::cout << column_data[i];
    if(i == (column_count - 1)) {
      std::cout << std::endl;
    } else {
      std::cout << " | ";
    }
  }
}

int main() {
  std::cout << "Say now what is our SQLite version? " << sqlite3_version << std::endl;
  std::cout << "What owner id are you interested in?" << std::endl;
  std::string id;
  std::cin >> id;
  
  std::string query = "SELECT name, breed FROM dogs WHERE owner_id = ";
  query.append(id);
  
  bool success = true;
  SqliteConnection conn("test");
  success = conn.Open();
  if(!success) {
    std::cout << "Error done occurt: " << conn.ErrorMessage() << std::endl;
    return 1;
  }
  /*
  success = conn.QuickQuery(query);
  if(!success) {
    std::cout << "Error done occurt: " << conn.ErrorMessage() << std::endl;
    return 1;
  }
  */
  
  SqliteDataSet *query_set = conn.DataQuery(query);
  if(query_set == NULL) {
    std::cout << "Error done occurt: " << conn.ErrorMessage() << std::endl;
    return 1;
  }
  
  std::cout << "They have " << query_set->RowCount() << (query_set->RowCount() == 1 ? " dog: " : " dogs: ") << std::endl;
  for(int i = 0; i < query_set->RowCount(); i++) {
    std::cout << query_set->GetRow(i).GetColumn("name");
    std::cout << " the ";
    std::cout << query_set->GetRow(i).GetColumn("breed") << std::endl;
  }
  
  success = conn.Close();
  if(!success) {
    std::cout << "Error done occurt: " << conn.ErrorMessage() << std::endl;
    return 1;
  }
  
  delete query_set;
  
  //std::string id = getInput("What owner id are you interested in?");
  /*
  sqlite3 *db;
  char *execMessage;
  int err;
  
  err = sqlite3_open("test", &db);
  if(err != SQLITE_OK) {
    std::cout << "Woah now there is an error: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_close(db);
    return 1;
  }
  
  std::string query = "SELECT name, breed FROM dogs WHERE owner_id = ";
  query.append(id);
  std::vector<std::string> dogList;
  
  err = sqlite3_exec(db, query.c_str(), dogEnumerator, &dogList, &execMessage);
  
  std::cout << "These are their dogs :" << std::endl;
  
  for(int i = 0; i < dogList.size(); i++) {
    std::cout << dogList.at(i) << std::endl;
  }
  
  int row = 1;
  err = sqlite3_exec(db, query.c_str(), PrintRow, &row, &execMessage);
  
  sqlite3_close(db);*/
    
  return 0;
}