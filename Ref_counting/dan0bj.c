#include <stdlib.h>
#include <string.h>
#include "danobj.h"


//  ref_count intializing funct
dan_obj_t *new_dan_obj(){
    dan_obj_t *obj = malloc(sizeof(dan_obj_t));
    if (obj== NULL ){return NULL; }

    obj->refcount = 1;
    return obj;
}


// ref_count increment func
void refcount_inc(dan_obj_t *obj){
    if (obj==NULL) { return ; }
    obj->refcount++;
}

//ref_count decrement func
void refcount_dec(dan_obj_t *obj){
  if(obj == NULL){ return ; }

  obj->refcount--;
  if(obj->refcount==0){
    refcount_free(obj);
  }
}

// refcount_free => release memory corresponding to the refcount_dec()
void refcount_free(dan_obj_t *obj){
    if(obj == NULL ){  return ; }


    switch(obj->kind){
        case INTEGER: break;
        case FLOAT: break;
        case STRING:{
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
            dan_array_t temp = obj->data.v_array;
            for(size_t i =0;i< temp.size;i++){
                refcount_dec(temp.elements[i]);
            }
            free(obj->data.v_array.elements);
            break;
        }
    }
    free(obj);
    return;
}

//integer object
dan_obj_t  *new_dan_integer(int value){
    dan_obj_t *obj = malloc(sizeof(dan_obj_t));
    if ( obj == NULL ){return NULL;}

    obj->kind = INTEGER;
    obj->data.v_int = value;

    return obj;
}

// float custom object
dan_obj_t *new_dan_float(float value){
    dan_obj_t *obj = malloc(sizeof(dan_obj_t));
    if(obj == NULL ){ return NULL; }

    obj->kind = FLOAT;
    obj->data.v_float = value;

    return obj;
}


//string custom object
dan_obj_t *new_dan_string(char* value){
    dan_obj_t *obj = malloc(sizeof(dan_obj_t));
    if (obj == NULL){return NULL;}

    obj->kind = STRING;
    obj->data.v_string = malloc(strlen(value)+1); 
    if(obj->data.v_string == NULL){return NULL; }
    strcpy(obj->data.v_string, value);
    return obj;
}

//vector custom object
dan_obj_t *new_dan_vector(dan_obj_t *x, dan_obj_t *y, dan_obj_t *z){
    if( x == NULL || y == NULL || z == NULL){ return NULL;}

    dan_obj_t *obj = malloc(sizeof(dan_obj_t));
    if(obj == NULL){return NULL;}

    obj->kind = VECTOR;

    refcount_inc(x);
    refcount_inc(y);
    refcount_inc(z);
    obj->data.v_vector.x = x;
    obj->data.v_vector.y = y;
    obj->data.v_vector.z = z;
    return obj;
}

//custom object to the array
dan_obj_t *new_dan_array(size_t size){
    dan_obj_t *obj = malloc(sizeof(dan_obj_t));
    if(obj == NULL) {return NULL; }
    obj->kind = ARRAY;
    dan_obj_t  **elements = calloc(size, sizeof(dan_obj_t *));
    if(elements == NULL) {return NULL;}

    dan_array_t array = {.size = size, .elements=elements};

    obj->data.v_array = array;
    return obj ;
}

//setting the value in the array
bool dan_array_set(dan_obj_t *dan_obj, size_t idx, dan_obj_t *value){
    if (dan_obj == NULL || value == NULL) {return false; }
    if (dan_obj->kind != ARRAY){return false;}
    if( dan_obj->data.v_array.size <= idx){return false;}

     refcount_inc(value);
     if(dan_obj->data.v_array.elements[idx] != NULL){
        refcount_dec(dan_obj->data.v_array.elements[idx]);
     }
     dan_obj->data.v_array.elements[idx]= value;
     return true;
}

dan_obj_t *dan_array_get(dan_obj_t *dan_obj, size_t idx){
    if(dan_obj == NULL ) return false;
    if(dan_obj->kind != ARRAY) {return false;}
    if(dan_obj->data.v_array.size<=idx) {return false;}
    return dan_obj->data.v_array.elements[idx];
}

int dan_length(dan_obj_t *obj){
    if (obj == NULL){ return -1 ;}

    switch(obj->kind){
        case INTEGER: return 1;
        case FLOAT: return 1;
        case STRING: return strlen(obj->data.v_string);
        case VECTOR: return 3;
        case ARRAY: return obj->data.v_array.size;
        default: return -1;
    }
}

//generic add function
dan_obj_t *dan_add(dan_obj_t *a, dan_obj_t *b){
    if(a == NULL || b == NULL ){return NULL; }
    switch(a->kind){
        case INTEGER:
            switch(b->kind){
                case INTEGER: return new_dan_integer(a->data.v_int + b->data.v_int);
                case FLOAT: return new_dan_float((float)a->data.v_int + b->data.v_float);
                default: return NULL;
            }
        case FLOAT:
            switch (b->kind){
                case INTEGER: return new_dan_float(a->data.v_float + (float)b->data.v_float);
                case FLOAT: return new_dan_float(a->data.v_float + b->data.v_float);
                default: return NULL;
            }
        case STRING:{
            if(b->kind != STRING){ return NULL; }
            size_t length = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
            char *new_string = calloc(sizeof(char *) , length);
            strcat(new_string, a->data.v_string);
            strcat(new_string, b->data.v_string);
            dan_obj_t *newstr = new_dan_string(new_string);
            free(new_string);
            return newstr; 
            }
        case VECTOR:{
            if(b->kind != VECTOR){ return NULL; }
            return new_dan_vector(
                dan_add(a->data.v_vector.x, b->data.v_vector.x),
                dan_add(a->data.v_vector.y, b->data.v_vector.y),
                dan_add(a->data.v_vector.z, b->data.v_vector.z)
            );
        }
        case ARRAY:{
            if(b->kind != ARRAY){ return NULL; }
            size_t length = a->data.v_array.size + b->data.v_array.size;
            dan_obj_t *obj = new_dan_array(length);

            for(size_t i =0;i< a->data.v_array.size; i++){
                dan_array_set(
                    obj,
                    i,
                    dan_array_get(a, i)
                    );
            }

            for(size_t i =0;i < b->data.v_array.size; i++){
                dan_array_set(
                    obj,
                    i + a->data.v_array.size,
                    dan_array_get(b, i)
                );
            }
            return obj;
        }
        default: return NULL;
    }
}

