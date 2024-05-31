//******************************************************************************
// Archivo: idtLoader.h
//******************************************************************************

#ifndef _IDTLOADER_H_
#define _IDTLOADER_H_

#define DEFAULT_MASTER_MASK 0xFC
#define DEFAULT_SLAVE_MASK 0xFF

//******************************************************************************
// DECLARACIÓN DE PROTOTIPOS
//******************************************************************************

// static void setup_IDT_entry(int index, uint64_t offset); // @todo
void load_idt();


#endif // _IDTLOADER_H_
