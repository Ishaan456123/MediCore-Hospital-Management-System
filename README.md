<p align="center">
  <img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge&logo=cplusplus&logoColor=white" />
  <img src="https://img.shields.io/badge/Paradigm-OOP-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Platform-Console-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" />
</p>

# 🏥 MediCore — Hospital Management System

> **A Hospital Emergency and Patient Management System developed using C++ and Object-Oriented Programming (OOP) concepts.**

MediCore is a console-based hospital management application that simulates real-world hospital operations including patient registration, doctor management, appointment scheduling, treatment tracking, and emergency triage prioritization.

---

## 📋 Table of Contents

- [Features](#-features)
- [OOP Concepts Used](#-oop-concepts-used)
- [Class Architecture](#-class-architecture)
- [Project Structure](#-project-structure)
- [How to Compile & Run](#-how-to-compile--run)
- [Sample Output](#-sample-output)
- [Menu Options](#-menu-options)
- [Technical Details](#-technical-details)
- [Future Enhancements](#-future-enhancements)
- [License](#-license)

---

## ✨ Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Patient Registration** | Register patients with ID, name, age, contact, condition, and severity priority (1–5) |
| 2 | **Doctor Registration** | Register doctors with specialization and availability tracking |
| 3 | **Patient Search** | Search for patients by their unique ID |
| 4 | **Appointment Scheduling** | Schedule appointments linking patients to doctors with date/time |
| 5 | **Treatment Records** | Record diagnosis and treatment notes for patient-doctor pairs |
| 6 | **Emergency Priority Management** | Auto-selects the highest-priority waiting patient (triage simulation) |
| 7 | **Hospital Statistics** | Dashboard showing total patients, doctors, appointments, treatments, and status breakdown |
| 8 | **Input Validation** | Robust validation for all user inputs (integer bounds, empty strings, duplicate IDs) |

---

## 🎯 OOP Concepts Used

This project demonstrates the following **Object-Oriented Programming** principles:

### 1. 🧬 Classes & Objects
All entities (Person, Patient, Doctor, Appointment, Treatment, HospitalSystem) are modeled as **classes** with their own attributes and methods.

```cpp
class Patient : public Person {
    string condition;
    int severity;
    string status;
    // ...
};
```

### 2. 🏗️ Inheritance
`Patient` and `Doctor` classes **inherit** from the `Person` base class, reusing common attributes (`id`, `name`, `age`, `contact`).

```
Person (Base Class)
├── Patient (Derived Class)
└── Doctor  (Derived Class)
```

### 3. 🎭 Polymorphism
The `displayDetails()` method is declared as a **pure virtual function** in `Person` and overridden in both `Patient` and `Doctor`, enabling runtime polymorphism.

```cpp
class Person {
    virtual void displayDetails() const = 0;  // Pure virtual
};

class Patient : public Person {
    void displayDetails() const override { /* Patient-specific display */ }
};
```

### 4. 🔒 Encapsulation
All class data members are **private/protected**, accessed only through **public getter/setter methods**.

```cpp
class Person {
protected:    // Accessible to derived classes
    int id;
    string name;
public:
    int getID() const { return id; }       // Controlled access
    string getName() const { return name; }
};
```

### 5. 🧩 Abstraction
The `Person` class is **abstract** (contains a pure virtual function), providing a common interface while hiding implementation details.

### 6. 🗂️ Composition
The `HospitalSystem` class **contains** vectors of Patient, Doctor, Appointment, and Treatment objects — demonstrating the "has-a" relationship.

```cpp
class HospitalSystem {
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    vector<Treatment> treatments;
};
```

> 📖 For a detailed explanation of each OOP concept, see [`docs/OOP_CONCEPTS.md`](docs/OOP_CONCEPTS.md)

---

## 🏛️ Class Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     MEDICORE SYSTEM                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│   ┌──────────────────────┐                                  │
│   │    Person (Abstract)  │                                  │
│   │ ─────────────────── │                                  │
│   │ # id : int           │                                  │
│   │ # name : string      │                                  │
│   │ # age : int          │                                  │
│   │ # contact : string   │                                  │
│   │ ─────────────────── │                                  │
│   │ + getID() : int      │                                  │
│   │ + getName() : string │                                  │
│   │ + displayDetails()*  │  ← Pure Virtual Function         │
│   └──────────┬───────────┘                                  │
│              │                                              │
│      ┌───────┴────────┐                                     │
│      │                │                                     │
│  ┌───▼──────────┐  ┌──▼───────────┐                         │
│  │   Patient     │  │   Doctor      │                        │
│  │ ──────────── │  │ ──────────── │                        │
│  │ - condition  │  │ - specialize │                        │
│  │ - severity   │  │ - available  │                        │
│  │ - status     │  │ ──────────── │                        │
│  │ ──────────── │  │ + isAvail()  │                        │
│  │ + getSev()   │  │ + display()↑ │                        │
│  │ + display()↑ │  └──────────────┘                         │
│  └──────────────┘                                           │
│                                                             │
│  ┌───────────────┐  ┌───────────────┐                       │
│  │  Appointment   │  │  Treatment     │                      │
│  │ ──────────── │  │ ──────────── │                      │
│  │ - appointID  │  │ - patientID  │                      │
│  │ - patientID  │  │ - doctorID   │                      │
│  │ - doctorID   │  │ - diagnosis  │                      │
│  │ - dateTime   │  │ - notes      │                      │
│  │ - status     │  └───────────────┘                       │
│  └───────────────┘                                          │
│                                                             │
│  ┌──────────────────────────────────────────────────┐       │
│  │              HospitalSystem (Composition)         │       │
│  │ ──────────────────────────────────────────────── │       │
│  │ - patients : vector<Patient>                     │       │
│  │ - doctors : vector<Doctor>                       │       │
│  │ - appointments : vector<Appointment>             │       │
│  │ - treatments : vector<Treatment>                 │       │
│  │ ──────────────────────────────────────────────── │       │
│  │ + registerPatient()  + scheduleAppointment()     │       │
│  │ + registerDoctor()   + addTreatment()            │       │
│  │ + searchPatient()    + emergencyManagement()     │       │
│  │ + hospitalStatistics() + menu()                  │       │
│  └──────────────────────────────────────────────────┘       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## 📁 Project Structure

```
MediCore-Hospital-Management-System/
│
├── src/
│   └── MediCore.cpp          # Main source code (all classes + main function)
│
├── docs/
│   └── OOP_CONCEPTS.md       # Detailed OOP concepts explanation
│
├── .gitignore                # Git ignore rules for C++ projects
├── LICENSE                   # MIT License
└── README.md                 # This file
```

---

## 🚀 How to Compile & Run

### Prerequisites
- A C++ compiler supporting **C++11** or later (g++, MSVC, clang++)

### Using g++ (Linux / macOS / MinGW on Windows)

```bash
# Navigate to the project directory
cd MediCore-Hospital-Management-System

# Compile
g++ -std=c++11 -o MediCore src/MediCore.cpp

# Run
./MediCore
```

### Using MSVC (Windows - Visual Studio Developer Command Prompt)

```cmd
cl /EHsc /std:c++11 src\MediCore.cpp /Fe:MediCore.exe
MediCore.exe
```

### Using an IDE
1. Open your preferred IDE (Visual Studio, Code::Blocks, Dev-C++, CLion)
2. Create a new C++ console project
3. Add `src/MediCore.cpp` to the project
4. Build and Run

---

## 📸 Sample Output

### Welcome Screen
```
***************************************
       WELCOME TO MEDICORE
  HOSPITAL MANAGEMENT SYSTEM
***************************************

========================================
       MEDICORE HOSPITAL SYSTEM
========================================
1.  Register Patient
2.  Display All Patients
3.  Search Patient
4.  Register Doctor
5.  Display Doctors
6.  Schedule Appointment
7.  Display Appointments
8.  Add Treatment Record
9.  Display Treatment Records
10. Emergency Priority Management
11. Hospital Statistics
12. Exit
========================================
Enter Your Choice:
```

### Patient Registration
```
===== PATIENT REGISTRATION =====
Enter Patient ID: 101
Enter Patient Name: Rahul Sharma
Enter Age: 35
Enter Contact Number: 9876543210
Enter Condition: Chest Pain
Enter Priority (1-5): 2

Patient Registered Successfully!
```

### Hospital Statistics
```
================================
       MEDICORE STATISTICS
================================
Total Patients       : 5
Total Doctors        : 3
Total Appointments   : 4
Treatment Records    : 2
Waiting Patients     : 3
Other Patient Status : 2
================================
```

### Emergency Priority Management
```
===== EMERGENCY PRIORITY SYSTEM =====

Highest Configured Priority Patient:

Patient ID: 103
Name: Anita Verma
Age: 62
Contact: 9123456780
Condition: Heart Attack
Priority: 1
Status: Waiting
-----------------------------

Patient selected successfully.
```

---

## 📜 Menu Options

| Option | Function | Description |
|--------|----------|-------------|
| `1` | Register Patient | Add a new patient with condition and priority |
| `2` | Display All Patients | View all registered patients |
| `3` | Search Patient | Find a patient by ID |
| `4` | Register Doctor | Add a new doctor with specialization |
| `5` | Display Doctors | View all registered doctors |
| `6` | Schedule Appointment | Create appointment between patient and doctor |
| `7` | Display Appointments | View all scheduled appointments |
| `8` | Add Treatment Record | Record diagnosis and treatment notes |
| `9` | Display Treatment Records | View all treatment records |
| `10` | Emergency Priority | Auto-select highest-priority waiting patient |
| `11` | Hospital Statistics | View system-wide statistics dashboard |
| `12` | Exit | Terminate the program |

---

## 🔧 Technical Details

| Aspect | Detail |
|--------|--------|
| **Language** | C++ (C++11 standard) |
| **Paradigm** | Object-Oriented Programming |
| **Libraries** | `<iostream>`, `<string>`, `<vector>`, `<iomanip>`, `<limits>` |
| **Data Storage** | In-memory (vectors) |
| **Input Handling** | Robust validation with `cin.clear()` and `cin.ignore()` |
| **Lines of Code** | ~726 |
| **Total Classes** | 6 (Person, Patient, Doctor, Appointment, Treatment, HospitalSystem) |

---

## 🔮 Future Enhancements

- [ ] File-based persistent storage (save/load patient data)
- [ ] Login system for admin authentication
- [ ] Billing and payment module
- [ ] Bed/ward management
- [ ] Medicine inventory tracking
- [ ] Date-based appointment filtering
- [ ] GUI using Qt or similar framework

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

<p align="center">
  <b>Made with ❤️ for OOP Mini Project</b>
  <br/>
  <i>MediCore — Because every patient matters.</i>
</p>
