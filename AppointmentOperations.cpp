#include "AppointmentOperations.h"
#include <iostream>
using namespace std;

AppointmentOperations::AppointmentOperations(DatabaseOperations& dbOps) : dbOps(dbOps) {}

void AppointmentOperations::addAppointment(int patientID, const string& date, const string& description) {
    string sql = "INSERT INTO Appointment (PatientID, Date, Description) VALUES (" +
                      to_string(patientID) + ", '" + date + "', '" + description + "');";
    
    if (dbOps.executeSQL(sql)) {
        int lastInsertId = sqlite3_last_insert_rowid(dbOps.getDatabase());
        cout << "Appointment booked successfully." << endl;
        cout << "Appointment ID: " << lastInsertId << endl;
    } else {
        cerr << "Failed to book an appointment.\n";
    }
}

void AppointmentOperations::viewAppointments(int patientID) {
    string sql = "SELECT AppointmentID, Date, Description FROM Appointment WHERE PatientID = " + to_string(patientID) + ";";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbOps.getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        cout << "Appointments for Patient ID " << patientID << ":\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int appointmentID = sqlite3_column_int(stmt, 0);
            const unsigned char* date = sqlite3_column_text(stmt, 1);
            const unsigned char* description = sqlite3_column_text(stmt, 2);

            cout << "ID: " << appointmentID << ", Date: " << date << ", Description: " << description << endl;
        }
        sqlite3_finalize(stmt);
    } else {
        cerr << "Failed to retrieve appointments.\n";
    }
}

void AppointmentOperations::rescheduleAppointment(int appointmentID, const::string& date){
    string sql ="UPDATE Appointment SET Date =  '" + date + "' WHERE AppointmentID = " + to_string(appointmentID) + ";";
    
    if (dbOps.executeSQL(sql)) {
        cout << "Appointment reschedule successfully.\n";
    } else {
        cerr << "Failed to update patient.\n";
    }
}

void AppointmentOperations::cancelAppointment(int appointmentID) {
    string sql = "UPDATE Appointment SET Description = 'Cancelled' WHERE AppointmentID = " + to_string(appointmentID) + ";";
    
    if (dbOps.executeSQL(sql)) {
        cout << "Appointment canceled successfully.\n";
    } else {
        cerr << "Failed to cancel the appointment.\n";
    }
}
