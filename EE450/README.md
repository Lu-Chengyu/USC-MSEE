Client.cpp (Client Application)
    This file contains the client application code.
    It handles user input for login credentials.
    Encrypts login information before sending it to the main server.
    Includes functionality to interact with the mian server, like viewing  books availability.
ServerM.cpp (Main Server Application)
    This file implements the main server (ServerM).
    It is responsible for verifying member identities.
    Coordinates communication between the client and department servers.
ServerS.cpp (Science Department Server)
    Contains the implementation for the Science department server.
    Manages the database or records of books related to the Science department.
    Handles requests from the main server regarding Science books.
ServerL.cpp (Literature Department Server)
    Implements the Literature department server.
    Manages the Literature department's book information.
    Responds to queries from the main server about Literature books.
ServerH.cpp (History Department Server)
    Code for the History department server.
    Maintains data about History books.
    Interacts with the main server to provide information on History books.