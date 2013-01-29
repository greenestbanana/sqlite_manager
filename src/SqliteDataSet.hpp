
#ifndef SQLITEDATASET_H
#define SQLITEDATASET_H

#include <string>
#include <vector>

class SqliteDataRow;

class SqliteDataSet {
public:
  SqliteDataSet(std::vector<std::string> column_names);
  ~SqliteDataSet();
  
  void InsertRow(std::vector<std::string> data);
  
  SqliteDataRow GetRow(int index);
  std::vector<std::string> GetColumnNames();
  int RowCount();
private:
  std::vector<std::string> column_names_;
  std::vector<SqliteDataRow> rows_;
};

#endif
