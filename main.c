#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

char *first_start();
char *initiate();
void command_controller();
void stopwatch();
void sleep(int s);
int login_admin();
int add_member();
void load_members();
int check_idcode(int codeid);
void print_members();
int add_subscription();
void load_subscriptions();
int add_subanduser(int usercode, int subcode);
void load_subanduser();
struct user *get_user_by_code(int usercode);
struct subscription *get_sub_by_code(int subcode);
int is_active_subscription(int subcode);
void print_active_members();
void print_inactive_members();
void back();
void print_subscriptions_per_user(int usercode);
void print_users_per_subscription(int subcode);
int login_member();
void search_member_by_sub();
void search_member_by_code();
void search_member_by_family();
void reset_user_pass();
void change_user_info();
void reset_admin_pass();
int sunscriber_number(int subcode);
void view_subscriptions(int active);
void change_subscription();
void charge_account();
void update_price(int usercode, int credit);
void charge_confirmation();
void buy_subscription();

struct user
{
    char firstname[100];
    char lastname[100];
    char pass[64];
    int idcode;
    int membercode;
    int credit;
};

struct subscription
{
    int start_month;
    int start_year;
    int period;
    int price;
    int code;
};

struct subanduser
{
    int usercode;
    int subcode;
};

char *admin_password = NULL;
struct user *members = NULL;
struct subscription *subscriptions = NULL;
struct subanduser *subandusers = NULL;
int members_numbers = 0;
int subscriptions_numbers = 0;
int subandusers_numbers = 0;
int current_year = 2023;
int current_month = 1;
int current_usercode = 0;

int main(int argc, char const *argv[])
{

    admin_password = initiate();
    command_controller();

    return 0;
}

