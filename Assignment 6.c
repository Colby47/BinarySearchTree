#include <stdlib.h>
#include <stdio.h>

//typedefs
typedef struct Node Node;
typedef struct Player Player;

//global variable to count total excitement
int totalExcitement = 0;

//node struct
struct Node {
    Node * left;
    Node * right;
    int champion;
    int value;
    int excitement;
};

//function to play the tournament through nodes in post order
//several if statement to determine of node has children and make the appropriate comparisons
void play(Node * root, int skills []){

    //base case
    if(root == NULL)
        return;

    //recursive step
    play(root->left, skills);
    play(root->right, skills);

    //if both children are NULL, compare via array of skills
    if(root->left == NULL && root->right == NULL){

        if(skills[root->value - 1] < skills[root->value]){
            root->champion = skills[root->value];
        }
        else{
            root->champion = skills[root->value - 1];
        }

        //calculate the excitement level for that match and store in node
        root->excitement = abs(skills[root->value] - skills[root->value - 1]);
    }

    //if only right child is null, compare left champion with array
    else if(root->left != NULL && root->right == NULL){

        if(root->left->champion < skills[root->value]){
            root->champion = skills[root->value];
        }
        else{
            root->champion = root->left->champion;
        }

        //calculate the excitement level for that match and store in node
        root->excitement = abs(skills[root->value] - root->left->champion);
    }

    //if only left child is null, compare right champion with array
    else if(root->left == NULL && root->right != NULL){

        if(root->right->champion < skills[root->value - 1]){
            root->champion = skills[root->value - 1];
        }
        else{
            root->champion = root->right->champion;
        }

        //calculate the excitement level for that match and store in node
        root->excitement = abs(skills[root->value - 1] - root->right->champion);
    }

    //if node has both children, compare left and right champions
    else{

        if(root->left->champion < root->right->champion){
            root->champion = root->right->champion;
        }
        else{
            root->champion = root->left->champion;
        }

        //calculate the excitement level for that match and store in node
        root->excitement = abs(root->left->champion - root->right->champion);
    }
}

//function to do another postOrder traversal and find the sum of the stored excitement levels in each node
void findTotalExcitement(Node * root){

    //base case
    if(root == NULL){
        return;
    }

    //recursive step
    findTotalExcitement(root->left);
    findTotalExcitement(root->right);

    //find sum
    totalExcitement = totalExcitement + root->excitement;
}

//creates a node and sets the value to value given and children to NULL
Node * createNode(int value) {
    Node * ret = calloc(1, sizeof(Node));
    ret->value = value;
    ret->right = ret->left = NULL;
    return ret;
}

//inserts node into tree based on comparisons of the nodes
//if empty, creates a node
Node * insert(Node * root, int value){
    if(root == NULL){
        return createNode(value);
    }

    if(root->value < value){
        root ->right = insert(root->right, value);
    }
    else{
        root->left = insert(root->left, value);
    }

    return root;
}

int main () {

    //scan for number of players
    int n;
    scanf("%d", &n);

    //scan for table activation backwards and store in array
    int tableActivation [n];
    for (int i = n-2; i >= 0; i--){
        scanf("%d", &tableActivation[i]);
    }

    //create root node and insert for each table activation
    Node * root = NULL;
    for (int i = 0; i < n-1; i++){
        root = insert(root, tableActivation[i]);
    }

    //create skill array
    int skills [n];
    for (int i = 0; i < n; i++){
        scanf("%d", &skills[i]);
    }

    //plays the tournament
    play(root, skills);

    //finds total excitement
    findTotalExcitement(root);

    //prints total excitement
    printf("%d\n", totalExcitement);

    return 0;
}
