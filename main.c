#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct people
{
    int id;
    char name[100];
    char gender;
    int age;
    char city[100];
    char hobby[25]; //bookreading, singing and dancing
    int friends;
};
typedef struct people *user;

//function prototypes
void accept(user P);
void display(user P);
void add_edge(int matrix[][100], user from, user to);
void remove_edge(int matrix[][100], user from, user to);
void convert_to_lower(char *name);
int find_user_index(struct people data[], int accounts, char *username);
void display_connections(int matrix[][100], struct people data[], int accounts, user x);
int isNotFollowingAnyone(user x, int matrix[][100], int accounts);
void bfs_with_distance(int matrix[][100], struct people data[], int accounts, user x, int limit);
void preload(int adjacency_matrix[][100], struct people database[], int *accounts);
void recommend_friends_wrt_hobby(int matrix[][100], struct people data[], int accounts, user x, int limit);
void friends_sharing_hobby(int matrix[][100], struct people data[], int accounts, user x);
void display_menu_options();

//Main function
int main(int argc, char *argv[])
{
    struct people database[100];          //array of struct which actually holds user data
    int adjacency_matrix[100][100] = {0}; //adjacency matrix storing the edge data
    int active_accounts = 0;              // number of active accounts

    char name1[100], name2[100];

    if (argc > 1)
    {
        if (strcmp(argv[1], "demo") == 0)
            preload(adjacency_matrix, database, &active_accounts);
        else
        {
            printf("\nInvalid command line input.\nUsage: './a.out demo' or './a.out'\n\n");
            return 0;
        }
    }

    int ch, n, idx1, idx2, lim;
    while (1)
    {
        display_menu_options();
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("\nNumber of account(s) to enter? : ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++)
            {
                printf("\n%dth entry : \n", i);
                accept(&database[active_accounts++]);
            }
            break;

        case 2:
            printf("\nAccount choices by name(1) or id(2)? Enter choice : ");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("\nUsername 1 : ");
                scanf(" %[^\n]s", name1);
                printf("\nUsername 2 : ");
                scanf(" %[^\n]s", name2);

                idx1 = find_user_index(database, active_accounts, name1);
                idx2 = find_user_index(database, active_accounts, name2);

                if (idx1 == -1 || idx2 == -1)
                {
                    printf("\nEither or both usernames not found!");
                    break;
                }

                add_edge(adjacency_matrix, &database[idx1], &database[idx2]);
                printf("\nConnection made successfully!");
            }
            else if (n == 2)
            {
                printf("\nEnter the account ID for both users : ");
                scanf("%d %d", &idx1, &idx2);

                if (idx1 >= active_accounts || idx2 >= active_accounts)
                {
                    printf("\nEither or both ID's not found!");
                    break;
                }

                add_edge(adjacency_matrix, &database[idx1], &database[idx2]);
                printf("\nConnection made successfully!");
            }
            else
            {
                printf("\nInvalid choice.");
            }
            break;

        case 3:
            printf("\nAccount choices by name(1) or id(2)? Enter choice : ");
            scanf("%d", &n);
            if (n == 1)
            {
                printf("\nUsername 1 : ");
                scanf(" %[^\n]s", name1);
                printf("\nUsername 2 : ");
                scanf(" %[^\n]s", name2);

                idx1 = find_user_index(database, active_accounts, name1);
                idx2 = find_user_index(database, active_accounts, name2);

                if (idx1 == -1 || idx2 == -1)
                {
                    printf("\nEither or both usernames not found!");
                    break;
                }

                remove_edge(adjacency_matrix, &database[idx1], &database[idx2]);
                printf("\nConnection removed successfully!");
            }
            else if (n == 2)
            {
                printf("\nEnter the account ID for both users : ");
                scanf("%d %d", &idx1, &idx2);

                if (idx1 >= active_accounts || idx2 >= active_accounts)
                {
                    printf("\nEither or both ID's not found!");
                    break;
                }

                add_edge(adjacency_matrix, &database[idx1], &database[idx2]);
                printf("\nConnection removed successfully!");
            }
            else
            {
                printf("\nInvalid choice.");
            }
            break;

        case 4:
            printf("\nAccount choices by name(1) or id(2)? Enter choice : ");
            scanf("%d", &n);

            if (n == 1)
            {
                printf("\nEnter username : ");
                scanf("%s", name1);

                idx1 = find_user_index(database, active_accounts, name1);
                if (idx1 == -1)
                {
                    printf("\nUsername not found!");
                    break;
                }

                display_connections(adjacency_matrix, database, active_accounts, &database[idx1]);
            }
            else if (n == 2)
            {
                printf("\nEnter user ID : ");
                scanf("%d", &idx1);

                if (idx1 >= active_accounts)
                {
                    printf("\nInvalid ID");
                    break;
                }

                display_connections(adjacency_matrix, database, active_accounts, &database[idx1]);
            }
            else
            {
                printf("\nInvalid choice.");
                break;
            }
            break;

        case 5:
            printf("\nHow many friends should be displayed maximum? : ");
            scanf("%d", &lim);

            printf("\nAccount choices by name(1) or id(2)? Enter choice : ");
            scanf("%d", &n);

            if (n == 1)
            {
                printf("\nEnter username : ");
                scanf(" %[^\n]s", name1);
                printf("\nEnter username : ");

                idx1 = find_user_index(database, active_accounts, name1);
                if (idx1 == -1)
                {
                    printf("\nUsername not founf!");
                    break;
                }

                bfs_with_distance(adjacency_matrix, database, active_accounts, &database[idx1], lim);
            }
            else if (n == 2)
            {
                printf("\nEnter user ID : ");
                scanf("%d", &idx1);

                if (idx1 >= active_accounts)
                {
                    printf("\nInvalid ID");
                    break;
                }

                bfs_with_distance(adjacency_matrix, database, active_accounts, &database[idx1], lim);
            }
            else
            {
                printf("\nInvalid choice.");
                break;
            }
            break;

        case 6:
            printf("\nHow many friends should be displayed maximum? : ");
            scanf("%d", &lim);

            printf("\nAccount choices by name(1) or id(2)? Enter choice : ");
            scanf("%d", &n);

            if (n == 1)
            {
                printf("\nEnter username : ");
                scanf(" %[^\n]s", name1);
                printf("\nEnter username : ");

                idx1 = find_user_index(database, active_accounts, name1);
                if (idx1 == -1)
                {
                    printf("\nUsername not founf!");
                    break;
                }

                recommend_friends_wrt_hobby(adjacency_matrix, database, active_accounts, &database[idx1], lim);
            }
            else if (n == 2)
            {
                printf("\nEnter user ID : ");
                scanf("%d", &idx1);

                if (idx1 >= active_accounts)
                {
                    printf("\nInvalid ID");
                    break;
                }

                recommend_friends_wrt_hobby(adjacency_matrix, database, active_accounts, &database[idx1], lim);
            }
            else
            {
                printf("\nInvalid choice.");
                break;
            }
            break;

        case 7:
            printf("\nAccount choices by name(1) or id(2)? Enter choice : ");
            scanf("%d", &n);

            if (n == 1)
            {
                printf("\nEnter username : ");
                scanf("%s", name1);

                idx1 = find_user_index(database, active_accounts, name1);
                if (idx1 == -1)
                {
                    printf("\nUsername not found!");
                    break;
                }

                friends_sharing_hobby(adjacency_matrix, database, active_accounts, &database[idx1]);
            }
            else if (n == 2)
            {
                printf("\nEnter user ID : ");
                scanf("%d", &idx1);

                if (idx1 >= active_accounts)
                {
                    printf("\nInvalid ID");
                    break;
                }

                friends_sharing_hobby(adjacency_matrix, database, active_accounts, &database[idx1]);
            }
            else
            {
                printf("\nInvalid choice.");
                break;
            }
            break;

        case 11:
            for (int i = 0; i < active_accounts; i++)
            {
                display(&database[i]);
                printf("\n");
            }
            break;

        case 22:
            for (int i = 0; i < active_accounts; i++)
            {
                for (int j = 0; j < active_accounts; j++)
                {
                    printf("%d ", adjacency_matrix[i][j]);
                }
                printf("\n");
            }
            break;

        default:
            return 0;
        }
    }
}

