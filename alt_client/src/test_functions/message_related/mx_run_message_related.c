//
// Created by Rostyslav Druzhchenko on 25.11.2020.
//

#include <alt_client.h>
#include <test_lib.h>
#include <rd_random.h>

t_message *get_last_message(t_list *list) {
    while (list) {
        if (list->next == 0)
            return (t_message *)list->data;
        list = list->next;
    }
    return 0;
}

void mx_run_message_related(void) {
    char *token = mx_run_login();

    // ------------ Send
    //
    t_list *list = mx_message_list(token);
    int size_init = mx_list_size(list);
    mx_message_list_del(&list);

    char *text = rd_random_strn(25);
    t_message *message = mx_message_send(token, text);
    ASSERT_EQUALS_STR(message->message, text);
    ASSERT_TRUE(message->type == E_MESSAGE_TYPE_TEXT);

    list = mx_message_list(token);
    int size = mx_list_size(list);
    t_message *last_message = get_last_message(list);
    message->id = last_message->id;
    ASSERT_EQUALS_STR(last_message->message, text);
    ASSERT_EQUALS(size_init + 1, size);
    mx_message_list_del(&list);
    last_message = 0;

    // ------------ Update
    //

    // Given
    message->type = E_MESSAGE_TYPE_UPDATE;
    mx_strdel(&(message->message));
    message->message = rd_random_strn(10);

    // When
    mx_message_update(token, message);

    // Then
    list = mx_message_list(token);
    int size_updated = mx_list_size(list);

    ASSERT_EQUALS(size_init + 1, size_updated);

    last_message = get_last_message(list);
    ASSERT_EQUALS_STR(message->message, last_message->message);
    ASSERT_EQUALS(size_init + 1, size);
    ASSERT_EQUALS(message->id, last_message->id);
    mx_message_list_del(&list);

    // ------------ Delete
    // Given
    message->type = E_MESSAGE_TYPE_DELETE;

    // When
    mx_message_delete(token, message);

    // Then
    list = mx_message_list(token);
    int size_deleted = mx_list_size(list);
    ASSERT_EQUALS(size_init, size_deleted);
    mx_message_list_del(&list);

    mx_message_del(&message);
    mx_strdel(&token);
    mx_strdel(&text);
}
