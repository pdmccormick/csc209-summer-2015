#include <stdio.h>

/* When defining a structure, you are creating a new data type that you can use
 * in any variable or parameter declaration.
 */
struct Course {
    /* These look like variable declarations, but they are instead defining the
     * fields that make up this structure. */
    int code;
    int num_enrolled;
    int prereq;
}; // <=== don't forget this semicolon.


/* You can define a struct and declare a variable of that type all at once;
 * such a declaration does not even necessarily require you to name the struct
 * (although if you don't, you will never be able to define another structure
 * of that type): */
struct this_name_is_optional { 
    int field;
} a_struct_of_type_other;

/* Prototypes */
void print_info(struct Course c);
void print_info_ptr(struct Course *c);

int main(int argc, char *argv[])
{
    /* Declare two variables, both of type `struct Course` */
    struct Course csc207, csc209;

    /* Use the `.` notation to access a struct's fields */
    csc207.code = 207;
    csc207.num_enrolled = 75;
    csc207.prereq = 148;

    /* Declare a struct pointer to another local variable */
    struct Course *csc209_ptr = &csc209;

    /* Use the `->` notation to dereference a pointer and access a struct's
     * fields */
    csc209_ptr->code = 209;
    csc209_ptr->num_enrolled = 100;
    csc209_ptr->prereq = 207;

    /* Passing an argument of type `struct Course` */
    print_info(csc207);
    
    /* Because `print_info_ptr` is expecting an argument of type `struct
     * Course *` (i.e. a pointer), you cannot pass in `csc209` by itself,
     * because that would be an argument of type `struct Course` (i.e. not
     * a pointer)
     *
     * Example (compiler will complain of "incompatible type for argument"):
     *
     *      print_info_ptr(csc207);
    */
    
    /* Instead, we take the address of the struct, which is a pointer to its
     * location in memory: */
    print_info_ptr(&csc207);
    print_info_ptr(&csc209);

    /* Or pass in a previous pointer we had access to: */
    print_info_ptr(csc209_ptr);

    return 0;
}

void print_info(struct Course c)
{
    /* Use the `.` notation when accessing a struct field that is _not_ through
     * a pointer to a struct. */
    printf("CSC%d has %3d students enrolled (prereq %d)\n", c.code, c.num_enrolled, c.prereq);
}

void print_info_ptr(struct Course *c_ptr)
{
    /* Use the `->` notation to dereference a pointer to a struct and access a field. */
    printf("CSC%d has %3d students enrolled (prereq %d)\n", c_ptr->code, c_ptr->num_enrolled, c_ptr->prereq);
}
