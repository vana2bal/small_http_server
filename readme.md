# Small Http Server

Toy project. A (very) small http server. The architecture and implementations are heavily based on the ones of:
  - Paul Griffiths  http://www.paulgriffiths.net
  - Head First C    ISBN:978-1-4493-9991-7
  - Richard Stevens, UNIX Network programming

Up to know this is a server in barely working order. It can decipher HEAD and GET request and respond accordingly.

+ Supported http features:
  - FULL and SIMPLE http request
  - GET, HEAD Methods
  - text/html mime type (in fact can handle any type but will answer that the file mime type is text/html)

+ Todo
  - add configuration files
  - add mime support
