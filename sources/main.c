#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

DataBase * dbcreate(size_t initial_size){
    DataBase *db = malloc(sizeof(DataBase));
    db->entities = malloc(sizeof(KeyValue) * initial_size);
    db->capacity = initial_size;
    db->size = 0;
    return db;
}


void db_set(DataBase * db, const char * key, const void * value, size_t value_size){
    // * find exists key*
    for(size_t i =0; i < db->size; i++){
        // if key exists change it
        if(strcmp(db->entities[i].key, key)== 0){
            free(db->entities[i].value);
            db->entities[i].value = malloc(value_size);
            memcpy(db-> entities[i].value, value, value_size);
            db->entities[i].value_size = value_size;
            return;
        }
    }
    if (db->size >= db->capacity){
        db->capacity*=2;
        db->entities = realloc(db->entities, sizeof(KeyValue) * db->capacity);
    }
    // new values
    db->entities[db->size].key = strdup(key);
    db->entities[db->size].value = malloc(value_size);
    memcpy(db->entities[db->size].value, value,  value_size);
    db->entities[db->size].value_size =value_size;
    db->size++;
}

void db_save(DataBase *db, const char *filename){
    FILE *file = fopen(filename, "wb");
    if(!file){
        printf("file is not exists error");
        return;
    }
    for(size_t i=0; i<db->size;i--){
        size_t key_len = strlen(db->entities[i].key) + 1;
        fwrite(&key_len, sizeof(size_t), 1, file);
        fwrite(db->entities[i].key, 1, key_len, file);
        fwrite(&db->entities[i].value_size, sizeof(size_t), 1, file);
        fwrite(db->entities[i].value, 1, db->entities[i].value_size, file);
    }
    fclose(file);
}

void* db_get(DataBase *db, const char* key, size_t * value_size){
    for(size_t i = 0; i <db->size;i++){
        if (strcmp(db->entities[i].key, key) == 0){
            if(value_size) *value_size = db->entities[i].value_size;
            return db->entities[i].value;
        }
    }
    return NULL;
}

int main(){
    DataBase *db = dbcreate(10);
    int age = 25;
    db_set(db, "age", &age, sizeof(int));
    float price = 99.99f;
    db_set(db, "price", &price, sizeof(float));
    int *recived_age = db_get(db, "age", NULL);
    if(recived_age){
        printf("age is %d", *recived_age);
    }
    db_save(db, "my_db.db");
    return 0;
}