void accept(user P)
{
    printf("Name: ");
    scanf(" %[^\n]s", P->name);
    printf("Gender(M/F): ");
    scanf(" %c", &P->gender);
    printf("Age: ");
    scanf("%d", &P->age);
    printf("City: ");
    scanf("%s", P->city);
    printf("Hobby: ");
    scanf("%s", P->hobby);
    P->friends = 0;
}

void display(user P)
{
    printf("ID : %d\n", P->id);
    printf("Name : '%s'\n", P->name);
    printf("Gender : %c\n", P->gender);
    printf("Age : %d\n", P->age);
    printf("City : %s\n", P->city);
    printf("Friend count : %d\n", P->friends);
    printf("Hobby : %s\n", P->hobby);
}

void add_edge(int matrix[][100], user from, user to)
{
    //adds the edge from adjacency matrix
    //"from" will be following "to" after this

    int from_idx = from->id, to_idx = to->id;
    matrix[from_idx][to_idx] = 1;
    matrix[to_idx][from_idx] = 1;

    from->friends += 1;
    to->friends += 1;
}

void remove_edge(int matrix[][100], user from, user to)
{
    //remove the edge from adjacency matrix
    //"from" will no longer be following "to" after this

    int from_idx = from->id, to_idx = to->id;
    matrix[from_idx][to_idx] = 0;
    matrix[to_idx][from_idx] = 0;

    from->friends -= 1;
    to->friends -= 1;
}

int find_user_index(struct people data[], int accounts, char *username)
{
    //returns the index of matching username in the database

    for (int i = 0; i < accounts; i++)
    {
        // match found, return its index in data array
        if (strcasecmp(username, data[i].name) == 0)
            return i;
    }

    //if not found return -1
    return -1;
}

// if person is not following anyone, returns 1, else 0
int isNotFollowingAnyone(user x, int matrix[][100], int accounts)
{
    int flag = 1;
    for (int i = 0; i < accounts; i++)
    {
        if (matrix[x->id][i] == 1)
        {
            flag = 0;
            break;
        }
    }

    return flag;
}

