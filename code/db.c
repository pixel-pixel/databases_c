#include <stdio.h>
#include "db.h"

int get_m() {
    FILE *fp;
    struct Customer customer;
    int id;

    if ((fp = fopen(CUSTOMERS_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    printf("id of customer(int): ");
    scanf("%d", &id);

    while (fread(&customer, sizeof(struct Customer), 1, fp) == 1) {
        if (customer.id == id) break;
    }

    printf("----customer-[id:%d]----\n", id);
    if (customer.id != id)
        perror("Customer with this id not found");
    else{
        printf("    id : %d\n  name : %s\ne-mail : %s\n",
               customer.id, customer.name, customer.e_mail);
        printf("------------------------\n", id);
    }

    fclose(fp);
    return 0;
}

int get_s(){
    FILE *fp;
    struct Project project;
    int id;

    if ((fp = fopen(PROJECT_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    printf("id of customer(int): ");
    scanf("%d", &id);

    printf("-----PROJECTS-[id:%d]----\n", id);
    while (fread(&project, sizeof(struct Project), 1, fp) == 1) {
        if(project.id_of_customer == id){
            printf("  master id: %d\n       name: %s\n      prise: %d\ndescription: %s\n",
                   project.id_of_customer, project.name, project.price, project.description);
            printf("%s", "------------------------\n");
        }
    }

    if (project.id_of_customer != id)
        perror("Project with this id not found");

    fclose(fp);
    return 0;
}

int del_m(){
    int num;

    __ut_m_small();
    printf("enter [id] of customer:\n");
    scanf("%d", &num);

    __del_m_by_id(num);
}

int del_s(){
    int num;

    __ut_s_small();
    printf("enter [number] of project:\n");
    scanf("%d", &num);

    __del_s_by_num(num);
}

int update_m(){
    int id;

    __ut_m_small();
    printf("enter an [id]:\n");
    scanf("%d", &id);

    return __update_m_by_id(id);
};

int update_s(){
    int num;

    __ut_s_small();
    printf("enter a [number]:\n");
    scanf("%d", &num);

    return __update_s_by_num(num);
};

int insert_m() {
    FILE *fp;
    struct Customer customer;
    int id;

    if ((fp = fopen(CUSTOMERS_PATH, "a+b")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    printf("id of customer(int): ");
    scanf("%d", &id);

    while(fread(&customer, sizeof(struct Customer), 1, fp) == 1){
        if(id == customer.id){
            perror("Customer with this id is already exist");
            return 0;
        }
    }

    customer.id = id;
    printf("%s", "name of customer(char[255]): ");
    scanf(" %s", customer.name);
    printf("%s", "e-mail of customer(char[255]): ");
    scanf(" %s", customer.e_mail);

    fwrite(&customer, sizeof(struct Customer), 1, fp);
    fclose(fp);
    return 0;
}

int insert_s(){
    FILE *fp;
    struct Project project;

    if ((fp = fopen(PROJECT_PATH, "ab")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    printf("%s", "name of project(char[255]): ");
    scanf(" %s", project.name);
    printf("prise(int): ");
    scanf("%d", &project.price);
    printf("%s", "description(char[255]): ");
    scanf(" %s", project.description);
    __ut_m_small();
    printf("id of customer(int): ");
    scanf("%d", &project.id_of_customer);

    fwrite(&project, sizeof(struct Project), 1, fp);
    fclose(fp);
    return 0;
}

int ut_m(){
    FILE *file;
    struct Customer customer;

    if ((file = fopen(CUSTOMERS_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    printf("%s", "-----CUSTOMERS-----\n");
    while (fread(&customer, sizeof(struct Customer), 1, file) == 1) {
        printf("    id : %d\n  name : %s\ne-mail : %s\n",
               customer.id, customer.name, customer.e_mail);
        printf("%s", "-------------------\n");
    }


    fclose(file);
    return 0;
}

int ut_s(){
    FILE *file;
    struct Project project;

    if ((file = fopen(PROJECT_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    printf("%s", "--------PROJECTS--------\n");
    while (fread(&project, sizeof(struct Project), 1, file) == 1) {
       int insert_m(struct Customer *pCustomer); printf("  master id: %d\n       name: %s\n      prise: %d\ndescription: %s\n",
               project.id_of_customer, project.name, project.price, project.description);
        printf("%s", "------------------------\n");
    }

    fclose(file);
    return 0;
}

int count_m(){
    FILE *fp;
    struct Customer customer;
    int cout = 0;

    if ((fp = fopen(CUSTOMERS_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    while (fread(&customer, sizeof(struct Customer), 1, fp) == 1) {
        cout++;
    }

    printf("count of CUSTOMERS : %d\n", cout);

    fclose(fp);
    return 0;
}

int count_s(){
    FILE *fp;
    struct Project project;
    int count = 0;
    int id;

    if ((fp = fopen(PROJECT_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    __ut_m_small();
    printf("enter the [master id] or [-1] for count all:\n");
    scanf("%d", &id);

    while (fread(&project, sizeof(struct Project), 1, fp) == 1) {
        if(id == -1 || project.id_of_customer == id) count++;
    }

    if(id == -1) printf("count of ALL PROJECTS : %d\n", count);
    else printf("count of PROJECTS with master id [%d]: %d\n", id, count);


    fclose(fp);
    return 0;
}

int __del_m_by_id(int id){
    FILE *get_file;
    FILE *put_file;
    int is_found = 0;

    struct Customer customer;

    if ((get_file = fopen(CUSTOMERS_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }
    if ((put_file = fopen(CUSTOMERS_TEMP_PATH, "ab")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    while (fread(&customer, sizeof(struct Customer), 1, get_file) == 1) {
        if(customer.id != id)
            fwrite(&customer, sizeof(struct Customer), 1, put_file);
        else
            is_found = 1;
    }

    fclose(get_file);
    fclose(put_file);

    if(is_found){
        __del_s_by_id(id);

        remove(CUSTOMERS_PATH);
        return rename(CUSTOMERS_TEMP_PATH, CUSTOMERS_PATH);
    } else{
        remove(CUSTOMERS_TEMP_PATH);
        perror("Customer with this id not found");
    }

}

int __del_s_by_num(int num){
    FILE *get_file;
    FILE *put_file;
    int is_found = 0;

    struct Project project;

    if ((get_file = fopen(PROJECT_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }
    if ((put_file = fopen(PROJECT_TEMP_PATH, "ab")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    int index = 1;

    while (fread(&project, sizeof(struct Project), 1, get_file) == 1) {
        if(index != num)
            fwrite(&project, sizeof(struct Project), 1, put_file);
        else
            is_found = 1;
        index++;
    }

    fclose(get_file);
    fclose(put_file);

    if(is_found){
        remove(PROJECT_PATH);
        return rename(PROJECT_TEMP_PATH, PROJECT_PATH);
    }else{
        remove(PROJECT_TEMP_PATH);
        perror("Project with this number not found");
    }

}

int __del_s_by_id(int id){
    FILE *get_file;
    FILE *put_file;

    struct Project project;

    if ((get_file = fopen(PROJECT_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }
    if ((put_file = fopen(PROJECT_TEMP_PATH, "ab")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    while (fread(&project, sizeof(struct Project), 1, get_file) == 1) {
        if(project.id_of_customer != id)
            fwrite(&project, sizeof(struct Project), 1, put_file);
    }

    fclose(get_file);
    fclose(put_file);

    remove(PROJECT_PATH);
    return rename(PROJECT_TEMP_PATH, PROJECT_PATH);
}

int __update_m_by_id(int id){
    FILE *fp;
    struct Customer customer;
    int property;
    int is_found = 0;

    if ((fp = fopen(CUSTOMERS_PATH, "r+b")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    while (fread(&customer, sizeof(struct Customer), 1, fp) == 1) {
        if(customer.id == id) {
            is_found = 1;
            break;
        }
    }

    if(!is_found){
        perror("Customer with this id not found");
        return 0;
    }

    __ut_m_by_struct(&customer);
    printf("enter the [property] for change it:\n");
    scanf("%d", &property);

    switch (property) {
        case 1:
            printf("enter the [new name]:\n");
            scanf("%s", customer.name);
            break;
        case 2:
            printf("enter the [new e-mail]:\n");
            scanf("%s", customer.e_mail);
            break;
        default:
            perror("Number not found");
    }

    fseek(fp, -sizeof(struct Customer), SEEK_CUR);
    fwrite(&customer, sizeof(struct Customer), 1, fp);

    fclose(fp);
    return 0;
}

int __update_s_by_num(int num){
    FILE *fp;
    struct Project project;
    int index = 1;
    int property;
    int is_found = 0;

    if ((fp = fopen(PROJECT_PATH, "r+b")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    while (fread(&project, sizeof(struct Project), 1, fp) == 1) {
        if(index == num) {
            is_found = 1;
            break;
        }
        index++;
    }

    if(!is_found){
        perror("Project with this number not found");
        return 0;
    }

    __ut_s_by_struct(&project);
    printf("enter the [property] for change it:\n");
    scanf("%d", &property);

    switch (property) {
        case 1:
            printf("enter the [new name]:\n");
            scanf("%s", project.name);
            break;
        case 2:
            printf("enter the [new price]:\n");
            scanf("%d", &project.price);
            break;
        case 3:
            printf("enter the [new description]:\n");
            scanf("%s", project.description);
            break;
        default:
            perror("Number not found");
    }

    fseek(fp, -sizeof(struct Project), SEEK_CUR);
    fwrite(&project, sizeof(struct Project), 1, fp);

    fclose(fp);
    return 0;
}

void __ut_m_by_struct(struct Customer *customer){
    printf("-----customer-----\n");
    printf("[1] name : %s\n[2] e-mail : %s\n",
           customer->name, customer->e_mail);
    printf("------------------\n");
}

void __ut_s_by_struct(struct Project *project){
    printf("-----project-----\n");
    printf("[1] name : %s\n[2] price : %d\n[3] description : %s\n",
           project->name, project->price, project->description);
    printf("-----------------\n");
}

int __ut_m_small(){
    FILE *file;
    struct Customer customer;

    if ((file = fopen(CUSTOMERS_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    printf("+------CUSTOMERS------+\n");
    printf("| [id], name, e-mail  |\n");
    printf("+---------------------+\n");
    while (fread(&customer, sizeof(struct Customer), 1, file) == 1) {
        printf("[%d], %s, %s\n",
               customer.id, customer.name, customer.e_mail);
    }
    printf("-----------------------\n");


    fclose(file);
    return 0;
}

int __ut_s_small(){
    FILE *file;
    struct Project project;

    if ((file = fopen(PROJECT_PATH, "rb")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    int index = 1;
    printf("+-----------------PROJECTS------------------+\n");
    printf("|    master id, name, prise, description    |\n");
    printf("+-------------------------------------------+\n");
    while (fread(&project, sizeof(struct Project), 1, file) == 1) {
        printf("[%d] {%d, %s, %d, %s}\n",
               index, project.id_of_customer, project.name, project.price, project.description);
        index++;
    }
    printf("---------------------------------------------\n");


    fclose(file);
    return 0;
}

void help(){
    printf("----COMMANDS----\n");
    printf(" [1] get-m\n"
           " [2] get-s\n"
           " [3] del-m\n"
           " [4] del--s\n"
           " [5] update-m\n"
           " [6] update-s\n"
           " [7] insert-m\n"
           " [8] insert-s\n"
           " [9] count-m\n"
           "[10] count-s\n"
           "[11] ut-m\n"
           "[12] ut-s\n"
           "[13] end\n");
    printf("----------enter: ");
}


