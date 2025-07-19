//
// Created by bruce on 2025/7/19.
//

#include "Message.h"
#include <iostream>

void Message::save(Folder &f)
{
    folders.insert(&f); // add the given Folder to our list of Folders
    f.addMsg(this); // add this Message to f’s set of Messages
}

void Message::remove(Folder &f)
{
    folders.erase(&f); // take the given Folder out of our list of Folders
    f.remMsg(this); // remove this Message to f’s set of Messages
}

// Message 被copy时， 所有保存了当前message的Folder下都要拷贝一份
void Message::add_to_Folders(const Message &m) {
    for (auto folder: m.folders) {
        folder->addMsg(this);
    }
}
// copy control
Message::Message(const Message &m) : contents(m.contents), folders(m.folders){
    // 所有保存了当前message的Folder下都要拷贝一份，都执行add_to_Folders
    add_to_Folders(m);
}

// 销毁message时，所有包含message的Folder下都要清除一次
void Message::remove_from_Folders() {
    for (auto folder: folders) {
        folder->remMsg(this);
    }
    // 不需要执行 析构函数 folers总会被销毁
    // self-assignment时，先执行remove_from_Folders， lhs和rhs下的folder被清空
    // 这样就无法赋值了
    // folders.clear();
}

Message::~Message() {
    remove_from_Folders();
}

// copy assignment  lhs 和rhs 一样时
Message &Message::operator=(const Message &rhs) {
    //先清除所有lhs下folers
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    // 再lhsfolder下添加新的message
    add_to_Folders(rhs);
    return *this;
}

void swap(Message &lhs, Message &rhs) {
    using std::swap;
    // 先清除m1， m2下的Folder
    lhs.remove_from_Folders();
    rhs.remove_from_Folders();
    // swap contents和 folder
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    // 再重新设置m1， m2下的Folder
    lhs.add_to_Folders(lhs);
    rhs.add_to_Folders(rhs);
}

// Folder Implementation

Folder::Folder(const Folder &f) : msgs(f.msgs) {
    add_to_Messages(f);
}

void Folder::add_to_Messages(const Folder &f) {
    // f下所有的massage 都添加到当前下
    for (auto msg: f.msgs) {
        msg->addFldr(this);
    }
}

void Folder::remove_from_Message() {
    // 清空当前folder的msg, 对应msg删除folder
    for (auto msg: msgs) {
        msg->remFldr(this);
    }
}

Folder::~Folder() {
    remove_from_Message();
}

Folder &Folder::operator=(const Folder &rhs) {
    // 先清除当前
    remove_from_Message();
    msgs = rhs.msgs;
    // 再添加
    add_to_Messages(rhs);
    return *this;
}

void swap(Folder &lhs, Folder &rhs) {
    using std::swap;
    lhs.remove_from_Message();
    rhs.remove_from_Message();
    swap(lhs.msgs, rhs.msgs);
    lhs.add_to_Messages(lhs);
    rhs.add_to_Messages(rhs);
}

