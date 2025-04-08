#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "danobj.h"

int main() {
    // Test Integer Creation
    dan_obj_t *i1 = new_dan_integer(42);
    assert(i1 != NULL);
    assert(i1->kind == INTEGER);
    assert(i1->data.v_int == 42);
    printf("Integer creation test passed.\n");

    // Test Float Creation
    dan_obj_t *f1 = new_dan_float(3.14f);
    assert(f1 != NULL);
    assert(f1->kind == FLOAT);
    assert(f1->data.v_float == 3.14f);
    printf("Float creation test passed.\n");

    // Test String Creation
    dan_obj_t *s1 = new_dan_string("hello");
    assert(s1 != NULL);
    assert(s1->kind == STRING);
    assert(strcmp(s1->data.v_string, "hello") == 0);
    printf("String creation test passed.\n");

    // Test Vector Creation
    dan_obj_t *vx = new_dan_integer(1);
    dan_obj_t *vy = new_dan_integer(2);
    dan_obj_t *vz = new_dan_integer(3);
    dan_obj_t *vec = new_dan_vector(vx, vy, vz);
    assert(vec != NULL);
    assert(vec->kind == VECTOR);
    assert(vec->data.v_vector.x->data.v_int == 1);
    assert(vec->data.v_vector.y->data.v_int == 2);
    assert(vec->data.v_vector.z->data.v_int == 3);
    printf("Vector creation test passed.\n");

    // Test Array Creation
    dan_obj_t *arr = new_dan_array(3);
    assert(arr != NULL);
    assert(arr->kind == ARRAY);
    assert(dan_length(arr) == 3);
    printf("Array creation test passed.\n");

    // Test Array Set/Get
    dan_array_set(arr, 0, new_dan_integer(100));
    dan_array_set(arr, 1, new_dan_integer(200));
    dan_array_set(arr, 2, new_dan_integer(300));
    assert(dan_array_get(arr, 0)->data.v_int == 100);
    assert(dan_array_get(arr, 1)->data.v_int == 200);
    assert(dan_array_get(arr, 2)->data.v_int == 300);
    printf("Array set/get test passed.\n");

    // Test Addition
    dan_obj_t *a = new_dan_integer(5);
    dan_obj_t *b = new_dan_integer(7);
    dan_obj_t *sum = dan_add(a, b);
    assert(sum != NULL);
    assert(sum->kind == INTEGER);
    assert(sum->data.v_int == 12);
    printf("Integer addition test passed.\n");

        // Test Float Addition
    dan_obj_t *fa = new_dan_float(2.5f);
    dan_obj_t *fb = new_dan_float(4.5f);
    dan_obj_t *fsum = dan_add(fa, fb);
    assert(fsum != NULL);
    assert(fsum->kind == FLOAT);
    assert(fsum->data.v_float == 7.0f);
    printf("Float addition test passed.\n");

    // Test String Concatenation (Assuming '+' means concat)
    dan_obj_t *sa = new_dan_string("Hello, ");
    dan_obj_t *sb = new_dan_string("world!");
    dan_obj_t *s_sum = dan_add(sa, sb);
    assert(s_sum != NULL);
    assert(s_sum->kind == STRING);
    assert(strcmp(s_sum->data.v_string, "Hello, world!") == 0);
    printf("String concatenation test passed.\n");

    // Test Vector Addition (element-wise addition)
    dan_obj_t *v1 = new_dan_vector(new_dan_integer(1), new_dan_integer(2), new_dan_integer(3));
    dan_obj_t *v2 = new_dan_vector(new_dan_integer(4), new_dan_integer(5), new_dan_integer(6));
    dan_obj_t *vsum = dan_add(v1, v2);
    assert(vsum != NULL);
    assert(vsum->kind == VECTOR);
    assert(vsum->data.v_vector.x->data.v_int == 5);
    assert(vsum->data.v_vector.y->data.v_int == 7);
    assert(vsum->data.v_vector.z->data.v_int == 9);
    printf("Vector addition test passed.\n");

    // Test Array Concatenation (Addition)
    dan_obj_t *arr1 = new_dan_array(2);
    dan_obj_t *arr2 = new_dan_array(2);
    dan_array_set(arr1, 0, new_dan_integer(1));
    dan_array_set(arr1, 1, new_dan_integer(2));
    dan_array_set(arr2, 0, new_dan_integer(3));
    dan_array_set(arr2, 1, new_dan_integer(4));
    
    dan_obj_t *arrsum = dan_add(arr1, arr2);
    assert(arrsum != NULL);
    assert(arrsum->kind == ARRAY);
    assert(dan_length(arrsum) == 4);
    
    // Validate concatenated values
    assert(dan_array_get(arrsum, 0)->data.v_int == 1);
    assert(dan_array_get(arrsum, 1)->data.v_int == 2);
    assert(dan_array_get(arrsum, 2)->data.v_int == 3);
    assert(dan_array_get(arrsum, 3)->data.v_int == 4);
    
    printf("Array concatenation (addition) test passed.\n");
    


    printf("All tests passed successfully!\n");
    return 0;
}
