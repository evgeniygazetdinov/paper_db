#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    DataBase *db = dbcreate(10);
    int age = 25;
    db_set(db, "age", &age, sizeof(int));
    float price = 99.99f;
    db_set(db, "price", &price, sizeof(float));
    int *recived_age = db_get(db, "age", NULL);
    if(recived_age){
        printf("age is %d \n", *recived_age);
    }
    db_save(db, "my_db.db");
    return 0;
}