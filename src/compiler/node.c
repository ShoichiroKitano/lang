#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#define NEW_NODE(type) type* node = (type*) malloc(sizeof(type))

Node* nodes[255];

Node* new_ivalue(int value) {
  NEW_NODE(IValue);
  node->value = value;
  sscanf("IValue", "%s", node->node_type);
  return (Node*)node;
}

Node* new_identifier(char *value) {
  NEW_NODE(Identifier);
  sscanf("Identifier", "%s", node->node_type);
  sscanf(value, "%s", node->value);
  return (Node*)node;
}

Node* new_func(Identifier* name, Args* args, Statements* body) {
  NEW_NODE(Func);
  node->name = name;
  node->args = args;
  node->body = body;
  sscanf("Func", "%s", node->node_type);
  return (Node*)node;
}

Node* new_arg(Identifier* type, Identifier* variable) {
  NEW_NODE(Arg);
  sscanf("Arg", "%s", node->node_type);
  node->type = type;
  node->variable = variable;
  return (Node*)node;
}

Node* new_args() {
  NEW_NODE(Args);
  sscanf("Args", "%s", node->node_type);
  node->length = 0;
  return (Node*)node;
}

Node* new_statements() {
  NEW_NODE(Statements);
  sscanf("Statements", "%s", node->node_type);
  node->length = 0;
  return (Node*)node;
}

Node* new_binary_op(Node* left, int operator_sim, Node* right) {
  NEW_NODE(BinaryExpression);
  sscanf("BinaryExpression", "%s", node->node_type);
  node->left = left;
  node->operator_sim = operator_sim;
  node->right = right;
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
  Debug* d = (Debug*) node;
  printf("%s\n", d->node_type);
}
