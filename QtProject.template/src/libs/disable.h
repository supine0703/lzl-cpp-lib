#ifndef __DISABLE_H__
#define __DISABLE_H__

#define DISABLE_COPY(Class)       \
    Class(const Class&) = delete; \
    Class& operator=(const Class&) = delete;

#define DISABLE_COPY_MOVE(Class) \
    DISABLE_COPY(Class)          \
    Class(Class&&) = delete;     \
    Class& operator=(Class&&) = delete;

#define DISABLE_CONSTRUCT(Class) \
    DISABLE_COPY_MOVE(Class)     \
    Class() = delete;

#endif // __DISABLE_H__
