#include "DatabaseOperations.h"
#include <iostream>
using namespace std;

int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

DatabaseOperations::DatabaseOperations(const string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db)) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        db = nullptr;
    } else {
        cout << "Opened database successfully." << endl;
        // Ensure the tables is created
        createPatientTable();
        createAppointmentTable();
        createDiagnosisTable();
    }
}

DatabaseOperations::~DatabaseOperations() {
    closeConnection();
}

void DatabaseOperations::openConnection(const string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
    }
}

void DatabaseOperations::closeConnection() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseOperations::executeSQL(const string& sql) {
    char* errorMessage = 0;
    // Enable foreign key enforcement first
    int exit = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "SQL error (PRAGMA): " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }

    exit = sqlite3_exec(db, sql.c_str(), callback, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        cerr << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

sqlite3* DatabaseOperations::getDatabase() {
    return db;
}

void DatabaseOperations::createAppointmentTable(){
    string sql = "CREATE TABLE IF NOT EXISTS Patient ("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Name TEXT NOT NULL, "
                 "Gender TEXT CHECK(Gender IN ('M', 'F', 'NA')), "
                 "DateOfBirth DATE, "
                 "Email TEXT, "
                 "PhoneNumber TEXT);";
    executeSQL(sql);
}

void DatabaseOperations::createPatientTable(){
    string sql = "CREATE TABLE IF NOT EXISTS Appointment ("
                 "AppointmentID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "PatientID INTEGER, "
                 "Date TEXT, "
                 "Description TEXT, "
                 "FOREIGN KEY (PatientID) REFERENCES Patient(ID));";
    executeSQL(sql);
}

void DatabaseOperations::createDiagnosisTable(){
    string sql = "CREATE TABLE IF NOT EXISTS Diagnosis ("
        "DiagnosticID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "PatientID INTEGER, "
        "DiagnosisDate DATE NOT NULL, "
        "Details TEXT, "
        "Diagnosis TEXT,"
        "FOREIGN KEY(PatientID) REFERENCES Patient(ID)); ";
    executeSQL(sql);
}
