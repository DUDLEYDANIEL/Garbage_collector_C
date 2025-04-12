#pragma once

#include "stack.h"
#include <stdlib.h>
#include "danobj.h"

typedef struct VirtualMachine{
    stack_t *frames;
    stack_t *objects;
} vm_t;

typedef struct StackFrame{
    stack_t *references;
} frame_t;


vm_t *vm_new();
void free_vm(vm_t *vm);

// frames
void vm_frame_push(vm_t *vm, frame_t *frame);
frame_t *vm_new_frame(vm_t *vm);
void vm_frame_free(frame_t *frame);
void frame_reference_object(frame_t *frame, dan_obj_t *obj);
//objects
void vm_track_object(vm_t *vm, dan_obj_t *obj);

void mark(vm_t *vm);