void display_connections(int matrix[][100], struct people data[], int accounts, user x)
{
    //print all the names of connections of a user x

    if (isNotFollowingAnyone(x, matrix, accounts))
    {
        printf("\nNo Friends Added!");
        return;
    }

    printf("\nConnections of %s : ", x->name);
    for (int i = 0, j = 1; i < accounts; i++)
    {
        if (matrix[x->id][i] == 1)
            printf("\n%d. %s", j++, data[i].name);
    }
}

void friends_sharing_hobby(int matrix[][100], struct people data[], int accounts, user x)
{
    //print all the names of connections of a user x

    if (isNotFollowingAnyone(x, matrix, accounts))
    {
        printf("\nNo Friends Added!");
        return;
    }

    printf("\nFriends of %s who also like %s : ", x->name, x->hobby);
    for (int i = 0, j = 1; i < accounts; i++)
    {
        if (matrix[x->id][i] == 1 && strcmp(x->hobby, data[i].hobby) == 0)
            printf("\n%d. %s", j++, data[i].name);
    }
}

void bfs_with_distance(int matrix[][100], struct people data[], int accounts, user x, int limit)
{
    // limit is the max number of suggestions that the user x wants
    // print the suggested persons name, age, gender and bfs distance from user x
    if (isNotFollowingAnyone(x, matrix, accounts))
    {
        printf("\nYou are not following anyone! Unable to produce suggestions.");
        return;
    }

    // First column is for visited, second column is for distance
    int visited[100][2] = {0};
    int queue[200], front = 0, rear = -1;

    queue[++rear] = x->id;
    visited[x->id][0] = 1;
    visited[x->id][1] = 0;

    printf("\nSuggestions : ");

    int popped;
    while (front <= rear && limit != 0)
    {
        popped = queue[front++];

        for (int i = 0; i < accounts && limit != 0; i++)
        {
            if (matrix[popped][i] == 1 && !visited[i][0])
            {
                queue[++rear] = i;
                visited[i][0] = 1;
                visited[i][1] = visited[popped][1] + 1;

                if (visited[i][1] > 1)
                {
                    printf("\n%s(%c), %d yrs old. (%d)", data[i].name, data[i].gender, data[i].age, visited[i][1]);
                    limit--;
                }
            }
        }
    }
}

void recommend_friends_wrt_hobby(int matrix[][100], struct people data[], int accounts, user x, int limit)
{
    // limit is the max number of suggestions that the user x wants
    // print the suggested persons name, age, gender and bfs distance from user x
    if (isNotFollowingAnyone(x, matrix, accounts))
    {
        printf("\nYou are not following anyone! Unable to produce suggestions.");
        return;
    }

    // First column is for visited, second column is for distance
    int visited[100][2] = {0};
    int queue[200], front = 0, rear = -1;

    queue[++rear] = x->id;
    visited[x->id][0] = 1;
    visited[x->id][1] = 0;

    printf("\nPeople with similar hobbies in your network : ");

    int popped;
    while (front <= rear && limit != 0)
    {
        popped = queue[front++];

        for (int i = 0; i < accounts && limit != 0; i++)
        {
            if (matrix[popped][i] == 1 && !visited[i][0])
            {
                queue[++rear] = i;
                visited[i][0] = 1;
                visited[i][1] = visited[popped][1] + 1;

                if (visited[i][1] > 1 && strcmp(data[i].hobby, x->hobby) == 0)
                {
                    printf("\n%s(%c), %d yrs old. (%d)", data[i].name, data[i].gender, data[i].age, visited[i][1]);
                    limit--;
                }
            }
        }
    }
}

void preload(int adjacency_matrix[][100], struct people database[], int *active_accounts)
{
    FILE *fp = fopen("database.txt", "r");
    int count;
    fscanf(fp, "%d", &count);
    *active_accounts = count;

    for (int i = 0; i < count; i++)
    {
        fscanf(fp, "%s", database[i].name);
        fscanf(fp, " %c", &database[i].gender);
        fscanf(fp, "%d", &database[i].age);
        fscanf(fp, "%s", database[i].city);
        fscanf(fp, "%s", database[i].hobby);
        database[i].id = i;
    }
    fclose(fp);

    fp = fopen("matrix_data.txt", "r");
    fscanf(fp, "%d", &count); //length of the matrix

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            fscanf(fp, "%d", &adjacency_matrix[i][j]);
        }
    }
    fclose(fp);
}

void display_menu_options()
{
    printf("\n\n");
    printf("\n***USER MENU***\n");
    printf("\n1. Create account(s)");
    printf("\n2. Add a new connection/friend");
    printf("\n3. Remove a connection/friend");
    printf("\n4. Display all friends");
    printf("\n5. **Recommend Friends**");

    //newly added
    printf("\n6. **Recommend people with similar hobby**");
    printf("\n7. **Display my friends with similar hobby**");

    printf("\n\n***Master MENU***\n");
    printf("\n11. Display All Data");
    printf("\n22. Display Matrix");

    printf("\n\n: ");
}