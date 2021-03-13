#include <stdio.h>
#include <stdlib.h>

#include "compiler/node.h"
#define NEW_NODE(type) type* node = (type*) malloc(sizeof(type)); \
  sscanf(#type, "%s", node->node_type);

Node* nodes[255];

Node* new_ivalue(int value) {
  NEW_NODE(IValue)
  node->value = value;
  return (Node*)node;
}

Node* new_identifier(char *value) {
  NEW_NODE(Identifier)
  sscanf(value, "%s", node->value);
  return (Node*)node;
}

Node* new_func(Identifier* name, Identifier* type, Args* args, Statements* body) {
  NEW_NODE(Func)
  node->name = name;
  node->type = type;
  node->args = args;
  node->body = body;
  return (Node*)node;
}

Node* new_arg(Identifier* type, Identifier* variable) {
  NEW_NODE(Arg)
  node->type = type;
  node->variable = variable;
  return (Node*)node;
}

Node* new_args() {
  NEW_NODE(Args)
  node->length = 0;
  return (Node*)node;
}

Node* new_statements() {
  NEW_NODE(Statements)
  node->length = 0;
  return (Node*)node;
}

Node* new_binary_op(Node* left, int operator_sim, Node* right) {
  NEW_NODE(BinaryExpression)
  node->left = left;
  node->operator_sim = operator_sim;
  node->right = right;
  return (Node*)node;
}

Node* new_return(Node* return_value) {
  NEW_NODE(Return)
  node->return_value = return_value;
  return (Node*)node;
}

void Statements_add(Statements* self, Node* statement) {
  self->statements[self->length] = statement;
  self->length++;
}

void Args_add(Args* self, Arg* arg) {
  self->args[self->length] = arg;
  self->length++;
}

void debug(Node* node) {
  printf("%s\n", node->node_type);
}
