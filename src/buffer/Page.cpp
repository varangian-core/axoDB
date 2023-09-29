#include "Page.h"

Page::Page(page_id_t page_id, char *data)
    : page_id_(page_id), data_(data), is_dirty_(false), is_pinned_(false) {}

Page::~Page() {}

page_id_t Page::GetPageId() const {
    return page_id_;
}

char *Page::GetData() {
    return data_;
}

bool Page::IsDirty() const {
    return is_dirty_;
}

void Page::SetDirty(bool is_dirty) {
    is_dirty_ = is_dirty;
}

bool Page::IsPinned() const {
    return is_pinned_;
}

bool Page::Pin() {
    if (is_pinned_) {
        return false;
    }
    is_pinned_ = true;
    return true;
}

bool Page::Unpin(bool is_dirty) {
    if (!is_pinned_) {
        return false;
    }
    is_pinned_ = false;
    is_dirty_ = is_dirty || is_dirty_;
    return true;
}