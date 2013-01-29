
#ifndef SQLITEDATAROW_H
#define SQLITEDATAROW_H

#include <string>
#include <vector>

class SqliteDataSet;

class SqliteDataRow {
public:
  SqliteDataRow(SqliteDataSet *parent, int column_count);
  ~SqliteDataRow();
  
  std::string GetAt(int index);
  std::string GetColumn(std::string column_name);
  
  std::string SetAt(int index, std::string value);
  std::string SetColumn(std::string column_name, std::string value);
  
private:
  SqliteDataSet *parent_;
  std::vector<std::string> data_;
  
  int FindColumnIndex(std::string column_name);
};

#endif
