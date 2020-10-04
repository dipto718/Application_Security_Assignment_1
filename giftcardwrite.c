/*
 * Gift Card Example Writer
 * Original Author: Shoddycorp's Cut-Rate Contracting
 * Maintainer: ???
 * Comments added by Justin Cappos (JAC)
 * Modification Date: 8 July 2020
 */

#include <stdio.h>
#include "giftcard.h"

/* JAC: Why is this included? */
#include <time.h>

struct this_gift_card examplegc;
struct gift_card_data examplegcd;
struct gift_card_record_data examplegcrd;
struct gift_card_amount_change examplegcac;
//struct gift_card_program exampleprogram;


// Break it up so that we don't have long functions!  Good programming style!
//  (JAC: This is so wrong.  Global variable use / initialization is a 
//  terrible thing to do.)
void setupgc() {
	examplegc.num_bytes = 368;
	examplegc.gift_card_data = (void *) &examplegcd;
	examplegcd.merchant_id = "a";
	examplegcd.customer_id = "b";
	examplegcd.number_of_gift_card_records = 1;

	/* JAC: Something seems fishy... */
	examplegcd.gift_card_record_data = malloc(examplegcd.number_of_gift_card_records);
	/* JAC: here too! */
	examplegcd.gift_card_record_data[0] = (void *) &examplegcrd;
	examplegcrd.record_size_in_bytes = 296;
	examplegcrd.type_of_record = 3; // JAC: Should be enum!  amount_change
	//examplegcrd.actual_record = (void *) &exampleprogram;
	//char message[32] = {0};
	//strcpy(message, "happy birthday");
	//exampleprogram.message = "happy birthday";
	//exampleprogram.program[256] = {
	//	0x01, 0x00, 0x00,
	//	0x84, 0x20, 0x01,
	//	0x05, 0x00, 0x01,
	//	0x02, 0x00, 0x00,
	//	0x07, 0x00, 0x00,
	//	0x03, 0x01, 0x00,
	//};
	//fwrite(&bytes, sizeof(bytes), 1, fd1);
	//fwrite(&type, sizeof(type), 1, fd1);
	//fwrite(message, 32, 1, fd1);
	//fwrite(program, 256, 1, fd1);
	//fclose(fd1);
}


// moved into separate files to avoid erroenous style checker error...
/* JAC: opening and writing a fixed filename using a global is terrible style.
 *     the style checker was right!  This code is terrible   
 */
void writegc() {
	FILE *fd1;
	// JAC: Why don't any of these check for error return codes?!?
	fd1 = fopen("hang.gft","w");
	char message[32] = {0};
	strcpy(message, "hello world");
	unsigned char program[256] = {
		0x09, -0x03, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
	};
	fwrite(&examplegc.num_bytes,4,1,fd1);
	fwrite(examplegcd.merchant_id,32,1,fd1);
	fwrite(examplegcd.customer_id,32,1,fd1);
	fwrite(&examplegcd.number_of_gift_card_records,4,1,fd1);
	fwrite(&examplegcrd.record_size_in_bytes,4,1,fd1);
	fwrite(&examplegcrd.type_of_record,4,1,fd1);
	fwrite(message,32,1,fd1);
	fwrite(program,256,1,fd1);
	fclose(fd1);
}

/* JAC: No args and return -1 for no reason!?! */
int main(void) {

	setupgc();
	writegc();
	return -1;
}

