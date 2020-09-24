#ifndef BD_DB_H
#define BD_DB_H

#define SIZE (255)
#define CUSTOMERS_PATH ("/home/andrew/CLionProjects/database/database/customers")
#define CUSTOMERS_TEMP_PATH ("/home/andrew/CLionProjects/database/database/customers_temp")
#define PROJECT_PATH ("/home/andrew/CLionProjects/database/database/projects")
#define PROJECT_TEMP_PATH ("/home/andrew/CLionProjects/database/database/projects_temp")

struct Project {
    int id_of_customer;
    int price;
    char name[SIZE];
    char description[SIZE];
};

struct Customer {
    int id;
    char name[SIZE];
    char e_mail[SIZE];
};

int get_m();

int get_s();

int del_m();

int del_s();

int update_m();

int update_s();

int insert_m();

int insert_s();

int ut_m();

int ut_s();

int count_m();

int count_s();

int __del_m_by_id(int id);

int __del_s_by_num(int num);

int __del_s_by_id(int id);

int __update_m_by_id(int id);

int __update_s_by_num(int num);

void __ut_m_by_struct(struct Customer *customer);

void __ut_s_by_struct(struct Project *project);

int __ut_m_small();

int __ut_s_small();

void help();


#endif //BD_DB_H
