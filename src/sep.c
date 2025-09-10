#include "sep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


Database create_file(char* name) {

  Database db;

  db.name = name;
  db.table_count = 0;
  db.max_tables = INIT_CAP;
  db.tables = malloc(db.max_tables * sizeof(Table));

  return db;
}

Table create_table(char* name) {

  Table tbl;

  tbl.name = name;
  tbl.max_rows = INIT_CAP;
  tbl.row_count = 0;
  tbl.longest_row = 0;
  tbl.rows = malloc(tbl.max_rows * sizeof(Row));

  return tbl;
}

Row create_row() {

  Row row;

  row.field_count = 0;
  row.max_fields = INIT_CAP;
  row.fields = malloc(row.max_fields * sizeof(Field));
  row.longest_field = 0;

  return row;
}

void add_table(Database* db, Table table) {

  db->tables[db->table_count++] = table;
}

void add_row(Table* table, Row row) {

  table->rows[table->row_count++] = row;
}

void add_field(Row* row, char* data) {

  Field f;
  f.data = data;
  f.length = strlen(data);

  row->fields[row->field_count++] = f;
}

void save_file(Database* db, char* filepath) {

  FILE* f = fopen(filepath, "w");

  fprintf(f, "%c", FILE_SEP);
  fprintf(f, "%d", db->table_count);
  fprintf(f, "%c", UNIT_SEP);
  fprintf(f, "%s", db->name);

  for (int d = 0; d < db->table_count; d++) {

    Table tbl = db->tables[d];
    fprintf(f, "%c", GRP_SEP);
    fprintf(f, "%d", tbl.row_count);
    fprintf(f, "%c", UNIT_SEP);
    fprintf(f, "%s", tbl.name);

    for (int r = 0; r < tbl.row_count; r++) {

      Row row = tbl.rows[r];
      fprintf(f, "%c", REC_SEP);
      fprintf(f, "%d", row.field_count);

      for (int i = 0; i < row.field_count; i++) {

        fprintf(f, "%c", UNIT_SEP);
        fprintf(f, "%s", row.fields[i].data);
      }
    }
  }

  fclose(f);
}

int load_file(Database* db, char* filepath) {

  FILE* f = fopen(filepath, "rb");

  struct stat st;
  fstat(f, &st);
  size_t file_size = st.st_size;

  char* file_string = malloc(file_size + 1);
  if (!file_string) {
    fclose(f);
    return 1; //Malloc failed
  }

  file_string[file_size]='\0';

  size_t bytes_read = fread(file_string, sizeof(char), file_size, f);
  if(bytes_read != file_size){
    fclose(f);
    return 10; //Read failed
  }

  int pos = 0;

  //First character needs to be a db separator
  if(data[pos++] != DB_SEP){
    fclose(f);
    return 20; //Invalid file;
  }

  char* stop
  long table_count = strtol(&data[pos], &stop, 10);
  pos += (stop - &data[pos]);
  db->table_count = table_count;

  //We should be at a field sep here
  if(data[pos++] != FLD_SEP){
    fclose(f);
    return 20; //Invalid file;
  }

  char* sep = strchr(data, TBL_SEP); 

  fclose(f);
  return 99;
}

// Build up a buffer until we hit the next separator
static int read_sep(char* dest_data, char* src_data, int pos, char sep) {

  int i;
  for(i = pos; src_data[i] == sep || src_data[i] == '\0'; i++);

  int len = i - pos;
  dest_data = malloc(len * sizeof(char));
  memcpy(dest_data, src_data, len - 1);
  
  return len;
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