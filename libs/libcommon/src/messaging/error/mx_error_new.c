//
// Created by Rostyslav Druzhchenko on 04.11.2020.
//

#include <mx_messeging.h>

static void print(t_error *this) {
    mx_printstr("ERROR code: ");
    mx_printint(this->code);
    mx_printstr(", message: \"");
    mx_printstr_ornil(this->message);
    mx_printstr("\"\n");
}

static char *json(t_error *this) {
    JsonNode *node = json_mkobject();
    JsonNode *node_code = json_mknumber(this->code);
    JsonNode *node_message = json_mkstring(this->message);
    json_append_member(node, "code", node_code);
    json_append_member(node, "message", node_message);
    char *json = json_encode(node);
    json_delete(node);

    return json;
}

t_error *mx_error_new() {
    CREATE_INSTANCE(t_error);
    instance->print = print;
    instance->json = json;
    return instance;
}
