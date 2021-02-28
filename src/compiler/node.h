#ifndef __NODE_H_
#define __NODE_H_
#define def_node(type, members) \
  typedef struct type { \
    char node_type[255]; \
    members \
  } type

typedef struct {
  char node_type[255];
} Node;

//typedef void* Node;
extern Node* nodes[255];

def_node(Identifier,
    char value[255];
    );

def_node(IValue,
    int value;
    );

def_node(Arg,
    Identifier* type;
    Identifier* variable;
    );

def_node(Statements,
    int length;
    Node* statements[255];
    );

def_node(BinaryExpression,
    Node* left;
    int operator_sim;
    Node* right;
    );

def_node(Args,
    int length;
    Arg* args[255];
    );

def_node(Func,
    Identifier* name;
    Args* args;
    Statements* body;
    );

def_node(Return,
    Node* return_value;
    );

Node* new_ivalue(int value);
Node* new_identifier(char *value);
Node* new_func(Identifier* name, Args* args, Statements* statements);
Node* new_arg(Identifier* type, Identifier* variable);
Node* new_binary_op();
Node* new_args();
Node* new_statements();
Node* new_return();
void Statements_add(Statements* statements, Node* statement);
void Args_add(Args* args, Arg* arg);
void debug(Node* node);

#endif