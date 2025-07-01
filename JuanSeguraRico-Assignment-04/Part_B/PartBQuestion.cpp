//
// Created by Juan Segura Rico on 7/25/23.
//

#include "PartBQuestion.h"
#include <iostream>
#include <memory> // Include the smart pointer library

class Person {
public:
    Person(const std::string& name) : name_(name) {
        std::cout << "Person " << name_ << " created." << std::endl;
    }

    ~Person() {
        std::cout << "Person " << name_ << " destroyed." << std::endl;
    }

    void introduce() const {
        std::cout << "Hi, I'm " << name_ << "." << std::endl;
    }

private:
    std::string name_;
};

int main() {
    // Using std::unique_ptr for exclusive ownership
    std::unique_ptr<Person> personUnique = std::make_unique<Person>("Alice");

    // Using std::shared_ptr for shared ownership
    std::shared_ptr<Person> personShared1 = std::make_shared<Person>("Bob");
    std::shared_ptr<Person> personShared2 = personShared1; // Share ownership

    // Using std::weak_ptr to avoid circular dependency and dangling pointers
    std::shared_ptr<Person> personShared3 = std::make_shared<Person>("Charlie");
    std::weak_ptr<Person> personWeak = personShared3;

    // Using unique_ptr with dynamic arrays
    std::unique_ptr<int[]> arrUnique = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        arrUnique[i] = i + 1;
    }

    // Outputting information
    personUnique->introduce();
    personShared1->introduce();
    personShared2->introduce();

    // Accessing the resource via weak_ptr
    if (auto sharedPtr = personWeak.lock()) {
        sharedPtr->introduce();
    } else {
        std::cout << "Person has been deleted." << std::endl;
    }

    // unique_ptr for arrays
    for (int i = 0; i < 5; ++i) {
        std::cout << "Element " << i << ": " << arrUnique[i] << std::endl;
    }

    return 0;
}