void command_controller()
{
    int state = 0;

    /*
    states:
    0 : Login Page
    1 : Admin Menu
    12 :  View Members
    13 : Search Page
    15 : Subscription Page
    2 : Member Menu
    */
    while (1)
    {
        if (state == 0)
        {
            system("cls");
            printf("Login Page:\n    1- Enter as an administrator\n    2- Enter as a member\n    3- Exit\n");
            printf("pleae enter your command : ");
            char command[15];
            while (1)
            {
                scanf("%s", &command);
                if (atoi(command) == 1)
                {
                    if (login_admin() == 0)
                    {
                        state = 1;
                    }
                    else
                    {
                        state = 0;
                    }

                    break;
                }
                else if (atoi(command) == 2)
                {
                    if (login_member() == 0)
                    {
                        state = 2;
                    }
                    else
                    {
                        state = 0;
                    }

                    break;
                }
                else if (atoi(command) == 3)
                {
                    exit(0);
                }
                else
                {
                    printf("Your command is not correct, pleae enter again : ");
                }
            }
        }
        else if (state == 1)
        {
            system("cls");
            printf("Admin Menu:\n    1- Add a new member\n    2- View active and inactive members\n    3- Search");
            printf("\n    4- Reset the password of members\n    5- Subscriptions\n    6- Charge confirmation");
            printf("\n    7- Change administrator password\n    8- Logout\n");
            char command[15];
            while (1)
            {
                scanf("%s", &command);
                if (atoi(command) == 1) // Add a new member
                {
                    int codem = add_member();
                    printf("a user with membership code %d is created\n", codem);
                    state = 1;
                    back();
                    break;
                }
                else if (atoi(command) == 2) // View Members
                {
                    state = 12;
                    break;
                }
                else if (atoi(command) == 3) // Search Page
                {
                    state = 13;
                    break;
                }
                else if (atoi(command) == 4) // reset user pass
                {
                    reset_user_pass();
                    back();
                    state = 1;
                    break;
                }
                else if (atoi(command) == 5) // Subscriptions
                {
                    state = 15;
                    break;
                }
                else if (atoi(command) == 6) // Charge confirmation
                {
                    charge_confirmation();
                    break;
                }
                else if (atoi(command) == 7) // Change administrator password
                {
                    reset_admin_pass();
                    back();
                    state = 1;
                    break;
                }
                else if (atoi(command) == 8)
                {
                    state = 0;
                    break;
                }
                else
                {
                    printf("Your command is not correct, pleae enter again : ");
                }
            }
        }
        else if (state == 12) // View Members
        {
            system("cls");
            printf("View Members:\n    1- View active members\n    2- View inactive members\n    3- Return back\n");
            char command[15];
            while (1)
            {
                scanf("%s", &command);
                if (atoi(command) == 1) // View active members
                {
                    print_active_members();
                    state = 12;
                    back();
                    break;
                }
                else if (atoi(command) == 2) // View inactive members
                {
                    print_inactive_members();
                    state = 12;
                    back();
                    break;
                }
                else if (atoi(command) == 3) // Return back
                {
                    state = 1;
                    break;
                }
                else
                {
                    printf("Your command is not correct, pleae enter again : ");
                }
            }
        }
        else if (state == 13) // Search Page
        {
            system("cls");
            printf("Search Page:\n    1- Search member by family\n    2- Search member by membership code\n    ");
            printf("3- Search subscription by code\n    4- Return back\n");
            char command[15];
            while (1)
            {
                scanf("%s", &command);
                if (atoi(command) == 1)
                {
                    search_member_by_family();
                    state = 13;
                    back();
                    break;
                }
                else if (atoi(command) == 2)
                {
                    search_member_by_code();
                    state = 13;
                    back();
                    break;
                }
                else if (atoi(command) == 3)
                {
                    search_member_by_sub();
                    state = 13;
                    back();
                    break;
                }
                else if (atoi(command) == 4)
                {
                    state = 1;
                    break;
                }
                else
                {
                    printf("Your command is not correct, pleae enter again : ");
                }
            }
        }
        else if (state == 15) // Subscription Page
        {
            system("cls");
            printf("Subscription Page:\n    1- View active subscriptions\n    2- View inactive subscriptions\n    ");
            printf("3- Define new subscription\n    4- Edit an existence subscription\n    5- Return back\n");
            char command[15];
            while (1)
            {
                scanf("%s", &command);
                if (atoi(command) == 1) // View active subscriptions
                {
                    view_subscriptions(1);
                    state = 15;
                    back();
                    break;
                }
                else if (atoi(command) == 2) // View inactive subscriptions
                {
                    view_subscriptions(0);
                    state = 15;
                    back();
                    break;
                }
                else if (atoi(command) == 3) // Define new subscription
                {
                    int r = add_subscription();
                    if (r != -1)
                    {
                        printf("a subscription with code %d is created\n", r);
                    }
                    state = 15;
                    back();
                    break;
                }
                else if (atoi(command) == 4) // Edit an existence subscription
                {
                    change_subscription();
                    state = 15;
                    back();
                    break;
                }
                else if (atoi(command) == 5)
                {
                    state = 1;
                    break;
                }
                else
                {
                    printf("Your command is not correct, pleae enter again : ");
                }
            }
        }
        else if (state == 2) // Member Menu
        {
            system("cls");
            printf("Member Menu:\n    1- View all subscriptions\n    2- Change personal information\n    3- Charge the accounth");
            printf("\n    4- Purchase a new subscription\n    5- Logout\n");
            char command[15];
            while (1)
            {
                scanf("%s", &command);
                if (atoi(command) == 1) // View all subscriptions
                {
                    print_subscriptions_per_user(current_usercode);
                    state = 2;
                    back();
                    break;
                }
                else if (atoi(command) == 2) // Change personal information
                {
                    change_user_info();
                    state = 2;
                    back();
                    break;
                }
                else if (atoi(command) == 3) // Charge the accounth
                {
                    charge_account();
                    state = 2;
                    back();
                    break;
                }
                else if (atoi(command) == 4) // Purchase a new subscription
                {
                    buy_subscription();
                    state = 2;
                    back();
                    break;
                }
                else if (atoi(command) == 5)
                {
                    state = 0;
                    break;
                }
                else
                {
                    printf("Your command is not correct, pleae enter again : ");
                }
            }
        }
    }
}

void stopwatch()
{
    system("cls");
    for (int i = 1200; i > 0; i--)
    {
        printf("%d\n", i / 20);
        system("cls");
    }
}

void sleep(int s)
{
    s *= 10000;
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < s; j++)
        {
            continue;
        }
    }
}

