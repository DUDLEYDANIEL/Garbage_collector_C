#include <stdbool.h>
#include <stddef.h>

typedef struct DanObj dan_obj_t;

typedef enum DanObjKind {
    INTEGER,
    FLOAT,
    STRING,
    VECTOR,
    ARRAY
} dan_obj_kind_t;

typedef struct  dan_vector{
  dan_obj_t *x;
  dan_obj_t *y;
  dan_obj_t *z;
} dan_vector_t;

typedef struct {
  size_t size;
  dan_obj_t **elements;
} dan_array_t;

typedef union DanObjData{
    int v_int;
    float v_float;
    char *v_string;
    dan_vector_t v_vector;
    dan_array_t v_array;
} dan_obj_data_t;


typedef struct DanObj{
  dan_obj_kind_t kind;
  dan_obj_data_t data;  
  int refcount;
} dan_obj_t;

dan_obj_t *new_dan_integer(int value);
dan_obj_t *new_dan_float(float value);
dan_obj_t *new_dan_string(char* value);
dan_obj_t *new_dan_vector(
  dan_obj_t *x,
  dan_obj_t *y,
  dan_obj_t *z
);
dan_obj_t *new_dan_array(size_t size);
bool dan_array_set(dan_obj_t *array, size_t idx,dan_obj_t *value);
dan_obj_t *dan_array_get(dan_obj_t *array, size_t idx);
int dan_length(dan_obj_t *obj);
dan_obj_t *dan_add(dan_obj_t *a, dan_obj_t *b);
dan_obj_t *new_dan_obj();
void refcount_inc(dan_obj_t *obj);
void refcount_dec(dan_obj_t *obj);
void refcount_free(dan_obj_t *obj);