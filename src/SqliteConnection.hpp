
#ifndef SQLITECONNECTION_H
#define SQLITECONNECTION_H

#include <string>
#include <vector>
#include "sqlite/sqlite3.h"
#include "SqliteDataSet.hpp"
#include "SqliteDataRow.hpp"

class SqliteConnection {
public:
  SqliteConnection(std::string db_path);
  ~SqliteConnection();
  
  bool Open();
  bool Close();
  
  SqliteDataSet* DataQuery(std::string query);
  
  /*
  bool QuickQuery(std::string query);
  static int PrintRow(void *callback_arg, int column_count, char **column_data, char **column_names);
  */
  
  std::string ErrorMessage();
private:
  std::string db_path_;
  sqlite3 *db_connection_;
  
  static int GetRow(void *data_set_ptr, int column_count, char **column_data, char **column_names);
};

#endif