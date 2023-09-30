//
// Created by Yormingandr on 9/29/2023.
//

#include "BufferFrame.h"

BufferFrame::BufferFrame(page_id_t pageId, char* data)
        : page_id_(pageId), data_(data), is_dirty_(false) {}

BufferFrame::~BufferFrame() {} //consider dynamic memory allocation

page_id_t BufferFrame::GetPageId() const {
    return page_id_;
}

char* BufferFrame::GetData() const {
    return data_;
}

bool BufferFrame::IsDirty() const {
    return is_dirty_;
}

void BufferFrame::SetDirty(bool is_dirty) {
    is_dirty_ = is_dirty;
}
