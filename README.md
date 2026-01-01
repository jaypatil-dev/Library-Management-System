# 📚 Library Management System in C

A **console-based Library Management System** developed using **C programming**.  
This project demonstrates the use of **structures, file handling, and menu-driven programming** to manage library book records with **persistent storage**.

---

## ✨ Features

- Add new books with proper input validation
- Display all available books
- Search books using **Book ID**
- Issue books with quantity check
- Return issued books
- Delete book records
- Persistent data storage using binary files
- Menu-driven and user-friendly interface

---

## 🛠 Technologies Used

- **C Programming**
- **Structures**
- **File Handling** (`fread`, `fwrite`)
- **Standard C Libraries** (`stdio.h`, `stdlib.h`, `string.h`)

---

## 🗂 File Handling Details

- Book records are stored in a binary file:  
  **`Library.dat`**
- Temporary file **`Temp.dat`** is used while issuing, returning, or deleting books to safely update records.
- Data remains saved even after the program terminates.

---

## 📋 Operations Supported

1. Add Book  
2. Display All Books  
3. Search Book  
4. Issue Book  
5. Return Book  
6. Delete Book  
7. Exit  

---

## ▶ How to Run the Project

### Step 1: Compile the program
```bash
gcc main.c -o library
```
### Step 2: Run the executable
```bash
./library
```
#### (On Windows, use library.exe)

## 🧠 Learning Outcomes
1. Practical understanding of file handling in C
2. Working with structures and binary files
3. Implementing CRUD operations
4. Using temporary files for safe record updates
5. Improved logical thinking and problem-solving skills

## 📌 Project Highlights

1. Uses binary file storage for efficiency
2. Handles edge cases like book unavailability and invalid inputs
3. Modular and readable code structure

