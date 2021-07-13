#ifndef PROTOTYPES_H
#define PROTOTYPES_H

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

#endif