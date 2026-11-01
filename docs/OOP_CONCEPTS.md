# 📘 OOP Concepts Demonstrated in MediCore

This document provides a **detailed explanation** of every Object-Oriented Programming concept used in the MediCore Hospital Management System, with code references and rationale.

---

## Table of Contents

1. [Classes and Objects](#1-classes-and-objects)
2. [Inheritance](#2-inheritance)
3. [Polymorphism](#3-polymorphism)
4. [Encapsulation](#4-encapsulation)
5. [Abstraction](#5-abstraction)
6. [Composition](#6-composition)
7. [Constructor Initialization](#7-constructor-initialization)
8. [Access Specifiers](#8-access-specifiers)
9. [Virtual Functions and vtable](#9-virtual-functions-and-vtable)
10. [Summary Table](#10-summary-table)

---

## 1. Classes and Objects

### Concept
A **class** is a user-defined blueprint that groups data (attributes) and functions (methods) together. An **object** is an instance of a class.

### In MediCore
The project defines **6 classes**, each modeling a real-world hospital entity:

| Class | Purpose | Key Attributes |
|-------|---------|----------------|
| `Person` | Abstract base for all people | `id`, `name`, `age`, `contact` |
| `Patient` | Represents a hospital patient | `condition`, `severity`, `status` |
| `Doctor` | Represents a hospital doctor | `specialization`, `available` |
| `Appointment` | Links patient to doctor | `appointmentID`, `dateTime`, `status` |
| `Treatment` | Medical treatment record | `diagnosis`, `notes` |
| `HospitalSystem` | Main system controller | Vectors of all entities |

### Code Example
```cpp
// Class definition
class Appointment {
private:
    int appointmentID;
    int patientID;
    int doctorID;
    string dateTime;
    string status;
public:
    Appointment(int a, int p, int d, string dt) { /* ... */ }
    void display() const { /* ... */ }
};

// Object creation (inside HospitalSystem)
appointments.emplace_back(nextAppointmentID++, pid, did, dateTime);
```

---

## 2. Inheritance

### Concept
**Inheritance** allows a derived (child) class to inherit properties and behaviors from a base (parent) class, promoting **code reuse** and establishing an **"is-a"** relationship.

### In MediCore
Both `Patient` and `Doctor` inherit from `Person`:

```
        Person (Base)
       /            \
  Patient            Doctor
 (Derived)          (Derived)
```

### Code Example
```cpp
// Base class
class Person {
protected:
    int id;
    string name;
    int age;
    string contact;
public:
    Person(int i, string n, int a, string c) { /* ... */ }
    virtual void displayDetails() const = 0;
    int getID() const { return id; }
    string getName() const { return name; }
    virtual ~Person() {}
};

// Derived class - inherits all Person members
class Patient : public Person {
private:
    string condition;   // Additional patient-specific data
    int severity;
    string status;
public:
    Patient(int i, string n, int a, string c, string cond, int sev)
        : Person(i, n, a, c) {    // Calls base constructor
        condition = cond;
        severity = sev;
        status = "Waiting";
    }
};
```

### Why It's Used
- **Eliminates code duplication**: `id`, `name`, `age`, `contact` are defined once in `Person`
- **Establishes logical hierarchy**: Every Patient and Doctor IS-A Person
- **Enables polymorphic behavior**: Base class pointers can refer to derived objects

---

## 3. Polymorphism

### Concept
**Polymorphism** ("many forms") allows the same function call to behave differently based on the actual object type. In C++, this is achieved through **virtual functions**.

### In MediCore
The `displayDetails()` method is:
- Declared as **pure virtual** in `Person` → makes Person abstract
- **Overridden** in `Patient` → displays patient-specific info
- **Overridden** in `Doctor` → displays doctor-specific info

### Code Example
```cpp
// Base class — pure virtual function
class Person {
    virtual void displayDetails() const = 0;  // No implementation
};

// Patient override
class Patient : public Person {
    void displayDetails() const override {
        cout << "\nPatient ID: " << id;
        cout << "\nName: " << name;
        cout << "\nCondition: " << condition;    // Patient-specific
        cout << "\nPriority: " << severity;       // Patient-specific
        cout << "\nStatus: " << status;           // Patient-specific
    }
};

// Doctor override
class Doctor : public Person {
    void displayDetails() const override {
        cout << "\nDoctor ID: " << id;
        cout << "\nName: " << name;
        cout << "\nSpecialization: " << specialization;  // Doctor-specific
        cout << "\nAvailability: " << (available ? "Available" : "Unavailable");
    }
};
```

### Behavior
When `displayDetails()` is called on a `Person*` pointer:
- If it points to a `Patient` → Patient's version runs
- If it points to a `Doctor` → Doctor's version runs

This is **runtime polymorphism** — the correct function is determined at runtime.

---

## 4. Encapsulation

### Concept
**Encapsulation** is the bundling of data and methods within a class, restricting direct access to internal state. External code interacts only through **public methods** (getters/setters).

### In MediCore
All data members are `private` or `protected`, accessed via public methods:

```cpp
class Patient : public Person {
private:                          // ← Cannot be accessed directly
    string condition;
    int severity;
    string status;

public:                           // ← Controlled access points
    int getSeverity() const { return severity; }
    string getStatus() const { return status; }
    void setStatus(string s) { status = s; }
};
```

### Benefits Demonstrated
| Principle | Example |
|-----------|---------|
| **Data Protection** | `severity` cannot be changed to an invalid value from outside |
| **Controlled Modification** | `setStatus()` is the only way to change patient status |
| **Read-only Access** | `getID()`, `getName()` provide data without allowing modification |
| **Implementation Hiding** | Internal vector management in `HospitalSystem` is hidden |

---

## 5. Abstraction

### Concept
**Abstraction** hides complex implementation details and exposes only essential features. In C++, **abstract classes** (with pure virtual functions) enforce this pattern.

### In MediCore
`Person` is an **abstract class** — it cannot be instantiated directly:

```cpp
class Person {
public:
    virtual void displayDetails() const = 0;  // = 0 makes it pure virtual
    virtual ~Person() {}                       // Virtual destructor
};

// This would cause a compile error:
// Person p(1, "Test", 25, "123");  ❌ Cannot instantiate abstract class
```

### Why Use Abstraction Here
- `Person` defines the **interface** (what every person must do)
- `Patient` and `Doctor` provide the **implementation** (how they do it)
- Users of the system don't need to know the internal workings

---

## 6. Composition

### Concept
**Composition** is a "has-a" relationship where a class contains objects of other classes as members. The contained objects' lifecycle is managed by the container.

### In MediCore
`HospitalSystem` **contains** all other objects:

```cpp
class HospitalSystem {
private:
    vector<Patient> patients;           // HospitalSystem HAS patients
    vector<Doctor> doctors;             // HospitalSystem HAS doctors
    vector<Appointment> appointments;   // HospitalSystem HAS appointments
    vector<Treatment> treatments;       // HospitalSystem HAS treatments
};
```

### Composition vs Inheritance
| Relationship | Type | Example |
|-------------|------|---------|
| Patient IS-A Person | **Inheritance** | `class Patient : public Person` |
| HospitalSystem HAS-A Patient | **Composition** | `vector<Patient> patients;` |

When `HospitalSystem` is destroyed, all contained patients, doctors, etc. are also destroyed — demonstrating **ownership semantics**.

---

## 7. Constructor Initialization

### Concept
**Constructors** initialize objects when they are created. C++ supports **initializer lists** for calling base class constructors.

### In MediCore
Derived classes use initializer lists to call the `Person` base constructor:

```cpp
// Initializer list: Person(i, n, a, c) is called first
Patient(int i, string n, int a, string c, string cond, int sev)
    : Person(i, n, a, c)     // ← Base class constructor call
{
    condition = cond;          // Then derived class members initialized
    severity = sev;
    status = "Waiting";
}
```

### Order of Construction
1. `Person` constructor runs first → sets `id`, `name`, `age`, `contact`
2. `Patient` constructor body runs → sets `condition`, `severity`, `status`

---

## 8. Access Specifiers

### Concept
C++ provides three levels of access control:

| Specifier | Same Class | Derived Class | Outside |
|-----------|:----------:|:-------------:|:-------:|
| `public` | ✅ | ✅ | ✅ |
| `protected` | ✅ | ✅ | ❌ |
| `private` | ✅ | ❌ | ❌ |

### In MediCore
```cpp
class Person {
protected:     // Accessible in Patient and Doctor
    int id;
    string name;

public:        // Accessible everywhere
    int getID() const { return id; }
    virtual void displayDetails() const = 0;
};

class Patient : public Person {
private:       // Only accessible within Patient
    string condition;
    int severity;

public:        // Interface methods
    int getSeverity() const { return severity; }
};
```

---

## 9. Virtual Functions and vtable

### Concept
When a class has **virtual functions**, the compiler creates a **vtable** (virtual function table) for that class. Each object gets a hidden **vptr** that points to its class's vtable, enabling dynamic dispatch.

### In MediCore
```cpp
class Person {
    virtual void displayDetails() const = 0;  // Entry in vtable
    virtual ~Person() {}                       // Virtual destructor — also in vtable
};
```

**Why Virtual Destructor?**
```cpp
Person* p = new Patient(1, "Rahul", 30, "123", "Fever", 3);
delete p;  // Without virtual destructor, Patient's destructor won't run!
```
The `virtual ~Person() {}` ensures proper cleanup of derived objects when deleted through a base pointer.

---

## 10. Summary Table

| OOP Concept | Where It's Used | Key Code Element |
|-------------|----------------|------------------|
| **Classes & Objects** | All 6 classes | `class Patient { ... };` |
| **Inheritance** | Patient → Person, Doctor → Person | `: public Person` |
| **Polymorphism** | `displayDetails()` override | `virtual void displayDetails() = 0` |
| **Encapsulation** | Private data + public getters | `private:` + `getID()` |
| **Abstraction** | Person as abstract base | `= 0` (pure virtual) |
| **Composition** | HospitalSystem contains all entities | `vector<Patient> patients;` |
| **Constructors** | Initializer lists in derived classes | `: Person(i, n, a, c)` |
| **Access Specifiers** | public, protected, private usage | Three-tier access control |
| **Virtual Destructor** | Proper cleanup in inheritance | `virtual ~Person() {}` |

---

<p align="center">
  <b>📎 This document is part of the MediCore Hospital Management System project.</b>
</p>
