Extended Euclidean Algorithm
void Ex_gcd(int a, int b, int &x, int &y){
    if(!b){
        x = 1, y = 0;
        return;
    }
    int x1, y1;
    Ex_gcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
}
