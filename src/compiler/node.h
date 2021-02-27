#ifndef __NODE_H_
#define __NODE_H_
#define def_type(type, members) typedef struct type { members } type

typedef void* Node;
extern Node nodes[255];

def_type(Identifier,
    char node_type[255];
    char value[255];
    );

def_type(IValue,
    char node_type[255];
    int value;
    );

def_type(Arg,
    char node_type[255];
    Identifier* type;
    Identifier* variable;
    );

def_type(Statements,
    char node_type[255];
    int length;
    Node statements[255];
    );

def_type(BinaryExpression,
    char node_type[255];
    Node left;
    int operator_sim;
    Node right;
    );

def_type(Args,
    char node_type[255];
    int length;
    Arg* args[255];
    );

def_type(Func,
    char node_type[255];
    Identifier* name;
    Args* args;
    Statements* body;
    );

def_type(Debug,
    char node_type[255];
    );

Node new_ivalue(int value);
Node new_identifier(char *value);
Node new_func(Identifier* name, Args* args, Statements* statements);
Node new_arg(Identifier* type, Identifier* variable);
Node new_binary_op();
Node new_args();
Node new_statements();
void Statements_add(Statements* statements, Node statement);
void Args_add(Args* args, Arg* arg);
void debug(Node node);

#endif
