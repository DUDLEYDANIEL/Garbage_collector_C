#include "custobj.h"
#include <stdlib.h>
#include <string.h>


cust_obj_t *new_cust_obj(){
    cust_obj_t  *c = malloc(sizeof(cust_obj_t));
    if(c == NULL){return NULL;}
    c->refcount = 1;
    return c;
}


void refcount_inc(cust_obj_t *obj){
    if (obj == NULL ){ return ;}
    obj->refcount++;
}

void refcount_dec(cust_obj_t *obj){
    if(obj == NULL ){ return ;}
    obj->refcount--;
    if(obj->refcount == 0){
        refcount_free(obj);
    }
}

void refcount_free(cust_obj_t *obj){
    if (obj == NULL ){ return ; }
    switch(obj->kind){
        case INTEGER: break;
        case FLOAT: break;
        case STRING: {
            free(obj->data.v_string);
            break;
        }
        case VECTOR: {
            refcount_dec(obj->data.v_vector.x);
            refcount_dec(obj->data.v_vector.y);
            refcount_dec(obj->data.v_vector.z);
            break;
        }
        case ARRAY:{
            cust_array_t temp = obj->data.v_array;
            for(size_t i =0;i< temp.size;i++){
                refcount_dec(temp.elements[i]);
            }
            free(obj->data.v_array.elements);
            break;
        }

    }
    free(obj);  
}

cust_obj_t *new_cust_int(int value){
    cust_obj_t *obj = malloc(sizeof(cust_obj_t));
    if (obj == NULL){ return NULL; }

    obj->kind = INTEGER;
    obj->data.v_int = value;
    return obj;
}

cust_obj_t *new_cust_float(float value){
    cust_obj_t *obj = malloc(sizeof(cust_obj_t));
    if( obj == NULL ){ return NULL;}
    obj->kind = FLOAT;
    obj->data.v_float = value;
    return obj;
}

cust_obj_t *new_cust_string(char *value){
    cust_obj_t *obj = malloc(sizeof(cust_obj_t));
    if (obj == NULL ){ return NULL ;}
    obj->kind = STRING;

    obj->data.v_string = malloc(strlen(value)+1);
    if (obj->data.v_string == NULL ){ return NULL; }
    strcpy(obj->data.v_string, value);
    return obj;
}

cust_obj_t *new_cust_vector(cust_obj_t *x, cust_obj_t *y, cust_obj_t *z){
    if (x == NULL || y == NULL || z == NULL) { return NULL ;}
    cust_obj_t *obj = malloc(sizeof(cust_obj_t));
    if (obj == NULL ){ return NULL; }

    obj->kind = VECTOR;
    refcount_inc(x);
    refcount_inc(y);
    refcount_inc(z);
    obj->data.v_vector = (cust_vector_t){ .x = x, .y = y, .z = z};
    return obj;
}

cust_obj_t *new_cust_array(size_t length){
    cust_obj_t *obj = malloc(sizeof(cust_obj_t));
    if (obj == NULL){ return NULL;}
    obj->kind = ARRAY;
    cust_obj_t **elements = calloc(length, sizeof(cust_obj_t *));
    if (elements == NULL ){ return NULL; }
    cust_array_t array = (cust_array_t){ .size=length, .elements=elements};
    obj->data.v_array = array;
    return obj;
}

bool cust_array_set(cust_obj_t *obj, size_t idx, cust_obj_t *value){
    if (value == NULL || obj == NULL){return false;}
    if (obj->kind != ARRAY){ return false; }
    if (obj->data.v_array.size <= idx ){ return false; }
    refcount_inc(value);
    if (obj->data.v_array.elements[idx] != NULL){ refcount_dec(obj->data.v_array.elements[idx]);}
    obj->data.v_array.elements[idx] = value;
    return true;
}

cust_obj_t *cust_array_get(cust_obj_t *obj, size_t idx){
    if ( obj == NULL ){ return NULL; }
    if (obj->kind != ARRAY){ return NULL; }
    if (obj->data.v_array.size <= idx){ return NULL; }
    return obj->data.v_array.elements[idx];
}