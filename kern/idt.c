#include "types.h"
#include "lib.h"
#include "io.h"
#include "idt.h"

void _asm_default_int(void);
void _asm_exc_GP(void);
void _asm_irq_0(void);
void _asm_irq_1(void);

/*
 * 'init_idt_desc' initialise un descripteur de segment situe en idt.
 * 'desc' est l'adresse lineaire du descripteur a initialiser.
 * L'argument 'type' doit avoir pour valeur INTGATE, TRAPGATE
 * ou TASKGATE.
 */
void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc *desc)
{
	desc->offset0_15 = (offset & 0xffff);
	desc->select = select;
	desc->type = type;
	desc->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}

/*
 * Cette fonction initialise la IDT apres que le kernel soit charge 
 * en memoire. 
 */
void init_idt(void)
{
	int i;

	/* Initialisation des descripteurs systeme par defaut */
	for (i = 0; i < IDTSIZE; i++)
		init_idt_desc(0x08, (u32) _asm_default_int, INTGATE, &kidt[i]);

	/* Les vecteurs 0 -> 31 sont reserves pour les exceptions */
	init_idt_desc(0x08, (u32) _asm_exc_GP, INTGATE, &kidt[13]);	/* #GP */

	/* Vecteurs d'interruption */
	init_idt_desc(0x08, (u32) _asm_irq_0, INTGATE, &kidt[32]);	/* horloge */
	init_idt_desc(0x08, (u32) _asm_irq_1, INTGATE, &kidt[33]);	/* clavier */

	/* Initialisation de la structure pour IDTR */
	kidtr.limite = IDTSIZE * 8;
	kidtr.base = IDTBASE;

	/* Recopie de la IDT a son adresse */
	memcpy((char *) kidtr.base, (char *) kidt, kidtr.limite);

	/* Chargement du registre IDTR */
	asm("lidtl (kidtr)");
}
