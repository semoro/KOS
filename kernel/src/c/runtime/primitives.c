 
char Kotlin_Int_toByte(int i) {
    return (char)i;
}

char Kotlin_Char_toByte(int i) {
    return (char)i;
}

int Kotlin_Int_inc(int i) {
    return i + 1;
}

int Kotlin_Int_compareTo_Int(int a, int b) {
    if(a < b)
        return -1;
    else if(a > b)
        return 1;
    else
        return 0;
}

int Kotlin_Int_plus_Int(int a, int b) {
    return a + b;
}

int Kotlin_Int_times_Int(int a, int b) {
    return a * b;
}
