/**
* This file contains the functions for CS 5002 assignment2.
*
* message.c
*
* @since Feb 7, 2017
* @author Negin
*/
#include <stdlib.h>
#include "message.h"
#include <string.h>


/**
 * This function Creates a message with the specified message string.
 *
 * @param msgstr a pointer to character (which is constant).
 * @return create message which is the pointer to Message*
 */

Message* createMessage(const char *msgstr) {
	// allocate memory for msg
	Message *msg= (Message*)malloc(sizeof(Message));
	//check if the specified message string is not NULL.
	if(msgstr != (char*)NULL){
		msg->msgstr = strdup(msgstr);
	}else{
		msg->msgstr = (char*)NULL;
	}
	return msg;
}

/**
 * This function Deletes the message by freeing its resources.
 *
 * @param msg a pointer to Message
 * @return freeing the resources of message
 */
void deleteMessage(Message* msg) {
	//free the message resources including char* msgstr
	free(msg->msgstr);
	//to make sure it is free
	msg->msgstr = (char*)NULL;
	free(msg);
}