char *initiate()
{
    FILE *fp;
    char *password;

    fp = fopen("admin.txt", "r+");
    if (fp == NULL)
    {
        printf("Error, the Admin File doesn't exist!");
        exit(1);
    }
    if (NULL != fp)
    {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);

        if (0 == size)
        {
            // printf("file is empty\n");
            password = first_start();
            fprintf(fp, password);
            return password;
        }
    }

    fseek(fp, 0, SEEK_SET);

    // fputs("This is testing for fputs...\n", fp);
    password = malloc(64);
    fgets(password, 64, (FILE *)fp);
    fclose(fp);

    load_members();
    load_subscriptions();
    load_subanduser();

    return password;
}

char *first_start()
{
    char *password;
    password = malloc(64);
    system("cls");
    printf("Welcome to Gym Manager App\n");
    printf("Your are supposed to be the Admin\n");
    printf("please choose a password:\n");
    scanf("%s", password);
    return password;
}

int login_admin()
{
    char *password;
    int mistake = 0;
    password = malloc(64);

    system("cls");

    while (mistake < 3)
    {
        printf("Dear Admin please enter your password:\n");
        scanf("%s", password);
        if (strcmp(password, admin_password) == 0)
        {
            return 0;
        }
        else
        {
            mistake += 1;
            printf("the password is wrong:\n");
        }
    }

    system("cls");
    printf("you have entered 3 times the wrong password\n");
    printf("so you should wait for 60 secs");
    sleep(3);
    stopwatch();
    mistake = 0;
    system("cls");
    return -1;
}

