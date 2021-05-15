#include<stdio.h>
#include<stdlib.h>


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
    scanf("%s", P->name);
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

void add_edge(struct people matrix[][100], user from, user to)
{
    //adds the edge from adjacency matrix
    //"from" will be following "to" after this

    //remember to update followers and following count
}

void remove_edge(struct people matrix[][100], user from, user to)
{
    //remove the edge from adjacency matrix
    //"from" will no longer be following "to" after this

    //remember to update followers and following count
}

int find_user_index(struct people data[], char *username)
{
    //returns the index of matching username in the database
}

void display_connections(struct people matrix[][100], user x)
{
    //print all the names of connections of a user x
}

int main()
{
    struct people database[100];               //array of struct which actually holds user data
    struct people adjacency_matrix[100][100];  //adjacency matrix storing the edge data
    int users = 0;       // number of active accounts






    struct people P;
    accept(&P);
    display(&P);
    return 0;
}
