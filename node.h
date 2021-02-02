#ifndef __NODE_H_
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

def_type(Expression,
    char node_type[255];
    void* op1;
    char operator[255];
    void* op2;
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


Node new_ivalue(int value);
Node new_identifier(char *value);
Node new_func(Identifier* name, Args* args, Statements* statements);
Node new_arg(Identifier* type, Identifier* variable);
Node new_args();
Node new_statements();
void Statements_add(Statements* statements, Node statement);
void Args_add(Args* args, Arg* arg);

#endif
