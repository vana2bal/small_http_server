# Small Http Server

* ******************************************************************************
 DISCLAIMER: This is a toy project that I conducted for educational purposes
 only ! This is no where from being a secure server. There is no security   
 check what-soever. This code is provided as is and should not be used in   
 production or even on a machine which can be accesible outside of your own
 network. This goes without saying that this should not be used under any   
 circonstance in a production environment.                                  
* ******************************************************************************

As mentionned in the disclaimer the Small Http Server is a Toy project. It's
sole purpose is to teach me basics of C programming as well as networking
standards. It is not meant to be the next small and fast http server, nor is it
even meant to cover the all Http protocol.

As already mentionned twice it is an educational, and I don't wan't to take any
credit on the code accesible here. I would even go a step further and say that
the architecture of the server and the various function prototypes implementations
are heavily based on the ones of:
  - Paul Griffiths  http://www.paulgriffiths.net
  - Head First C    ISBN:978-1-4493-9991-7
  - Richard Stevens, UNIX Network programming

Pete Warden, https://github.com/petewarden, should also be credited. I shamelessly
ripped the Hasmpap implementation which is at the core of the MIME type decoding,
from his github repository.

Up to know this is a server in barely working order. It can decipher HEAD and GET
request and respond accordingly.

+ Supported http features:
  - FULL and SIMPLE http request
  - GET, HEAD Methods
  - MIME types (some) deciphering
  - Send viable responses with minimal headers and correct Http protocol version

+ Below is a list of the TODOs I'd like to tackle in the future
  - Add configuration files concerning for instance, server root folder path,
listening port, MIME types, name of the default pages to display when the
asked resource is "/";
  - Produce logs on the activity of the server
