//
// Created by Rostyslav Druzhchenko on 04.11.2020.
//

#include <mx_messeging.h>

t_error *mx_error_j(const char *json) {
    t_error *error = mx_error_new();

    JsonNode *node = json_decode(json);
    JsonNode *node_error = json_find_member(node, "error");
    if (node_error && node_error->tag == JSON_OBJECT) {
        JsonNode *node_code = node_error->children.head;
        error->code = node_code->number_;
        JsonNode *node_message = node_error->children.head->next;
        error->message = mx_strdup(node_message->string_);
    }
    json_delete(node);

    return error;
}
