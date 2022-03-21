#include <iostream>
#include <stdio.h>
#include<ctime>
#include<fstream>
//#include <conio.h>
using namespace std;
int n;//��Ʒ����
double c;//��������
double v[100];//������Ʒ�ļ�ֵ��value��������
double w[100];//������Ʒ��������weight
double cw = 0.0;//��ǰ����������current weight
double cp = 0.0;//��ǰ��������Ʒ�ܼ�ֵ��current value
double bestp = 0.0;//��ǰ���ż�ֵbest price
double perp[100];//��λ��Ʒ��ֵ(�����) per price
int order[100];//��Ʒ���
int put[100];//�����Ƿ�װ�룬Ϊ1��ʱ���ʾѡ���������װ�룬Ϊ0�ı�ʾ��ѡ���������


//����λ��ֵ����
void knapsack()
{
    int i,j;
    int temporder = 0;
    double temp = 0.0;

    for(i=1;i<=n;i++)
        perp[i]=v[i]/w[i]; //���㵥λ��ֵ����λ��������Ʒ��ֵ��
    for(i=1;i<=n-1;i++)
    {
        for(j=i+1;j<=n;j++)
            if(perp[i]<perp[j])//ð������perp[],order[],sortv[],sortw[]
        {
            temp = perp[i];  //ð�ݶ�perp[]����
            perp[i]=perp[j];
            perp[j]=temp;

            temporder=order[i];//ð�ݶ�order[]����
            order[i]=order[j];
            order[j]=temporder;

            temp = v[i];//ð�ݶ�v[]����
            v[i]=v[j];
            v[j]=temp;

            temp=w[i];//ð�ݶ�w[]����
            w[i]=w[j];
            w[j]=temp;
        }
    }
}

//���ݺ���
void backtrack(int i)
{   //i����ָʾ����Ĳ������ڼ�������0��ʼ����ͬʱҲָʾ��ǰѡ������˼�����Ʒ
    double bound(int i);
    if(i>n) //�ݹ�������ж�����
    {
        bestp = cp;
        return;
    }
    //�������ӽڵ���У���ֱ������������;
    //�������������ȼ����Ͻ纯�������ж��Ƿ����ȥ
    if(cw+w[i]<=c)//����Ʒi���뱳��,����������
    {
        cw+=w[i];//ͬ�����µ�ǰ����������
        cp+=v[i];//ͬ�����µ�ǰ�������ܼ�ֵ
        put[i]=1;
        backtrack(i+1);//�������������һ��
        cw-=w[i];//���ݸ�ԭ
        cp-=v[i];//���ݸ�ԭ
    }
    if(bound(i+1)>bestp)//������������������������
        backtrack(i+1);
}

//�����Ͻ纯��������Ϊ��֦
double bound(int i)
{   //�жϵ�ǰ�������ܼ�ֵcp��ʣ�����������ɵ�����ֵ<=��ǰ���ż�ֵ
    double leftw= c-cw;//ʣ�౳������
    double b = cp;//��¼��ǰ�������ܼ�ֵcp,������Ͻ�
    //����Ʒ��λ������ֵ�ݼ�����װ����Ʒ
    while(i<=n && w[i]<=leftw)
    {
        leftw-=w[i];
        b+=v[i];
        i++;
    }
    //װ������
    if(i<=n)
        b+=v[i]/w[i]*leftw;
    return b;//���ؼ�������Ͻ�

}



int main()
{
	clock_t startTime = clock();
    int i;
    printf("��������Ʒ�������ͱ�����������");
    scanf("%d %lf",&n,&c);
    /*printf("��������Ʒ�������ͼ�ֵ��\n");
    for(i=1;i<=n;i++)
    {
        printf("��%d����Ʒ��������",i);
        scanf("%lf",&w[i]);
        printf("��%d����Ʒ�ļ�ֵ�ǣ�",i);
        scanf("%lf",&v[i]);
        order[i]=i;
    }*/
    printf("����������%d����Ʒ������:\n",n);
    for(i=1;i<=n;i++){
        scanf("%lf",&w[i]);
        order[i]=i;
    }

    printf("����������%d����Ʒ�ļ�ֵ:\n",n);
    for(i=1;i<=n;i++){
        scanf("%lf",&v[i]);
    }


    knapsack();
    backtrack(1);


    printf("���ż�ֵΪ��%lf\n",bestp);
    printf("��Ҫװ�����Ʒ����ǣ�");
    for(i=1;i<=n;i++)
    {
        if(put[i]==1)
            printf("%d ",order[i]);
    }
    clock_t endTime = clock();
    cout << "����������ʱ��"  << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    ofstream outfile;
    outfile.open("data.txt");
    outfile<<"���ż�ֵΪ��cp\n"<<endl;
    outfile<<"��Ҫװ�����Ʒ����ǣ�"<<endl;
    outfile<<"����������ʱ��"<<endl;
    return 0;
}
