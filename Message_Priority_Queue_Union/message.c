/*
 * message.c
 *
 * The functions in this file implement a Message with optional message string.
 *
 * @since Feb 1, 2017
 * @author phil
 */
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include "message.h"

/**
 * Create a message with the specified message string.
 *
 * @param msgstr the message string; may be NULL for no message
 * @return the new message
 */
Message* createMessage(const char *msgstr) {
	Message* message = malloc(sizeof(Message));
	assert( message != (Message*)NULL );

	// add copy of message string or NULL the field
	if (msgstr == (char*)NULL) {
		message->msgstr = (char*)NULL;
	} else {
		message->msgstr = strdup(msgstr);
		assert ( message->msgstr != (char*)NULL );
	}
	return message;
}

/**
 * Delete the message by freeing its resources.
 *
 * @param msg the Message to delete
 */
void deleteMessage(Message* msg) {
	assert ( msg != (Message*)NULL );

	// need to free allocated message string
	free(msg->msgstr);
	msg->msgstr = NULL;

	free(msg);
}

