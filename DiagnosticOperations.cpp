#include "DiagnosticOperations.h"
#include <iostream>
using namespace std;

DiagnosticOperations::DiagnosticOperations(DatabaseOperations& dbOps) : dbOps(dbOps) {}

int DiagnosticOperations::addDiagnostic(int patientID, const string& diagnosisDate, const string& details, const string& diagnosis) {
    string sql = "INSERT INTO Diagnosis (PatientID, DiagnosisDate, Details, Diagnosis) VALUES (" +
                      to_string(patientID) + ", '" + diagnosisDate + "', '" + details + "', '" + diagnosis + "');";

    if (dbOps.executeSQL(sql)) {
        int lastInsertId = sqlite3_last_insert_rowid(dbOps.getDatabase());
        cout << "Diagnostic record added Successfully." << endl;
        cout << "Diagnostic ID: " << lastInsertId << endl;
        return lastInsertId;
    } else {
        cerr << "Failed to add diagnostic record.\n";
        return -1; // Indicate failure
    }
}

void DiagnosticOperations::viewDiagnostics(int patientID)
{
    string sql = "SELECT * FROM Diagnosis WHERE PatientID = " + to_string(patientID) + ";";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbOps.getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "Diagnostics for Patient ID " << patientID << ":\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int diagnosticID = sqlite3_column_int(stmt, 0);
            const unsigned char* date = sqlite3_column_text(stmt, 2);
            const unsigned char* details = sqlite3_column_text(stmt, 3);
            const unsigned char* diagnosis = sqlite3_column_text(stmt, 4);

            cout << "Diagnostic ID: " << diagnosticID << "\n"
                      << "Date: " << date << "\n"
                      << "Details: " << details << "\n"
                      << "Diagnosis: " << diagnosis << "\n\n";
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Failed to retrieve diagnostics.\n";
    }
}

void DiagnosticOperations::updateDiagnostic(int diagnosticID, const string& diagnosis) {
    string sql = "UPDATE Diagnosis SET Diagnosis = '" + diagnosis +
                      "' WHERE DiagnosisID = " + to_string(diagnosticID) + ";";

    if (dbOps.executeSQL(sql)) {
        cout << "Diagnostic record updated successfully.\n";
    } else {
        cerr << "Failed to update diagnostic record.\n";
    }
}
