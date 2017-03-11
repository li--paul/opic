/* init_helper.c ---
 *
 * Filename: init_helper.c
 * Description:
 * Author: Felix Chern
 * Maintainer:
 * Created: Sat Mar  4 17:55:44 2017 (-0800)
 * Version:
 * Package-Requires: ()
 * Last-Updated:
 *           By:
 *     Update #: 0
 * URL:
 * Doc URL:
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/* Code: */

#include <stdbool.h>
#include <sys/mman.h>
#include <string.h>
#include "lookup_helper.h"
#include "init_helper.h"
#include "opic/common/op_log.h"

OP_LOGGER_FACTORY(logger, "opic.malloc.init_helper");

bool
OPHeapNew(OPHeap** heap_ref)
{
  void *addr, *map_addr;
  addr = NULL + OPHEAP_SIZE;
  map_addr = MAP_FAILED;
  for (int i = 0; i < (1<<15); i++)
    {
      OP_LOG_INFO(logger,
                  "Attempt to create OPHeap on %p",
                  addr);
      map_addr = mmap(addr, OPHEAP_SIZE,
                      PROT_READ | PROT_WRITE,
                      MAP_ANON | MAP_PRIVATE | MAP_FIXED,
                      -1, 0);
      if (map_addr != MAP_FAILED)
        {
          OP_LOG_INFO(logger,
                      "Successfully created OPHeap on %p",
                      map_addr);
          *heap_ref = map_addr;
          memset(*heap_ref, 0, sizeof(OPHeap));
          return true;
        }
      else
        addr += OPHEAP_SIZE;
    }
  OP_LOG_ERROR(logger, "Cannot allocate OPHeap, reached address limit");
  return false;
}

bool
OPHeapNewFromFile(OPHeap** heap_ref, FILE fd)
{
  OP_LOG_ERROR(logger, "Not implemented yet");
  return false;
}

void
OPHeapDestroy(OPHeap* heap)
{
  munmap(heap, OPHEAP_SIZE);
  OP_LOG_INFO(logger, "Successfully destroyed OPHeap on %p", heap);
}

void
HPageInit(OPHeapCtx* ctx, Magic magic)
{
  HugePage* hpage;
  hpage = ctx->hspan.hpage;
  hpage->magic = magic;
  hpage->pcard = 0;
  hpage->state = BM_NEW;  // TODO: we need to define new state
  HPageEmptiedBMaps(hpage,
                    hpage->occupy_bmap,
                    hpage->header_bmap);
}

void
USpanInit(OPHeapCtx* ctx, Magic magic, unsigned int spage_cnt)
{
  UnarySpan* uspan;
  uintptr_t uspan_base;
  unsigned int obj_size, obj_cnt, bitmap_cnt, padding, headroom;
  uint64_t* bmap;

  uspan = ctx->sspan.uspan;
  uspan_base = ObtainSSpanBase(uspan);
  obj_size = magic.typed_uspan.obj_size;
  obj_cnt = spage_cnt * SPAGE_SIZE / obj_size;
  bitmap_cnt = round_up_div(obj_cnt, 64);
  padding = bitmap_cnt * 64 - obj_cnt;
  headroom = round_up_div((uintptr_t)uspan - uspan_base +
                          bitmap_cnt * sizeof(a_uint64_t),
                          obj_size);
  uspan->magic = magic;
  uspan->bitmap_cnt = bitmap_cnt;
  uspan->bitmap_headroom = headroom;
  uspan->bitmap_padding = padding;
  uspan->bitmap_hint = 0;
  uspan->pcard = 0;
  uspan->obj_cnt = 0;
  uspan->state = BM_NEW;
  uspan->next = NULL;

  bmap = (uint64_t*)(ctx->sspan.uintptr + sizeof(UnarySpan));
  USpanEmptiedBMap(uspan, bmap);
}

void
HPageEmptiedBMaps(HugePage* hpage,
                  BmapPtr occupy_bmap,
                  BmapPtr header_bmap)
{
  OPHeap* heap;
  heap = ObtainOPHeap(hpage);

  memset(occupy_bmap.uint64, 0, 8 * sizeof(uint64_t));
  memset(header_bmap.uint64, 0, 8 * sizeof(uint64_t));

  if (hpage == &heap->hpage)
    {
      int header_size, cnt_spage, cnt_bmidx, cnt_bmbit;
      header_size = (int)(sizeof(OPHeap) + sizeof(HugePage));
      cnt_spage = round_up_div(header_size, SPAGE_SIZE);
      cnt_bmidx = cnt_spage / 64;
      cnt_bmbit = cnt_spage % 64;
      memset(occupy_bmap.uint64, 0xff, cnt_bmidx * sizeof(uint64_t));
      if (cnt_bmbit)
        occupy_bmap.uint64[cnt_bmidx] |= (1UL << cnt_bmbit) - 1;
    }
}

void
USpanEmptiedBMap(UnarySpan* uspan, BmapPtr bmap)
{
  int headroom_bmidx, headroom_bmbit;
  headroom_bmidx = uspan->bitmap_headroom / 64;
  headroom_bmbit = uspan->bitmap_headroom % 64;

  memset(bmap.uint64, 0, uspan->bitmap_cnt * sizeof(uint64_t));
  if (headroom_bmidx)
    memset(bmap.uint64, 0xff, headroom_bmidx * sizeof(uint64_t));
  if (headroom_bmbit)
    bmap.uint64[headroom_bmidx] |= (1UL << headroom_bmbit) - 1;

  if (uspan->bitmap_padding)
    bmap.uint64[uspan->bitmap_cnt - 1] |=
      ~((1UL << (64 - uspan->bitmap_padding)) - 1);
}


/* init_helper.c ends here */