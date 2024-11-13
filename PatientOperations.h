#ifndef PATIENTOPERATIONS_H
#define PATIENTOPERATIONS_H

#include "DatabaseOperations.h"
#include <string>

using namespace std;

class PatientOperations {
public:
    PatientOperations(DatabaseOperations& dbOps); // Dependency injection of DatabaseOperations

    int addPatient(const string& name, const string& gender, const string& dateOfBirth,
                   const string& email, const string& phoneNumber);
    void updatePatient(int id, const string& name, const string& gender, const string& dateOfBirth,
                       const string& email, const string& phoneNumber);
    void viewPatient(int id);
    void viewAllPatients();
    void deletePatient(int id);

private:
    DatabaseOperations& dbOps; // Reference to shared DatabaseOperations instance
};

#endif
