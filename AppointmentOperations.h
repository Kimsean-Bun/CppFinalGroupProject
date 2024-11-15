#ifndef APPOINTMENTOPERATIONS_H
#define APPOINTMENTOPERATIONS_H

#include "DatabaseOperations.h"
#include <string>
using namespace std;

class AppointmentOperations {
public:
    AppointmentOperations(DatabaseOperations& dbOps); // Dependency injection of DatabaseOperations

    void addAppointment(int patientID, const string& date, const string& description);
    void rescheduleAppointment(int appointmentID, const string& date);
    void cancelAppointment(int appointmentID);
    void viewAppointments(int patientID);

private:
    DatabaseOperations& dbOps; // Reference to shared DatabaseOperations instance
};

#endif
