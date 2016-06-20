#ifndef DBACCESS_H
#define DBACCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <db.h>

#define DATABASE "repository.db"

DB *getDBP();
int init_db ();
int set(DB *hDb, char *key, char *value);
int get(DB *hDb, char *key, char *value);
int del(DB *hDb, char *key);

#endif