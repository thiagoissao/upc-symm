default: symm

symm: 
	gcc -O3 -I utilities -I sequential utilities/polybench.c sequential/symm.c -DPOLYBENCH_TIME -o symm_time  

clean:
	rm -f symm_time