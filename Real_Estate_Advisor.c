#include <mysql.h>
#include <stdio.h>
#include <string.h>
// This function is used for adding data into the database by taking input from the user.
// This function takes the initialized connection as input.
int insert(MYSQL *conn)
{
    // initializing the required variables.
    int P_id, bhk, price;
    char Desired_Area[10], locality[40], P_name[50];
    char query[200];
    // Taking all the required data from user.
    printf("Enter property id: ");
    scanf("%d", &P_id);
    printf("Enter area of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c", Desired_Area);
    printf("Enter number of BHK: ");
    scanf("%d", &bhk);
    printf("Enter locality of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c", locality);
    printf("Enter name of your property: ");
    scanf("\n");
    scanf("%[^\n]%*c", P_name);
    printf("Enter price of ypur property: ");
    scanf("%d", &price);
    // creating the query variable by adding the required sql query and the variables entered by the user.
    sprintf(query, "INSERT INTO property (p_id, Desired_Area, bhk, locality, P_name, price) VALUES(%d, '%s', %d, '%s', '%s', %d)",
            P_id, Desired_Area, bhk, locality, P_name, price);
    // Inserting values to the mysql database.
    // The mysql_query function returns '0' when executed successfully.
    // So if it does not return zero then the required error will be printed on the screen.
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return 0;
}
// This function is for fetching the details of banks which provide loan.
// It takes the initializes connection as input.
int loan(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    if (mysql_query(conn, "select * from bank_record"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s %s %s %s\n", row[0], row[1], row[2], row[3]);
    }
    mysql_free_result(res);

    return 0;
}
// This function deletes data from the database.
// This function takes the initialized connection and the property id as input from the user.
int delete(MYSQL *conn, int id)
{
    char query[100];
    sprintf(query, "DELETE FROM property where P_id = %d", id);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    return 0;
}
// This function is used to search the property in the database in which the user is interested and view them also.
// This function takes the initialized connection, area of property and the price entered by the user and displays the property
// which have values less than and equal to the entered value.
int search(MYSQL *conn, int area, int price)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];
    sprintf(query, "SELECT * FROM property WHERE Desired_Area<= %d AND price <= %d", area, price);
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    if (res == NULL)
    {
        printf("Sorry !!!");
        printf("We do not have any property according to your choice.\n");
        printf("Better luck next time!!!\n");
    }
    while (row = mysql_fetch_row(res))
    {
        printf("%s %s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    }
    return 0;
    mysql_free_result(res);
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
    int var, id, price, area, loan_var;
    printf("Press 1 if you want to buy property:\n");
    printf("Press 2 if you want to sell property:\n");
    printf("Enter your response: ");
    scanf("%d", &var);
    if (var == 1)
    {
        printf("Enter the required details of your dream property:\n");
        printf("Enter the desired area of your property in sqft: ");
        scanf("%d", &area);
        printf("Enter the estimated price of your peoperty: ");
        scanf("%d", &price);
        search(conn, area, price);
        printf("Enter the id of the property you want to buy: ");
        scanf("%d", &id);
        if (!(delete (conn, id)))
        {
            printf("The selected property has been assigned to you!!!");
            printf("Press 1 if you want to take loan.\n");
            printf("Press 0 if you do not want to take loan\n");
            printf("Enter your response: ");
            scanf("%d", &loan_var);
            if (loan_var == 1)
            {
                loan(conn);
            }
            else if (loan_var == 0)
            {
                printf("We are happy to hear that you are capable of buying your property on your own.\n");
                printf("You can contact us whenever you want any assistance related to property.!!!");
            }
            else
            {
                printf("Enter valid input!!!");
            }
        }
    }
    else if (var == 2)
    {
        printf("Enter the required details of your property: ");
        if (insert(conn))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        else
        {
            printf("Your property is successfully added to the database.");
        }
    }
    else
    {
        printf("Enter valid input!!!");
    }
    // if (mysql_query(conn, "SELECT * FROM property")) {
    //     fprintf(stderr, "%s\n", mysql_error(conn));
    //     exit(1);
    // }

    // res = mysql_use_result(conn);
    // loan(conn);
    // delete(conn, 1);
    //  while ((row = mysql_fetch_row(res)) != NULL) {
    //      printf("%s %s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    //  }
    // search(conn,24000,3000000);
    //  mysql_free_result(res);
    mysql_close(conn);

    return 0;
}