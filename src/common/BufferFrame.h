//
// Created by Yormingandr on 9/29/2023.
//

#ifndef AXODB_BUFFERFRAME_H
#define AXODB_BUFFERFRAME_H


#include <cstdint>

typedef uint64_t page_id_t;

class BufferFrame {

public:
    BufferFrame(page_id_t pageId, char* data);
    ~BufferFrame();

    page_id_t GetPageId() const;
    char* GetData() const;
    bool IsDirty() const;
    void SetDirty(bool is_dirty);


private:
    page_id_t page_id_;
    char* data_;
    bool is_dirty_;
};


#endif //AXODB_BUFFERFRAME_H
