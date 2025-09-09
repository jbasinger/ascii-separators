
#ifndef _sep
#define _sep

#define DB_SEP '\x1C'
#define TBL_SEP '\x1D'
#define ROW_SEP '\x1E'
#define FLD_SEP '\x1F'

#define FILE_SEP '\x1C'
#define GRP_SEP '\x1D'
#define REC_SEP '\x1E'
#define UNIT_SEP '\x1F'

#define INIT_CAP 2

typedef struct Field {
  int length;
  char* data;
} Field;
typedef Field Unit;

typedef struct Row {
  int field_count;
  int max_fields;
  int longest_field;
  Field* fields;
} Row;
typedef Row Record;

typedef struct Table {
  int row_count;
  int max_rows;
  char* name;
  Row* longest_row;
  Row* rows;
} Table;
typedef Table Group;

typedef struct Database {
  int table_count;
  int max_tables;
  char* name;
  Table* tables;
} Database;
typedef Database File;

void save_file(Database* db, char* filepath);
// Database load_file(char* filepath);
// char* print_file(Database db);

Database create_file(char* name);
Table create_table(char* name);
Row create_row();

void add_table(Database* db, Table table);
void add_row(Table* table, Row row);
void add_field(Row* row, char* data);

#endif