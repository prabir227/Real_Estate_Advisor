#include <mysql.h>
#include <stdio.h>
#include <string.h>
int insert(MYSQL *conn)
{
    int P_id, bhk, price;
    char Desired_Area[10], locality[40], P_name[50];
    char query[200];
    printf("Enter property id: ");
    scanf("%d", &P_id);
    printf("Enter area of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c",Desired_Area);
    printf("Enter number of BHK: ");
    scanf("%d", &bhk);
    printf("ENter locality of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c",locality);
    printf("Enter name of your property");
    scanf("\n");
    scanf("%[^\n]%*c",P_name);
    printf("Enter price of ypur property");
    scanf("%d", &price);
    sprintf(query, "INSERT INTO property (p_id, Desired_Area, bhk, locality, P_name, price) VALUES(%d, '%s', %d, '%s', '%s', %d)",
            P_id, Desired_Area, bhk, locality, P_name, price);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return 0;
}

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "prabir227";
    char *password = "Prabir@123";
    char *database = "Real_Estate_Advisor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // if (mysql_query(conn, "SELECT * FROM property")) {
    //     fprintf(stderr, "%s\n", mysql_error(conn));
    //     exit(1);
    // }
    insert(conn);

    res = mysql_use_result(conn);

    // while ((row = mysql_fetch_row(res)) != NULL) {
    //     printf("%s %s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    // }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
