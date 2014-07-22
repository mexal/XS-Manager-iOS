#import "sqlite3.h" // лучше перенести подключение sqllite в .cpp. Будет меньше зависимостей. В .h можно написать перед классом где используется  
                    // class sqlite;
                    // но это прокатит, только если в .h используется указатель или ссылка на этот класс. Если по значению, то не прокатит
#import "Person.h" // #import - это, наверное, из Objective C. Это точно не кросплатформенно. Используй #include
#import "Door.h"
#import "Permission.h"

class CommonLib
{
public:
    CommonLib(const char* fileName);
    ~CommonLib();
    
    int processDoors(const char* xml);
    int processPersons(const char* xml);
    int processPermissions(const char* xml);
    
    bool bindDoorToDevice(const char* doorNumber, const char* deviceUUID);
    
    int getPersonsLength();
    void getPersons(Person* arr);
    
    int getDoorsLength();
    void getDoors(Door* arr);
    
    int getPermissionsLength();
    void getPermissions(Permission* arr);
    
    
protected:
    void createTable(const char* sql);
    int getEntriesCount(char* tableName);
private:
    sqlite3* _database;
};
