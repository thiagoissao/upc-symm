default: symm

symm: 
	gcc -O3 -I utilities -I sequential utilities/polybench.c sequential/symm.c -DPOLYBENCH_TIME -o symm_time  

upc-symm:
	/usr/local/berkeley_upc/bin/upcc parallel/symm.c utilities/polybench.c --network=smp -I utilities -I parallel -DPOLYBENCH_TIME -o upc_symm_time  

upc-symm-run:
	/usr/local/berkeley_upc/bin/upcrun -n 4 ./upc_symm_time

clean:
	rm -f symm_time