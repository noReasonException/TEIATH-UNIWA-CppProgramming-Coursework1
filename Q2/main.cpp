
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#define RETURN_TOTAL_STATISTICS 1
#define RETURN_NON_PASS_FIRST_STATISTICS 2
#define RETURN_NON_PASS_SECOND_STATISTICS 3
#define RETURN_PRINT_COMB_STATISTICS 4
#define RETURN_COMB_FRECYENCY_STATISTICS 5
struct FilterParameters{
    int x1,x2,y1,y2;
};


int comb(int *arr,int *,int ,int ,int ,int ,struct FilterParameters *);
int combination_filter(int *,struct FilterParameters *,int);
int *countingSort(int *,int ,int );
void UserInterface_INPUT();
void print_combination(int *);



int comb(int *arr,int *data,int begin,int end,int index,int r,struct FilterParameters *ThisFilterParameter){
    if(index==r){
        combination_filter(data,ThisFilterParameter,0);
    }
    else{
        for (int i = begin; i <end && r-index<end-i+1;++i) {
            *(data+index)=(*(arr+i));
            //data[index]=arr[i];
            comb(arr,data,i+1,end,index+1,r,ThisFilterParameter);

        }
    }

}
int *countingSort(int *arr,int size_of_array,int max_n){//Παραλλαγή του Counting Sort Για ταξινὀμηση
    int *FrecuencyTable = (int *)malloc(sizeof(int)*max_n);///αφου γνωρίζουμε τον μέγιστο αριθμό (συμφωνα με προδιαγραφες >6 .. <49
    int *SortedArray=(int *)malloc(sizeof(int)*size_of_array);
    memset(FrecuencyTable,0,max_n*sizeof(int));
    memset(SortedArray,0,size_of_array*sizeof(int));
    int i,j;
    for(i=0;i<size_of_array;i++){
        //FrecuencyTable[arr[i]]+=1;
        *(FrecuencyTable+(*(arr+i)))+=1;
    }
    for (i=0,j=0;i<max_n;){
        if(FrecuencyTable[i]>0){
            //FrecuencyTable[i]-=1;
            *(FrecuencyTable+i)-=1;
            *(SortedArray+j)=i;
            //SortedArray[j]=i;
            j++;
        }
        else{
            i++;
        }
    }
    free(FrecuencyTable);
    return SortedArray;
}


int combination_filter(int *arr,struct FilterParameters *ThisFilterParameter,int flag=0){
    static int TotalCombinations=0,NonPassFirstFilter=0,NonPassSecondFilter=0,PrintCombinations=0,isFrecuencyTableClear=0;
    static int *FrecuencyTable = (int *)malloc(sizeof(int)*50);
    if(!isFrecuencyTableClear){
        memset(FrecuencyTable,0,sizeof(int)*50);
        isFrecuencyTableClear=1;
    }
    if(flag==RETURN_TOTAL_STATISTICS){
        return TotalCombinations;
    }
    else if(flag==RETURN_NON_PASS_FIRST_STATISTICS){
        return NonPassFirstFilter;
    }
    else if(flag==RETURN_NON_PASS_SECOND_STATISTICS){
        return NonPassSecondFilter;
    }
    else if(flag==RETURN_PRINT_COMB_STATISTICS){
        return PrintCombinations;
    }
    else if(flag==RETURN_COMB_FRECYENCY_STATISTICS){
        int i;
        for (i=0;i<50;++i) {
            if(FrecuencyTable[i]>0){
                //printf("\t\tNumber %d -> %d times\n",i,FrecuencyTable[i]);

                printf("\t\tNumber %d -> %d times\n",i,*(FrecuencyTable+i));
            }

        }
        return -1;
    }
    TotalCombinations+=1;
    int sum=0,odd=0,i;
    for (i=0;i<6;++i) {
        if(arr[i]%2==0)odd+=1;
        //if(6-i>ThisFilterParameter->x2-ThisFilterParameter->x1)return -1;//ignore by odd filter
        //sum+=arr[i];
        //FrecuencyTable[arr[i]]+=1;
        sum+=*(arr+i);
        *(FrecuencyTable+*(arr+i))+=1;

    }
    if(odd>ThisFilterParameter->x1 && odd<ThisFilterParameter->x2 ){

        if(sum>=ThisFilterParameter->y1 && sum<=ThisFilterParameter->y2){
            print_combination(arr);
            PrintCombinations+=1;
        }
        else{
            NonPassSecondFilter+=1;
        }
    }
    else{
        NonPassFirstFilter+=1;
    }
}
void print_combination(int *arr){
    int i;
    for(i=0;i<6;i++){
        //printf(" %d ",arr[i]);
        printf(" %d ",*(arr+i));
    }
    printf("\n");
}

