#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


struct people
{
    int id;
    char name[100];
    char gender;
    int age;
    char city[100];

    int followers, following;
};
typedef struct people *user;

void accept(user P)
{
    printf("enter your name:\n");
    gets(P->name);
    printf("enter your gender:\n");
    scanf("%s", P->gender);
    printf("enter your age:\n");
    scanf("%d", &P->age);
    printf("enter your city:\n");
    scanf("%s", P->city);
}

void display(user P)
{
    printf("ID : %d\n", P->id);
    printf("Name :%s\n",P->name);
	printf("Gender : %s\n",P->gender);
	printf("Age : %d\n",P->age);
	printf("City : %s\n",P->city);
    printf("Follower count : %d\n", P->followers);
    printf("Following count : %d\n", P->following);
}


void add_edge(int matrix[][100], user from, user to)
{
    //adds the edge from adjacency matrix
    //"from" will be following "to" after this

    int from_idx = from->id, to_idx = to->id;
    matrix[from_idx][to_idx] = 1;

    from->following += 1;
    to->followers += 1;
}

void remove_edge(int matrix[][100], user from, user to)
{
    //remove the edge from adjacency matrix
    //"from" will no longer be following "to" after this

    int from_idx = from->id, to_idx = to->id;
    matrix[from_idx][to_idx] = 0;

    from->following -= 1;
    to->followers -= 1;
}

void convert_to_lower(char *name)
{
    for (int i = 0; i < strlen(name); i++)
    {
        name[i] = tolower(name[i]);
    }
}

int find_user_index(struct people data[], int accounts, char *username)
{
    //returns the index of matching username in the database
    //checking lower cases
    convert_to_lower(username);
    char temp[100];
    
    for (int i = 0; i < accounts; i++)
    {
        strcpy(temp, data[i].name);
        convert_to_lower(temp);

        // match found, return its index in data array
        if (strcmp(username, temp) == 0)
            return i;
    }

    //if not found return -1
    return -1;
}

void display_connections(int matrix[][100], struct people data[], int accounts, user x)
{
    //print all the names of connections of a user x
    printf("\nFollowing : ");
    for (int i = 0, j = 1; i < accounts; i++)
    {
        if (matrix[x->id][i] == 1)
            printf("\n%d. %s", j++, data[i].name);
    }

    printf("\nFollowers : ");
    for (int i = 0, j = 1; i < accounts; i++)
    {
        if (matrix[i][x->id] == 1)
            printf("\n%d. %s", j++, data[i].name);
    }
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


void bfs_with_distance(int matrix[][100], struct people data[], int accounts, user x, int limit)
{
    // limit is the max number of suggestions that the user x wants
    // print the suggested persons name, age, gender and bfs distance from user x
    if (isNotFollowingAnyone(x, matrix, accounts))
    {
        printf("\nYou are not following anyone! Unable to produce suggestions.");
        return;
    }

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
                    printf("%s(%c), %d yrs old. (%d)", data[i].name, data[i].gender, data[i].age, visited[i][1]);
                    limit--;
                }
            }
        }
    }

}

int main()
{
    struct people database[100];                        //array of struct which actually holds user data
    int adjacency_matrix[100][100] = {0};     //adjacency matrix storing the edge data
    int active_accounts = 0;       // number of active accounts






    struct people P;
    accept(&P);
    display(&P);
    return 0;
}
