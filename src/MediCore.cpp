#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// ==========================================
// 1. BASE CLASS: PERSON
// ==========================================

class Person {
protected:
  int id;
  string name;
  int age;
  string contact;

public:
  Person(int i, string n, int a, string c) {
    id = i;
    name = n;
    age = a;
    contact = c;
  }

  virtual void displayDetails() const = 0;

  int getID() const { return id; }

  string getName() const { return name; }

  virtual ~Person() {}
};

// ==========================================
// 2. PATIENT CLASS (INHERITANCE)
// ==========================================

class Patient : public Person {

private:
  string condition;
  int severity;
  string status;

public:
  Patient(int i, string n, int a, string c, string cond, int sev)
      : Person(i, n, a, c) {

    condition = cond;
    severity = sev;
    status = "Waiting";
  }

  int getSeverity() const { return severity; }

  string getStatus() const { return status; }

  void setStatus(string s) { status = s; }

  void displayDetails() const override {

    cout << "\nPatient ID: " << id;
    cout << "\nName: " << name;
    cout << "\nAge: " << age;
    cout << "\nContact: " << contact;
    cout << "\nCondition: " << condition;
    cout << "\nPriority: " << severity;
    cout << "\nStatus: " << status;
    cout << "\n-----------------------------";
  }
};

// ==========================================
// 3. DOCTOR CLASS (INHERITANCE)
// ==========================================

class Doctor : public Person {

private:
  string specialization;
  bool available;

public:
  Doctor(int i, string n, int a, string c, string spec) : Person(i, n, a, c) {

    specialization = spec;
    available = true;
  }

  bool isAvailable() const { return available; }

  void displayDetails() const override {

    cout << "\nDoctor ID: " << id;
    cout << "\nName: " << name;
    cout << "\nAge: " << age;
    cout << "\nContact: " << contact;
    cout << "\nSpecialization: " << specialization;

    cout << "\nAvailability: " << (available ? "Available" : "Unavailable");

    cout << "\n-----------------------------";
  }
};

// ==========================================
// 4. APPOINTMENT CLASS
// ==========================================

class Appointment {

private:
  int appointmentID;
  int patientID;
  int doctorID;
  string dateTime;
  string status;

public:
  Appointment(int a, int p, int d, string dt) {

    appointmentID = a;
    patientID = p;
    doctorID = d;
    dateTime = dt;
    status = "Scheduled";
  }

  void display() const {

    cout << "\nAppointment ID: " << appointmentID;
    cout << "\nPatient ID: " << patientID;
    cout << "\nDoctor ID: " << doctorID;
    cout << "\nDate & Time: " << dateTime;
    cout << "\nStatus: " << status;

    cout << "\n-----------------------------";
  }
};

// ==========================================
// 5. TREATMENT CLASS
// ==========================================

class Treatment {

private:
  int patientID;
  int doctorID;
  string diagnosis;
  string notes;

public:
  Treatment(int p, int d, string diag, string n) {

    patientID = p;
    doctorID = d;
    diagnosis = diag;
    notes = n;
  }

  void display() const {

    cout << "\nPatient ID: " << patientID;
    cout << "\nDoctor ID: " << doctorID;
    cout << "\nDiagnosis: " << diagnosis;
    cout << "\nTreatment Notes: " << notes;

    cout << "\n-----------------------------";
  }
};

// ==========================================
// 6. HOSPITAL SYSTEM CLASS
// ==========================================

class HospitalSystem {

private:
  vector<Patient> patients;
  vector<Doctor> doctors;
  vector<Appointment> appointments;
  vector<Treatment> treatments;

  int nextAppointmentID = 1001;

  // Check duplicate patient ID
  bool patientExists(int id) const {

    for (const auto &p : patients) {

      if (p.getID() == id)
        return true;
    }

    return false;
  }

  // Check duplicate doctor ID
  bool doctorExists(int id) const {

    for (const auto &d : doctors) {

      if (d.getID() == id)
        return true;
    }

    return false;
  }

  // Find patient
  Patient *findPatient(int id) {

    for (auto &p : patients) {

      if (p.getID() == id)
        return &p;
    }

    return nullptr;
  }

  // Find doctor
  Doctor *findDoctor(int id) {

    for (auto &d : doctors) {

      if (d.getID() == id)
        return &d;
    }

    return nullptr;
  }

