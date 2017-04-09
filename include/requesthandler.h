/*
 * Main service prototype 
 *
 * This method is the main one of this tiny server. This handle the request
 * comming from connection on c_socket. This should parse the request and
 * respond accordingly.
 */
int handle_request(int c_socket);
