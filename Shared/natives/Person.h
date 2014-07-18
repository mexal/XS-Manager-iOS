//class Person
//{
//    Person(const char* number, const char* name){
//        this->number = number;
//        this->name = name;
//    };
//    ~Person(){};
//private:
//    const char* number;
//    const char* name;
//public:
//    const char* getNumber() {
//        return number;
//    }
//    
//    const char* getName() {
//        return name;
//    }
//};

struct Person {
    const unsigned char* number;
    const unsigned char* name;
};