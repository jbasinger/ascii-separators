#include <stdlib.h>
#include <string.h>
#include "sep.h"

File create_file(char* name){
  
  File f;
  
  f.name = name;
  f.table_count = 0;
  f.max_tables = INIT_CAP;
  f.tables = malloc(f.max_tables * sizeof(Table));

  return f;

}

Table create_table(char* name){
  
  Table tbl;

  tbl.name = name;
  tbl.max_rows = INIT_CAP;
  tbl.row_count = 0;
  tbl.longest_row = 0;
  tbl.rows = malloc(tbl.max_rows * sizeof(Row));

  return tbl;

}

Row create_row(){
  
  Row row;
  
  row.field_count = 0;
  row.max_fields = INIT_CAP;
  row.fields = malloc(row.max_fields * sizeof(Row));
  row.longest_field = 0;

  return row;

}

void add_table(File* file, Table table){
  
  file->tables[file->table_count++] = table;

}

void add_row(Table* table, Row row){

  table->rows[table->row_count++] = row;

}

void add_field(Row* row, char* data){

  Field f;
  f.data = data;
  f.length = strlen(data);

  row->fields[row->field_count++] = f;

}