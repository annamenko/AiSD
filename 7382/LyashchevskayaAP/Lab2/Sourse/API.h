typedef struct Node {                                                   //Struct node of list
        int flag_type[2];                                               //Array keeps type of args: 1 - int, 2 - struct Node *
        char sign;                                                      //Arg-sign
        union {                                                         //First arg
                int one;                                                //May be digit
                struct Node *left;                                      //May be expression
        };
        union {                                                         //Second arg
                int two;                                                //May be digit
                struct Node *right;                                     //May be expression
        };
} Node;

typedef struct List {                                                   //Struct of list
        Node *top;
} List;

void abort_(const char * , ...);					//Consulting error with message
void fill_list(Node *, char *);						//Filling function list
void find_args(char *, int *);						//Finding function args
int find_sec_bracket(char *);						//Finding function second bracket
void fill_node(Node *, int *, char *);					//Filling finction node
void fill_expr(Node *,int , int ,char *);				//Filling function exprission
void print_list(Node *);						//Printting function list


