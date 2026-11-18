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
private:
    // parallel to `chats`: members and display name of each chat
    vector<vector<string> > chatMembers;
    vector<string> chatNames;

    bool isMemberOfChat(size_t i, const string& username) const {
        for (size_t j = 0; j < chatMembers[i].size(); j++)
            if (chatMembers[i][j] == username) return true;
        return false;
    }

public:
    WhatsApp(const WhatsApp&) = delete;            
    WhatsApp& operator=(const WhatsApp&) = delete;

    ~WhatsApp() {
        for (size_t i = 0; i < chats.size(); i++)
            delete chats[i];
        chats.clear();
    }

    void startPrivateChat() {
        if (!isLoggedIn()) { cout << "Please login first.\n"; return; }

        string other;
        cout << "Enter the username you want to chat with: ";
        getline(cin, other);

        int idx = findUserIndex(other);
        if (idx == -1) { cout << "Error: user not found.\n"; return; }
        if (idx == currentUserIndex) { cout << "Error: you can't chat with yourself.\n"; return; }

        string me = getCurrentUsername();

        // don't create a duplicate private chat
        for (size_t i = 0; i < chats.size(); i++) {
            if (dynamic_cast<PrivateChat*>(chats[i]) == nullptr) continue;
            if (isMemberOfChat(i, me) && isMemberOfChat(i, other)) {
                cout << "You already have a chat with " << other << ".\n";
                return;
            }
        }

        chats.push_back(new PrivateChat(me, other));
        chatMembers.push_back(vector<string>{me, other});
        chatNames.push_back("Chat between " + me + " and " + other);
        users[currentUserIndex].updateLastSeen();
        cout << "Private chat with " << other << " created.\n";
    }

    void createGroup() {
        if (!isLoggedIn()) { cout << "Please login first.\n"; return; }

        string name;
        cout << "Enter group name: ";
        getline(cin, name);
        if (name.empty()) { cout << "Error: group name can't be empty.\n"; return; }

        string me = getCurrentUsername();
        vector<string> members;
        cout << "Enter member usernames one per line (empty line to finish):\n";
        while (true) {
            string u;
            if (!getline(cin, u) || u.empty()) break;
            if (u == me) { cout << "You are added automatically as admin.\n"; continue; }
            if (findUserIndex(u) == -1) { cout << "User '" << u << "' not found, skipped.\n"; continue; }
            if (find(members.begin(), members.end(), u) != members.end()) {
                cout << "Already added.\n";
                continue;
            }
            members.push_back(u);
        }

        if (members.size() < 2) {
            cout << "Error: a group needs at least 2 participants.\n";
            return;
        }

        // GroupChat constructor adds the creator to participants and admins
        chats.push_back(new GroupChat(members, name, me));

        vector<string> all = members;
        all.push_back(me);
        chatMembers.push_back(all);
        chatNames.push_back(name);

        users[currentUserIndex].updateLastSeen();
        cout << "Group '" << name << "' created. You are the admin.\n";
    }

    void viewChats() const {
        if (!isLoggedIn()) { cout << "Please login first.\n"; return; }

        string me = getCurrentUsername();
        bool found = false;
        for (size_t i = 0; i < chats.size(); i++) {
            if (!isMemberOfChat(i, me)) continue;   
            found = true;
            cout << "\n=== " << chatNames[i] << " ===\n";
            chats[i]->displayChat();              
        }
        if (!found) cout << "You have no chats yet.\n";
    }

    void run() {
        while (true) {
            int choice;
            if (!isLoggedIn())
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
            else
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";

            if (!(cin >> choice)) {
                if (cin.eof()) break;               
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input, please enter a number.\n";
                continue;
            }
            cin.ignore(10000, '\n');               

            if (!isLoggedIn()) {
                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
                else cout << "Invalid option.\n";
            } else {
                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
                else cout << "Invalid option.\n";
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
