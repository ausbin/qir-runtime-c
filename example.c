#include <stdio.h>

#include "callables.h"

static void label__fwd_wrapper(void *captures, void *args, void *result) {
    puts("Forward invoked!");
    (void)captures; (void)args; (void)result;
}

static void label__adj_wrapper(void *captures, void *args, void *result) {
    puts("Adjoint invoked!");
    (void)captures; (void)args; (void)result;
}

static qir_spec_func label__func_table[4] = {
    label__fwd_wrapper,
    label__adj_wrapper,
    NULL,
    NULL,
};

int main(void) {
    qir_callable *callable = __quantum__rt__callable_create(&label__func_table, NULL, NULL);
    __quantum__rt__callable_invoke(callable, NULL, NULL);
    __quantum__rt__callable_make_adjoint(callable);
    __quantum__rt__callable_invoke(callable, NULL, NULL);
    __quantum__rt__callable_update_reference_count(callable, -1);
    return 0;
}
