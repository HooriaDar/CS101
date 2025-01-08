#include <iostream>
using namespace std;

int main() {
    int num;
    cout<<"Enter a number : ";
    cin>>num;
    // Step 1: Convert to binary
    int binary[16] = {0};
    int temp = num;

    for (int i = 0; i < 16; i++) {
        binary[i] = temp % 2; // Store binary digits in reverse order
        temp /= 2;
    }

    // Step 2: Convert binary to Gray code
    int gray[16] = {0};
    gray[15] = binary[15]; // The MSB remains the same

    for (int i = 14; i >= 0; i--) {
        gray[i] = binary[i] ^ binary[i + 1]; // XOR the current bit with the next bit
    }

    // Output the Gray code
    cout << "Gray code: ";
    for (int j = 15; j >= 0; j--) {
        cout << gray[j];
    }
    cout << endl;

    return 0;
}
