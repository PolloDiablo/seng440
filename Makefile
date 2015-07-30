all: compile

compile:
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -o optimized.out optimized.c
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -o main.out main.c

test:
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -pg -o main.out main.c
	qemu-arm main.out
	gprof main.out | head -n20
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -pg -o optimized.out optimized.c
	qemu-arm optimized.out
	gprof optimized.out | head -n20

assembly:
	arm-none-linux-gnueabi-gcc-4.3.2 -static -S -O -Wall -Wextra -pg -o optimized.s optimized.c
	arm-none-linux-gnueabi-gcc-4.3.2 -static -S -O -Wall -Wextra -pg -o main.s main.c

test_assembly:
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -pg -o main.out main.s
	qemu-arm main.out
	gprof main.out | head -n20
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -pg -o optimized.out optimized.s
	qemu-arm optimized.out
	gprof optimized.out | head -n20

main_compile:
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -o main.out main.c

main_test:
	arm-none-linux-gnueabi-gcc-4.3.2 -static -O -Wall -Wextra -pg -o main.out main.c
	qemu-arm main.out
	gprof main.out | head -n20

main_assembly:
	arm-none-linux-gnueabi-gcc-4.3.2 -static -S -O -Wall -Wextra -pg -o main.s main.c
