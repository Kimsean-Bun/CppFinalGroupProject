#ifndef DIAGNOSTICOPERATIONS_H
#define DIAGNOSTICOPERATIONS_H

#include "DatabaseOperations.h"
#include <string>
using namespace std;

class DiagnosticOperations {
public:
    DiagnosticOperations(DatabaseOperations& dbOps);

    int addDiagnostic(int patientID, const string& diagnosisDate, const string& details, const string& Diagnosis);
    void viewDiagnostics(int patientID);
    void updateDiagnostic(int diagnosticID, const string& Diagnosis);

private:
    DatabaseOperations& dbOps; // Reference to DatabaseOperations instance
};

#endif
