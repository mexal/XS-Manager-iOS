#import "sqlite3.h"
#import "Person.h"

class CommonLib
{
public:
    CommonLib(const char* fileName);
    ~CommonLib();
    int processDoors(const char* xml);
    int processPersons(const char* xml);
    int processPermissions(const char* xml);
    bool bindDoorToDevice(const char* doorNumber, const char* deviceUUID);
    
    Person** getPersons();
private:
    sqlite3* _database;
};