# seng440
SENG 440 - Cryptography Project
Authors: Jeremy Kroeker and Daniel Faulkner

There are a number of files in this project, showing the iterative and incremental improvements made. In order created, they are

 - __main.c__ The original project file. Features few optimizations beyond basic best practices and general concerns
 - __int_ops.c__ A remake of the original project file using integer arrays instead of character arrays
 - __inline_rs.c__ The rightshift_wc function (for character arrays) is updated to be inlined
 - __inl_unr_rs.c__ The rightshift_wc function (for character arrays) is unrolled into a series of individual steps
 - __inline_add.c__ The add_wc function (for character arrays) is update to be inlined
 - __inline_pipe_add.c__ Software pipelining is implemented for the add_wc function
 - __inline_pipe_add.s__ The assembly code is generated for reference and fine tuned 
 - __carry_add.s__ The assembly is fine tuned in the add_wc method (for character arrays) to eliminate a large number of unnecessary operations for determining addition carrying
 - __int_inl_pipe_add.c__ The integer functions are added back in to current code
 - __int_inl_pipe_add.s__ Assembly code is generated (for integer arrays)
 - __int_carry_flags.s__ Assembly code optimized to use carry bits in both add and right shift functions