void UserInterface_INPUT(){
    int AmountOfNumbers,temp,counter;
    int *NumbersArray;
    int x1,x2,y1,y2;
    int i;
    int ans;

    do{
        fflush(stdin);
        printf("[INPUT]\tGive me the Amount of numbers you gonna play(At least 7!!)-> ");
        scanf("%d",&AmountOfNumbers);

    }while(AmountOfNumbers<7||AmountOfNumbers>=49);
    printf("[INFO]\tCatching Memory...\n");
    NumbersArray=(int *)malloc(AmountOfNumbers*sizeof(int));
    if(NumbersArray==NULL){
        printf("[INFO_ERR]\tError in malloc() system call\n");
        return ;
    }
    else{
        printf("[INFO]\tSuccessfully Catched %d bytes of data\n",AmountOfNumbers*sizeof(int));
    }
    for (counter=0;counter<AmountOfNumbers;counter++){
        do{
            fflush(stdin);
            printf("[INPUT]\t%d)Give Number",counter);
            scanf("%d",&temp);
        }while(temp<0 || temp>49);
        //NumbersArray[counter] = temp;
        *(NumbersArray+counter)=temp;
        printf("[INFO]\tValue No %d inserted \n",counter);
    }
    do{
        fflush(stdin);
        printf("[INPUT]\tGive the number x1");
        scanf("%d",&x1);
        fflush(stdin);
        printf("[INPUT]\tGive the number x2");
        scanf("%d",&x2);
    }while(x1>x2 || x1<0 || x2>6);
    do{
        fflush(stdin);
        printf("[INPUT]\tGive the number y1");
        scanf("%d",&y1);
        fflush(stdin);
        printf("[INPUT]\tGive the number y2");
        scanf("%d",&y2);
    }while(y1>y2 || y1<21 || y2>279);
    NumbersArray = countingSort(NumbersArray,AmountOfNumbers,50);
    int *TempData=(int *)malloc(6*sizeof(int));

    printf("-----------------------Numbers .....  \n\n");
    struct FilterParameters ThisFilterParameters{x1,x2,y1,y2};
    comb(NumbersArray,TempData,0,AmountOfNumbers,0,6,&ThisFilterParameters);


    printf("-----------------------Final Results \n\n");
    printf("\t Combinations n choose 6-> %d \n",combination_filter(NULL,NULL,RETURN_TOTAL_STATISTICS));
    printf("\t Combinations with no proper odd numbers-> %d \n",combination_filter(NULL,NULL,RETURN_NON_PASS_FIRST_STATISTICS));
    printf("\t Combinations with no proper sum -> %d \n",combination_filter(NULL,NULL,RETURN_NON_PASS_SECOND_STATISTICS));
    printf("\t Total Amount of print combinations -> %d \n",combination_filter(NULL,NULL,RETURN_PRINT_COMB_STATISTICS));
    printf("\t Frecuency Table.........\n");
    combination_filter(NULL,NULL,RETURN_COMB_FRECYENCY_STATISTICS);

    /*
     * 1)Πληθος συνδιασμών n ανα 6
     * 2)Πλἠθος συνδιασμων που δεν πληρούν τον πρώτο όρο
     * 3)
     */
}

int main() {
    freopen("file.txt","r",stdin);
    UserInterface_INPUT();
}