  // Safe integer input
  int getInteger(string message) {

    int value;

    while (true) {

      cout << message;

      if (cin >> value) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
      }

      cout << "Invalid input! Enter a number.\n";

      cin.clear();

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  // Safe text input
  string getText(string message) {

    string value;

    while (true) {

      cout << message;
      getline(cin, value);

      if (!value.empty())
        return value;

      cout << "Input cannot be empty!\n";
    }
  }

public:
  // ======================================
  // 7. PATIENT REGISTRATION
  // ======================================

  void registerPatient() {

    cout << "\n===== PATIENT REGISTRATION =====\n";

    int id = getInteger("Enter Patient ID: ");

    if (id <= 0 || patientExists(id)) {

      cout << "Invalid or duplicate Patient ID!\n";
      return;
    }

    string name = getText("Enter Patient Name: ");

    int age = getInteger("Enter Age: ");

    if (age <= 0 || age > 120) {

      cout << "Invalid age!\n";
      return;
    }

    string contact = getText("Enter Contact Number: ");

    string condition = getText("Enter Condition: ");

    int severity = getInteger("Enter Priority (1-5): ");

    if (severity < 1 || severity > 5) {

      cout << "Priority must be between 1 and 5.\n";
      return;
    }

    patients.emplace_back(id, name, age, contact, condition, severity);

    cout << "\nPatient Registered Successfully!\n";
  }

  // ======================================
  // 8. DISPLAY ALL PATIENTS
  // ======================================

  void displayPatients() const {

    cout << "\n===== PATIENT RECORDS =====\n";

    if (patients.empty()) {

      cout << "No patient records found.\n";
      return;
    }

    for (const auto &p : patients) {

      p.displayDetails();
    }

    cout << endl;
  }

  // ======================================
  // 9. SEARCH PATIENT
  // ======================================

  void searchPatient() {

    cout << "\n===== SEARCH PATIENT =====\n";

    int id = getInteger("Enter Patient ID: ");

    Patient *p = findPatient(id);

    if (p != nullptr) {

      cout << "\nPatient Found!\n";

      p->displayDetails();

      cout << endl;
    }

    else {

      cout << "\nPatient Not Found!\n";
    }
  }

  // ======================================
  // 10. DOCTOR REGISTRATION
  // ======================================

  void registerDoctor() {

    cout << "\n===== DOCTOR REGISTRATION =====\n";

    int id = getInteger("Enter Doctor ID: ");

    if (id <= 0 || doctorExists(id)) {

      cout << "Invalid or duplicate Doctor ID!\n";
      return;
    }

    string name = getText("Enter Doctor Name: ");

    int age = getInteger("Enter Doctor Age: ");

    if (age <= 0 || age > 120) {

      cout << "Invalid age!\n";
      return;
    }

    string contact = getText("Enter Contact: ");

    string specialization = getText("Enter Specialization: ");

    doctors.emplace_back(id, name, age, contact, specialization);

    cout << "\nDoctor Registered Successfully!\n";
  }

  // ======================================
  // 11. DISPLAY DOCTORS
  // ======================================

  void displayDoctors() const {

    cout << "\n===== DOCTOR RECORDS =====\n";

    if (doctors.empty()) {

      cout << "No doctor records found.\n";
      return;
    }

    for (const auto &d : doctors) {

      d.displayDetails();
    }

    cout << endl;
  }

  // ======================================
  // 12. APPOINTMENT SCHEDULING
  // ======================================

  void scheduleAppointment() {

    cout << "\n===== SCHEDULE APPOINTMENT =====\n";

    int pid = getInteger("Enter Patient ID: ");

    int did = getInteger("Enter Doctor ID: ");

    Patient *p = findPatient(pid);

    Doctor *d = findDoctor(did);

    if (p == nullptr) {

      cout << "Patient does not exist!\n";
      return;
    }

    if (d == nullptr) {

      cout << "Doctor does not exist!\n";
      return;
    }

    if (!d->isAvailable()) {

      cout << "Doctor is unavailable!\n";
      return;
    }

    string dateTime = getText("Enter Appointment Date and Time: ");

    appointments.emplace_back(nextAppointmentID++, pid, did, dateTime);

    cout << "\nAppointment Scheduled Successfully!\n";
  }

  // ======================================
  // 13. DISPLAY APPOINTMENTS
  // ======================================

  void displayAppointments() const {

    cout << "\n===== APPOINTMENT RECORDS =====\n";

    if (appointments.empty()) {

      cout << "No appointments available.\n";
      return;
    }

    for (const auto &a : appointments) {

      a.display();
    }

    cout << endl;
  }

  // ======================================
  // 14. ADD TREATMENT RECORD
  // ======================================

  void addTreatment() {

    cout << "\n===== ADD TREATMENT RECORD =====\n";

    int pid = getInteger("Enter Patient ID: ");

    int did = getInteger("Enter Doctor ID: ");

    if (findPatient(pid) == nullptr) {

      cout << "Invalid Patient ID!\n";
      return;
    }

    if (findDoctor(did) == nullptr) {

      cout << "Invalid Doctor ID!\n";
      return;
    }

    string diagnosis = getText("Enter Diagnosis: ");

    string notes = getText("Enter Treatment Notes: ");

    treatments.emplace_back(pid, did, diagnosis, notes);

    cout << "\nTreatment Record Added Successfully!\n";
  }

  // ======================================
  // 15. DISPLAY TREATMENTS
  // ======================================

  void displayTreatments() const {

    cout << "\n===== TREATMENT RECORDS =====\n";

    if (treatments.empty()) {

      cout << "No treatment records found.\n";
      return;
    }

    for (const auto &t : treatments) {

      t.display();
    }

    cout << endl;
  }

  // ======================================
  // 16. EMERGENCY PRIORITY SIMULATION
  // ======================================

  void emergencyManagement() {

    cout << "\n===== EMERGENCY PRIORITY SYSTEM =====\n";

    Patient *selected = nullptr;

    for (auto &p : patients) {

      if (p.getStatus() != "Waiting")
        continue;

      if (selected == nullptr || p.getSeverity() < selected->getSeverity()) {

        selected = &p;
      }
    }

    if (selected == nullptr) {

      cout << "No waiting patients found.\n";
      return;
    }

    cout << "\nHighest Configured Priority Patient:\n";

    selected->displayDetails();

    selected->setStatus("Selected");

    cout << "\n\nPatient selected successfully.\n";
  }

  // ======================================
  // 17. HOSPITAL STATISTICS
  // ======================================

  void hospitalStatistics() const {

    int waiting = 0;
    int selected = 0;

    for (const auto &p : patients) {

      if (p.getStatus() == "Waiting")
        waiting++;

      else
        selected++;
    }

    cout << "\n================================\n";
    cout << "       MEDICORE STATISTICS\n";
    cout << "================================\n";

    cout << "Total Patients       : " << patients.size() << endl;

    cout << "Total Doctors        : " << doctors.size() << endl;

    cout << "Total Appointments   : " << appointments.size() << endl;

    cout << "Treatment Records    : " << treatments.size() << endl;

    cout << "Waiting Patients     : " << waiting << endl;

    cout << "Other Patient Status : " << selected << endl;

    cout << "================================\n";
  }

  // ======================================
  // 18. MAIN MENU
  // ======================================

  void menu() {

    int choice;

    do {

      cout << "\n\n";
      cout << "========================================\n";
      cout << "       MEDICORE HOSPITAL SYSTEM\n";
      cout << "========================================\n";

      cout << "1.  Register Patient\n";
      cout << "2.  Display All Patients\n";
      cout << "3.  Search Patient\n";
      cout << "4.  Register Doctor\n";
      cout << "5.  Display Doctors\n";
      cout << "6.  Schedule Appointment\n";
      cout << "7.  Display Appointments\n";
      cout << "8.  Add Treatment Record\n";
      cout << "9.  Display Treatment Records\n";
      cout << "10. Emergency Priority Management\n";
      cout << "11. Hospital Statistics\n";
      cout << "12. Exit\n";

      cout << "========================================\n";

      choice = getInteger("Enter Your Choice: ");

      switch (choice) {

      case 1:
        registerPatient();
        break;

      case 2:
        displayPatients();
        break;

      case 3:
        searchPatient();
        break;

      case 4:
        registerDoctor();
        break;

      case 5:
        displayDoctors();
        break;

      case 6:
        scheduleAppointment();
        break;

      case 7:
        displayAppointments();
        break;

      case 8:
        addTreatment();
        break;

      case 9:
        displayTreatments();
        break;

      case 10:
        emergencyManagement();
        break;

      case 11:
        hospitalStatistics();
        break;

      case 12:
        cout << "\nThank You for Using MediCore!\n";
        cout << "Program Terminated Successfully.\n";
        break;

      default:
        cout << "\nInvalid Choice! Try Again.\n";
      }

    } while (choice != 12);
  }
};

// ==========================================
// 19. MAIN FUNCTION
// ==========================================

int main() {

  HospitalSystem hospital;

  cout << "\n";
  cout << "***************************************\n";
  cout << "       WELCOME TO MEDICORE\n";
  cout << "  HOSPITAL MANAGEMENT SYSTEM\n";
  cout << "***************************************\n";

  hospital.menu();

  return 0;
}