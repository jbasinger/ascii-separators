#include <stdio.h>
#include <string.h>
#include "sep.h"

int test_should_add_field_to_row() {
  printf("test_should_add_field_to_row...");

  int res = 0;
  char* data = strdup("test data");
  Row r = create_row();

  add_field(&r, data);

  if(strcmp(r.fields[0].data, data)){
    printf("\n\tFile name not set properly");
    res |= 1;
  }

  if(r.fields[0].length != strlen(data)){
    printf("\n\tField data length does not match");
    res |= 1;
  }

  if(r.field_count != 1){
    printf("\n\tRow field_count not equal to 1");
    res |= 1;
  }
  
  if(!res){
    printf("🟢\n");
  }else{
    printf("\n🔴 FAILED\n");
  }

  return res;
}

int test_should_add_row_to_table() {
  printf("test_should_add_row_to_table...");

  int res = 0;
  char* table_name = strdup("test_table");
  Table t = create_table(table_name);
  Row r = create_row();

  add_row(&t, r);

  if(t.row_count != 1){
    printf("\n\tTable row_count not equal to 1");
    res |= 1;
  }
  
  if(t.rows[0].max_fields != r.max_fields){
    printf("\n\tTable added doesn't match table we started with");
    res |= 1;
  }

  if(!res){
    printf("🟢\n");
  }else{
    printf("\n🔴 FAILED\n");
  }

  return res;
}

int test_should_add_table_to_file() {
  printf("test_should_add_table_to_file...");

  int res = 0;
  char* file_name = strdup("test");
  char* table_name = strdup("test_table");
  File f = create_file(file_name);
  Table t = create_table(table_name);

  add_table(&f,t);

  if(f.table_count != 1){
    printf("\n\tFile table_count not equal to 1");
    res |= 1;
  }
  
  if(strcmp(f.tables[0].name, t.name)){
    printf("\n\tTable added doesn't match table we started with");
    res |= 1;
  }

  if(!res){
    printf("🟢\n");
  }else{
    printf("\n🔴 FAILED\n");
  }

  return res;
}

int test_should_make_row() {
  printf("test_should_make_row...");
  int res = 0;

  Row r = create_row();
  
  if(r.field_count != 0){
    printf("\n\tRow field_count not equal to 0");
    res |= 1;
  }

  if(r.max_fields != INIT_CAP){
    printf("\n\tRow max_fields not equal to INIT_CAP");
    res |= 1;
  }

  if(r.longest_field != 0){
    printf("\n\tRow longest_field not equal to 0");
    res |= 1;
  }

  if(sizeof(r.fields) != (sizeof(r.fields) * r.max_fields)){
    printf("\n\tRow fields not allocated");
    res |= 1;
  }

  if(!res){
    printf("🟢\n");
  }else{
    printf("\n🔴 FAILED\n");
  }

  return res;

}

int test_should_make_table() {
  printf("test_should_make_table...");
  int res = 0;

  char* name = strdup("test_table");
  Table t = create_table(name);

  if(t.row_count != 0){
    printf("\n\tTable row_count not equal to 0");
    res |= 1;
  }

  if(t.max_rows != INIT_CAP){
    printf("\n\tTable max_rows not equal to INIT_CAP");
    res |= 1;
  }

  if(strcmp(t.name, name)){
    printf("\n\tTable table_count not equal to 0");
    res |= 1;
  }

  if(sizeof(t.rows) != (sizeof(t.rows) * t.max_rows)){
    printf("\n\tTable rows not allocated");
    res |= 1;
  }

  if(!res){
    printf("🟢\n");
  }else{
    printf("\n🔴 FAILED\n");
  }
  return res;

}

int test_should_make_file() {
  printf("test_should_make_file...");

  int res = 0;
  char* name = strdup("test");
  File f = create_file(name);

  if(f.max_tables != INIT_CAP){
    printf("\n\tFile max_tables not equal to INIT_CAP");
    res |= 1;
  }

  if(f.table_count != 0){
    printf("\n\tFile table_count not equal to 0");
    res |= 1;
  }
  
  if(strcmp(f.name, name)){
    printf("\n\tFile name not set properly");
    res |= 1;
  }

  if(sizeof(f.tables) != (sizeof(f.tables) * f.max_tables)){
    printf("\n\tFile tables not allocated");
    res |= 1;
  }

  if(!res){
    printf("🟢\n");
  }else{
    printf("\n🔴 FAILED\n");
  }

  return res;

}

int main(){
  
  int result = 0;
  
  printf("\n");

  result |= test_should_make_file();
  result |= test_should_make_table();
  result |= test_should_make_row();
  result |= test_should_add_table_to_file();
  result |= test_should_add_row_to_table();
  result |= test_should_add_field_to_row();

  printf("\n");

  if(result == 0){
    printf("All tests passed!\n");
  } else {
    printf("Tests failed.\n");
  }

  printf("\n");
  return result;
}