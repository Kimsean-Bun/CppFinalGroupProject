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

void DatabaseOperations::createPatientTable(){
    string sql = "CREATE TABLE IF NOT EXISTS Patient ("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Name TEXT NOT NULL CHECK( Name != ''), "
                 "Gender TEXT CHECK(Gender IN ('M', 'F', 'NA')) NOT NULL, "
                 "DateOfBirth TEXT NOT NULL CHECK( DateOfBirth != ''), "
                 "Email TEXT, "
                 "PhoneNumber TEXT) STRICT;";
    executeSQL(sql);
}

void DatabaseOperations::createAppointmentTable(){
    string sql = "CREATE TABLE IF NOT EXISTS Appointment ("
                 "AppointmentID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "PatientID INTEGER NOT NULL CHECK( PatientID != ''), "
                 "Date TEXT NOT NULL CHECK( Date != ''), "
                 "Description TEXT, "
                 "FOREIGN KEY (PatientID) REFERENCES Patient(ID)) STRICT;";
    executeSQL(sql);
}

void DatabaseOperations::createDiagnosisTable(){
    string sql = "CREATE TABLE IF NOT EXISTS Diagnosis ("
        "DiagnosticID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "PatientID INTEGER NOT NULL CHECK( PatientID != ''), "
        "DiagnosisDate TEXT NOT NULL CHECK( DiagnosisDate != ''), "
        "Details TEXT NOT NULL CHECK( Details != ''), "
        "Diagnosis TEXT,"
        "FOREIGN KEY(PatientID) REFERENCES Patient(ID)) STRICT; ";
    executeSQL(sql);
}
