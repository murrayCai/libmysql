add_executable(test_readline test_readline.c)
target_link_libraries(test_readline ${l_readline} termcap)

add_executable(test_mysql_connect test_mysql_connect.c)
target_link_libraries(test_mysql_connect ${l_mysqlclient} ${l_mc} db_mysql)
