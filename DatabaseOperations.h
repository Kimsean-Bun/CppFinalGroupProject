#ifndef DATABASEOPERATIONS_H
#define DATABASEOPERATIONS_H

#include <sqlite3.h>
#include <string>

class DatabaseOperations {
public:
    DatabaseOperations(const std::string& dbName);
    ~DatabaseOperations();
    
    bool executeSQL(const std::string& sql);
    sqlite3* getDatabase(); // Getter to access the database connection

private:
    sqlite3* db;
    void createAppointmentTable();
    void createPatientTable();
    void createDiagnosisTable();
    void openConnection(const std::string& dbName);
    void closeConnection();
};

#endif
