#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define HISTORY_SIZE 5

// Function declarations
void basic_operations();
void advanced_operations();
void trigonometric_operations();
void logarithmic_operations();
void factorial_operation();
void permutation_combination();
void degree_radian_converter();
void memory_operations();
int factorial(int n);
void add_to_history(double result);
void show_history();

// Global variables
double memory = 0.0;
double history[HISTORY_SIZE] = {0};
int history_index = 0;

int main()
{
    int choice;
    char cont;

    printf("************************************\n");
    printf("*      SCIENTIFIC CALCULATOR       *\n");
    printf("************************************\n");

    do
    {
        printf("\n=== Main Menu ===\n");
        printf("1. Basic Operations (+, -, *, /, %%)\n");
        printf("2. Advanced Operations (power, sqrt, etc.)\n");
        printf("3. Trigonometric Functions\n");
        printf("4. Logarithmic & Exponential Functions\n");
        printf("5. Factorial\n");
        printf("6. Permutations & Combinations (nPr, nCr)\n");
        printf("7. Degree <-> Radian Converter\n");
        printf("8. Memory Functions (M+, M-, MC, MR)\n");
        printf("9. Show Calculation History\n");
        printf("10. Exit\n");
        printf("Enter your choice (1-10): ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            basic_operations();
            break;
        case 2:
            advanced_operations();
            break;
        case 3:
            trigonometric_operations();
            break;
        case 4:
            logarithmic_operations();
            break;
        case 5:
            factorial_operation();
            break;
        case 6:
            permutation_combination();
            break;
        case 7:
            degree_radian_converter();
            break;
        case 8:
            memory_operations();
            break;
        case 9:
            show_history();
            break;
        case 10:
            printf("Exiting calculator. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }

        printf("\nDo you want to perform another operation? (y/n): ");
        scanf(" %c", &cont);

    }
    while(cont == 'y' || cont == 'Y');

    printf("Thank you for using the calculator!\n");
    return 0;
}

// Add result to history
void add_to_history(double result)
{
    history[history_index % HISTORY_SIZE] = result;
    history_index++;
}

// Show last few results
void show_history()
{
    printf("\n--- Calculation History (last %d results) ---\n", HISTORY_SIZE);
    int start = history_index > HISTORY_SIZE ? history_index - HISTORY_SIZE : 0;
    for(int i = start; i < history_index; i++)
    {
        printf("%d) %.4lf\n", i - start + 1, history[i % HISTORY_SIZE]);
    }
}

// Memory operations
void memory_operations()
{
    int op;
    double num;

    printf("\n--- Memory Functions ---\n");
    printf("1. M+ (Add to memory)\n");
    printf("2. M- (Subtract from memory)\n");
    printf("3. MC (Clear memory)\n");
    printf("4. MR (Recall memory)\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    switch(op)
    {
    case 1:
        printf("Enter number to add: ");
        scanf("%lf", &num);
        memory += num;
        printf("Memory = %.4lf\n", memory);
        break;
    case 2:
        printf("Enter number to subtract: ");
        scanf("%lf", &num);
        memory -= num;
        printf("Memory = %.4lf\n", memory);
        break;
    case 3:
        memory = 0.0;
        printf("Memory cleared.\n");
        break;
    case 4:
        printf("Memory recall: %.4lf\n", memory);
        break;
    default:
        printf("Invalid choice!\n");
    }
}

// Permutations & combinations
void permutation_combination()
{
    int n, r;
    double result;
    int op;

    printf("\n--- Permutations & Combinations ---\n");
    printf("1. nPr (Permutation)\n");
    printf("2. nCr (Combination)\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    printf("Enter value of n: ");
    scanf("%d", &n);
    printf("Enter value of r: ");
    scanf("%d", &r);

    if(n < 0 || r < 0 || n < r)
    {
        printf("Invalid input! Ensure n >= r >= 0.\n");
        return;
    }

    if(op == 1)
    {
        result = factorial(n) / (double)factorial(n - r);
        printf("nPr = %.0lf\n", result);
        add_to_history(result);
    }
    else if(op == 2)
    {
        result = factorial(n) / (double)(factorial(r) * factorial(n - r));
        printf("nCr = %.0lf\n", result);
        add_to_history(result);
    }
    else
    {
        printf("Invalid choice!\n");
    }
}

// Degree ↔ Radian converter
void degree_radian_converter()
{
    int op;
    double angle, result;

    printf("\n--- Degree <-> Radian Converter ---\n");
    printf("1. Degrees to Radians\n");
    printf("2. Radians to Degrees\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    printf("Enter angle: ");
    scanf("%lf", &angle);

    if(op == 1)
    {
        result = angle * (M_PI / 180);
        printf("%.2lf degrees = %.4lf radians\n", angle, result);
    }
    else if(op == 2)
    {
        result = angle * (180 / M_PI);
        printf("%.4lf radians = %.2lf degrees\n", angle, result);
    }
    else
    {
        printf("Invalid choice!\n");
    }
}

// Other functions (reuse previous ones)
void basic_operations()
{
    int op;
    double num1, num2, result;

    printf("\n--- Basic Operations ---\n");
    printf("1. Addition (+)\n2. Subtraction (-)\n3. Multiplication (*)\n4. Division (/)\n5. Modulus (%%)\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    printf("Enter first number: ");
    scanf("%lf", &num1);
    printf("Enter second number: ");
    scanf("%lf", &num2);

    switch(op)
    {
    case 1:
        result = num1 + num2;
        printf("Result: %.2lf\n", result);
        break;
    case 2:
        result = num1 - num2;
        printf("Result: %.2lf\n", result);
        break;
    case 3:
        result = num1 * num2;
        printf("Result: %.2lf\n", result);
        break;
    case 4:
        if(num2 != 0) result = num1 / num2;
        else
        {
            printf("Division by zero!\n");
            return;
        }
        printf("Result: %.2lf\n", result);
        break;
    case 5:
        if((int)num2 != 0) printf("Result: %d\n", (int)num1 % (int)num2);
        else printf("Division by zero!\n");
        return;
    default:
        printf("Invalid choice!\n");
        return;
    }
    add_to_history(result);
}

void advanced_operations()
{
    int op;
    double num, num2, result;

    printf("\n--- Advanced Operations ---\n");
    printf("1. Power (x^y)\n2. Square (x^2)\n3. Cube (x^3)\n4. Square Root\n5. Cube Root\n6. Absolute Value\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    if(op == 1)
    {
        printf("Enter base: ");
        scanf("%lf", &num);
        printf("Enter exponent: ");
        scanf("%lf", &num2);
        result = pow(num, num2);
    }
    else
    {
        printf("Enter number: ");
        scanf("%lf", &num);
        switch(op)
        {
        case 2:
            result = num * num;
            break;
        case 3:
            result = num * num * num;
            break;
        case 4:
            if(num >= 0) result = sqrt(num);
            else
            {
                printf("Negative number!\n");
                return;
            }
            break;
        case 5:
            result = cbrt(num);
            break;
        case 6:
            result = fabs(num);
            break;
        default:
            printf("Invalid choice!\n");
            return;
        }
    }
    printf("Result: %.4lf\n", result);
    add_to_history(result);
}

void trigonometric_operations()
{
    int op;
    double angle, result;

    printf("\n--- Trigonometric Functions ---\n");
    printf("1. Sine\n2. Cosine\n3. Tangent\n4. Cosecant\n5. Secant\n6. Cotangent\n");
    printf("Note: Enter angle in degrees.\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    printf("Enter angle: ");
    scanf("%lf", &angle);
    double radians = angle * (M_PI / 180);

    switch(op)
    {
    case 1:
        result = sin(radians);
        break;
    case 2:
        result = cos(radians);
        break;
    case 3:
        result = tan(radians);
        break;
    case 4:
        if(sin(radians)!=0) result=1/sin(radians);
        else
        {
            printf("Division by zero!\n");
            return;
        }
        break;
    case 5:
        if(cos(radians)!=0) result=1/cos(radians);
        else
        {
            printf("Division by zero!\n");
            return;
        }
        break;
    case 6:
        if(tan(radians)!=0) result=1/tan(radians);
        else
        {
            printf("Division by zero!\n");
            return;
        }
        break;
    default:
        printf("Invalid choice!\n");
        return;
    }
    printf("Result: %.4lf\n", result);
    add_to_history(result);
}

void logarithmic_operations()
{
    int op;
    double num, result;

    printf("\n--- Logarithmic & Exponential Functions ---\n");
    printf("1. ln(x)\n2. log10(x)\n3. e^x\n");
    printf("Enter your choice: ");
    scanf("%d", &op);

    printf("Enter number: ");
    scanf("%lf", &num);

    switch(op)
    {
    case 1:
        if(num>0) result=log(num);
        else
        {
            printf("Log of non-positive!\n");
            return;
        }
        break;
    case 2:
        if(num>0) result=log10(num);
        else
        {
            printf("Log of non-positive!\n");
            return;
        }
        break;
    case 3:
        result=exp(num);
        break;
    default:
        printf("Invalid choice!\n");
        return;
    }
    printf("Result: %.4lf\n", result);
    add_to_history(result);
}

void factorial_operation()
{
    int n;
    double result;
    printf("\n--- Factorial ---\nEnter non-negative integer: ");
    scanf("%d", &n);
    if(n<0)
    {
        printf("Negative number!\n");
        return;
    }
    result = factorial(n);
    printf("%d! = %.0lf\n", n, result);
    add_to_history(result);
}

int factorial(int n)
{
    if(n==0||n==1) return 1;
    else return n*factorial(n-1);
}
