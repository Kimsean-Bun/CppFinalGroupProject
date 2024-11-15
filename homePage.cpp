#include <iostream>
#include "DatabaseOperations.h"
#include "PatientOperations.h"
#include "AppointmentOperations.h"
#include "DiagnosticOperations.h"

using namespace std;

// Function prototypes for each module's menu
void patientMenu(PatientOperations& patientOps);
void appointmentMenu(AppointmentOperations& apptOps);
void diagnosticMenu(DiagnosticOperations& diagOps);
void addPatient(PatientOperations& patientOps);
void updatePatient(PatientOperations& patientOps);
void deletePatient(PatientOperations& patientOps);
void searchPatient(PatientOperations& patientOps);
void displayPatients(PatientOperations& patientOps);
void addAppointment(AppointmentOperations& apptOps);
void viewAppointments(AppointmentOperations& apptOps);
void rescheduleAppointment(AppointmentOperations& apptOps);
void cancelAppointment(AppointmentOperations& apptOps);
void addDiagnostic(DiagnosticOperations& diagOps);
void viewDiagnostics(DiagnosticOperations& diagOps);
void updateDiagnostic(DiagnosticOperations& diagOps);

int main() {
    system("clear");

    // Initialize the database connection
    DatabaseOperations dbOps("hospital.db");

    // Initialize each operations class with the database connection
    PatientOperations patientOps(dbOps);
    AppointmentOperations apptOps(dbOps);
    DiagnosticOperations diagOps(dbOps);

    int choice;
    do {
        cout << "\n==================================\n";
        cout << "     Hospital Management System\n";
        cout << "==================================\n";
        cout << "1. Patient Management\n";
        cout << "2. Appointment Management\n";
        cout << "3. Diagnostic Management\n";
        cout << "4. Exit\n";
        cout << "----------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                patientMenu(patientOps);
                break;
            case 2:
                appointmentMenu(apptOps);
                break;
            case 3:
                diagnosticMenu(diagOps);
                break;
            case 4:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Menu for Patient Management
void patientMenu(PatientOperations& patientOps) {
    int choice;
    do {
        cout << "\n==================================\n";
        cout << "        Patient Management\n";
        cout << "==================================\n";
        cout << "1. Add Patient\n";
        cout << "2. Update Patient\n";
        cout << "3. Delete Patient\n";
        cout << "4. Search Patient\n";
        cout << "5. Display All Patients\n";
        cout << "6. Return to Main Menu\n";
        cout << "----------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addPatient(patientOps);
                break;
            case 2:
                updatePatient(patientOps);
                break;
            case 3:
                deletePatient(patientOps);
                break;
            case 4:
                searchPatient(patientOps);
                break;
            case 5:
                displayPatients(patientOps);
                break;
            case 6:
                cout << "Returning ...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

// Menu for Appointment Management
void appointmentMenu(AppointmentOperations& apptOps) {
    int choice;
    do {
        cout << "\n==================================\n";
        cout << "      Appointment Management\n";
        cout << "==================================\n";
        cout << "1. Add Appointment\n";
        cout << "2. View Appointments\n";
        cout << "3. Reschedule Appointment\n";
        cout << "4. Cancel Appointment\n";
        cout << "5. Return to Main Menu\n";
        cout << "----------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addAppointment(apptOps);
                break;
            case 2:
                viewAppointments(apptOps);
                break;
            case 3:
                rescheduleAppointment(apptOps);
                break;
            case 4:
                cancelAppointment(apptOps);
                break;
            case 5:
                cout << "Returning ...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

// Menu for Diagnostic Management
void diagnosticMenu(DiagnosticOperations& diagOps) {
    int choice;
    do {
        cout << "\n==================================\n";
        cout << "       Diagnostic Management\n";
        cout << "==================================\n";
        cout << "1. Add Diagnostic\n";
        cout << "2. View Diagnostics\n";
        cout << "3. Update Diagnostic\n";
        cout << "4. Return to Main Menu\n";
        cout << "----------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addDiagnostic(diagOps);
                break;
            case 2:
                viewDiagnostics(diagOps);
                break;
            case 3:
                updateDiagnostic(diagOps);
                break;
            case 4:
                cout << "Returning ...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

// Function for PatientMenu/Registration
void addPatient(PatientOperations& patientOps) {
    string name, gender, dob, email, phone;

    cout << endl;
    cout << "Enter Name: ";
    getline(cin, name);
    // Gender input validation
    do {
        cout << "Enter Gender (M, F, or NA): ";
        getline(cin, gender);
        if (gender != "M" && gender != "F" && gender != "NA") {
            cout << "Invalid input. Please enter 'M', 'F', or 'NA'.\n";
        }
    } while (gender != "M" && gender != "F" && gender != "NA");
    cout << "Enter Date of Birth (YYYY-MM-DD): ";
    getline(cin, dob);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Phone Number: ";
    getline(cin, phone);

    patientOps.addPatient(name, gender, dob, email, phone);
}

void updatePatient(PatientOperations& patientOps) {
    int id;
    string newName, newGender, newDateOfBirth, newEmail, newPhone;

    cout << endl;
    cout << "Enter Patient ID to update: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Patient name: ";
    getline(cin, newName);
    do {
        cout << "Enter Gender (M, F, or NA): ";
        getline(cin, newGender);
    } while (newGender != "M" && newGender != "F" && newGender != "NA");
    cout << "Enter Date of Birth (YYYY-MM-DD): ";
    getline(cin, newDateOfBirth);
    cout << "Enter Email: ";
    getline(cin, newEmail);
    cout << "Enter Phone: ";
    getline(cin, newPhone);

    patientOps.updatePatient(id, newName, newGender, newDateOfBirth, newEmail, newPhone);
}

void deletePatient(PatientOperations& patientOps) {
    int id;

    cout << endl;
    cout << "Enter Patient ID to delete: ";
    cin >> id;
    cin.ignore();

    patientOps.deletePatient(id);
}

void searchPatient(PatientOperations& patientOps){
    int id;

    cout << endl;
    cout << "Enter Patient ID to Search: ";
    cin >> id;
    cout << endl;
    cin.ignore();
    patientOps.viewPatient(id);
}

void displayPatients(PatientOperations& patientOps) {
    cout << endl;
    patientOps.viewAllPatients();
}

// Functions for AppointmentMenu
void addAppointment(AppointmentOperations& apptOps){
    int patientID;
    string date, description;

    cout << endl;
    cout << "Enter Patient ID: ";
    cin >> patientID;
    cin.ignore();
    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter description: ";
    getline(cin, description);
    apptOps.addAppointment(patientID, date, description);
}

void viewAppointments(AppointmentOperations& apptOps){
    int patientID;
    cout << endl;
    cout << "Enter Patient ID to search: ";
    cin >> patientID;
    cin.ignore();

    apptOps.viewAppointments(patientID);
}

void rescheduleAppointment(AppointmentOperations& apptOps){
    int appointmentID;
    string date;

    cout << endl;
    cout << "Enter Appointment ID: ";
    cin >> appointmentID;
    cin.ignore();
    cout << "Enter the new Date: ";
    getline(cin, date);
    apptOps.rescheduleAppointment(appointmentID, date);
}

void cancelAppointment(AppointmentOperations& apptOps) {
    int appointmentID;
    char confirmation;

    cout << endl;
    cout << "Enter Appointment ID to cancel: ";
    cin >> appointmentID;
    cin.ignore();
    cout << "Enter (Y) to confirm cancelling Appointment ID (" << appointmentID << "): ";
    cin >> confirmation;
    cin.ignore(); // Clear newline character after char input

    if (toupper(confirmation) == 'Y') {
        apptOps.cancelAppointment(appointmentID);
    } else {
        cout << "Cancelling unsuccessful." << endl;
    }
}

// Function for Diagnostic Menu
void addDiagnostic(DiagnosticOperations& diagOps) {
    int patientID;
    string date, details, diagnosis;

    cout << endl;
    cout << "Enter Patient ID: ";
    cin >> patientID;
    cin.ignore();
    cout << "Enter Diagnosis Date (YYYY-MM-DD): ";
    getline(cin, date);
    cout << "Enter Details: ";
    getline(cin, details);
    cout << "Enter Diagnosis: ";
    getline(cin, diagnosis);

    diagOps.addDiagnostic(patientID, date, details, diagnosis);
}

void viewDiagnostics(DiagnosticOperations& diagOps) {
    int patientID;

    cout << endl;
    cout << "Enter Patient ID to view diagnostics: ";
    cin >> patientID;
    cin.ignore();

    diagOps.viewDiagnostics(patientID);
}

void updateDiagnostic(DiagnosticOperations& diagOps) {
    int diagnosticID;
    string newDiagnosis;

    cout << endl;
    cout << "Enter Diagnostic ID to update: ";
    cin >> diagnosticID;
    cin.ignore();
    cout << "Enter new Diagnosis: ";
    getline(cin, newDiagnosis);

    diagOps.updateDiagnostic(diagnosticID, newDiagnosis);
}
