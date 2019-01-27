.name "name here"
.comment "comment here"

		ld   %0,r3
l2:		sti r1, %:live, %1
		and r1, %0, r1

label:	
	zjmp %:live
		zjmp %0	

live: live %1
      zjmp %:live
