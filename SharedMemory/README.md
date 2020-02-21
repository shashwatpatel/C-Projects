# Producer
The producer creates a shared-memory object named
OS and writes the infamous string "Hello World!" to shared memory. The
program memory-maps a shared-memory object of the specified size and
allows writing to the object. The flag MAP SHARED specifies that changes to the
shared-memory object will be visible to all processes sharing the object. Notice
that we write to the shared-memory object by calling the sprintf() function
and writing the formatted string to the pointer ptr . After each write, we must
increment the pointer by the number of bytes written.

# Consumer
The consumer reads and outputs the con-
tents of the shared memory. The consumer also invokes the shm unlink()
function, which removes the shared-memory segment after the consumer has
accessed it.
