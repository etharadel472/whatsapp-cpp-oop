#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
using namespace std;

// =========================================================================
// [KAN-1] ASSIGNED TO: MAZEN  |  USER CLASS
// RULE: Write your code ONLY between START and END markers below.
// =========================================================================
// --- START: MAZEN (User Class) ---
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User() {
        // TODO: Implement default constructor
    }

    User(string uname, string pwd, string phone) {
        // TODO: Implement parameterized constructor
    }

    string getUsername() const {
        // TODO: Implement getter
        return "";
    }

    string getPhoneNumber() const {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const {
        // TODO: Implement getter
        return "";
    }

    string getLastSeen() const {
        // TODO: Implement getter
        return "";
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
    }

    void setPhoneNumber(string phone) {
        // TODO: Implement setter
    }

    void updateLastSeen() {
        // TODO: Implement last seen update
    }

    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        return false;
    }

    void changePassword(string newPwd) {
        // TODO: Implement password change
    }
};
// --- END: MAZEN (User Class) ---


// =========================================================================
// [KAN-2] ASSIGNED TO: KARIM  |  MESSAGE CLASS
// RULE: Write your code ONLY between START and END markers below.
// =========================================================================
// --- START: KARIM (Message Class) ---
class Message {
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;

public:
    Message() {
        // TODO: Implement default constructor
    }

    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
    }

    string getContent() const {
        // TODO: Implement getter
        return "";
    }

    string getSender() const {
        // TODO: Implement getter
        return "";
    }

    string getTimestamp() const {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const {
        // TODO: Implement getter
        return "";
    }

    Message* getReplyTo() const {
        // TODO: Implement getter
        return nullptr;
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
    }

    void setReplyTo(Message* msg) {
        // TODO: Implement setter
    }

    void updateTimestamp() {
        // TODO: Implement timestamp update
    }

    void display() const {
        // TODO: Implement message display
    }

    void addEmoji(string emojiCode) {
        // TODO: Implement emoji support
    }
};
// --- END: KARIM (Message Class) ---


// =========================================================================
// [KAN-3] ASSIGNED TO: RAHMA  |  CHAT CLASS (BASE)
// RULE: Write your code ONLY between START and END markers below.
// =========================================================================
// --- START: RAHMA (Chat Base Class) ---
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat() {
        // TODO: Implement default constructor
    }

    Chat(vector<string> users, string name) {
        // TODO: Implement parameterized constructor
    }

    virtual ~Chat() {}

    void addMessage(const Message& msg) {
        // TODO: Implement message addition
    }

    bool deleteMessage(int index, const string& username) {
        // TODO: Implement message deletion
        return false;
    }

    virtual void displayChat() const {
        // TODO: Implement chat display
    }

    vector<Message> searchMessages(string keyword) const {
        // TODO: Implement message search
        return {};
    }

    void exportToFile(const string& filename) const {
        // TODO: Implement export to file
    }
};
// --- END: RAHMA (Chat Base Class) ---


// =========================================================================
// [KAN-4] ASSIGNED TO: IBRAHEEM  |  PRIVATE CHAT CLASS (+ TC1-TC5 QA)
// RULE: Write your code ONLY between START and END markers below.
// =========================================================================
// --- START: IBRAHEEM (PrivateChat Class) ---
class PrivateChat : public Chat {
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2) {
        // TODO: Implement constructor
    }

    void displayChat() const override {
        // TODO: Implement private chat display
    }

    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
    }
};
// --- END: IBRAHEEM (PrivateChat Class) ---


// =========================================================================
// [KAN-5] ASSIGNED TO: ETHAR  |  GROUP CHAT CLASS
// RULE: Write your code ONLY between START and END markers below.
// =========================================================================
// --- START: ETHAR (GroupChat Class) ---
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator) {
        // TODO: Implement constructor
    }

    void addAdmin(string newAdmin) {
        // TODO: Implement add admin
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        // TODO: Implement remove participant
        return false;
    }

    bool isAdmin(string username) const {
        // TODO: Implement admin check
        return false;
    }

    bool isParticipant(string username) const {
        // TODO: Implement participant check
        return false;
    }

    void setDescription(string desc) {
        // TODO: Implement set description
    }

    void displayChat() const override {
        // TODO: Implement group chat display
    }

    void sendJoinRequest(const string& username) {
        // TODO: Implement join request
    }
};
// --- END: ETHAR (GroupChat Class) ---


// =========================================================================
// [KAN-6 & KAN-7] WHATSAPP APP CLASS (SPLIT BETWEEN YOUSSEF & SHAHD)
// RULE: Each member edits ONLY inside their marked section below.
// =========================================================================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    // --- START: YOUSSEF [KAN-6] (Account Helper Methods) ---
    int findUserIndex(string username) const {
        // TODO: Implement user search
        for (int i = 0; i < users.size(); i++) {
        if (users[i].getUsername() == username) {
            return i;
        }
    }
        return -1;
    }

    bool isLoggedIn() const {
        // TODO: Implement login check
           return currentUserIndex >= 0 &&
           currentUserIndex < users.size();
    }

    string getCurrentUsername() const {
         if (!isLoggedIn()) {
        return "";
    }

    return users[currentUserIndex].getUsername();
    }
    // --- END: YOUSSEF [KAN-6] (Account Helper Methods) ---

public:
    WhatsApp() : currentUserIndex(-1) {}

    // --- START: YOUSSEF [KAN-6] (SignUp, Login, Logout) ---
    void signUp() {
        // TODO: Implement user registration
        string username, password, phone;

    cout << "Enter username: ";
    cin >> username;

    if (findUserIndex(username) != -1) {
        cout << "Username already exists!\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (password.length() < 6) {
        cout << "Password must be at least 6 characters!\n";
        return;
    }

    cout << "Enter phone number: ";
    cin >> phone;

    users.push_back(User(username, password, phone));

    cout << "Account created successfully!\n";
    }

    void login() {
        // TODO: Implement user login
          string username, password;

    cout << "Enter username: ";
    cin >> username;

    int index = findUserIndex(username);

    if (index == -1) {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (users[index].checkPassword(password)) {
        currentUserIndex = index;
        cout << "Login successful!\n";
    }
    else {
        cout << "Incorrect password!\n";
    }
    }

    void logout() {
        // TODO: Implement logout
        if (!isLoggedIn()) {
        cout << "No user is logged in!\n";
        return;
    }

    users[currentUserIndex].updateLastSeen();
    currentUserIndex = -1;

    cout << "Logged out successfully!\n";
    }
    // --- END: YOUSSEF [KAN-6] (SignUp, Login, Logout) ---


    // --- START: SHAHD [KAN-7] (Chats Management, Destructor & Menu) ---
    ~WhatsApp() {
        // TODO: Delete all dynamically allocated Chat* pointers in chats vector
    }

    void startPrivateChat() {
        // TODO: Implement private chat creation
    }

    void createGroup() {
        // TODO: Implement group creation
    }

    void viewChats() const {
        // TODO: Implement chat viewing
    }

    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
// --- END: SHAHD [KAN-7] (Chats Management, Destructor & Menu) ---
