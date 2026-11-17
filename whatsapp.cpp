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
        sender = "";
        content = "";
        timestamp = "";
        status = "";
        replyTo = nullptr;
    }
    
    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
        sender = sndr;
        content = cntnt;
        status = "sent";
        replyTo = nullptr;
        updateTimestamp();
    }
    
    string getContent() const {
        // TODO: Implement getter
        return content;
    }
    
    string getSender() const {
        // TODO: Implement getter
        return sender;
    }
    
    string getTimestamp() const {
        // TODO: Implement getter
        return timestamp;
    }
    
    string getStatus() const {
        // TODO: Implement getter
        return status;
    }
    
    Message* getReplyTo() const {
        // TODO: Implement getter
        return replyTo;
    }
    
    void setStatus(string newStatus) {
        // TODO: Implement setter
        if (newStatus == "sent" || newStatus == "delivered" || newStatus == "read") {
            status = newStatus;
        }
    }
    
    void setReplyTo(Message* msg) {
        // TODO: Implement setter
        replyTo = msg;
    }
    
    void updateTimestamp() {
        // TODO: Implement timestamp update
        time_t current_time = time(nullptr);
        char* time_string = ctime(&current_time);
        timestamp = time_string;
        if (!timestamp.empty() && timestamp.back() == '\n') {
            timestamp.pop_back();
        }
    }
    
    void display() const {
        // TODO: Implement message display
        if (replyTo != nullptr) {
            cout << "  -> Replying to " << replyTo->getSender() << ": \"" << replyTo->getContent() << "\"" << endl;
        }
        cout << "[" << timestamp << "] " << sender << ": " << content << " (" << status << ")" << endl;
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
        return -1;
    }
    
    bool isLoggedIn() const {
        // TODO: Implement login check
        return false;
    }
    
    string getCurrentUsername() const {
        // TODO: Implement get current user
        return "";
    }
    // --- END: YOUSSEF [KAN-6] (Account Helper Methods) ---
    
public:
    WhatsApp() : currentUserIndex(-1) {}
    
    // --- START: YOUSSEF [KAN-6] (SignUp, Login, Logout) ---
    void signUp() {
        // TODO: Implement user registration
    }
    
    void login() {
        // TODO: Implement user login
    }
    
    void logout() {
        // TODO: Implement logout
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
