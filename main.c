#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define D 10
#define H 10
//#define PASSWORD 123
#define ASK (ORDER*)malloc(sizeof(ORDER))
#define MaxCapacity 4
//���嶩���ṹ
typedef struct Order{
    int Table_ID;//��¼������
    int Dish_ID[N];//��¼�˵ı��
    struct Order *next;
}ORDER;
//��������ṹ��
typedef struct Table{
    int Table_ID;//�������
    int Capacity;//������������ɵ�����
    int Table_State;//1�������ã�0û������
    struct Table *next;
}TABLE;
//����˵Ľṹ��
typedef struct Dish{
    int Dish_ID;//�˵ı��
    char Dish_Name[10];//����
    float Dish_Price;//�۸�
    struct Dish *next;
}DISH;
TABLE tb[H];//�����ṹ������
DISH dish[D];//�˵Ľṹ������
int PASSWORD=123;//��������
//��������
void Load_Dish(void);//���ļ��ж�ȡ����
ORDER*CreateOne(int);//����һ�������ڵ�
void Dish_Menu(void);//��ʾ����
void Table_Init(void);//������Ϣ��ʼ��
int search(void);//����ƥ��Ĳ���
ORDER* Dish_Order(ORDER*,ORDER*);//���ڵ���ӵ�����
void Display(int);//��ʾ�˵���Ϣ
void saveInList(float);//���ͻ����Ѷ�д���˵�
void Save_Inform(ORDER*,int);//���ѽ��˶�����Ϣд����ʷ��¼
ORDER *Payment(ORDER*);//����
void ModifyPW(void);//�޸�����
int Pass_Word(void);//������֤
void Observe(void);//��Ŀ��ѯ
void ListMenu(void);//�˵�����˵�
void List_Management(void);//�˵�����
void Main_Menu(void);//���˵�
void Get_Rank(void);//ͳ��
void Menu_select(void);//ѡ����
//������
main(){
    Table_Init();
    Menu_select();
}
//ϵͳ���˵�
void Main_Menu(){
    printf("             **********************\n");
    printf("                 ��������ϵͳ\n");
    printf("             **********************\n");
    printf("1.���\n");
    printf("2.�ͻ�����\n");
    printf("3.��Ŀ����\n");
    printf("4.����ͳ��\n");
    printf("5.��Աר��\n");
    printf("6.�˳�ϵͳ\n");
}
//ѡ����
void Menu_select(void){
    ORDER* head;
    int choose;
    int result;
    head=NULL;
    system("cls");
    do{
        Load_Dish();
        Main_Menu();
        printf("��ѡ��:\n");
        fflush(stdin);
        scanf("%d",&choose);
        //system("cls");
        switch(choose){
        case 1: result=search();
                if(result==1)
                    printf("�����Ե�%d�Ų����Ͳ�\n",result);
                else
                    printf("�����������ѿ��Ե�%d�Ų����Ͳ�\n",result);
                Dish_Menu();
                head=Dish_Order(head,CreateOne(result));
                //system("cls");
                break;
        case 2: head=Payment(head);
                break;
        case 3: List_Management();
                break;
        case 4: Get_Rank();
                break;
        case 5: puts("�𾴵Ļ�Ա�û�����ӭ���Ϊ�����Ա�����������ܵķ�����");
                puts("1.�����Ŷӣ������ĵȴ�ʱ�併�����");
                puts("2.�����������ˣ��ֽ���Ҳ���ԳԷ���");
                puts("����������ǵ�Ϊ��׼���Ĳ˵���");
            break;
        case 6: exit(1);
                break;
        }
    }while(1);
}
//���ļ��ж�ȡ����
void Load_Dish(void){
    FILE *fp;
    int i;
    fp=fopen("dishname.txt","r");
    for(i=0;i<D;i++)
    {
        fscanf(fp,"%d\t%s\t%f\n",&dish[i].Dish_ID,dish[i].Dish_Name,&dish[i].Dish_Price);
        printf("%d\t%s\t%f\n",dish[i].Dish_ID,dish[i].Dish_Name,dish[i].Dish_Price);
    }
}
//������ʼ��
void Table_Init(){
    tb[0].Capacity=1;tb[0].Table_ID=1;
    tb[1].Capacity=1;tb[1].Table_ID=2;
    tb[2].Capacity=2;tb[2].Table_ID=3;
    tb[3].Capacity=2;tb[3].Table_ID=4;
    tb[4].Capacity=2;tb[4].Table_ID=5;
    tb[5].Capacity=3;tb[5].Table_ID=6;
    tb[6].Capacity=4;tb[6].Table_ID=7;
    tb[7].Capacity=4;tb[7].Table_ID=8;
    tb[8].Capacity=4;tb[8].Table_ID=9;
    tb[9].Capacity=4;tb[9].Table_ID=10;
}
//��ʾ����
void Dish_Menu(void){
    int i;
    printf("*********��ӭѡ�������**********\n");
    printf("�˱��\t����\t�˵���\n");
    for(i=0;i<D;i++)
        printf("%d\t%s\t%f\n",dish[i].Dish_ID,dish[i].Dish_Name,
        dish[i].Dish_Price);
}
//������û��ƥ��Ĳ���
int search (void){
    int Cust_Num;
    int i;
    printf("��������������:\n");
    scanf("%d",&Cust_Num);
    if(MaxCapacity<Cust_Num){
        printf("��Ǹ������û������%d�Ĳ���!",Cust_Num);
        return -1;
    }
    while(Cust_Num<=MaxCapacity){
        for(i=0;i<H;i++){
            if(tb[i].Table_State==0){
                if(tb[i].Capacity==Cust_Num)
                    return (tb[i].Table_ID);
            }
        }
        printf("��Ǹ������û��%d����",Cust_Num);
               Cust_Num+=1;
    }printf("���������������Ե�һ�ᡣ");
    return -1;
}
//����һ�ݶ���
ORDER*CreateOne(int result){
    ORDER*p;
    int i;
    p=ASK;
    if(result!=-1){

        for(i=0;i<D;i++){
            printf("������˵ı�ţ���0��������:");
            scanf("%d",&p->Dish_ID[i]);
            if(p->Dish_ID[i]<0/p->Dish_ID[i]>10){
                printf("�������׷�Χ������������\n");
                i--;
            }
           else  if(p->Dish_ID[i]==0)
                break;
            else
                p->Table_ID=0;
        }
        tb[result-1].Table_State=1;
    }
    p->Table_ID=result;
    p->next=NULL;
    return p;
}
//��ӵ�����
ORDER*Dish_Order(ORDER*head,ORDER*p){
    ORDER*p1;
    p1=head;
    if(p1!=NULL){
        if(p!=NULL){
            while(p1->next!=NULL){
                p1=p1->next;
            }
            p1->next=p;
            printf("���������ɹ�\n");
        }
        else
            printf("��������ʧ��\n");
    }
    else{
        if(head==NULL&&p!=NULL)
            head=p;
    }
    return head;
}
//���ݲ˵ı�Ŵ�ӡһ���˵���Ϣ
void Display(int ID){
    int i=0;
    for(i=0;i<D;i++){
        if(dish[i].Dish_ID==ID){
            printf("%d\t%s\t%f\n",dish[i].Dish_ID,dish[i].Dish_Name,
                dish[i].Dish_Price);
            break;
        }
    }
}
//�����Ѷ�д���˵�
void saveInList(float pay){
    FILE*fp;
    time_t timer;
    timer=time(NULL);
    if((fp=fopen("�˱�.txt","a"))==NULL){
        printf("����ʧ��\n");
        exit(1);
    }
    fprintf(fp,"%f\t%s\n",pay,ctime(&timer));//ϵͳʱ��������
    printf("�˱�����ɹ�\n");
    fclose(fp);
}
//���ѽ��˿ͻ�д����ʷ��¼
void Save_Inform(ORDER *p,int m){
    FILE *fp;
    time_t timer;
    int i=0;
    timer=time(NULL);
    if((fp=fopen("��ʷ��¼.txt","a"))==NULL){
        printf("����ʧ��\n");
        exit(1);
    }
    fprintf(fp,"%d\n",m);
    while(p->Dish_ID[i]>0){
        fprintf(fp,"%d\t%s\t%f\n",dish[p->Dish_ID[i]-1].Dish_ID,
            dish[p->Dish_ID[i]-1].Dish_Name,
            dish[p->Dish_ID[i]-1].Dish_Price);
        i++;
    }fprintf(fp,"%s",ctime(&timer));
    printf("��ʷ��¼����ɹ�\n");
    fclose(fp);
}
//����
ORDER *Payment(ORDER *head){
    int i=0;
    int count=0;
    float pay=0.0;
    float Pay;
    int ID;
    ORDER *p,*p1;
    p=head;
    printf("��������Ĳ�����\n");
    fflush(stdin);
    scanf("%d",&ID);
    while(p!=NULL){
        if(p->Table_ID==ID){
            printf("���˵��������:\n");
            printf("���\t����\t�۸�\n");
            while(p->Dish_ID[i]!=0){
                Display(p->Dish_ID[i]);
                pay+=dish[p->Dish_ID[i]-1].Dish_Price;
                i++;
                count++;
            }
            printf("��һ������%d����\n",count);
            printf("�����ε����Ѷ�Ϊ%fԪ\n",pay);
            printf("��ʵ�ʵĸ���:\n");
            scanf("%f",&Pay);
            if(Pay>pay)
                printf("����%f\n",Pay-pay);
            else
                printf("���㣬���������Ļ�Ա�û����Ѿ�Ϊ���������˷���\n");
            printf("лл���Ļݹˣ���ӭ�´ι���\n");
            if(count>0){
                saveInList(pay);
                Save_Inform(p,count);
            }
            tb[p->Table_ID].Table_State=0;
            break; }
        else{
            p1=p;
            p=p->next;
        }
    }
    if(p==head)
        head=head->next;
    else
        p1->next=p->next;
    free(p);
    return head;

}
//�޸�����
void ModifyPW(){
    int password;
    printf("�������µ�����\n");
    scanf("%d",&password);
    PASSWORD=password;
    printf("�����޸ĳɹ�\n");
}
//�鿴��Ŀ
void Observe(){
    FILE *fp;
    float pay;
    char str[25];
    int i=0;
    int j=0;
    if((fp=fopen("�˱�.txt","r"))==NULL){
    printf("����ʧ��\n");
    exit(1);
    }
    printf("���ѽ��\t����ʱ��\n");
    while(!feof(fp)){
        i=0;
        j=0;
        fscanf(fp,"%f\t",&pay);
        while(i<=5&&j<25){
            fscanf(fp,"%c",&str[j]);
            j++;
            if(str[j]==' ')
                i++;
        }
        fscanf(fp,"\n\n");
        i=0;
        j=0;
        printf("%f\t",pay);
        while(i<=5&&j<25){
            printf("%c",str[j]);
            j++;
            if(str[j]==' ')
                i++;
        }
        printf("\n");
    }
    fclose(fp);
}
//�˵�����˵�
void ListMenu(){
    int choice;
    printf("1.�޸���Ŀ\n");
    printf("2.�鿴�˱�\n");
    printf("3.����\n");
    do{
        printf("��ѡ��:\n");
        scanf("%d",&choice);
        switch(choice){
        case 1:ModifyPW();
            break;
        case 2:Observe();
            break;
        case 3:Menu_select();
            break;
        default:printf("û�иù�����\n");
        }
    }while(1);
}
//�˵�����
void List_Management(){
    FILE *fp;
    if((fp=fopen("�˱�.txt","r"))==NULL){
        printf("����ʧ��\n");
        exit(1);
    }
    if(Pass_Word())
        ListMenu();
}
//��ý��ڸ��˵��ܻ�ӭ�̶�
void Get_Rank(void){
    FILE *fp;
    int n,i,m=0,j;
    int count[10]={0},t=0;
    char s[16]="",a[10];
    fp=fopen("��ʷ��¼.txt","r");
    while(!feof(fp)){
        fscanf(fp,"%d\n",&n);
        i=0;
        while(!feof(fp)){
            fscanf(fp,"%d%*s%*s",&m,s,s);
            for(j=0;j<10;j++){
                if(m==dish[j].Dish_ID){
                    count[j]++;
                    break;
                }
            }
            i++;
            if(i==n)
                fscanf(fp,"%*s%*s%*s%*s%*s\n",s,s,s,s,s);
        }
    }
    printf("�˵��ܻ�ӭ�̶�����:\n");
    for(i=0;i<10;i++){
        printf("\n%d��:",i+1);
        for(j=0;j<count[i];j++)
            printf(" * ");
    }
    for(i=0;i<9;i++){
        for(j=0;j<9-i;j++){
            if(count[j]<count[j+1]){
                t=count[j];
                strcpy(a,dish[j].Dish_Name);
                count[j]=count[j+1];
                strcpy(dish[j].Dish_Name,dish[j+1].Dish_Name);
                count[j+1]=t;
                strcpy(dish[j+1].Dish_Name,a);
            }
        }
    }
    printf("\n�Ƚ��ܹ˿ͻ�ӭ���ĸ�����:\n");
    for(i=0;i<4;i++){
        printf("%s\n",dish[i].Dish_Name);
    }
}
//������֤
int Pass_Word(){
    int password;
    do{
        printf("����������\n");
        scanf("%d",&password);
        if(PASSWORD==password){
            printf("*********************************\n");
            printf("     ��ӭ������Ŀ����ϵͳ\n");
            printf("*********************************\n");
            return 1;
        }
        else{
            printf("����������������������\n");
            printf("�Ƿ���������\n");
        }
    }while(getchar()=='y'/getchar()=='y');
    return 0;
}
