//
// Created by Rostyslav Druzhchenko on 04.11.2020.
//

#include <mx_messeging.h>

t_error *mx_error(const char *json) {
    t_error *error = mx_error_new();

    mx_leaks_check_enabled(false);
    JsonNode *node = json_decode(json);
    JsonNode *node_error = json_find_member(node, "error");
    if (node_error && node_error->tag == JSON_OBJECT) {
        JsonNode *node_code = node_error->children.head;
        error->code = node_code->number_;
        JsonNode *node_message = node_error->children.head->next;
        mx_leaks_check_enabled(true);
        error->message = mx_strdup(node_message->string_);
        mx_leaks_check_enabled(false);
    }
    json_delete(node);
    mx_leaks_check_enabled(true);

    return error;
}
