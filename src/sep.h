
#ifndef _sep
#define _sep

#define FILE_SEP '\x1C'
#define TBL_SEP '\x1D'
#define ROW_SEP '\x1E'
#define FLD_SEP '\x1F'

#define INIT_CAP 1

typedef struct Field {
  int length;
  char* data;
} Field;

typedef struct Row {
  int field_count;
  int max_fields;
  int longest_field;
  Field* fields;
} Row;

typedef struct Table {
  int row_count;
  int max_rows;
  char* name;
  Row* longest_row;
  Row* rows;
} Table;

typedef struct File {
  int table_count;
  int max_tables;
  char* name;
  Table* tables;
} File;

// void save_file(File file, char* filepath);
// File load_file(char* filepath);
// void print_file(File file);

File create_file(char* name);
Table create_table(char* name);
Row create_row();

void add_table(File* file, Table table);
void add_row(Table* table, Row row);
void add_field(Row* row, char* data);

#endif