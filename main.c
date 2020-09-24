#include <stdio.h>
#include "code/db.h"

int main() {
    //TODO більше 30

    int command;

    while (1){
        help();
        scanf("%d", &command);

        switch (command) {
            case 1:
                get_m();
                break;
            case 2:
                get_s();
                break;
            case 3:
                del_m();
                break;
            case 4:
                del_s();
                break;
            case 5:
                update_m();
                break;
            case 6:
                update_s();
                break;
            case 7:
                insert_m();
                break;
            case 8:
                insert_s();
                break;
            case 9:
                count_m();
                break;
            case 10:
                count_s();
                break;
            case 11:
                ut_m();
                break;
            case 12:
                ut_s();
                break;
            case 13:
                return 0;
            default:
                printf("COMMAND ERROR\n");
        }
    }
}
