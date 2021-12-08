default: symm upc-symm

symm: 
	gcc -O3 -I utilities -I sequential utilities/polybench.c sequential/symm.c -DPOLYBENCH_TIME -o symm_time  

upc-symm:
	/usr/local/berkeley_upc/bin/upcc parallel/symm.c utilities/polybench.c -T=4 --network=mpi -I utilities -I parallel -DPOLYBENCH_TIME -o upc_symm_time  

upc-symm-run:
	/usr/local/berkeley_upc/bin/upcrun ./upc_symm_time 

clean:
	rm -f symm_time upc_symm_time