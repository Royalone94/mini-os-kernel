#ifndef INCLUDE_PROC_H
#define INCLUDE_PROC_H

#include "types.h"
#include "vmm.h"

// 进程状态
typedef
enum task_state {
    TASK_UNINIT = 0,
    TASK_SLEEPING = 1,
    TASK_RUNNABLE = 2,
    TASK_ZOMBIE = 3,
} task_state_t;

typedef
struct context {
    uint32_t esp;
    uint32_t ebp;
    uint32_t ebx;
    uint32_t esi;
    uint32_t edi;
    uint32_t eflags;
} context_t;

// 进程内存
typedef
struct mm_struct {
     pgd_t *pgd_dir;
} mm_struct_t;

// 进程控制块
typedef
struct proc_struct {
    volatile task_state_t state;
    pid_t pid;
    void *stack;               // 栈地址
    mm_struct_t *mm;
    context_t context;

    // 双向循环链表
    struct proc_struct *prev;
    struct proc_struct *next;
} proc_struct_t;


extern pid_t now_pid;

// 内核线程创建
int32_t kernel_thread(int (*fn)(void *), void *arg);

// 内核线程退出
void kthread_exit();

#endif // INCLUDE_PROC_H