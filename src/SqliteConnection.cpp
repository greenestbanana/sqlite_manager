
#include "SqliteConnection.hpp"

SqliteConnection::SqliteConnection(std::string db_path) {
  db_path_ = db_path;
}
SqliteConnection::~SqliteConnection() {

}

bool SqliteConnection::Open() {
  int err = sqlite3_open(db_path_.c_str(), &db_connection_);
  return err == SQLITE_OK;
} 

bool SqliteConnection::Close() {
  int err = sqlite3_close(db_connection_);
  return err == SQLITE_OK;
}

SqliteDataSet* SqliteConnection::DataQuery(std::string query) {
  SqliteDataSet *return_set = NULL;
  int err = sqlite3_exec(db_connection_, query.c_str(), SqliteConnection::GetRow, &return_set, NULL);
  if(err == SQLITE_OK) {
    return return_set;
  } else {
    return NULL;
  }
}

int SqliteConnection::GetRow(void *data_set_ptr, int column_count, char **column_data, char **column_names) {
  SqliteDataSet **data_set = (SqliteDataSet**) data_set_ptr;
  if(*data_set == NULL) {
    std::vector<std::string> columns = std::vector<std::string>(column_count);
    for(int i = 0; i < column_count; i++) {
      columns.at(i) = column_names[i];
    }
    *data_set = new SqliteDataSet(columns);
  }
  
  std::vector<std::string> new_data = std::vector<std::string>(column_count);
  for(int i = 0; i < column_count; i++) {
    new_data.at(i) = column_data[i];
  }
  (*data_set)->InsertRow(new_data);
  return SQLITE_OK;
}

/*
bool SqliteConnection::QuickQuery(std::string query) {
  int row_count = 1;
  char *exec_message;
  int err = sqlite3_exec(db_connection_, query.c_str(), SqliteConnection::PrintRow, &row_count, &exec_message);
  return err == SQLITE_OK;
}

int SqliteConnection::PrintRow(void *callback_arg, int column_count, char **column_data, char **column_names) {
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
*/
std::string SqliteConnection::ErrorMessage() {
  return sqlite3_errmsg(db_connection_);
}
