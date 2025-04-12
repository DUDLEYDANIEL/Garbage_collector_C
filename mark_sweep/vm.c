#include "vm.h"
vm_t *vm_new(){
    vm_t *vm = malloc(sizeof(vm_t));
    if (vm == NULL ){ return NULL; }
    
    vm->frames = new_stack(8);
    if(vm->frames == NULL ){
        free(vm);
        return NULL;
    }

    vm->objects = new_stack(8);
    if(vm->objects == NULL){
        free(vm);
        return NULL;
    }

    return vm;
}

void free_vm(vm_t *vm){
    if (vm->frames == NULL){ return ;}
    stack_drop(vm->frames);
    stack_drop(vm->objects);
    free(vm);
}

void vm_frame_push(vm_t *vm, frame_t *frame){
    if(frame == NULL){return ;}
    stack_push(vm->frames, (void *)frame);
}

frame_t *vm_new_frame(vm_t *vm){
    frame_t *frame = malloc(sizeof(frame_t));
    if (frame == NULL ){ return NULL; }
    frame->references = new_stack(8);
    if (frame->references == NULL ){
        free(frame);
        return NULL;
    }
    vm_frame_push(vm, frame);
    return frame;
}

void vm_frame_free(frame_t *frame){
    if (frame == NULL){return ;}
    stack_drop(frame->references);
    free(frame);
}

void vm_track_object(vm_t *vm, dan_obj_t *obj){
    if (vm == NULL ||obj == NULL ){ return ;}
    stack_push(vm->objects, (void *)obj);
}

/**
 * Adds a reference to the given object in the given frame.
 * 
 * The object is added to the frame's reference stack.
 * 
 * @param frame The frame to reference the object in.
 * @param obj The object to reference.
 */
void frame_reference_object(frame_t *frame, dan_obj_t *obj){
    stack_push(frame->references, obj);
}

void mark(vm_t *vm){
    if (vm == NULL ){ return ;}

    for(int i =0;i,vm->frames->count;i++){
        frame_t *frame = vm->frames[i];

    }
}