# EE3204-Computer-Networks

##Ex1:
A socket program in UNIX/Linux that uses (i) TCP as the transport protocol and (ii) UDP as the transport protocol for transferring a short message between a client and server. The client sends a string (input by the user) to the server and the server prints the string on the screen after receiving it.

##Ex2:
A TCP-based client-server socket program for transferring a large message. Here, the message transmitted from the client to server is read from a large file. The entire message is sent by the client as a single data-unit. After receiving the file, the server sends an ACK message to the receiver.

##Ex3:
A TCP-based client-server socket program for transferring a large message. Here, the message transmitted from the client to server is read from a large file. The message is split into short data-units which are sent one by one without waiting for any acknowledgement between transmissions of two successive data-units.

##Ex4:
A TCP-based client-server socket program for transferring a large message. Here, the message transmitted from the client to server is read from a large file. The message is split into short data-units which are sent by using stop-and-wait flow control. Also, a data-unit sent could be damaged with some error probability
