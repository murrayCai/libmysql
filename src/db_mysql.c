#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "base.h"
#include "db_mysql.h"

#define M_DB_VALID(expr) M((expr),MODULE_DB_MYSQL)
#define MC_DB_VALID(expr,func) MC((expr),(func),MODULE_DB_MYSQL)

int db_init(){
    int ret = 0;
    M_DB_VALID(0 != mysql_library_init(0,NULL,NULL));
    return ret;
}

int db_finish(){
    mysql_library_end();
    return 0;
}

int db_connect(db_mysql_t *db){
    int ret = 0;
    M_DB_VALID(NULL == db);
    M_DB_VALID(NULL != db->_instance);
    M_DB_VALID(DB_UN_INIT != db->status);

    db_mysql_config_t *conf = db->config;
    M_DB_VALID(NULL == conf);
    M_DB_VALID(NULL == conf->host);
    M_DB_VALID(0 >= conf->port || 65536 <= conf->port);
    M_DB_VALID(NULL == conf->user);
    M_DB_VALID(NULL == conf->password);
    M_DB_VALID(NULL == conf->db);

    MYSQL *mysql = mysql_init(NULL);
    M_DB_VALID(NULL == mysql);

    MC_DB_VALID(NULL == mysql_real_connect(mysql,conf->host,conf->user,
                conf->password,conf->db,conf->port,NULL,0),{
            db->error = mysql_error(db->_instance); // may be have a [not free/null pointer] bug
            mysql_close(db->_instance);
            db->_instance = NULL;
            });

    db->status = DB_CONNECTED;
    db->_instance = mysql; 

    return ret;
}

int db_close(db_mysql_t *db){
    int ret = 0;
    M_DB_VALID(NULL == db);
    M_DB_VALID(NULL == db->_instance);
    M_DB_VALID(DB_CONNECTED != db->status);
    mysql_close((MYSQL *)db->_instance);
    db->_instance = NULL;
    db->status = DB_CLOSED;
    return ret;
}


int db_select(db_mysql_t *pdb,const char *sql,db_param_t *params);

int db_insert(db_mysql_t *pdb,const char *sql,db_param_t *params);

int db_update(db_mysql_t *pdb,const char *sql,db_param_t *params);

int db_count(db_mysql_t *pdb,const char *sql,db_param_t *params,int *count);


