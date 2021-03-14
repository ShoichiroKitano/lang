#ifndef __NODE_H
#define __NODE_H

#define def_node(type, members) \
  typedef struct type { \
    char node_type[255]; \
    members \
  } type

typedef struct {
  char node_type[255];
} Node;

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
    Identifier* type;
    Args* args;
    Statements* body;
    );

def_node(Return,
    Node* return_value;
    );

#endif

extern Node* nodes[255];
extern int node_length;

Node* new_ivalue(int value);
Node* new_identifier(char *value);
Node* new_func(Identifier* name, Identifier* type, Args* args, Statements* statements);
Node* new_arg(Identifier* type, Identifier* variable);
Node* new_binary_op(Node* left, int operator_sim, Node* right);
Node* new_args();
Node* new_statements();
Node* new_return(Node* return_value);
void Statements_add(Statements* statements, Node* statement);
void Args_add(Args* args, Arg* arg);
void debug(Node* node);

