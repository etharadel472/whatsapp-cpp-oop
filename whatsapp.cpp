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
        sender = "";
        content = "";
        timestamp = "";
        status = "";
        replyTo = nullptr;
    }
    
    Message(string sndr, string cntnt) {
        sender = sndr;
        content = cntnt;
        status = "sent";
        replyTo = nullptr;
        updateTimestamp();
    }
    
    string getContent() const {
        return content;
    }
    
    string getSender() const {
        return sender;
    }
    
    string getTimestamp() const {
        return timestamp;
    }
    
    string getStatus() const {
        return status;
    }
    
    Message* getReplyTo() const {
        return replyTo;
    }
    
    void setStatus(string newStatus) {
        if (newStatus == "sent" || newStatus == "delivered" || newStatus == "read") {
            status = newStatus;
        }
    }
    
    void setReplyTo(Message* msg) {
        replyTo = msg;
    }
    
    void updateTimestamp() {
        time_t current_time = time(nullptr);
        char* time_string = ctime(&current_time);
        timestamp = time_string;
        if (!timestamp.empty() && timestamp.back() == '\n') {
            timestamp.pop_back();
        }
    }
    
    void display() const {
        if (replyTo != nullptr) {
            cout << "  -> Replying to " << replyTo->getSender() << ": \"" << replyTo->getContent() << "\"" << endl;
        }
        cout << "[" << timestamp << "] " << sender << ": " << content << " (" << status << ")" << endl;
    }
    
    void addEmoji(string emojiCode) {
        string emoji = "";
        if (emojiCode == ":)") {
            emoji = "😊";
        }
        else if (emojiCode == ":(") {
            emoji = "😢";
        }
        else if (emojiCode == ":D") {
            emoji = "😃";
        }
        else if (emojiCode == "<3") {
            emoji = "❤️";
        }
        else if (emojiCode == ":thumbsup:") {
            emoji = "👍";
        }
        else {
            return;
        }

        size_t pos = 0;
        while ((pos = content.find(emojiCode, pos)) != string::npos) {
            content.replace(pos, emojiCode.length(), emoji);
            pos += emoji.length();
        }
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
        chatName = "";
    }

    Chat(vector<string> users, string name) {
        participants = users;
        chatName = name;
    }

    virtual ~Chat() {}

    void addMessage(const Message& msg) {
        vector<int> replyIndexes(messages.size() + 1, -1);

        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            for (int j = 0; j < static_cast<int>(messages.size()); j++) {
                if (messages[i].getReplyTo() == &messages[j]) {
                    replyIndexes[i] = j;
                    break;
                }
            }
        }

        for (int j = 0; j < static_cast<int>(messages.size()); j++) {
            if (msg.getReplyTo() == &messages[j]) {
                replyIndexes[messages.size()] = j;
                break;
            }
        }

        Message newMessage = msg;
        messages.push_back(newMessage);

        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            if (replyIndexes[i] != -1) {
                messages[i].setReplyTo(&messages[replyIndexes[i]]);
            }
        }
    }

    bool deleteMessage(int index, const string& username) {
        if (index < 0 || index >= static_cast<int>(messages.size())) {
            return false;
        }

        if (messages[index].getSender() != username) {
            return false;
        }

        vector<int> replyIndexes(messages.size(), -1);

        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            for (int j = 0; j < static_cast<int>(messages.size()); j++) {
                if (messages[i].getReplyTo() == &messages[j]) {
                    replyIndexes[i] = j;
                    break;
                }
            }
        }

        messages.erase(messages.begin() + index);

        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            int oldIndex = i < index ? i : i + 1;
            int replyIndex = replyIndexes[oldIndex];

            if (replyIndex == index) {
                messages[i].setReplyTo(nullptr);
            }
            else if (replyIndex != -1) {
                if (replyIndex > index) {
                    replyIndex--;
                }
                messages[i].setReplyTo(&messages[replyIndex]);
            }
        }

        return true;
    }

    virtual void displayChat() const {
        cout << "\n===== " << chatName << " =====\n";

        if (messages.empty()) {
            cout << "No messages yet.\n";
            return;
        }

        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            cout << i + 1 << ". ";
            messages[i].display();
        }
    }

    vector<Message> searchMessages(string keyword) const {
        vector<Message> results;
        vector<int> originalIndexes;

        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            if (messages[i].getContent().find(keyword) != string::npos) {
                results.push_back(messages[i]);
                originalIndexes.push_back(i);
            }
        }

        for (int i = 0; i < static_cast<int>(results.size()); i++) {
            for (int j = 0; j < static_cast<int>(messages.size()); j++) {
                if (results[i].getReplyTo() == &messages[j]) {
                    Message* reply = nullptr;

                    for (int k = 0; k < static_cast<int>(originalIndexes.size()); k++) {
                        if (originalIndexes[k] == j) {
                            reply = &results[k];
                            break;
                        }
                    }

                    results[i].setReplyTo(reply);
                    break;
                }
            }
        }

        return results;
    }

    void exportToFile(const string& filename) const {
        ofstream file(filename);

        if (!file.is_open()) {
            cout << "Could not open file.\n";
            return;
        }

        file << "Chat: " << chatName << "\n";

        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            file << "[" << messages[i].getTimestamp() << "] "
                 << messages[i].getSender() << ": "
                 << messages[i].getContent() << " ("
                 << messages[i].getStatus() << ")\n";
        }

        file.close();
        cout << "Chat exported successfully.\n";
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
