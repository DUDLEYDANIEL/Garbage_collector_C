#include <stdio.h>
#include <assert.h>
#include "danobj.h"
#include <string.h>

int main() {
    // Test Integer Object
    dan_obj_t *int_obj = new_dan_integer(10);
    assert(int_obj != NULL);
    assert(int_obj->kind == INTEGER);
    assert(int_obj->data.v_int == 10);
    printf("Integer test passed.\n");

    // Test Float Object
    dan_obj_t *float_obj = new_dan_float(3.14f);
    assert(float_obj != NULL);
    assert(float_obj->kind == FLOAT);
    assert(float_obj->data.v_float == 3.14f);
    printf("Float test passed.\n");

    // Test String Object
    dan_obj_t *str_obj = new_dan_string("hello");
    assert(str_obj != NULL);
    assert(str_obj->kind == STRING);
    assert(strcmp(str_obj->data.v_string, "hello") == 0);
    printf("String test passed.\n");

    // Test Vector Object
    dan_obj_t *vx = new_dan_integer(1);
    dan_obj_t *vy = new_dan_integer(2);
    dan_obj_t *vz = new_dan_integer(3);
    dan_obj_t *vector_obj = new_dan_vector(vx, vy, vz);
    assert(vector_obj != NULL);
    assert(vector_obj->kind == VECTOR);
    printf("Vector test passed.\n");

    // Test Array Object
    dan_obj_t *array_obj = new_dan_array(3);
    assert(array_obj != NULL);
    assert(array_obj->kind == ARRAY);
    assert(dan_array_set(array_obj, 0, int_obj));
    assert(dan_array_set(array_obj, 1, float_obj));
    assert(dan_array_get(array_obj, 0)->kind == INTEGER);
    printf("Array test passed.\n");

    // Test Add (Integer + Integer)
    dan_obj_t *sum_int = dan_add(int_obj, new_dan_integer(20));
    assert(sum_int->kind == INTEGER);
    assert(sum_int->data.v_int == 30);
    printf("Add Integer test passed.\n");

    // Test Add (String + String)
    dan_obj_t *hello = new_dan_string("hello ");
    dan_obj_t *world = new_dan_string("world");
    dan_obj_t *concat = dan_add(hello, world);
    assert(concat->kind == STRING);
    assert(strcmp(concat->data.v_string, "hello world") == 0);
    printf("Add String test passed.\n");

    // Clean up
    refcount_dec(int_obj);
    refcount_dec(float_obj);
    refcount_dec(str_obj);
    refcount_dec(vx);
    refcount_dec(vy);
    refcount_dec(vz);
    refcount_dec(vector_obj);
    refcount_dec(array_obj);
    refcount_dec(sum_int);
    refcount_dec(hello);
    refcount_dec(world);
    refcount_dec(concat);

    printf("All tests passed successfully!\n");
    return 0;
}
