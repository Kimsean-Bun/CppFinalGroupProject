#include "PatientOperations.h"
#include <iostream>
using namespace std;

PatientOperations::PatientOperations(DatabaseOperations& dbOps) : dbOps(dbOps) {}

int PatientOperations::addPatient(const string& name, const string& gender, 
                                  const string& dateOfBirth, const string& email, 
                                  const string& phoneNumber) {
    string sql = "INSERT INTO Patient (Name, Gender, DateOfBirth, Email, PhoneNumber) VALUES ('" + 
                      name + "', '" + gender + "', '" + dateOfBirth + "', '" + email + "', '" + phoneNumber + "');";

    if (dbOps.executeSQL(sql)) {
        int lastInsertId = sqlite3_last_insert_rowid(dbOps.getDatabase());
        cout << "Patient added successfully." << endl;
        cout << "Patient ID: " << lastInsertId << endl;
        return lastInsertId;
    } else {
        cerr << "Failed to add patient.\n";
        return -1;
    }
}

void PatientOperations::updatePatient(int id, const string& name, const string& gender, 
                                      const string& dateOfBirth, const string& email, 
                                      const string& phoneNumber) {
    string sql = "UPDATE Patient SET Name = '" + name + "', Gender = '" + gender +
                      "', DateOfBirth = '" + dateOfBirth + "', Email = '" + email + 
                      "', PhoneNumber = '" + phoneNumber + "' WHERE ID = " + to_string(id) + ";";
    
    if (dbOps.executeSQL(sql)) {
        cout << "Patient updated successfully.\n";
    } else {
        cerr << "Failed to update patient.\n";
    }
}

void PatientOperations::viewPatient(int id) {
    string sql = "SELECT * FROM Patient WHERE ID = " + to_string(id) + ";";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbOps.getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            cout << "ID: " << sqlite3_column_int(stmt, 0) << "\n"
                      << "Name: " << sqlite3_column_text(stmt, 1) << "\n"
                      << "Gender: " << sqlite3_column_text(stmt, 2) << "\n"
                      << "Date of Birth: " << sqlite3_column_text(stmt, 3) << "\n"
                      << "Email: " << sqlite3_column_text(stmt, 4) << "\n"
                      << "PhoneNumber: " << sqlite3_column_text(stmt, 5) << "\n";
        } else {
            cout << "No patient found with ID " << id << ".\n";
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Failed to retrieve patient information.\n";
    }
}

void PatientOperations::viewAllPatients(){
    string sql = "SELECT * FROM Patient;";
    dbOps.executeSQL(sql);
}

void PatientOperations::deletePatient(int id) {
    string sql = "DELETE FROM Patient WHERE ID = " + to_string(id) + ";";
    
    if (dbOps.executeSQL(sql)) {
        cout << "Patient deleted successfully.\n";
    } else {
        cerr << "Failed to delete patient.\n";
    }
}
