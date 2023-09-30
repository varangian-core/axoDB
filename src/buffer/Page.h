#include <cstdint>


#ifndef PAGE_H
#define PAGE_H

typedef uint64_t page_id_t;

class Page {
public:
    explicit Page(page_id_t page_id, char *data);

    ~Page();

    page_id_t GetPageId() const;

    char *GetData();

    bool IsDirty() const;

    void SetDirty(bool is_dirty);

    bool IsPinned() const;

    bool Pin();

    bool Unpin(bool is_dirty);

private:
    page_id_t page_id_;
    char *data_;
    bool is_dirty_;
    bool is_pinned_;
};

#endif