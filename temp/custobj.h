#include <stdbool.h>
#include <stddef.h>

typedef struct custObj cust_obj_t;

typedef enum custObjKind{
    INTEGER,
    FLOAT,
    STRING,
    VECTOR,
    ARRAY
} cust_obj_kind;


typedef struct {
    cust_obj_t *x;
    cust_obj_t *y;
    cust_obj_t *z;
} cust_vector_t;

typedef struct {
    size_t size;
    cust_obj_t **elements;
} cust_array_t;


typedef union custObjData{
    int v_int;
    float v_float;
    char *v_string;
    cust_vector_t v_vector;
    cust_array_t v_array;
} cust_obj_data;

typedef struct custObj{
    cust_obj_kind kind;
    cust_obj_data data;
    int refcount;
} cust_obj_t;

cust_obj_t *new_cust_obj();
cust_obj_t *new_cust_int(int value);
cust_obj_t *new_cust_float(float value);
cust_obj_t *new_cust_string(char* value);
cust_obj_t *new_cust_vector(cust_obj_t *x, cust_obj_t *y, cust_obj_t *z);
cust_obj_t *new_cust_array(size_t length);
bool  cust_array_set(cust_obj_t *obj, size_t idx, cust_obj_t *value);
cust_obj_t *cust_array_get(cust_obj_t *obj, size_t idx);
void refcount_inc(cust_obj_t *obj);
void refcount_dec(cust_obj_t *obj);
void refcount_free(cust_obj_t *obj);