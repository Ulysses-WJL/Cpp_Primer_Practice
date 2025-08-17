#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <set>

class Folder;
class Message {
    friend void swap(Message &, Message &);
    friend class Folder;
public:
    // folders is implicitly initialized to the empty set
    explicit Message(const std::string &str = ""):
    contents(str) { }
    // copy control to manage pointers to this Message
    Message(const Message&); // copy constructor
    // move constructor
    Message(Message&&);
    Message& operator=(const Message&); // copy assignment
    Message& operator=(Message&&);
    ~Message(); // destructor
    // add/remove this Message from the specified Folder’s set of messages
    void save(Folder&);
    void remove(Folder&);
    // move the Folder pointers fromm to this Message
    void move_Folders(Message *m);
private:
    std::string contents; // actual message text
    std::set<Folder*> folders; // Folders that have this Message
    // utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message&);
    // remove this Message from every Folder in folders
    void remove_from_Folders();
    // to insert or remove a given Folder * into folders
    // f 保存/删除 当前message； 当前message 保存在Folder或从Folder中删除
    void addFldr(Folder *f) { folders.insert(f); }
    void remFldr(Folder *f) { folders.erase(f); }
};

void swap(Message &, Message &);

class Folder {
    friend void swap(Folder &, Folder &);
    friend class Message;
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
private:
    std::set<Message *> msgs;  // 文件夹下的所有msg
    void addMsg(Message *m) {msgs.insert(m);};
    void remMsg(Message *m) {msgs.erase(m);};
    // to insert or remove a given Folder * into folders
    void remove_from_Message(); // 当前文件夹下msg都删除
    void add_to_Messages(const Folder&);  // msg 被保存在当前文件夹
};

void swap(Folder &, Folder &);

#endif //MESSAGE_H
