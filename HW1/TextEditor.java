import java.util.Scanner;

public class Stack {
    static final int MAX = 1000000;
    int top;
    char[] a = new char[MAX]; // Maximum size of Stack

    boolean isEmpty() {
        return (top < 0);
    }

    Stack() {
        top = -1;
    }

    boolean push(char x) {
        if (top >= (MAX - 1)) {
            System.out.println("Stack Overflow");
            return false;
        } else {
            a[++top] = x;
            return true;
        }
    }

    char pop() {
        if (top < 0) {
            System.out.println("Stack Underflow");
            return 0;
        } else {
            char x = a[top--];
            return x;
        }
    }

    char peek() {
        if (top < 0) {
            System.out.println("Stack Underflow");
            return 0;
        } else {
            char x = a[top];
            return x;
        }
    }

    public void display() {
        if (isEmpty())
            System.out.println("-1");
        else
            for (int i = top; i >= 0; i--)
                System.out.print(a[i]);

    }

    public void TextEditor(String input) {
        Stack stack1 = new Stack();
        Stack stack2 = new Stack();
        for (int i = 0; i < input.length(); i++) {

            if (input.charAt(i) != '<' && input.charAt(i) != '>' && input.charAt(i) != '-')
                stack1.push(input.charAt(i));

            else if (input.charAt(i) == '<') {
                if (!stack1.isEmpty())
                    stack2.push(stack1.pop());

            } else if (input.charAt(i)== '>') {
                if (!stack2.isEmpty())
                    stack1.push(stack2.pop());
            } else if (input.charAt(i) == '-') {
                if (!stack1.isEmpty())
                    stack1.pop();
            }
        }

        while (!stack2.isEmpty())
            stack1.push(stack2.pop());

        while (!stack1.isEmpty())
            stack2.push(stack1.pop());

        stack2.display();

    }

    public static void main(String[] args) {
        Stack s=new Stack();
        Scanner scn=new Scanner(System.in);
        String input=scn.nextLine();
        s.TextEditor(input);
    }
}