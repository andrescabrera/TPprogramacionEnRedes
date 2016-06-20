#include "db-api.h"

DB *dbp;

int init_db () {
    u_int32_t flags; /* database open flags */
    int ret; /* function return value */
  
    ret = db_create(&dbp, NULL, 0);
  
    fprintf(stdout, "opening %s...\n", DATABASE);

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
        return ret;
    } else {
        return 0;
    }
}

int set(DB *hDb, char *key, char *value) {

    DBT strKey, strValue;
    
    memset(&strKey, 0, sizeof(strKey));
    memset(&strValue, 0, sizeof(strValue));
    
    strKey.data = key;
    strKey.size = (int) strlen(key);
    strValue.data = value;
    strValue.size = ( (int) strlen(value) )-0;
    
    int ret = hDb->put(hDb, NULL, &strKey, &strValue, 0);
    
    if(ret == 0) {
        printf("item added[%s] = %s \n", key, value);
        return 0;
    } else {
        hDb->err(hDb, ret, "DB->put");
        return 1;
    }
}

int get(DB *hDb, char *key, char *value) {

    DBT strKey, strValue;
    
    memset(&strKey, 0, sizeof(strKey));
    memset(&strValue, 0, sizeof(strValue));
    
    strKey.data = key;
    strKey.size = (int) strlen(key);
    
    int ret = hDb->get(hDb, NULL, &strKey, &strValue, 0);
    printf("trying to get [%s]\n", key);
    if(ret == 0) {
        printf("get [%s] = [%s]\n", key, (char *) strValue.data);
        strcpy(value, strValue.data);
        return 0;
    } else {
        hDb->err(hDb, ret, "DB->get");
        return 1;
    }
}

int del(DB *hDb, char *key) {

    DBT strKey;
    
    memset(&strKey, 0, sizeof(strKey));
    
    strKey.data = key;
    strKey.size = (int) strlen(key);
    
    
    int ret = hDb->del(hDb, NULL, &strKey, 0);
    
    if(ret == 0) {
        printf("item [%s] removed!\n", key);
        return 0;
    } else {
        hDb->err(hDb, ret, "DB->del");
        return 1;
    }
}

DB *getDBP()
{
    return dbp;
}


