#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sep.h"

Database create_file(char* name){
  
  Database db;
  
  db.name = name;
  db.table_count = 0;
  db.max_tables = INIT_CAP;
  db.tables = malloc(db.max_tables * sizeof(Table));

  return db;

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
  row.fields = malloc(row.max_fields * sizeof(Field));
  row.longest_field = 0;

  return row;

}

void add_table(Database* db, Table table){
  
  db->tables[db->table_count++] = table;

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

void save_file(Database* db, char* filepath){

  FILE* f = fopen(filepath, "w");

  fprintf(f, "%c", FILE_SEP);
  fprintf(f, "%d", db->table_count);
  fprintf(f, "%c", UNIT_SEP);
  fprintf(f, "%s", db->name);

  for(int d = 0; d < db->table_count; d++){

    Table tbl = db->tables[d];
    fprintf(f, "%c", GRP_SEP);
    fprintf(f, "%d", tbl.row_count);
    fprintf(f, "%c", UNIT_SEP);
    fprintf(f, "%s", tbl.name);

    for(int r = 0; r < tbl.row_count; r++){

      Row row = tbl.rows[r];
      fprintf(f, "%c", REC_SEP);
      fprintf(f, "%d", row.field_count);
      

      for(int i = 0; i < row.field_count; i++){

        fprintf(f, "%c", UNIT_SEP);
        fprintf(f, "%s", row.fields[i].data);

      }

    }

  }

  fclose(f);

}
/*
      [DB]table count[FIELD]db_name
        [TABLE]row_count[FIELD]table_name
          [ROW]field_count
            [FIELD]data[FIELD]data[FIELD]data
          [ROW]field_count
            [FIELD]data[FIELD]data
      EOF no actual \n unless pretty printed?
      Could do another db in the same physical file
*/