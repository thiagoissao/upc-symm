default: symm upc-symm

symm: 
	gcc -O3 -I utilities -I . utilities/polybench.c symm.c -DPOLYBENCH_TIME -o symm_time  

upc-symm:
	/usr/local/berkeley_upc/bin/upcc symm-par.c utilities/polybench.c -T=8 --network=udp -I utilities -I . -DPOLYBENCH_TIME -o upc_symm_time  

upc-symm-run:
	/usr/local/berkeley_upc/bin/upcrun -localhost  ./upc_symm_time 

clean:
	rm -f symm_time upc_symm_time