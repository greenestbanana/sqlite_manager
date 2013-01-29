
#include "SqliteDataRow.hpp"
#include "SqliteDataSet.hpp"

SqliteDataRow::SqliteDataRow(SqliteDataSet *parent, int column_count) {
  parent_ = parent;
  data_ = std::vector<std::string>(column_count);
}
SqliteDataRow::~SqliteDataRow() {
  parent_ = NULL;
}

std::string SqliteDataRow::GetAt(int index) {
  return data_.at(index);
}

std::string SqliteDataRow::GetColumn(std::string column_name) {
  int index = this->FindColumnIndex(column_name);
  if(index >= 0) {
    return this->GetAt(index);
  }
  return NULL;
}

std::string SqliteDataRow::SetAt(int index, std::string value) {
  data_.at(index) = value;
}

std::string SqliteDataRow::SetColumn(std::string column_name, std::string value) {
  int index = this->FindColumnIndex(column_name);
  if(index >= 0) {
    this->SetAt(index, value);
  }
}

int SqliteDataRow::FindColumnIndex(std::string column_name) {
  std::vector<std::string> column_list = parent_->GetColumnNames();
  for(int i = 0; i < column_list.size(); i++) {
    if(column_list.at(i) == column_name) {
      return i;
    }
  }
  return -1;
}
