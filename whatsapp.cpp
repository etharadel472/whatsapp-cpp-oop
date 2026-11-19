#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
#endif
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
    User() : status("Offline") {
        updateLastSeen();
    }

    User(string uname, string pwd, string phone)
        : username(uname), password(pwd), phoneNumber(phone), status("Offline") {
        updateLastSeen();
    }

    string getUsername() const { return username; }
    string getPhoneNumber() const { return phoneNumber; }
    string getStatus() const { return status; }
    string getLastSeen() const { return lastSeen; }

    void setStatus(string newStatus) {
        status = newStatus;
        updateLastSeen();
    }

    void setPhoneNumber(string phone) {
        phoneNumber = phone;
        updateLastSeen();
    }

    void updateLastSeen() {
        time_t now = time(nullptr);
        char* dt = ctime(&now);
        if (dt != nullptr) {
            lastSeen = dt;
            if (!lastSeen.empty() && lastSeen.back() == '\n') {
                lastSeen.pop_back();
            }
        }
    }

    bool checkPassword(string pwd) const {
        return password == pwd;
    }

    bool changePassword(string newPwd) {
        if (newPwd.length() < 6) return false;
        password = newPwd;
        updateLastSeen();
        return true;
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
            emoji = "\xF0\x9F\x98\x8A"; // 😊
        }
        else if (emojiCode == ":(") {
            emoji = "\xF0\x9F\x98\xA2"; // 😢
        }
        else if (emojiCode == ":D") {
            emoji = "\xF0\x9F\x98\x83"; // 😃
        }
        else if (emojiCode == "<3") {
            emoji = "\xE2\x9D\xA4\xEF\xB8\x8F"; // ❤️
        }
        else if (emojiCode == ":thumbsup:") {
            emoji = "\xF0\x9F\x91\x8D"; // 👍
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

    Message* getMessagePtr(int index) {
        if (index < 0 || index >= static_cast<int>(messages.size())) {
            return nullptr;
        }
        return &messages[index];
    }

    void markAsDelivered(const string& receiver) {
        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            if (messages[i].getSender() != receiver && messages[i].getStatus() == "sent") {
                messages[i].setStatus("delivered");
            }
        }
    }

    void markAsRead(const string& reader) {
        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            if (messages[i].getSender() != reader && messages[i].getStatus() != "read") {
                messages[i].setStatus("read");
            }
        }
    }

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
        user1 = u1;
        user2 = u2;
        participants.push_back(u1);
        participants.push_back(u2);
        chatName = "Chat between " + u1 + " and " + u2;
    }

    void displayChat() const override {
        Chat::displayChat();
    }

    void showTypingIndicator(const string& username) const {
        cout << username << " is typing..." << endl;
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
    vector<string> joinRequests;

public:
    GroupChat(vector<string> users, string name, string creator) : Chat(users, name) {
        admins.push_back(creator);
        if (!isParticipant(creator)) {
            participants.push_back(creator);
        }
        description = "No description";
    }

    void addAdmin(string newAdmin) {
        if (!isParticipant(newAdmin)) {
            cout << "Error: the participant is not in this group!" << endl;
            return;
        }
        if (isAdmin(newAdmin)) {
            cout << "User is already an admin." << endl;
            return;
        }
        admins.push_back(newAdmin);
        cout << newAdmin << " is now an admin." << endl;
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        if (!isAdmin(admin)) {
            cout << "Error: this participant cannot do this action!" << endl;
            return false;
        }
        if (!isParticipant(userToRemove)) {
            return false;
        }
        
        for (int i = 0; i < static_cast<int>(participants.size()); i++) {   
            if (participants[i] == userToRemove) {
                participants.erase(participants.begin() + i);
                break;
            }
        }
        
        if (isAdmin(userToRemove)) {
            for (int i = 0; i < static_cast<int>(admins.size()); i++) {
                if (admins[i] == userToRemove) {
                    admins.erase(admins.begin() + i);
                    break;
                }
            }
        }
        
        cout << "Command confirmed!" << endl;
        return true;
    }

    bool isAdmin(string username) const {
        for (int i = 0; i < static_cast<int>(admins.size()); i++) {
            if (admins[i] == username) {
                return true;
            }
        }
        return false;
    }

    bool isParticipant(string username) const {
        for (int i = 0; i < static_cast<int>(participants.size()); i++) {
            if (participants[i] == username) {
                return true;
            }
        }
        return false;
    }

    void setDescription(string desc) {
        description = desc;
    }

    void displayChat() const override {
        cout << "\n===== " << chatName << " =====\n";
        cout << "Description: " << description << endl;
        
        cout << "Participants (" << participants.size() << "):" << endl;
        for (int i = 0; i < static_cast<int>(participants.size()); i++) {
            cout << "- " << participants[i];
            if (isAdmin(participants[i])) {
                cout << " (Admin)";
            }
            cout << endl;
        }
        
        cout << "Messages:" << endl;
        if (messages.empty()) {
            cout << "No messages yet.\n";
            return;
        }
        for (int i = 0; i < static_cast<int>(messages.size()); i++) {
            cout << i + 1 << ". ";
            messages[i].display();
        }
    }

    void sendJoinRequest(const string& username) {
        if (isParticipant(username)) {
            cout << username << " is already a participant!" << endl;
            return;
        }
        if (find(joinRequests.begin(), joinRequests.end(), username) != joinRequests.end()) {
            cout << "You already sent a join request to " << chatName << "!" << endl;
            return;
        }
        joinRequests.push_back(username);
        cout << "Join request sent by " << username << " to " << chatName << "." << endl;
    }

    vector<string> getJoinRequests() const {
        return joinRequests;
    }

    bool approveJoinRequest(const string& admin, const string& username) {
        if (!isAdmin(admin)) {
            cout << "Error: only admins can approve requests!" << endl;
            return false;
        }
        auto it = find(joinRequests.begin(), joinRequests.end(), username);
        if (it == joinRequests.end()) {
            return false;
        }
        joinRequests.erase(it);
        if (!isParticipant(username)) {
            participants.push_back(username);
        }
        cout << username << " has been approved and added to " << chatName << "!" << endl;
        return true;
    }

    bool rejectJoinRequest(const string& admin, const string& username) {
        if (!isAdmin(admin)) {
            cout << "Error: only admins can reject requests!" << endl;
            return false;
        }
        auto it = find(joinRequests.begin(), joinRequests.end(), username);
        if (it == joinRequests.end()) {
            return false;
        }
        joinRequests.erase(it);
        cout << "Join request from " << username << " rejected." << endl;
        return true;
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
        for (int i = 0; i < static_cast<int>(users.size()); i++) {
            if (users[i].getUsername() == username) {
                return i;
            }
        }
        return -1;
    }

    bool isLoggedIn() const {
        return currentUserIndex >= 0 &&
               currentUserIndex < static_cast<int>(users.size());
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
            for (size_t i = 0; i < chats.size(); i++) {
                if (isMemberOfChat(i, username)) {
                    chats[i]->markAsDelivered(username);
                }
            }
            cout << "Login successful!\n";
        }
        else {
            cout << "Incorrect password!\n";
        }
    }

    void logout() {
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
    vector<vector<string> > chatMembers;
    vector<string> chatNames;

    bool isMemberOfChat(size_t i, const string& username) const {
        for (size_t j = 0; j < chatMembers[i].size(); j++)
            if (chatMembers[i][j] == username) return true;
        return false;
    }

    bool readInt(const string& prompt, int& out) const {
        cout << prompt;
        string line;
        if (!getline(cin, line)) return false;
        try {
            size_t pos = 0;
            out = stoi(line, &pos);
            return pos == line.size();
        } catch (...) {
            return false;
        }
    }

    void sendMessage(Chat* chat, const string& me) {
        PrivateChat* pc = dynamic_cast<PrivateChat*>(chat);
        if (pc != nullptr) pc->showTypingIndicator(me);

        cout << "Message: ";
        string content;
        getline(cin, content);
        if (content.empty()) { cout << "Error: message can't be empty.\n"; return; }

        Message m(me, content);
        const char* codes[] = { ":thumbsup:", ":)", ":(", ":D", "<3" };
        for (size_t i = 0; i < 5; i++) m.addEmoji(codes[i]);

        chat->addMessage(m);
        users[currentUserIndex].updateLastSeen();
        cout << "Message sent.\n";
    }

    void replyToMessage(Chat* chat, const string& me) {
        int n;
        if (!readInt("Message number to reply to: ", n)) {
            cout << "Invalid number.\n";
            return;
        }
        Message* target = chat->getMessagePtr(n - 1);
        if (target == nullptr) {
            cout << "Message not found.\n";
            return;
        }

        PrivateChat* pc = dynamic_cast<PrivateChat*>(chat);
        if (pc != nullptr) pc->showTypingIndicator(me);

        cout << "Reply: ";
        string content;
        getline(cin, content);
        if (content.empty()) { cout << "Error: message can't be empty.\n"; return; }

        Message m(me, content);
        m.setReplyTo(target);
        const char* codes[] = { ":thumbsup:", ":)", ":(", ":D", "<3" };
        for (size_t i = 0; i < 5; i++) m.addEmoji(codes[i]);

        chat->addMessage(m);
        users[currentUserIndex].updateLastSeen();
        cout << "Reply sent.\n";
    }

    void openChat() {
        if (!isLoggedIn()) { cout << "Please login first.\n"; return; }

        string me = getCurrentUsername();

        vector<size_t> mine;
        for (size_t i = 0; i < chats.size(); i++)
            if (isMemberOfChat(i, me)) mine.push_back(i);

        if (mine.empty()) { cout << "You have no chats yet.\n"; return; }

        cout << "\nYour chats:\n";
        for (size_t k = 0; k < mine.size(); k++)
            cout << k + 1 << ". " << chatNames[mine[k]] << "\n";

        int pick;
        if (!readInt("Open chat number: ", pick) || pick < 1 || pick > static_cast<int>(mine.size())) {
            cout << "Invalid chat number.\n";
            return;
        }
        size_t chatIdx = mine[pick - 1];
        Chat* chat = chats[chatIdx];
        GroupChat* gc = dynamic_cast<GroupChat*>(chat);

        while (true) {
            chat->markAsRead(me);
            chat->displayChat();
            cout << "\n1. Send message\n2. Reply to message\n3. Delete my message"
                 << "\n4. Search messages\n5. Export chat to file";
            if (gc != nullptr) {
                cout << "\n6. Set group description\n7. Add admin\n8. Remove participant"
                     << "\n9. Manage join requests (" << gc->getJoinRequests().size() << ")";
            }
            cout << "\n0. Back\n";

            int choice;
            if (!readInt("Choice: ", choice)) {
                if (cin.eof()) return;
                cout << "Invalid input, please enter a number.\n";
                continue;
            }

            if (choice == 0) return;
            else if (choice == 1) {
                sendMessage(chat, me);
            }
            else if (choice == 2) {
                replyToMessage(chat, me);
            }
            else if (choice == 3) {
                int n;
                if (!readInt("Message number to delete: ", n)) {
                    cout << "Invalid number.\n";
                } else if (chat->deleteMessage(n - 1, me)) {
                    users[currentUserIndex].updateLastSeen();
                    cout << "Message deleted.\n";
                } else {
                    cout << "Can't delete: invalid number or not your message.\n";
                }
            }
            else if (choice == 4) {
                cout << "Keyword: ";
                string keyword;
                getline(cin, keyword);
                if (keyword.empty()) { cout << "Error: keyword can't be empty.\n"; continue; }

                vector<Message> results = chat->searchMessages(keyword);
                if (results.empty()) {
                    cout << "No messages found.\n";
                } else {
                    cout << results.size() << " message(s) found:\n";
                    for (size_t i = 0; i < results.size(); i++) results[i].display();
                }
            }
            else if (choice == 5) {
                cout << "File name (e.g. chat.txt): ";
                string filename;
                getline(cin, filename);
                if (filename.empty()) { cout << "Error: file name can't be empty.\n"; continue; }
                chat->exportToFile(filename);
            }
            else if (gc != nullptr && choice == 6) {
                if (!gc->isAdmin(me)) {
                    cout << "Error: only admins can change description.\n";
                    continue;
                }
                cout << "New description: ";
                string desc;
                getline(cin, desc);
                gc->setDescription(desc);
                cout << "Description updated.\n";
            }
            else if (gc != nullptr && choice == 7) {
                if (!gc->isAdmin(me)) {
                    cout << "Error: only admins can add an admin.\n";
                    continue;
                }
                cout << "Username to make admin: ";
                string target;
                getline(cin, target);
                gc->addAdmin(target);
            }
            else if (gc != nullptr && choice == 8) {
                cout << "Username to remove: ";
                string target;
                getline(cin, target);
                if (gc->removeParticipant(me, target)) {
                    vector<string>& mems = chatMembers[chatIdx];
                    for (size_t j = 0; j < mems.size(); j++) {
                        if (mems[j] == target) {
                            mems.erase(mems.begin() + j);
                            break;
                        }
                    }
                    if (target == me) return;
                }
            }
            else if (gc != nullptr && choice == 9) {
                if (!gc->isAdmin(me)) {
                    cout << "Error: only admins can manage join requests.\n";
                    continue;
                }
                vector<string> reqs = gc->getJoinRequests();
                if (reqs.empty()) {
                    cout << "No pending join requests.\n";
                    continue;
                }
                cout << "\nPending join requests:\n";
                for (size_t i = 0; i < reqs.size(); i++) {
                    cout << i + 1 << ". " << reqs[i] << "\n";
                }
                int reqPick;
                if (!readInt("Select request number (0 to cancel): ", reqPick) || reqPick < 0 || reqPick > static_cast<int>(reqs.size())) {
                    cout << "Invalid number.\n";
                    continue;
                }
                if (reqPick == 0) continue;

                string applicant = reqs[reqPick - 1];
                int action;
                if (!readInt("1. Approve\n2. Reject\nChoice: ", action)) {
                    cout << "Invalid choice.\n";
                    continue;
                }
                if (action == 1) {
                    if (gc->approveJoinRequest(me, applicant) && !isMemberOfChat(chatIdx, applicant)) {
                        chatMembers[chatIdx].push_back(applicant);
                    }
                } else if (action == 2) {
                    gc->rejectJoinRequest(me, applicant);
                } else {
                    cout << "Invalid option.\n";
                }
            }
            else {
                cout << "Invalid option.\n";
            }
        }
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

        chats.push_back(new GroupChat(members, name, me));

        vector<string> all = members;
        all.push_back(me);
        chatMembers.push_back(all);
        chatNames.push_back(name);

        users[currentUserIndex].updateLastSeen();
        cout << "Group '" << name << "' created. You are the admin.\n";
    }

    void requestJoinGroup() {
        if (!isLoggedIn()) { cout << "Please login first.\n"; return; }

        string me = getCurrentUsername();
        vector<size_t> available;
        for (size_t i = 0; i < chats.size(); i++) {
            if (dynamic_cast<GroupChat*>(chats[i]) != nullptr && !isMemberOfChat(i, me)) {
                available.push_back(i);
            }
        }

        if (available.empty()) {
            cout << "No available groups to join.\n";
            return;
        }

        cout << "\nAvailable groups:\n";
        for (size_t k = 0; k < available.size(); k++) {
            cout << k + 1 << ". " << chatNames[available[k]] << "\n";
        }

        int pick;
        if (!readInt("Select group number to request join: ", pick) || pick < 1 || pick > static_cast<int>(available.size())) {
            cout << "Invalid group number.\n";
            return;
        }

        GroupChat* gc = dynamic_cast<GroupChat*>(chats[available[pick - 1]]);
        if (gc != nullptr) {
            gc->sendJoinRequest(me);
        }
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

    void changeUserPassword() {
        if (!isLoggedIn()) { cout << "Please login first.\n"; return; }

        string oldPwd, newPwd;
        cout << "Enter current password: ";
        getline(cin, oldPwd);

        if (!users[currentUserIndex].checkPassword(oldPwd)) {
            cout << "Incorrect current password!\n";
            return;
        }

        cout << "Enter new password (min 6 chars): ";
        getline(cin, newPwd);

        if (users[currentUserIndex].changePassword(newPwd)) {
            cout << "Password changed successfully!\n";
        } else {
            cout << "Password must be at least 6 characters!\n";
        }
    }

    void run() {
        while (true) {
            int choice;
            if (!isLoggedIn())
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
            else
                cout << "\n1. Start Private Chat\n2. Create Group\n3. Request to Join Group\n4. View Chats\n5. Open Chat\n6. Change Password\n7. Logout\nChoice: ";

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
                else if (choice == 3) requestJoinGroup();
                else if (choice == 4) viewChats();
                else if (choice == 5) openChat();
                else if (choice == 6) changeUserPassword();
                else if (choice == 7) logout();
                else cout << "Invalid option.\n";
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
// --- END: SHAHD [KAN-7] (Chats Management, Destructor & Menu) ---
