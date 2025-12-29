#ifndef DATABASE_H  // Защита от множественного включения
#define DATABASE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
typedef struct{
    char * key;
    void * value;
    size_t value_size;
} KeyValue;


typedef struct{
    KeyValue *entities;
    size_t capacity;
    size_t size;
} DataBase;

DataBase * dbcreate(size_t initial_size);
void db_set(DataBase * db, const char * key, const void * value, size_t value_size);
void db_save(DataBase *db, const char *filename);
void* db_get(DataBase *db, const char* key, size_t * value_size);
bool db_get_bool(DataBase *db, const char * key, size_t * value_size);
#endif