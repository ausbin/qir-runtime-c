#include "callables.h"
#include <assert.h>
#include <stdlib.h>

qir_callable *__quantum__rt__callable_create(
        qir_spec_func (*func_table)[4],
        qir_mem_func (*mem_table)[2],
        void *captures) {
    qir_callable *c = calloc(sizeof (qir_callable), 1);
    assert(c);
    c->func_table = func_table;
    c->mem_table = mem_table;
    c->captures = captures;
    c->refcount = 1;
    return c;
}

void __quantum__rt__callable_invoke(
        qir_callable *callable,
        void *args,
        void *result) {
    if (!callable->is_adj && !callable->ctrls_count) {
        (*callable->func_table)[0](callable->captures, args, result);
    } else if (callable->is_adj && !callable->ctrls_count) {
        (*callable->func_table)[1](callable->captures, args, result);
    } else if (!callable->is_adj && callable->ctrls_count) {
        (*callable->func_table)[2](callable->captures, args, result);
    } else { // callable->is_adj && callable->ctrls_count
        (*callable->func_table)[3](callable->captures, args, result);
    }
}

qir_callable *__quantum__rt__callable_copy(
        qir_callable *callable,
        bool force_copy) {
    if (force_copy || !callable->alias_count) {
        qir_callable *c =
            __quantum__rt__callable_create(callable->func_table,
                                           callable->mem_table,
                                           callable->captures);

        c->is_adj = callable->is_adj;
        c->ctrls_count = callable->ctrls_count;
        return c;
    } else {
        // Copy elision
        __quantum__rt__callable_update_reference_count(callable, 1);
        return callable;
    }
}

// Apply Adjoint functor in-place
void __quantum__rt__callable_make_adjoint(
        qir_callable *callable) {
    callable->is_adj = !callable->is_adj;
}

// Apply Controlled functor in-place
void __quantum__rt__callable_make_controlled(
        qir_callable *callable) {
    callable->ctrls_count++;
}

void __quantum__rt__callable_update_reference_count(
        qir_callable *callable,
        int32_t delta) {
    callable->refcount += delta;
    if (!callable->refcount) {
        free(callable);
    }
}

void __quantum__rt__callable_update_alias_count(
        qir_callable *callable,
        int32_t delta) {
    callable->alias_count += delta;
}

void __quantum__rt__capture_update_reference_count(
        qir_callable *callable,
        int32_t delta) {
    (*callable->mem_table)[0](callable->captures, delta);
}

void __quantum__rt__capture_update_alias_count(
        qir_callable *callable,
        int32_t delta) {
    (*callable->mem_table)[1](callable->captures, delta);
}
