#ifndef RECURSIVE_H_INCLUDED
#define RECURSIVE_H_INCLUDED


// HÀM 1

int strLen(char *str){
    if(*str == '\0') return 0;
    else{
        str++;
        return 1 + strLen(str);
    }
}

// strstr function START  HÀM 2
bool similar(char* str1, char* str2){
    if (*str2 == '\0') return 1;
    if (*str1 != *str2) return 0;
    str1++;
    str2++;
    return similar(str1, str2);
}


// HÀM 3
bool containsPattern(char* text, char* pattern){
    if (strLen(text) < strLen(pattern)) return 0;
    if (*text == *pattern && similar(text, pattern) ) return 1;
    text++;
    return containsPattern(text, pattern);
}

// strstr function END

int findGCD(int a, int b)
{
    if (!b) return a;
    else return findGCD(b,a%b);

}


int findLCM(int a, int b)
{
    if (!a || !b ) return a + b;
    else if ( b < a ){
        a += b;
        b = a - b;
        a = a - b;
    }
    static int m=b;
    if (!(b%a)) {
        return b;
    }
    return findLCM(a, b+m);
}

void printPattern(int n)
{

     if ( n > 0 ) cout << n <<" ";
     else cout << n;
     if( n > 0 ) {
        printPattern(n-5);
        cout << " "<<n;
     }

}

void printArray(int n)
{
    if (n) printArray(n-1);
    cout <<"back: "<<endl;
    if (!n) cout << n;
    else cout << ", "<<n;
}

int dectobi(int n)
{
    if(!n) return 0;
    return 10*(dectobi(n/2))+n%2;


    //if(n/2) return 10*(dectobi(n/2))+n%2;
    //else return 1;

}

int Arr_to_Int(char *str, int n)
{
    n--;
    if (!n) return (int)str[n]-48;
    return (int)str[n]-48 + 10*Arr_to_Int(str,n);
}

bool isPalindrome(string str)
{
    while (str[0] == ' ') str = str.substr(1, str.length()-1);
    while (str[str.length()-1] == ' ') str = str.substr(0, str.length()-1);

    if (str.length() == 1) return 1;

    if (str[0] != str[str.length()-1]) return 0;

    if (str.length() == 2) return 1;

    str = str.substr(1,str.length()-2);
    return isPalindrome(str);
}

int findMax(int* arr, int length)
{
    /*
     * STUDENT ANSWER
     */
     length --;
     if (!length) return *arr;

     if (arr[length] > arr[length-1])
     arr[length-1] = arr[length];
     return findMax(arr, length);
}

#endif // RECURSIVE_H_INCLUDED
