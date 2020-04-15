#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday{
	int day;
	int month;
	int year;
	struct list_head list;
};

LIST_HEAD(birthday_list);

struct birthday *createBirthday(int day,int month,int year){
	struct birthday *person= kmalloc(sizeof(struct birthday),
			GFP_KERNEL);	      
	person->day = day;
        person->month = month;
	person->year = year;
	return person;
}

int simple_init(void)
{
	struct birthday *person = createBirthday(13,4,1987);
	struct birthday *ptr;
	printk("INSTALL MODULE:bdlist");
	INIT_LIST_HEAD(&birthday_list);
	list_add_tail(&person->list,&birthday_list);
	createBirthday(13,4,1987);
	list_add_tail(&person-> list, &birthday_list);
	person=createBirthday(14,1,1964);
	list_add_tail(&person->list,&birthday_list);
	person=createBirthday(2,6,1964);
	list_add_tail(&person->list,&birthday_list);
	person=createBirthday(13,8,1986);
	list_add_tail(&person->list,&birthday_list);
	person=createBirthday(10,6,1990);
	list_add_tail(&person->list,&birthday_list);
	
	list_for_each_entry(ptr,&birthday_list,list) {
	/*for(ptr=list_first_entry(birthday_list,typeof(*ptr),list);
	   &ptr->list!=(birthday_list);
	   ptr=list_next_entry(ptr,list);*/
	printk(KERN_INFO "OS Module: Day %d.%d.%d\n",
	ptr->day,
	ptr->month,
	ptr->year);
	}
	return 0;
}

void simple_exit(void){
	struct birthday *tmp;
	struct list_head *pos,*q;
	struct birthday birthday_list;
	printk("Removing Module\n");
	if(list_empty(&birthday_list.list)){
		printk("List is Empty\n");
		return;
	}
#define list_for_each_safe (pos,q,&birthday_list.list){
		tmp=list_entry(pos,struct birthday,list);
		printk(KERN_INFO "OS Module:Removing %d.%d.%d\n", 
		tmp->day, 
		tmp-> month,
		tmp->year);
		list_del(pos);			
		kfree(tmp);
	
	printk("Remove module:bdlist\n");
	return;
}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("make a list of birthdays and print");
MODULE_AUTHOR("kimyeonsu_2017011794");

