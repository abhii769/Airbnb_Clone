# Room Rental System

This project implements a **Room Rental System** using **Object-Oriented Programming (OOP)** concepts in C++. The application supports functionality for three types of users: **Customers**, **Employees**, and a **Manager**. Each user type has unique roles and responsibilities within the system.

---

## Key Features of the Code

### 1. **Class Structure and Inheritance**
- **Base Class:**
  - `User`: Acts as a parent class for `Customer`, `Employee`, and `Manager`. It provides common attributes and methods shared among all user types, such as viewing available rooms, renting rooms, checking availability, and clearing dues.

- **Derived Classes:**
  - `Customer`: Inherits from `User`. Contains functionality specific to customers, such as returning rooms and managing personal profiles.
  - `Employee`: Inherits from `User`. Similar to customers but includes slight variations like rental pricing adjustments.
  - `Manager`: Inherits from `User`. Has the ability to manage system settings, modify databases (customers, employees, rooms), and view detailed data.

---

### 2. **Encapsulation**
Encapsulation is achieved by:
- Using `private` and `protected` access specifiers to restrict access to sensitive data like passwords in `Customer` and `Employee` classes.
- Providing public methods like `display()`, `see_available_rooms()`, and `clear_due()` to interact with the system in a controlled manner.

---

### 3. **Polymorphism**
- **Virtual Functions:**
  - The `display()` function is declared as a `virtual` function in the base class `User` and is overridden in derived classes (`Customer`, `Employee`, and `Manager`) to provide user-specific behavior.

---

### 4. **Abstraction**
- The `User` class serves as an abstract base class by including pure virtual functions, such as `display()`.
- Specific implementations for these functions are provided in the derived classes.

---

### 5. **File Handling**
The system uses file handling extensively to:
- Read data for customers, employees, rooms, and manager settings from `.csv` files.
- Update these files with new information whenever changes occur.

---

### 6. **Dynamic Behavior**
- The system dynamically calculates dues and adjusts user records based on room conditions and overdue days. This behavior ensures real-time data updates during room rentals and returns.

---

## How to Use
1. Compile the program using a C++ compiler:
   ```bash
   g++ -std=c++17 main.cpp -o room_rental_system
