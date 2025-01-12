/****************************************************************************
 * Driver for Solarflare network controllers and boards
 * Copyright 2019 Solarflare Communications Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#ifndef EFX_TX_COMMON_H
#define EFX_TX_COMMON_H

extern unsigned int tx_cb_order __read_mostly;

int efx_probe_tx_queue(struct efx_tx_queue *tx_queue);
int efx_init_tx_queue(struct efx_tx_queue *tx_queue);
void efx_fini_tx_queue(struct efx_tx_queue *tx_queue);
void efx_remove_tx_queue(struct efx_tx_queue *tx_queue);
void efx_destroy_tx_queue(struct efx_tx_queue *tx_queue);

void efx_purge_tx_queue(struct efx_tx_queue *tx_queue);

void efx_dequeue_buffer(struct efx_tx_queue *tx_queue,
			struct efx_tx_buffer *buffer,
			unsigned int *pkts_compl,
			unsigned int *bytes_compl,
			unsigned int *efv_pkts_compl);

static inline bool efx_tx_buffer_in_use(struct efx_tx_buffer *buffer)
{
	return buffer->len || (buffer->flags & EFX_TX_BUF_OPTION);
}

void efx_xmit_done_check_empty(struct efx_tx_queue *tx_queue);
void efx_xmit_done(struct efx_tx_queue *tx_queue, unsigned int index);

void efx_enqueue_unwind(struct efx_tx_queue *tx_queue,unsigned int insert_count);
struct efx_tx_buffer *efx_tx_map_chunk(struct efx_tx_queue *tx_queue,
				       dma_addr_t dma_addr, size_t len);
int efx_tx_map_data(struct efx_tx_queue *tx_queue, struct sk_buff *skb,
		    unsigned int segment_count);
int efx_tx_tso_header_length(struct sk_buff *skb);
int efx_tx_tso_fallback(struct efx_tx_queue *tx_queue, struct sk_buff *skb);

#endif

