# Small Http Server

Toy project. A (very) small http server. The architecture and implementations are heavily based on the ones of:
  - Paul Griffiths  http://www.paulgriffiths.net
  - Head First C    ISBN:978-1-4493-9991-7
  - Richard Stevens, UNIX Network programming

Credits also goes to https://github.com/petewarden from which I shamelessly borrowed the Hasmpap implementation which is at the core of the MIME type decoding.

Up to know this is a server in barely working order. It can decipher HEAD and GET request and respond accordingly.

+ Supported http features:
  - FULL and SIMPLE http request
  - GET, HEAD Methods
  - MIME types (some) deciphering

+ Todo
  - add configuration filest
