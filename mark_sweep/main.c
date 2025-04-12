#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include "vm.h" // Make sure this header includes the declarations you gave
#include "danobj.h"

void test_vm_initialization() {
    vm_t *vm = vm_new();
    assert(vm != NULL);
    assert(vm->frames != NULL);
    assert(vm->objects != NULL);
    printf("✅ VM initialization passed.\n");
    free_vm(vm);
}

void test_frame_push_and_free() {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    assert(frame != NULL);
    assert(frame->references != NULL);

    vm_frame_push(vm, frame); // Just push it — assume stack grows
    printf("✅ Frame push passed.\n");

    vm_frame_free(frame); // Frees only the frame
    free_vm(vm);
}

void test_object_tracking() {
    vm_t *vm = vm_new();
    dan_obj_t *obj = new_dan_integer(42); // Assuming this creates an INTEGER danObj
    vm_track_object(vm, obj);

    // Simple test: object stack size should be 1
    assert(stack_size(vm->objects) == 1);
    printf("✅ Object tracking passed.\n");

    // Clean-up
    free_vm(vm); // should handle freeing the objects as well
}

int main() {
    test_vm_initialization();
    test_frame_push_and_free();
    test_object_tracking();
    printf("✅ All VM tests passed.\n");
    return 0;
}
