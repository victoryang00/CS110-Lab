## 1
Size=2^8=256


## 2
TLB Hits: 5, TLB Misses: 5, Page Hits: 0, Page Faults: 5

## 3
The simulator assumes that the number of TLB's entries is the same as number of pages in physical memory. So if TLB misses, the data is definitely not in physical memory, and therefore not in Page Table.

So it's impossible to think of a set of ten addresses that would result in Page Hit.

## 4
access 9E
	100-page#4 11110-offset
	TLB search for page#4  --  TLB miss
		look up row4 in the PT
		valid bit 0 -- page fault
			page#3 should be brought into physical memory from hard disk
			PM is empty so the first pageframe is filled
			Physical address generated, physical page frame # 0 offest 30(11110)
	now, in PT, row4 has a frame # 0, valid bit 1, in TLB, VPN 4 PPN 0

access F1
	111 10001--17 offset
	TLB miss;row7 valid bit 0 -- page fault
	page7 brought from hard disk to PM frame#1
	TLB VPN 7 PPN 1

access 4D
	010 01101--13 offset
`	TLB miss; row2 valid bit 0 -- page fault
	brought from HD to PM page frame 2
	PT row2 --frame number 2; valid bit 1
	TLB VPN 2 PPN 2

access B3
	101--page5 10011--offest 19
	TLB miss. PT row5 valid bit 0 --page fault
	PT row5, frame number 3. valid bit 1
	TLB VPN 5 PPN 3


TLB full, physical memory frame full 


access 96
	100--page4 10110--offset22
	TLB hit! VPN4 PPN0
	go for offset 22 in PM

access 52
	010 10010
	TLB hit VPN2 PPN2
	go for offset 18

access EE
	111 01110
	TLB hit VPN 7 PPN1
	offset 14

access 11
	000 10001
	TLB miss, PT row0 valid bit 0 -- page fault
	PM is full so LRU replacement plolicy, PPN3 will be replaced
	previouly, PT row5(VPN5) hold PPN3, but now, PPN3 holds not VPN5, but VPN0, so now, reset PT row5, valid bit0
	PT row0 frame#3 valid bit1
	previouly, PPN3 in TLB is correspond to VPN5 page#5, since now PPN3 hlod page#0. So now in TLB VPN0 -- PPN3

access 81
	100 00001
	TLB hit VPN4 PPN0
	offset1

access D5
	110--page6 10101
	page 6 TLB miss. row6 in PT valid bit 0 --- page fault. 
	move page 6 from HD to PM. use LRU policy, replace PPN2
	so in TLB, VPN2-PPN2 change into PVN6-PPN2
	in PT row2 reset. valid bit into0
	row6 valid, frame number 2
-------------------------------------------
end
-------------------------------------------

	
