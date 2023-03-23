#include <mysql.h>
#include <stdio.h>
#include <string.h>
int insert(MYSQL *conn)
{
    //initializing the required variables.
    int P_id, bhk, price;
    char Desired_Area[10], locality[40], P_name[50];
    char query[200];
    //Taking all the required data from user.
    printf("Enter property id: ");
    scanf("%d", &P_id);
    printf("Enter area of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c",Desired_Area);
    printf("Enter number of BHK: ");
    scanf("%d", &bhk);
    printf("Enter locality of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c",locality);
    printf("Enter name of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c",P_name);
    printf("Enter price of ypur property: ");
    scanf("%d", &price);
    //creating the query variable by adding the required sql query and the variables entered by the user.
    sprintf(query, "INSERT INTO property (p_id, Desired_Area, bhk, locality, P_name, price) VALUES(%d, '%s', %d, '%s', '%s', %d)",
            P_id, Desired_Area, bhk, locality, P_name, price);
    //Inserting values to the mysql database.
    //The mysql_query function returns '0' when executed successfully.
    //So if it does not return zero then the required error will be printed on the screen.
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
