#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Resource {
protected:
    string name;
    bool isAvailable;

public:
    string resourceID;
    Resource(const string& id, const string& n, bool avail = true)
        : resourceID(id), name(n), isAvailable(avail) {}

    virtual ~Resource() {}

    virtual void showDetails() const = 0;
    virtual bool isResourceAvailable() const = 0;
    virtual void borrowResource() = 0;
    virtual void returnResource() = 0;
};

class Textbook : public Resource {
private:
    string writer;
    string isbnCode;

public:
    Textbook(const string& id, const string& n, const string& w, const string& isbn)
        : Resource(id, n), writer(w), isbnCode(isbn) {}

    void showDetails() const override {
        cout << "Textbook ID: " << resourceID << "\nName: " << name
            << "\nWriter: " << writer << "\nISBN: " << isbnCode
            << "\nAvailability: " << (isAvailable ? "Available" : "Unavailable") << endl;
    }

    bool isResourceAvailable() const override {
        return isAvailable;
    }

    void borrowResource() override {
        if (isAvailable) {
            isAvailable = false;
            cout << "Textbook borrowed successfully.\n";
        }
        else {
            cout << "Textbook is currently unavailable.\n";
        }
    }

    void returnResource() override {
        isAvailable = true;
        cout << "Textbook returned successfully.\n";
    }
};

class Magazine : public Resource {
private:
    string publication;
    int editionNumber;

public:
    Magazine(const string& id, const string& n, const string& pub, int edition)
        : Resource(id, n), publication(pub), editionNumber(edition) {}

    void showDetails() const override {
        cout << "Magazine ID: " << resourceID << "\nName: " << name
            << "\nPublication: " << publication << "\nEdition Number: " << editionNumber
            << "\nAvailability: " << (isAvailable ? "Available" : "Unavailable") << endl;
    }

    bool isResourceAvailable() const override {
        return isAvailable;
    }

    void borrowResource() override {
        if (isAvailable) {
            isAvailable = false;
            cout << "Magazine borrowed successfully.\n";
        }
        else {
            cout << "Magazine is currently unavailable.\n";
        }
    }

    void returnResource() override {
        isAvailable = true;
        cout << "Magazine returned successfully.\n";
    }
};

class User {
private:
    string userID;
    string userName;
    string contactDetails;
    int maxLoans;
    vector<string> borrowedResources;

public:
    User(const string& id, const string& name, const string& contact, int max)
        : userID(id), userName(name), contactDetails(contact), maxLoans(max) {}

    void borrowResource(Resource& resource) {
        if (borrowedResources.size() < maxLoans) {
            if (resource.isResourceAvailable()) {
                resource.borrowResource();
                borrowedResources.push_back(resource.resourceID);
                cout << userName << " borrowed resource: " << resource.resourceID << "\n";
            }
            else {
                cout << "Resource is not available for borrowing.\n";
            }
        }
        else {
            cout << "Reached the maximum borrowing limit.\n";
        }
    }

    void returnResource(Resource& resource) {
        resource.returnResource();
        for (size_t i = 0; i < borrowedResources.size(); ++i) {
            if (borrowedResources[i] == resource.resourceID) {
                borrowedResources.erase(borrowedResources.begin() + i);
                break;
            }
        }
        cout << userName << " returned resource: " << resource.resourceID << "\n";
    }

    void showBorrowedResources() const {
        cout << "Borrowed Resources of " << userName << ":\n";
        for (const auto& id : borrowedResources) {
            cout << id << "\n";
        }
    }
};

class BorrowRecord {
private:
    string recordID;
    Resource& resource;
    User& user;
    int dueDay; // due date represented in days
    int actualReturnDay;

public:
    BorrowRecord(const string& id, Resource& res, User& usr, int due)
        : recordID(id), resource(res), user(usr), dueDay(due), actualReturnDay(0) {}

    void recordReturn(int returnDay) {
        actualReturnDay = returnDay;
        resource.returnResource();
    }

    double computeFine() const {
        if (actualReturnDay > dueDay) {
            double fineRate = 1.0; // fine rate per day
            int daysOverdue = actualReturnDay - dueDay;
            return daysOverdue * fineRate;
        }
        return 0.0;
    }
};


int main()
{
    Textbook textbook1("T001", "C++ Guide", "Bjarne Stroustrup", "987-654-321");
    Magazine magazine1("M001", "ACM Computing Surveys", "ACM", 25);

    User user1("U001", "Bob", "bob@example.com", 3);

    textbook1.showDetails();
    magazine1.showDetails();

    user1.borrowResource(textbook1);
    user1.showBorrowedResources();

    user1.returnResource(textbook1);
    user1.showBorrowedResources();

    return 0;
}
