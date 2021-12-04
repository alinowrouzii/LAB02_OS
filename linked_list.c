#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
/* this function is called when the module is loaded*/

struct birthday
{
    int day;
    int month;
    int year;
    struct list_head list;
};
struct list_head birthday_list;

int simple_init(void)
{

    printk(KERN_INFO "Loding Module...\n");
    INIT_LIST_HEAD(&birthday_list);

    struct birthday *person;
    person = kmalloc(sizeof(person), GFP_KERNEL);
    person->day = 2;
    person->month = 8;
    person->year = 1995;
    INIT_LIST_HEAD(&person->list);

    list_add_tail(&person->list, &birthday_list);
    // ************************************

    struct birthday *person_2;
    person_2 = kmalloc(sizeof(person_2), GFP_KERNEL);
    person_2->day = 5;
    person_2->month = 9;
    person_2->year = 2000;
    INIT_LIST_HEAD(&person_2->list);

    list_add_tail(&person_2->list, &birthday_list);
    // ************************************

    struct birthday *person_3;
    person_3 = kmalloc(sizeof(person_3), GFP_KERNEL);
    person_3->day = 3;
    person_3->month = 7;
    person_3->year = 1990;
    INIT_LIST_HEAD(&person_3->list);

    list_add_tail(&person_3->list, &birthday_list);
    // ************************************
    struct birthday *person_4;
    person_4 = kmalloc(sizeof(person_4), GFP_KERNEL);
    person_4->day = 1;
    person_4->month = 2;
    person_4->year = 1200;
    INIT_LIST_HEAD(&person_4->list);

    list_add_tail(&person_4->list, &birthday_list);
    // ************************************
    struct birthday *person_5;
    person_5 = kmalloc(sizeof(person_5), GFP_KERNEL);
    person_5->day = 2;
    person_5->month = 4;
    person_5->year = 1999;
    INIT_LIST_HEAD(&person_5->list);

    list_add_tail(&person_5->list, &birthday_list);
    // ************************************

    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list)
    {
        printk("day %d - month %d - year %d \n\n\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}
/* this function is called when the module is removed*/

void simple_exit(void)
{
    printk(KERN_INFO "Removing Module...\n");

    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list)
    {
        printk(KERN_INFO "remove: day %d - month: %d - year %d\n", ptr->day, ptr->month, ptr->year);

        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_INFO "Module removed...\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple module");
MODULE_AUTHOR("SGG");

// tail -f /var/log/syslog