int add_member()
{
    struct user a;
    FILE *fptr;

    if ((fptr = fopen("users.bin", "ab")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    printf("enter firstname: ");
    scanf("%s", &a.firstname);
    printf("enter lastname: ");
    scanf("%s", &a.lastname);
    printf("enter pass: ");
    scanf("%s", &a.pass);

    while (1)
    {
        printf("enter national code: ");
        scanf("%d", &a.idcode);
        if (check_idcode(a.idcode) == 0)
        {
            break;
        }
        else
        {
            printf("the National Code is duplicated, try again\n");
        }
    }

    if (members == NULL)
    {
        a.membercode = 1;
    }
    else
    {
        a.membercode = (members + (members_numbers - 1))->membercode + 1;
    }

    a.credit = 0;

    // printf("%s %s %s %d %d", a.firstname, a.lastname, a.pass, a.membercode, a.membercode);
    fwrite(&a, sizeof(struct user), 1, fptr);
    fclose(fptr);
    members_numbers += 1;
    load_members();

    return a.membercode;
}

void load_members()
{
    int n = 0;
    FILE *fptr;
    struct user a;

    if ((fptr = fopen("users.bin", "rb")) == NULL)
    {
        if (members == NULL)
        {
            return;
        }
        printf("Error! opening file");
        exit(1);
    }

    if (members == NULL)
    {
        while (fread(&a, sizeof(struct user), 1, fptr) == 1)
        {
            n++;
        }
        members_numbers = n;
        members = (struct user *)malloc(members_numbers * sizeof(struct user));
    }
    else
    {
        members = realloc(members, members_numbers * sizeof(struct user));
    }

    fseek(fptr, 0, SEEK_SET);
    n = 0;
    while (fread((members + n), sizeof(struct user), 1, fptr) == 1)
    {
        n++;
    }

    fclose(fptr);
}

int check_idcode(int codeid)
{

    for (int i = 0; i < members_numbers; i++)
    {
        if ((members + i)->idcode == codeid)
        {
            return -1;
        }
    }

    return 0;
}

void print_members()
{
    for (int i = 0; i < members_numbers; i++)
    {
        printf("\ncode:%d name:%s lastname:%s nationalcode:%d pass:%s credit:%d \n\n", (members + i)->membercode, (members + i)->firstname, (members + i)->lastname, (members + i)->idcode, (members + i)->pass, (members + i)->credit);
    }
}

int add_subscription()
{
    struct subscription a;
    FILE *fptr;

    if ((fptr = fopen("subscription.bin", "ab")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (1)
    {
        printf("enter start year: ");
        scanf("%d", &a.start_year);
        if (2020 < a.start_year <= 2030)
        {
            break;
        }
        else
        {
            printf("the year must be between 2020 and 2030, try again \n");
        }
    }

    while (1)
    {
        printf("enter start month (a number form 1 to 12): ");
        scanf("%d", &a.start_month);
        if (0 < a.start_month <= 12)
        {
            break;
        }
        else
        {
            printf("wrong number for month, try again \n");
        }
    }

    while (1)
    {
        printf("enter period: ");
        scanf("%d", &a.period);
        if (0 < a.period <= 9)
        {
            break;
        }
        else
        {
            printf("the period must be between 1 and 9, try again \n");
        }
    }

    printf("enter price: ");
    scanf("%d", &a.price);

    for (int i = 0; i < subscriptions_numbers; i++)
    {
        if ((subscriptions + i)->period == a.period && (subscriptions + i)->start_month == a.start_month && (subscriptions + i)->start_year == a.start_year && (subscriptions + i)->price == a.price)
        {
            printf("Unfortunately there is a subscription with this specification\n ");
            return -1;
        }
    }

    if (subscriptions == NULL)
    {
        a.code = 1;
    }
    else
    {
        a.code = (subscriptions + (subscriptions_numbers - 1))->code + 1;
    }

    fwrite(&a, sizeof(struct subscription), 1, fptr);
    fclose(fptr);
    subscriptions_numbers += 1;
    load_subscriptions();

    return a.code;
}

void load_subscriptions()
{
    int n = 0;
    FILE *fptr;
    struct subscription a;

    if ((fptr = fopen("subscription.bin", "rb")) == NULL)
    {
        if (subscriptions == NULL)
        {
            return;
        }
        printf("Error! opening file");
        exit(1);
    }

    if (subscriptions == NULL)
    {
        while (fread(&a, sizeof(struct subscription), 1, fptr) == 1)
        {
            n++;
        }
        subscriptions_numbers = n;
        subscriptions = (struct subscription *)malloc(subscriptions_numbers * sizeof(struct subscription));
    }
    else
    {
        subscriptions = realloc(subscriptions, subscriptions_numbers * sizeof(struct subscription));
    }

    fseek(fptr, 0, SEEK_SET);
    n = 0;
    while (fread((subscriptions + n), sizeof(struct subscription), 1, fptr) == 1)
    {
        n++;
    }

    fclose(fptr);
}

int add_subanduser(int usercode, int subcode)
{
    struct subanduser a;
    FILE *fptr;

    if ((fptr = fopen("subanduser.bin", "ab")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    a.subcode = subcode;
    a.usercode = usercode;

    fwrite(&a, sizeof(struct subanduser), 1, fptr);
    fclose(fptr);
    subandusers_numbers += 1;
    load_subanduser();

    return 0;
}

void load_subanduser()
{
    int n = 0;
    FILE *fptr;
    struct subanduser a;

    if ((fptr = fopen("subanduser.bin", "rb")) == NULL)
    {
        if (subandusers == NULL)
        {
            return;
        }
        printf("Error! opening file");
        exit(1);
    }

    if (subandusers == NULL)
    {
        while (fread(&a, sizeof(struct subanduser), 1, fptr) == 1)
        {
            n++;
        }
        subandusers_numbers = n;
        subandusers = (struct subanduser *)malloc(subandusers_numbers * sizeof(struct subanduser));
    }
    else
    {
        subandusers = realloc(subandusers, subandusers_numbers * sizeof(struct subanduser));
    }

    fseek(fptr, 0, SEEK_SET);
    n = 0;
    while (fread((subandusers + n), sizeof(struct subanduser), 1, fptr) == 1)
    {
        n++;
    }

    fclose(fptr);
}

struct user *get_user_by_code(int usercode)
{
    for (int i = 0; i < members_numbers; i++)
    {
        if ((members + i)->membercode == usercode)
        {
            return (members + i);
        }
    }
    return NULL;
}

struct subscription *get_sub_by_code(int subcode)
{
    for (int i = 0; i < subscriptions_numbers; i++)
    {
        if ((subscriptions + i)->code == subcode)
        {
            return (subscriptions + i);
        }
    }
    return NULL;
}

int is_active_subscription(int subcode)
{
    struct subscription *a;
    a = get_sub_by_code(subcode);

    if ((a->start_year == current_year) && (a->start_month + a->period > current_month))
    {
        return 0;
    }

    if ((a->start_year < current_year) && (a->start_month + a->period > current_month + 12))
    {
        return 0;
    }

    return -1;
}

void print_active_members()
{
    printf("Active Members :\n");
    for (int i = 0; i < members_numbers; i++)
    {
        for (int j = 0; j < subandusers_numbers; j++)
        {
            if (((members + i)->membercode == (subandusers + j)->usercode) && (is_active_subscription((subandusers + j)->subcode) == 0))
            {
                printf("code:%d name:%s lastname:%s\n", (members + i)->membercode, (members + i)->firstname, (members + i)->lastname);
                break;
            }
        }
    }
}

void print_inactive_members()
{
    int inactive;
    printf("Inactive Members :\n");
    for (int i = 0; i < members_numbers; i++)
    {
        inactive = 1;
        for (int j = 0; j < subandusers_numbers; j++)
        {
            if (((members + i)->membercode == (subandusers + j)->usercode) && (is_active_subscription((subandusers + j)->subcode) == 0))
            {
                inactive = 0;
                break;
            }
        }
        if (inactive == 1)
        {
            printf("code:%d name:%s lastname:%s\n", (members + i)->membercode, (members + i)->firstname, (members + i)->lastname);
        }
    }
}

void back()
{
    printf("\nType sth and press Enter to back and continue\n");
    char cc[15];
    scanf("%s", &cc);
}

void print_subscriptions_per_user(int usercode)
{
    int empty;
    struct subscription *a;
    for (int i = 0; i < members_numbers; i++)
    {
        if ((members + i)->membercode != usercode)
        {
            continue;
        }

        empty = 0;
        printf("Active subscription :\n");
        for (int j = 0; j < subandusers_numbers; j++)
        {
            if (((members + i)->membercode == (subandusers + j)->usercode) && (is_active_subscription((subandusers + j)->subcode) == 0))
            {
                a = get_sub_by_code((subandusers + j)->subcode);
                printf("code:%d start:%d/%d period:%d price:%d\n", a->code, a->start_year, a->start_month, a->period, a->price);
                empty = 1;
            }
        }
        if (empty == 0)
        {
            printf("there isn't any active subscription\n");
        }

        empty = 0;
        printf("Inactive subscription :\n");
        for (int j = 0; j < subandusers_numbers; j++)
        {
            if (((members + i)->membercode == (subandusers + j)->usercode) && (is_active_subscription((subandusers + j)->subcode) != 0))
            {
                a = get_sub_by_code((subandusers + j)->subcode);
                printf("code:%d start:%d/%d period:%d price:%d\n", a->code, a->start_year, a->start_month, a->period, a->price);
                empty = 1;
            }
        }
        if (empty == 0)
        {
            printf("there isn't any inactive subscription\n");
        }
    }
}

void print_users_per_subscription(int subcode)
{
    int empty = 0;
    struct user *a;

    printf("Members :\n");
    for (int i = 0; i < subandusers_numbers; i++)
    {
        if ((subandusers + i)->subcode == subcode)
        {
            a = get_user_by_code((subandusers + i)->usercode);
            printf("code:%d name:%s lastname:%s\n", a->membercode, a->firstname, a->lastname);
            empty = 1;
        }
    }

    if (empty == 0)
    {
        printf("there isn't any member for this subscription\n");
    }
}

int login_member()
{
    char *password;
    int usercode;
    int mistake = 0;
    struct user *a;
    password = malloc(64);

    system("cls");

    printf("Dear User please enter your membership code:\n");
    scanf("%d", &usercode);

    a = get_user_by_code(usercode);
    if (a == NULL)
    {
        printf("your membership code isn't correct\n");
        sleep(3);
        return -1;
    }

    while (mistake < 3)
    {
        printf("Dear User please enter your password:\n");
        scanf("%s", password);
        if (strcmp(password, a->pass) == 0)
        {
            current_usercode = usercode;
            return 0;
        }
        else
        {
            mistake += 1;
            printf("the password is wrong:\n");
        }
    }

    system("cls");
    printf("you have entered 3 times the wrong password\n");
    printf("so you should wait for 60 secs");
    sleep(3);
    stopwatch();
    mistake = 0;
    system("cls");
    return -1;
}

void search_member_by_family()
{
    char *lastname;
    int counter = 0;
    lastname = malloc(100);

    printf("Enter the lastname that you want to search: ");
    scanf("%s", lastname);

    for (int i = 0; i < members_numbers; i++)
    {
        if (strcmp((members + i)->lastname, lastname) == 0)
        {
            counter += 1;
            printf("\nNumber%d:\ncode:%d name:%s lastname:%s\n\n", counter, (members + i)->membercode, (members + i)->firstname, (members + i)->lastname);
            print_subscriptions_per_user((members + i)->membercode);
        }
    }

    if (counter == 0)
    {
        printf("There isn't any user with this lastname\n");
    }
}

void search_member_by_code()
{
    int usercode;
    int exist = 0;

    printf("Enter the membership code:\n");
    scanf("%d", &usercode);

    for (int i = 0; i < members_numbers; i++)
    {
        if ((members + i)->membercode == usercode)
        {
            printf("\ncode:%d name:%s lastname:%s\n\n", (members + i)->membercode, (members + i)->firstname, (members + i)->lastname);
            print_subscriptions_per_user((members + i)->membercode);
            return;
        }
    }

    if (exist == 0)
    {
        printf("There isn't any user with this membership code\n");
    }
}

void search_member_by_sub()
{
    int subcode;
    int exist = 0;

    printf("Enter the subscription code:\n");
    scanf("%d", &subcode);
    printf("\n");

    print_users_per_subscription(subcode);
}

void reset_user_pass()
{
    int usercode;
    int exist = 0;
    FILE *fptr;
    struct user a;
    char *pass1;
    char *pass2;

    pass1 = malloc(64);
    pass2 = malloc(64);

    printf("Enter the membership code:\n");
    scanf("%d", &usercode);

    for (int i = 0; i < members_numbers; i++)
    {
        if ((members + i)->membercode == usercode)
        {
            exist = 1;
            break;
        }
    }

    if (exist == 0)
    {
        printf("There isn't any user with this membership code\n");
    }

    while (1)
    {
        printf("Enter new password :\n");
        scanf("%s", pass1);
        printf("Please Enter new password again :\n");
        scanf("%s", pass2);

        if (strcmp(pass1, pass2) == 0)
        {
            break;
        }

        printf("the passwords aren't matched\n\n");
    }

    if ((fptr = fopen("users.bin", "rb+")) == NULL)
    {
        if (members == NULL)
        {
            return;
        }
        printf("Error! opening file");
        exit(1);
    }

    fseek(fptr, 0, SEEK_SET);
    for (int i = 0; i < members_numbers; i++)
    {
        fread(&a, sizeof(struct user), 1, fptr);

        if (a.membercode == usercode)
        {
            strcpy(a.pass, pass1);
            fseek(fptr, -1 * (long int)sizeof(struct user), SEEK_CUR);
            fwrite(&a, sizeof(struct user), 1, fptr);
            printf("the password is changed\n");
            break;
        }
    }

    fclose(fptr);
    load_members();
}

void change_user_info()
{
    FILE *fptr;
    struct user a;
    int idcode;
    char *firstname;
    char *lastname;

    firstname = malloc(64);
    lastname = malloc(64);

    for (int i = 0; i < members_numbers; i++)
    {
        if ((members + i)->membercode == current_usercode)
        {
            printf("\ncode:%d name:%s lastname:%s nationalcode:%d \n\n", (members + i)->membercode, (members + i)->firstname, (members + i)->lastname, (members + i)->idcode);
            break;
        }
    }

    if ((fptr = fopen("users.bin", "rb+")) == NULL)
    {
        if (members == NULL)
        {
            return;
        }
        printf("Error! opening file");
        exit(1);
    }

    fseek(fptr, 0, SEEK_SET);
    for (int i = 0; i < members_numbers; i++)
    {
        fread(&a, sizeof(struct user), 1, fptr);
        if (a.membercode == current_usercode)
        {
            break;
        }
    }

    fseek(fptr, -1 * (long int)sizeof(struct user), SEEK_CUR);

    printf("Enter new firstname OR no if you don't wanna change it :\n");
    scanf("%s", firstname);
    if (strcmp(firstname, "no") != 0)
    {
        strcpy(a.firstname, firstname);
    }

    printf("Enter new lastname OR no if you don't wanna change it :\n");
    scanf("%s", lastname);
    if (strcmp(lastname, "no") != 0)
    {
        strcpy(a.lastname, lastname);
    }

    while (1)
    {
        printf("Enter new idcode OR 0 if you don't wanna change it :\n");
        scanf("%d", &idcode);
        if (idcode == 0)
        {
            break;
        }
        else if (check_idcode(idcode) == 0)
        {
            a.idcode = idcode;
            break;
        }
        else
        {
            printf("the National Code is duplicated, try again\n");
        }
    }

    fwrite(&a, sizeof(struct user), 1, fptr);
    printf("your information is updated\n");
    fclose(fptr);
    load_members();
}

void reset_admin_pass()
{
    char *password;
    FILE *fp;

    password = malloc(64);
    printf("please choose a new password:\n");
    scanf("%s", password);

    fp = fopen("admin.txt", "w");
    if (fp == NULL)
    {
        printf("Error, the Admin File doesn't exist!");
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    fprintf(fp, password);

    printf("the password is changed\n");
    admin_password = password;
    fclose(fp);
}

int sunscriber_number(int subcode)
{
    int count = 0;
    for (int j = 0; j < subandusers_numbers; j++)
    {
        if ((subandusers + j)->subcode == subcode)
        {
            count += 1;
        }
    }
    return count;
}

void view_subscriptions(int active)
{
    int empty = 0;

    if (active == 1)
    {
        for (int i = 0; i < subscriptions_numbers; i++)
        {
            if (is_active_subscription((subscriptions + i)->code) == 0)
            {
                printf("code:%d start:%d/%d period:%d price:%d subscriber:%d\n", (subscriptions + i)->code, (subscriptions + i)->start_year, (subscriptions + i)->start_month, (subscriptions + i)->period, (subscriptions + i)->price, sunscriber_number((subscriptions + i)->code));
                empty = 1;
            }
        }
        if (empty == 0)
        {
            printf("there isn't any active subscription\n");
        }
    }
    else
    {
        for (int i = 0; i < subscriptions_numbers; i++)
        {
            if (is_active_subscription((subscriptions + i)->code) != 0)
            {
                printf("code:%d start:%d/%d period:%d price:%d subscriber:%d\n", (subscriptions + i)->code, (subscriptions + i)->start_year, (subscriptions + i)->start_month, (subscriptions + i)->period, (subscriptions + i)->price, sunscriber_number((subscriptions + i)->code));
                empty = 1;
            }
        }
        if (empty == 0)
        {
            printf("there isn't any inactive subscription\n");
        }
    }
}

void change_subscription()
{
    int subcode;
    FILE *fptr;
    struct subscription a;
    int price;
    int period;
    int start_year;
    int start_month;

    printf("Enter the subscription code:\n");
    scanf("%d", &subcode);

    if ((fptr = fopen("subscription.bin", "rb+")) == NULL)
    {
        if (subscriptions == NULL)
        {
            printf("there isn't any subscription\n");
            return;
        }
        printf("Error! opening file");
        exit(1);
    }

    fseek(fptr, 0, SEEK_SET);
    for (int i = 0; i < subscriptions_numbers; i++)
    {
        fread(&a, sizeof(struct subscription), 1, fptr);
        if (a.code == subcode)
        {
            break;
        }
    }

    fseek(fptr, -1 * (long int)sizeof(struct subscription), SEEK_CUR);

    printf("Enter new start_year OR 0 if you don't wanna change it :\n");
    scanf("%d", &start_year);
    if (start_year != 0)
    {
        a.start_year = start_year;
    }

    printf("Enter new start_month OR 0 if you don't wanna change it :\n");
    scanf("%d", &start_month);
    if (start_month != 0)
    {
        a.start_month = start_month;
    }

    printf("Enter new period OR 0 if you don't wanna change it :\n");
    scanf("%d", &period);
    if (period != 0)
    {
        a.period = period;
    }

    printf("Enter new price OR 0 if you don't wanna change it :\n");
    scanf("%d", &price);
    if (price != 0)
    {
        a.price = price;
    }

    for (int i = 0; i < subscriptions_numbers; i++)
    {
        if ((subscriptions + i)->period == a.period && (subscriptions + i)->start_month == a.start_month && (subscriptions + i)->start_year == a.start_year && (subscriptions + i)->price == a.price)
        {
            printf("Unfortunately there is a subscription with this specification\n ");
            return;
        }
    }

    fwrite(&a, sizeof(struct subscription), 1, fptr);
    printf("the subscription is updated\n");
    fclose(fptr);
    load_subscriptions();
}

void charge_account()
{
    FILE *fp;
    int price;

    fp = fopen("charge_list.txt", "a");
    if (fp == NULL)
    {
        printf("Error, the charge_list File doesn't exist!");
        exit(1);
    }

    printf("How much do you want to charge your account?\n");
    scanf("%d", &price);

    fprintf(fp, "%d %d\n", current_usercode, price);

    printf("\nwait for confirmation\n");
    fclose(fp);
}

void update_price(int usercode, int credit)
{
    FILE *fptr;
    struct user a;

    if ((fptr = fopen("users.bin", "rb+")) == NULL)
    {
        if (members == NULL)
        {
            return;
        }
        printf("Error! opening file");
        exit(1);
    }

    fseek(fptr, 0, SEEK_SET);
    for (int i = 0; i < members_numbers; i++)
    {
        fread(&a, sizeof(struct user), 1, fptr);
        if (a.membercode == usercode)
        {
            break;
        }
    }

    fseek(fptr, -1 * (long int)sizeof(struct user), SEEK_CUR);
    a.credit += credit;

    fwrite(&a, sizeof(struct user), 1, fptr);
    fclose(fptr);
    load_members();
}

void charge_confirmation()
{
    FILE *fp;
    FILE *temp_fp;
    struct user *a;
    int price;
    int usercode;
    int charging_user;

    fp = fopen("charge_list.txt", "r+");
    if (fp == NULL)
    {
        printf("Error, the charge_list File doesn't exist!");
        exit(1);
    }

    temp_fp = fopen("temp_charge_list.txt", "a");
    if (temp_fp == NULL)
    {
        printf("Error, the temp_charge_list File doesn't exist!");
        exit(1);
    }

    while (!feof(fp))
    {
        fscanf(fp, "%d %d\n", &usercode, &price);
        printf("\nthe user %d wants to charge %d \n", usercode, price);
    }

    printf("\nEnter the user code which you want to confirm\n");
    scanf("%d", &charging_user);

    fseek(fp, 0, SEEK_SET);
    while (!feof(fp))
    {
        fscanf(fp, "%d %d\n", &usercode, &price);
        if (usercode == charging_user)
        {
            update_price(usercode, price);
        }
        else
        {
            fprintf(temp_fp, "%d %d\n", usercode, price);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    remove("charge_list.txt");
    rename("temp_charge_list.txt", "charge_list.txt");

    printf("the user is charged\n");
}

void buy_subscription()
{
    view_subscriptions(1);
    struct subscription *a;
    struct user *b;
    int subcode;

    b = get_user_by_code(current_usercode);
    printf("\nyour credit : %d\n", b->credit);

    printf("which subscription do you want to buy? enter the code:\n");
    scanf("%d", &subcode);
    a = get_sub_by_code(subcode);

    if (b->credit < a->price)
    {
        printf("your credit is less than the price\n");
        return;
    }

    for (int i = 0; i < subandusers_numbers; i++)
    {
        if ((subandusers + i)->subcode == subcode && (subandusers + i)->usercode == current_usercode)
        {
            printf("you already have this subscription\n");
            return;
        }
    }

    add_subanduser(current_usercode, subcode);
    update_price(current_usercode, a->price * -1);
    printf("done!\n");
}