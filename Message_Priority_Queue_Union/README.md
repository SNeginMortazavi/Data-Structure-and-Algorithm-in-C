In Programming Assignment 2, MessageQueue and MessagePriorityQueue handled a single type of Message that had a message string as its content. In actual use, message systems provide multiple types of messsages for different purposes. Each message type has information that is appropriate to its purpose.

In this assignment, you will extend "message.c" and "message.h" to support three different message types. These might represent different messages that can be sent by a client application on one computer to a message handling system on another computer. The message handling system enqueues messages it receives, and then dequeues and dispatches the oldest one with the highest priority to be handled by the appropriate service for the message type, such as a email or print server. We will implement message types in such a way that we can easily add new ones if needed in the future.

The C language provides a feature called a "union" that enables us to create "variant" content in our Message struct for the three message types. We simply define a struct for each of the three message types, and then include all three in our Message struct as variants in a union. The amount of storage in our Message struct is based on the size of the largest variant struct in the union.

To determine which variant to use for a given message, we can add a "tag" field to the Message struct that identifies the message type. Any type of tag can be used, but an enum seems the most suitable in this case.

In "message.h":

Define and typedef structs for three message variants described below
Define and typedef an enum MessageType with labels that identify the three message variants: stringMessage, blockMessage, statusMessage.
Replace the current Message struct with one that includes a MessageType field msgType, and an "anonymous" union of the three variant message structs (do not name the union or union field in the Message struct).
Message Variant Name	    Message Variant Struct
StringMessage	
const char* msgstr (optional message string)
BlockMessage	   
unsigned int blkSize (number of bytes in the block)
unsigned int blkFormat (format of block bytes: 1, 2, or 3)
const unsigned char* blkBytes (array of bytes -- no NULL terminator!)
StatusMessage  
unsigned long timeStamp (miliseconds since Jan 1 1970)
unsigned int statusCode
const char* statusMsg (optional string for status code)
In "message.c":

Rename createMessage() to createStringMessage()
Add equivalent methods for the other two message types, with parameters corresponding to the variant struct fields. Be sure to allocate storage for any array fields and copy their contents. (Caution: blkBytes is an array of bytes with no terminating null character).
Make sure to also set the "msgType" field in the Message struct in all three creation methods.
Rewrite deleteMessage() to use a 'switch' statement to free and clear the Message fields based based on its messageType, then free the message.
The "messagePriorityQueue_main.c" has been modified to test the new message variant functionality.