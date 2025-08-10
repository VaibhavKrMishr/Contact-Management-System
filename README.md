# Contact-Management-System
A simple console-based Contact Management System built in C++ that allows you to add, search, display, and delete contacts. Contacts are saved to a text file (contacts.txt) for persistence between runs.<br>
##Features
- Add Contact: Name (required, must be unique), one or more phone numbers (default: 1 if skipped), Email (optional)
- Display All Contacts – Shows all saved contacts with their details
- Search Contact – Case-insensitive, partial match search
- Delete Contact – Case-insensitive, partial match delete
- Data Persistence – Contacts are saved to contacts.txt<br>
##How It Works<br>
Contacts are stored in memory using a std::vector<Contact>. File I/O is used to save and load contacts. Input validation ensures no duplicate names and proper defaults for optional fields.
