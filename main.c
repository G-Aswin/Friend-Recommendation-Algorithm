#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "prototypes.h"

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

