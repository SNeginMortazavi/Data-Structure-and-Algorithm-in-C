/*
 * message.h
 *
 *  Created on: Feb 1, 2017
 *      Author: phil
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

/**
 * A Message includes a message string
 */
typedef struct {
	char *msgstr;
} Message;

/**
 * Create a message with the specified message string.
 */
Message* createMessage(const char *msgstr);

/**
 * Delete the message by freeing its resources.
 */
void deleteMessage(Message* msg);

#endif /* MESSAGE_H_ */
