This is a partial implementation of a QIR runtime in C. Currently I have only
implemented QIR callables, it looks like.

Here is a blurb I wrote about QIR callables in a lost document long ago:

> In simple terms, a function "value" that flows through a program will be
> lowered to a pointer to a struct. That struct holds a pointer to an array in
> static memory holding 4 function pointers, one for each of the 4
> specializations shown above. This is called the "function table." The struct
> also holds a pointer to captures for a lambda and a pointer to another static
> array containing pointers to functions that update the refcounts for the
> captures — the "memory table." To apply functors, the function "value"
> (pointer to callable struct) is copied and modified in-place.

If you want more details, see [the spec][1] and [Stefan's implementation][2]. 

[1]: https://github.com/qir-alliance/qir-spec/blob/main/specification/v0.1/2_Callables.md
[2]: https://github.com/qir-alliance/qir-runner/blob/2fac7354f4e98c3efc05f8fd4180a02d0b712907/stdlib/src/callables.rs
