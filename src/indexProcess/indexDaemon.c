//
//  indexDaemon.c
//  repositorio
//
//  Created by Diego Marafetti on 5/16/15.
//  Copyright (c) 2015 diego. All rights reserved.
//

#include "main.h"

#define DATABASE "repository.db"




void set(DB *hDb, char *key, char *value) {

    DBT strKey, strValue;
    
    memset(&strKey, 0, sizeof(strKey));
    memset(&strValue, 0, sizeof(strValue));
    
    strKey.data = key;
    strKey.size = (int) strlen(key);
    strValue.data = value;
    strValue.size = (int) strlen(value);
    
    
    int ret = hDb->put(hDb, NULL, &strKey, &strValue, 0);
    
    if(ret == 0) {
    
        printf("item [%s] added!\n", key);
        
    } else {
    
        hDb->err(hDb, ret, "DB->put");
    }
}



void get(DB *hDb, char *key) {

    DBT strKey, strValue;
    
    memset(&strKey, 0, sizeof(strKey));
    memset(&strValue, 0, sizeof(strValue));
    
    strKey.data = key;
    strKey.size = (int) strlen(key);
    
    int ret = hDb->get(hDb, NULL, &strKey, &strValue, 0);
    
    if(ret == 0) {
        
        printf("get [%s] = %s\n", key, (char *) strValue.data);
        
    } else {
        
        hDb->err(hDb, ret, "DB->get");
    }
}


void del(DB *hDb, char *key) {

    DBT strKey, strValue;
    
    memset(&strKey, 0, sizeof(strKey));
    
    strKey.data = key;
    strKey.size = (int) strlen(key);
    
    
    int ret = hDb->del(hDb, NULL, &strKey, 0);
    
    if(ret == 0) {
        
        printf("item [%s] removed!\n", key);
        
    } else {
        
        hDb->err(hDb, ret, "DB->del");
    }
}




int main(int argc, const char * argv[]) {

    
    DB *dbp; /* DB structure handle */
    u_int32_t flags; /* database open flags */
    int ret; /* function return value */
    
    
    ret = db_create(&dbp, NULL, 0);
    
    if (ret != 0) {
        
        fprintf(stderr, "db_create: %s\n", db_strerror(ret));
        exit(1);
    }
    
    /* Database open flags */
    flags = DB_CREATE; /* If the database does not exist, create it.*/
    /* open the database */
    ret = dbp->open(dbp, /* DB structure pointer */
                    NULL, /* Transaction pointer */
                    DATABASE, /* On-disk file that holds the database. */
                    NULL, /* Optional logical database name */
                    DB_BTREE, /* Database access method */
                    flags, /* Open flags */
                    0);

    if(ret != 0) {
    
        dbp->err(dbp, ret, "%s", DATABASE);
        exit(1);
    }
    
    
    fprintf(stdout, "openning %s...\n", DATABASE);
    fprintf(stdout, "Adding elements to database\n");
    
    // add
    set(dbp, "example1.html", "/resources/example1.html");
    set(dbp, "image-playa.jpg", "/resources/example1.html");
    set(dbp, "image-fondo.jpg", "/resources/example1.html");
    set(dbp, "image-auto.jpg", "/resources/example1.html");
    
    // get
    get(dbp, "example1.html");
    get(dbp, "image-playa.jpg");
    get(dbp, "image-fondo.jpg");
    get(dbp, "image-auto.jpg");
    
    // get not found
    get(dbp, "hola.jpg");
    get(dbp, "como.jpg");
    get(dbp, "estas.jpg");
    get(dbp, "hoy.jpg");
    
    del(dbp, "example1.html");
    del(dbp, "image-playa.jpg");
    del(dbp, "image-fondo.jpg");
    del(dbp, "image-auto.jpg");
    
    dbp->close(dbp, 0);
    return 0;
}
