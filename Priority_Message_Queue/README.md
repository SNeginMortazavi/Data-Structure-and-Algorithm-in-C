Message Priority Queue

A Priority Queue is a queue (first-in first-out) where elements are enqueued with a priority. The next element dequeued from a priority queue is the oldest one with the highest priority. If there are no elements with the highest priority, then dequeue operation returns the oldest one with the second-highest priority, and so on to the lowest priority.

One use of a priority queue is to implement a message priority queue, where certain messages have a higher priority and must be delivered sooner than any messages with lower priorities. For example, message queues are used for email systems, inter-program communication, and for managing print jobs.

Implement a MessagePriorityQueue that is a struct and the functions specified in the "messagepriorityqueue.h" file in the "2017SPCS5002SV/prog-assignment-2-template" repository. Stubs for the functions are in the "messagepriorityqueue.c" source file. The "messagepriorityqueue.h" file also defines a Priority enum. The ordinal values of the priorities indicate the priority, with Highest (0) being the highest and Lowest (3) the lowest.

The MessagePriorityQueue manages a MessageQueue for each priority. The MessageQueue is a struct and uses functions that are specified in the "messagequeue.h" file. A "messagequeue.c" file has stubs for the functions.

Messages are defined by the Message struct and functions specified in the "message.h" file. Stubs for the functions are in the file "message.c".

A main program and unit tests are contained in the "messagepriorityqueue_main.c" file. Your implementation must pass all the unit tests.