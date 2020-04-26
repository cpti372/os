#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

void dfs(struct task_struct *task) {
  struct task_struct *cursor;
  struct list_head *list;
  printk(KERN_INFO "COMM: %-20s STATE: %ld\tPID: %d\n", task->comm, task->state,task->pid);
  list_for_each(list, &task->children) {
    cursor=list_entry(list, struct task_struct, sibling); 
    dfs(cursor); 
    }
}

static int __init list_task_init(void) {
  struct pid *init_pid=find_get_pid(1);
  struct task_struct *init_task;
  
  init_task=pid_task(init_pid, PIDTYPE_PID);
 
  printk(KERN_INFO "INSTALL: list_tasks_dfs\n");
  dfs(init_task); 
  return 0;
  init_task=current;
  while(init_task->pid !=1){
   init_task=init_task->parent;
  }
}

static void list_task_exit(void) {
  printk(KERN_INFO "REMOVE: list_tasks_dfs\n");
}

module_init(list_task_init);
module_exit(list_task_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("list tasks by dfs");
MODULE_AUTHOR("OS2019");
