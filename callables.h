#ifndef CALLABLE_H
#define CALLABLE_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*qir_spec_func)(void *captures, void *args, void *result);
typedef void (*qir_mem_func)(void *captures, int32_t delta);

typedef struct {
    // Constants
    qir_spec_func (*func_table)[4];
    qir_mem_func (*mem_table)[2];
    // Capture state
    void *captures;
    // Functor state
    bool is_adj;
    uint32_t ctrls_count;
    // Refcounting
    uint32_t refcount;
    uint32_t alias_count;
} qir_callable;

qir_callable *__quantum__rt__callable_create(
    qir_spec_func (*func_table)[4],
    qir_mem_func (*mem_table)[2],
    void *captures);

void __quantum__rt__callable_invoke(
    qir_callable *callable,
    void *args,
    void *result);

qir_callable *__quantum__rt__callable_copy(
    qir_callable *callable,
    bool force_copy);

// Apply Adjoint functor in-place
void __quantum__rt__callable_make_adjoint(
    qir_callable *callable);

// Apply Controlled functor in-place
void __quantum__rt__callable_make_controlled(
    qir_callable *callable);

void __quantum__rt__callable_update_reference_count(
    qir_callable *callable,
    int32_t delta);

void __quantum__rt__callable_update_alias_count(
    qir_callable *callable,
    int32_t delta);

void __quantum__rt__capture_update_reference_count(
    qir_callable *callable,
    int32_t delta);

void __quantum__rt__capture_update_alias_count(
    qir_callable *callable,
    int32_t delta);

#endif
