

#ifndef FUNCTION_POINTER_H_INCLUDED
#define FUNCTION_POINTER_H_INCLUDED

int add(int a, int b) {
    return a + b;
}
int minus(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    return a / b;
}
void calculate(int a, int b, int opt)
{
    int (*myfunc)(int, int);

    // STUDENT ANSWER BEGIN

    switch (opt)
    {
    case 0:
        myfunc = add;
        break;
    case 1:
        myfunc = ::minus;
        break;
    case 2:
        myfunc = multiply;
        break;
    case 3:
        myfunc = divide;
        break;
    }

    // STUDENT ANSWER END

    int ans = (*myfunc)(a, b);
    printf("Output of calculation is %d.\n", ans);
}

void descendingSort(int *arr, int num )
{
    for (int i = 0; i < num - 1; i++){
        bool haveswap = 0;
        for (int j = 0; j < num - i -1; j++ ){
            if (arr[j] < arr [j+1]){
                arr[j] = arr[j]+ arr[j+1];
                arr[j+1]= arr[j]-arr[j+1];
                arr[j]= arr[j]-arr[j+1];
                haveswap = 1;
            }
        }
    }
}

void ascendingSort(int *arr, int num)
{
    for (int i = 0; i < num - 1; i++){
        bool haveswap = 0;
        for (int j = 0; j < num - i -1; j++ ){
            if (arr[j] > arr [j+1]){
                arr[j] = arr[j]+ arr[j+1];
                arr[j+1]= arr[j]-arr[j+1];
                arr[j]= arr[j]-arr[j+1];
                haveswap = 1;
            }
        }
    }
}

void mySort(int *arr, int num, void (*Sort)(int *, int) )
{
    if (Sort == ascendingSort)
        ascendingSort(arr, num);
    else if (Sort == descendingSort)
        descendingSort(arr, num);
}

#endif // FUNCTION_POINTER_H_INCLUDED
