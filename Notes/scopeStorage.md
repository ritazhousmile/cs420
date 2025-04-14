## Scope & Storage

# storage type impacts the life-span of variables
- static variable: variables exist for the life of the process
- automatic variable: variables exist for the life of a function/method
- dynamic variable : programmer controls life span of variables

# Global vs Static
- c/C+ allows global variables 


# automatic storage
- local variables and function parameters are automatically allocated in a part of memory called the stack 
- dynamic storage occurs in the heap
    - a larger area of storage ofr use with malloc() dan free 
<pre>
``` C
int *ptr //stored in stack 8 bytes local variable
ptr = malloc(5*sizeof(int)) // stored in heap  dynamic variable
```
</pre>

