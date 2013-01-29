
#include "SqliteDataSet.hpp"
#include "SqliteDataRow.hpp"

SqliteDataSet::SqliteDataSet(std::vector<std::string> column_names) {
  column_names_ = std::vector<std::string>(column_names.size());
  for(int i = 0; i < column_names.size(); i++) {
    column_names_.at(i) = column_names.at(i);
  }
}

SqliteDataSet::~SqliteDataSet() {

}

void SqliteDataSet::InsertRow(std::vector<std::string> data) {
  SqliteDataRow new_row = SqliteDataRow(this, this->GetColumnNames().size());
  for(int i = 0; i < data.size(); i++) {
    new_row.SetAt(i, data.at(i));
  }
  rows_.push_back(new_row);
}

SqliteDataRow SqliteDataSet::GetRow(int index) {
  return rows_.at(index);
}

std::vector<std::string> SqliteDataSet::GetColumnNames() {
  return column_names_;
}
int SqliteDataSet::RowCount() {
  return rows_.size();
}
