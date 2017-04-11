/*
 * Main service prototype
 *
 * This method is the main one of this tiny server. This handle the request
 * comming from connection on c_socket. This should parse the request and
 * respond accordingly.
 */
 #ifndef REQUEST_HANDLER_H
 #define REQUEST_HANDLER_H

int handle_request(int c_socket);

#endif
